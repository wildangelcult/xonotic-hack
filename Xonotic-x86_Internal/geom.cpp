#include "geom.h"

//VM_CL_project
bool world2screen(Vector3 pos, Vector2& screen) {
	float f[3] = { pos.x, pos.y, pos.z };
	float v[3];
	float m[16];
	G::Matrix4x4_Invert_Full(m, G::r_refdef->matrix);
	G::Matrix4x4_Transform(m, f, v);
	if (G::v_flipped->integer) {
		v[1] = -v[1];
	}

	screen = {
		G::r_refdef->width * (0.5f * (1.0f + v[1] / v[0] / -G::r_refdef->frustum_x)),
		G::r_refdef->height * (0.5f * (1.0f + v[2] / v[0] / -G::r_refdef->frustum_y))
	};

	if (screen.x >= 0 && screen.x <= G::r_refdef->width && screen.y >= 0 && screen.y <= G::r_refdef->height && !(v[0] < 0.1f))
		return true;
	else
		return false;
}

float calc3DDistance(Vector3 src, Vector3 dst) {
	return sqrt(pow(src.x - dst.x, 2) + pow(src.y - dst.y, 2) + pow(src.z - dst.z, 2));
}