#pragma once
#include <cmath>
#define ASSIGN_VECTOR3_TO_FARR(arr, vec) (arr)[0] = (vec).x; (arr)[1] = (vec).y; (arr)[2] = (vec).z;

struct Vector2 { float x, y; };

class Vector3
{
public:

	float x, y, z;

	Vector3() {};
	Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
	Vector3 operator + (const Vector3& rhs) const { return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
	Vector3 operator - (const Vector3& rhs) const { return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
	Vector3 operator * (const float& rhs) const { return Vector3(x * rhs, y * rhs, z * rhs); }
	Vector3 operator / (const float& rhs) const { return Vector3(x / rhs, y / rhs, z / rhs); }
	Vector3& operator += (const Vector3& rhs) { return *this = *this + rhs; }
	Vector3& operator -= (const Vector3& rhs) { return *this = *this - rhs; }
	Vector3& operator *= (const float& rhs) { return *this = *this * rhs; }
	Vector3& operator /= (const float& rhs) { return *this = *this / rhs; }
	float length() const { return sqrtf(x * x + y * y + z * z); }
	float lengthSqr() const { return x * x + y * y + z * z; }
	Vector3 normalize() const { return *this * (1 / length()); }
	float distance(const Vector3& rhs) const { return (*this - rhs).length(); }
	void correctAngles() { while (y < -180) y += 360; while (y > 180) y -= 360; if (x > 90) x = 90; if (x < -90) x = -90; }
	float dot(const Vector3& rhs) { return x * rhs.x + y * rhs.y + z * rhs.z; }
};

struct Vector4 {
	float x, y, z, w;
};