#include <math.h>




extern float g_662d40[3];

void __cdecl fcn_00455540(char* o, float* v, float* out);
void __cdecl d3_TransformPoint(char* src, char* pos, float* out);
void __cdecl d3_NormalizeVector(float* v);


/* ADDRESS: GOLD 0x00448ac0 */
float __cdecl d3_ComputeYawToTarget(char* obj, float* target)
{
	float pos[4];
	float td[4];
	float a[4];
	float y;
	float dot;
	float ang;
	float s;
	float c;
	float rotated_x;

	fcn_00455540(obj, g_662d40, a);
	d3_TransformPoint(obj, obj + 0x4c, pos);
	a[0] -= pos[0];
	a[2] -= pos[2];
	a[1] = 0.0f;
	td[0] = target[0] - pos[0];
	td[2] = target[2] - pos[2];
	td[1] = 0.0f;
	d3_NormalizeVector(td);
	d3_NormalizeVector(a);
	y = td[1] * a[1];
	dot = (td[0] * a[0] + td[2] * a[2]) + y;
	dot = (-1.0f > dot ? -1.0f : dot) < 1.0f ? (-1.0f > dot ? -1.0f : dot) : 1.0f;
	ang = (float) acos(dot);
	s = (float) sin(*(double*) 0x5eb868);
	c = (float) cos(*(double*) 0x5eb868);
	rotated_x = s * a[2] + c * a[0];
	if ((td[2] * (c * a[2] - s * a[0]) + rotated_x * td[0]) + y > 0.0f) {
		ang = -ang;
	}
	return ang;
}
