extern double g_662aa0;
extern float g_664138;
extern float g_664160;
extern float g_664188;
extern float g_6628a0;
extern unsigned char g_773d75;

int __cdecl gm_RandomMod(int a0);
int __cdecl fcn_0050d320(unsigned short* a0, int a1);
int __cdecl fcn_004a5340(unsigned short* a0, int a1, int* a2, int a3, float a4, int* a5);
int __cdecl fcn_0050dac0(int a0);
int __cdecl fcn_0064d228(void);
int __cdecl fcn_005463a0(int a0, int a1, int a2, int a3, int a4);

/* ADDRESS: GOLDTL 0x0049bfa0 */
unsigned int __cdecl fcn_0049bfa0(unsigned int a0, unsigned short* a1, int a2, char* a3, char* a4)
{
	int v7;
	int out;
	int v9;
	int v10;
	char* p;
	float f;
	int v5;
	int slot;

	v7 = 0xf00500;
	v9 = gm_RandomMod(3) & 0xffff;
	v10 = fcn_0050d320(a1, (int) g_773d75);
	if (a2 != 0) {
		return 0;
	}
	slot = gm_RandomMod(0x19) & 0xffff;
	f = (float) ((double) slot + g_662aa0);
	if (fcn_004a5340(a1, 1, &v7, 0, f, &out) == 0) {
		return 0;
	}
	p = (char*) (0x7f4ca0 + (out & 0xffff) * 0x21c);
	f = (float) fcn_0050dac0(*a1) * g_664138;
	f = (float) fcn_0050dac0(*(unsigned short*) p) * g_664138 + f;
	f = ((float) v9 * g_664188 + g_6628a0) * (float) fcn_0064d228();
	v5 = fcn_0064d228();
	if (!((float) v5 > (float) v10 * g_664160)) {
		return 0;
	}
	if (fcn_005463a0(2, 0, 0x18, 2, *a1) != 0) {
		return 0;
	}
	*a3 = 7;
	*(int*) (a3 + 4) = *(int*) (p + 4);
	*(int*) (a3 + 8) = 1;
	*(int*) (a3 + 0x10) = v5;
	*a4 = 0;
	*(int*) (a4 + 4) = 0;
	*(int*) (a4 + 8) = 0;
	*(int*) (a4 + 0x10) = 0;
	return 0x25;
}
