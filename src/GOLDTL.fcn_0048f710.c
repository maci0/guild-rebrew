typedef struct F8 {
	int mask;
	int b;
} F8;
// SIZE 0x8

extern char* g_77261c;

int __cdecl fcn_00502cd0(int a, int b, int c, int d, int e);
int __cdecl fcn_005463a0(int a, int b, int c, int d, int e);
unsigned short __cdecl fcn_0042e410(int n);
int __cdecl fcn_004a5e60(char* p, int kind, F8 f, int c, float r, int* out);

// FUNCTION: GOLD 0x490160
// SIZE: 320
// FUNCTION: GOLDTL 0x48f710
// SIZE: 306
int __cdecl fcn_0048f710(char* a1, char* e, char* r, char* out)
{
	int w;
	int h;
	int found;
	F8 f;

	w = fcn_0042e410(3);
	h = fcn_0042e410(3);
	*(int*) (r + 0x10) = 1;
	*(int*) (r + 0xc) = *(int*) (e + 1);
	if ((unsigned int) ((h + 2) * (w + 2)) > *(unsigned int*) (a1 + 0x194)) {
		return 0;
	}
	if (!fcn_00502cd0(*(int*) (e + 0x5d), 2, 0, 0x211, 6)) {
		return 0;
	}
	if (fcn_005463a0(2, 0, 0x90, 3, *(int*) (e + 1))) {
		return 0;
	}
	found = -1;
	f.mask = 0xa07c43b4;
	f.b = 1;
	if (g_77261c == 0 || (fcn_004a5e60(g_77261c, 4, f, 0, 100.0f, &found), found == -1)) {
		if (!fcn_004a5e60(a1, 6, f, 0, (float) fcn_0042e410(0x20) + 19.0f, &found)) {
			return 0;
		}
	}
	*(int*) (out + 8) = h;
	*(int*) (out + 4) = w;
	*(int*) (out + 0xc) = found;
	return 1;
}
