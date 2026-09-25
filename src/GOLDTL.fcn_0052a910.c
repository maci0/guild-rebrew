extern double g_6653f0;
extern double g_664e60;
extern double g_665de0;
// FUNCTION: GOLDTL 0x0052a910
// SIZE: 72

double __cdecl gm_RandomFloat01(void);

char __cdecl fcn_0052a910(char* e, int flag)
{
	float v;

	if (flag == 0) {
		v = gm_RandomFloat01() * g_6653f0 + g_664e60;
	} else {
		v = g_665de0 - gm_RandomFloat01() * g_6653f0;
	}
	if (*(int*) (e + 0x1e8) != 0) {
		*(float*) (*(int*) (e + 0x1e8) + 0x1a4) = v;
	}
	return 1;
}
