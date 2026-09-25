typedef struct Ent {
	unsigned short id;
	char pad2[2];
	int seed;
	char pad8[0x21c - 8];
} Ent;
// SIZE 0x21c

extern Ent g_7f4ca0[];

unsigned short __cdecl fcn_0042e410(int n);
int __cdecl fcn_004a5340(int a, int n, int* lim, int a4, float r, unsigned short* ids);

// FUNCTION: GOLDTL 0x4a8da0
// SIZE: 146
int __cdecl fcn_004a8da0(int a1, int a2, int a3, int a4, char* out)
{
	unsigned short ids[2];
	int lim[2];

	lim[0] = 0xf00500;
	lim[1] = 0xf00500;
	if (!fcn_004a5340(a2, 2, lim, 0, (float) fcn_0042e410(0x40), ids)) {
		return 0;
	}
	out[0] = 7;
	*(int*) (out + 4) = g_7f4ca0[ids[0]].seed;
	*(int*) (out + 8) = g_7f4ca0[ids[1]].seed;
	return 1;
}
