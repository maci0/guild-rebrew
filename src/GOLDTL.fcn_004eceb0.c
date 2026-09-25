// FUNCTION: GOLD 0x4eb130
// SIZE: 80
// FUNCTION: GOLDTL 0x4eceb0
// SIZE: 77

extern float g_6628a0;

float* __cdecl fcn_004ec960(char*, int);
int __cdecl ahm_CheckFlag(void*);
float __cdecl fcn_004ec8a0(char*, int);

float __cdecl fcn_004eceb0(char* a1, int a2)
{
	float* e;

	e = fcn_004ec960(a1, a2);
	if (ahm_CheckFlag(a1) == 0) {
		return g_6628a0;
	}
	if (e == 0) {
		return g_6628a0;
	}
	return fcn_004ec8a0(a1, 1) * e[1] + g_6628a0;
}
