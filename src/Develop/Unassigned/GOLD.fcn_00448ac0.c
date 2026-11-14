#include <math.h>




extern float g_662d40[3];

void __cdecl fcn_00455540(char* o, float* v, float* out);
void __cdecl fcn_00458a10(char* src, char* pos, float* out);
void __cdecl fcn_004518a0(float* v);


/* ADDRESS: GOLD 0x00448ac0 */
float __cdecl fcn_00448ac0(char* obj, float* target)
{
	float pos[4];
	float td[4];
	float a[4];
	float y;
	float dot;
	float ang;
	double s;
	double c;
	float rotated_x;

	fcn_00455540(obj, g_662d40, a);
	fcn_00458a10(obj, obj + 0x4c, pos);
	a[0] -= pos[0];
	a[2] -= pos[2];
	a[1] = 0.0f;
	td[0] = target[0] - pos[0];
	td[2] = target[2] - pos[2];
	td[1] = 0.0f;
	fcn_004518a0(td);
	fcn_004518a0(a);
	y = td[1] * a[1];
	dot = (td[0] * a[0] + td[2] * a[2]) + y;
	dot = (-1.0f > dot ? -1.0f : dot) < 1.0f ? (-1.0f > dot ? -1.0f : dot) : 1.0f;
	ang = (float) acos(dot);
	s = sin(*(double*) 0x5eb868);
	c = cos(*(double*) 0x5eb868);
	rotated_x = (float) (c * a[0] + s * a[2]);
	if ((td[0] * rotated_x + td[2] * (c * a[2] - s * a[0])) + y > 0.0f) {
		ang = -ang;
	}
	return ang;
}
