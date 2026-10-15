


#include <stdio.h>

extern char* g_6b7e98;
#include "Develop/Units/d3/d3_camera.h"
char* __cdecl fcn_00412eb0(char* name, int kind);
void __cdecl fcn_00438b40(char* h, char* pos);
void __cdecl fcn_00438cb0(char* h, char* rot);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl fcn_0040fd20(char** name)
{
	char buf[0x80];
	char* o;

	o = fcn_00412eb0(*name, 2);
	if (o != 0) {
		fcn_00438b40(g_6b8014, o + 0x5c);
		fcn_00438cb0(g_6b8014, o + 0x90);
		return 0;
	}
	sprintf(buf, "SetCameraToDummy(): Could not find Cameradummy '%s'!", *name);
	fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), buf);
	return 0;
}
