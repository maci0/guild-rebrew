// FUNCTION: GOLDTL 0x0057dd70
// SIZE: 70
// FUNCTION: GOLD 0x00575830
// SIZE: 70

extern char g_773d75;
extern float g_6628a0;

float __cdecl fcn_0050bb50(int, unsigned char);
double __cdecl gm_RandomFloat01(void);
void __cdecl fcn_004c51a0(int, int, char, int);

void __cdecl fcn_0057dd70(char* e)
{
	float v;

	v = fcn_0050bb50(0x2b7, g_773d75);
	fcn_004c51a0(*(int*) (e + 4), -1, g_773d75, (int) ((gm_RandomFloat01() * 2.0 + g_6628a0) * v));
}
