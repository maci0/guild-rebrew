extern int g_6b8010;



void __cdecl fcn_004432d0(int, int);
#include "client_scene_transform.h"

void __cdecl fcn_005986f0(float* result, char* object)
{
	float v[4];
	int saved;

	saved = g_6b8010;
	fcn_004432d0(0, 1);
	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
	fcn_00455540(object, v, result);
	fcn_004432d0(saved, 1);
}
