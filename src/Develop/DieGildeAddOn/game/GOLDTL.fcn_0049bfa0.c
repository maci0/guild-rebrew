extern double g_662aa0;
extern float g_664138;
extern float g_664160;
extern float g_664188;
extern float g_6628a0;
extern unsigned char g_773d75;
extern char g_7f4ca0[];

int __cdecl gm_RandomMod(int a0);
int __cdecl fcn_0050d320(short* ent, unsigned char player);
int __cdecl fcn_004a5340(short* a0, int a1, int* a2, int a3, float a4, int* a5);
int __cdecl gm_WalkEntityChain(unsigned short a0);
int __cdecl fcn_005463a0(int a0, int a1, int a2, int a3, int a4);

/* ADDRESS: GOLDTL 0x0049bfa0 */
int __cdecl ai_StartSpionage(int code, short* target, int zero, char* out1, char* out2)
{
	int mask;
	int idx;
	int rnd;
	int thr;
	char* p;
	int v5;

	mask = 0xf00500;
	rnd = gm_RandomMod(3) & 0xffff;
	thr = fcn_0050d320(target, g_773d75);
	if (zero != 0) {
		return 0;
	}
	if (fcn_004a5340(target, 1, &mask, 0, (float) ((double) (gm_RandomMod(0x19) & 0xffff) + g_662aa0), &idx) == 0) {
		return 0;
	}
	p = &g_7f4ca0[(unsigned short) idx * 0x21c];
	v5 = (int) ((float) (int) ((float) gm_WalkEntityChain(*target) * g_664138 + (float) gm_WalkEntityChain(*(unsigned short*) p) * g_664138) * ((float) rnd * g_664188 + g_6628a0));
	if ((float) v5 > (float) thr * g_664160) {
		return 0;
	}
	if (fcn_005463a0(2, 0, 0x18, 2, *target) != 0) {
		return 0;
	}
	*out1 = 7;
	*(int*) (out1 + 4) = *(int*) (p + 4);
	*(int*) (out1 + 8) = 1;
	*(int*) (out1 + 0x10) = v5;
	*out2 = 0;
	*(int*) (out2 + 4) = 0;
	*(int*) (out2 + 8) = 0;
	*(int*) (out2 + 0x10) = 0;
	return 0x25;
}
