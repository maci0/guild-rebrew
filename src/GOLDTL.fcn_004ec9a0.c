// FUNCTION: GOLD 0x004eac20
// SIZE: 63
// FUNCTION: GOLDTL 0x4ec9a0
// SIZE: 63

extern float g_664164;

int __cdecl ahm_CheckFlag(void*);
int __cdecl fcn_004ec810(char*);
float __cdecl fcn_004ec8a0(char*, int);

int __cdecl fcn_004ec9a0(char* a1)
{
	int n;

	if (ahm_CheckFlag(a1) == 0) {
		return 0;
	}
	n = fcn_004ec810(a1);
	return (int) (fcn_004ec8a0(a1, 2) * g_664164) > n;
}
