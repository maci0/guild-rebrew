// FUNCTION: GOLDTL 0x4a9040
// SIZE: 260

typedef struct Ent {
	char pad0[4];
	int x4;
	char pad8[0x21c - 8];
} Ent;
// SIZE 0x21c

extern Ent g_7f4ca0[768];
extern float g_664458;
extern float g_6629e8;

unsigned short __cdecl fcn_0042e410(int n);
int __cdecl fcn_004a5340(char* e, int a, int* b, float c, float r, unsigned short* out);
float __cdecl fcn_0050f980(int a, int b, int c);

int __cdecl fcn_004a9040(char* a1, char* e, char* a3, char* a4, char* out)
{
	unsigned short idx[2];
	int mask[2];
	float d1;
	float d2;

	mask[0] = 0xf00500;
	mask[1] = 0xf00500;
	if (fcn_004a5340(e, 2, mask, 33.0f, fcn_0042e410(0x18) + g_664458, idx) == 0) {
		return 0;
	}
	d1 = fcn_0050f980(idx[0], idx[1], 1);
	d2 = fcn_0050f980(idx[1], idx[0], 1);
	if (!(d1 > g_6629e8) || !(d2 > g_6629e8)) {
		out[0] = 7;
		*(int*) (out + 4) = g_7f4ca0[idx[0]].x4;
		*(int*) (out + 8) = g_7f4ca0[idx[1]].x4;
		return 1;
	}
	return 0;
}
