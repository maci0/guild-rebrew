// FUNCTION: GOLDTL 0x4a8bf0
// SIZE: 285

typedef struct Ent {
	char pad0[4];
	int x4;
	char pad8[0x21c - 8];
} Ent;
// SIZE 0x21c

extern Ent g_7f4ca0[768];

unsigned short __cdecl fcn_0042e410(int n);
int __cdecl fcn_004a5340(char* e, int a, int* b, int c, float r, int* out);

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

int __cdecl fcn_004a8bf0(char* a1, char* e, char* a3, char* a4, char* out)
{
	int mask;
	int idx;

	if (*(int*) (e + 0x194) < 3) {
		return 0;
	}
	mask = e[9] ? 0xf00501 : 0xf00502;
	if (fcn_004a5340(e, 1, &mask, 0, fcn_0042e410(0x40), &idx) == 0) {
		return 0;
	}
	out[0] = 7;
	*(int*) (out + 4) = g_7f4ca0[(unsigned short) idx].x4;
	*(int*) (out + 8) = min(max(fcn_0042e410(*(int*) (e + 0x194) / 2), 1), 5);
	return 1;
}
