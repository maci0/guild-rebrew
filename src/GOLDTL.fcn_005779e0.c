// FUNCTION: GOLDTL 0x5779e0
// SIZE: 114

float __cdecl fcn_00507f10(void*, int);
float __cdecl gm_RandomFloat01(void);
float __cdecl fcn_004ff210(unsigned short, int);

int __cdecl fcn_005779e0(char* a, unsigned short* b, int c)
{
	float fa;
	float fb;

	if (b != 0) {
		fa = fcn_00507f10(a, 2);
		fb = fcn_00507f10(b, 2);
		if (gm_RandomFloat01() + (fa - fb * 0.5f) >= 1.0f) {
			fcn_004ff210(*b, (-1 - c) * 5);
			return 1;
		}
	}
	return 0;
}
