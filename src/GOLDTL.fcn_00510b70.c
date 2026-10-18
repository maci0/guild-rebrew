extern int g_67a370;


int __cdecl sprintf(char*, const char*, ...);
#include "client_scene_loader.h"
void __cdecl fcn_00437ac0(int, int, int, void (__cdecl*)(void));
void __cdecl fcn_00510bd0(void);

char __cdecl fcn_00510b70(const char* name)
{
	char path[256];

	sprintf(path, "scenes/*stadt_%s.ed3", name);
	if (!fcn_00448360(path, 0, 0)) {
		return 0;
	}
	fcn_00437ac0(g_67a370, 0, 6, fcn_00510bd0);
	return 1;
}
