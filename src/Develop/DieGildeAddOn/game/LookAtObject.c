#include "Develop/DieGildeAddOn/game/ch_script.h"



extern char* evt_CurrentScript;
extern float g_6628dc;
void __cdecl d3_TransformPoint(char* src, char* pos, float* out);
float __cdecl d3_ComputeYawToTarget(int h, float* pos);
char* __cdecl ch_CreateAction(char* e, int kind, ...);
void __cdecl evt_LogScriptError(char* g, int h, const char* msg);

/* ADDRESS: GOLDDE 0x0040cbc0 */
int __cdecl LookAtObject(char** a, char** b)
{
	float pos[4];
	float f;

	if (*a == 0 || *b == 0) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "invalid object");
		return 1;
	}
	d3_TransformPoint(*b, *b + 0x4c, pos);
	f = d3_ComputeYawToTarget(*(int*) (*a + 0x34), pos) * g_6628dc;
	ch_CreateAction(*a, 7, (int) f, 0);
	return 0;
}
