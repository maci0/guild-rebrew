typedef struct Ent {
	unsigned short id;
	char pad2[2];
	int seed;
	char pad8[0x21c - 8];
} Ent;
// SIZE 0x21c

extern char g_7f4ca0[];

unsigned short __cdecl gm_RandomMod(int n);
int __cdecl fcn_004a5340(char* e, int n, int* lim, float a4, float r, unsigned short* ids);

/* ADDRESS: GOLDTL 0x004a9780 */
int __cdecl fcn_004a9780(int a1, char* e, int a3, int a4, char* out)
{
	int lim;
	unsigned short id;

	if (*(int*) (e + 0x1cc) & 0x40000) {
		return 0;
	}
	if (*(int*) (e + 0x194) < 8) {
		return 0;
	}
	lim = 0xf00d00;
	if (!fcn_004a5340(e, 1, &lim, 0.0f, (float) gm_RandomMod(0x10) + 18.0f, &id)) {
		return 0;
	}
	out[0] = 7;
	*(int*) (out + 4) = ((Ent*)g_7f4ca0)[id].seed;
	return 1;
}
