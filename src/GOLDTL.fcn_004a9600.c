typedef struct Ent {
	unsigned short id;
	char pad2[2];
	int seed;
	char pad8[0x1c8 - 8];
	int flags;
	char pad1cc[0x21c - 0x1cc];
} Ent;
// SIZE 0x21c

extern char g_7f4ca0[];

unsigned short __cdecl gm_RandomMod(int n);
int __cdecl fcn_004a5340(char* e, int n, int* lim, float a4, float r, unsigned short* ids);
float __cdecl fcn_00507e70(char* e, Ent* t, int k);
float __cdecl gm_RandomFloat01(void);

/* ADDRESS: GOLDTL 0x004a9600 */
/* ADDRESS: GOLD 0x004a94e0 */
int __cdecl fcn_004a9600(int a1, char* e, int a3, int a4, char* out)
{
	int lim;
	unsigned short id;
	float f;

	if (*(int*) (e + 0x194) >= 3 && !(*(int*) (e + 0x1c8) & 0x400)) {
		lim = 0xf00500;
		if (fcn_004a5340(e, 1, &lim, 0.0f, (float) gm_RandomMod(0x20) + 18.0f, &id) && !(((Ent*)g_7f4ca0)[id].flags & 0x400)) {
			f = fcn_00507e70(e, &((Ent*)g_7f4ca0)[id], 3);
			if (gm_RandomFloat01() + f >= 1.0f) {
				out[0] = 7;
				*(int*) (out + 4) = ((Ent*)g_7f4ca0)[id].seed;
				return 1;
			}
		}
	}
	return 0;
}
