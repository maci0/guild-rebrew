#include "Develop/DieGildeAddOn/game/ch_script.h"



extern char* evt_CurrentScript;
extern float g_6628dc;
void __cdecl fcn_00455350(char* src, char* pos, float* out);
float __cdecl fcn_00444700(int h, float* pos);
char* __cdecl fcn_0040c120(char* e, int kind, ...);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl LookAtObject(char** a, char** b)
{
	float pos[4];
	float f;

	if (*a == 0 || *b == 0) {
		fcn_00425bf0(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "invalid object");
		return 1;
	}
	fcn_00455350(*b, *b + 0x4c, pos);
	f = fcn_00444700(*(int*) (*a + 0x34), pos) * g_6628dc;
	fcn_0040c120(*a, 7, (int) f, 0);
	return 0;
}
