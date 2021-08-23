#include "mem.h"
#include <Windows.h>

void mem::PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProc) {
	DWORD oldprotect;
	VirtualProtectEx(hProc, dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	WriteProcessMemory(hProc, dst, src, size, nullptr);
	VirtualProtectEx(hProc, dst, size, oldprotect, &oldprotect);
}

void mem::NopEx(BYTE* dst, unsigned int size, HANDLE hProc) {
	BYTE* nopArr = new BYTE[size];
	memset(nopArr, 0x90, size);
	PatchEx(dst, nopArr, size, hProc);
	delete[] nopArr;
}

uintptr_t mem::FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets) {
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offsets.size(); ++i) {
		ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
		addr += offsets[i];
	}
	return addr;
}

void mem::Patch(BYTE* dst, BYTE* src, unsigned int size) {
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

void mem::Nop(BYTE* dst, unsigned int size) {
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memset(dst, 0x90, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

uintptr_t mem::FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets) {
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offsets.size(); ++i) {
		addr = *(uintptr_t*)addr;
		addr += offsets[i];
	}
	return addr;
}

bool mem::Detour32(BYTE* src, BYTE* dst, const uintptr_t len) {
	if (len < 5) return false;

	DWORD oldprotect;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &oldprotect);

	uintptr_t jmpOffset = dst - src - 5;

	*src = 0xE9;
	*(uintptr_t*)(src + 1) = jmpOffset;

	VirtualProtect(src, len, oldprotect, &oldprotect);
	return true;
}

BYTE* mem::TrampHook32(BYTE* src, BYTE* dst, const uintptr_t len) {
	if (len < 5) return 0;

	//Create gateway
	BYTE* gateway = (BYTE*)VirtualAlloc(0, len + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);	

	//write the stolen bytes to the gateway
	memcpy_s(gateway, len, src, len);

	//get the gateway to dest addr
	uintptr_t retOffset = src - gateway - 5;

	//add jmp opcode to the end of the gateway
	*(gateway + len) = 0xE9;

	//write the jmp offset
	*(uintptr_t*)((uintptr_t)gateway + len + 1) = retOffset;

	//detour
	Detour32(src, dst, len);

	return gateway;
}

void* mem::patternScan(char* baseAddr, size_t size, const char* pattern, const char* mask) {
	size_t patternLen = strlen(mask);

	unsigned int i = 0, j = 0;
	bool found = true;
	for (i = 0; i < (size - patternLen); ++i) {
		found = true;
		for (j = 0; j < patternLen; ++j) {
			if (mask[j] != '?' && pattern[j] != *(baseAddr + i + j)) {
				found = false;
				break;
			}
		}

		if (found) {
			return (void*)(baseAddr + i);
		}
	}

	return nullptr;
}