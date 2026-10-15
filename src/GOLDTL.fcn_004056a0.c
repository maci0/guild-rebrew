#include "Develop/Units/d3/d3_camera.h"



void __cdecl fcn_004055a0(int, int, void*, void*);
void __cdecl fcn_00438cb0(char*, void*);
void __cdecl fcn_00438b40(char*, void*);

void __cdecl fcn_004056a0(int a1, int a2)
{
	char a[0xc];
	char b[0x10];

	fcn_004055a0(a1, a2, b, a);
	fcn_00438cb0(g_6b8014, a);
	fcn_00438b40(g_6b8014, b);
}
