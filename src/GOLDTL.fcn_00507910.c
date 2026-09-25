// FUNCTION: GOLDTL 0x00507910
// SIZE: 213

int __cdecl fcn_00507910(int k)
{
	switch (k) {
	case 4:
		return 0xb;
	case 5:
		return 9;
	case 7:
		return 7;
	case 8:
		return 6;
	case 9:
		return 8;
	case 14:
		return 5;
	case 16:
		return 0xc;
	case 18:
		return 1;
	case 19:
		return 0xa;
	case 20:
		return 2;
	case 21:
		return 3;
	case 22:
		return 4;
	case 29:
		return 0xd;
	case 31:
		return 0xe;
	case 32:
		return 0xf;
	}
	return 0;
}

// SIZE 0x24d
typedef struct {
	unsigned char type;
	char pad1[0x24c];
} Ent;

extern Ent* g_868050;

float __cdecl fcn_0050b8d0(unsigned char* p, int k, int a, int b);

// FUNCTION: GOLDTL 0x005101e0
// SIZE: 116

/* Lives in this file because it must see fcn_00507910 above it: msvc6 then
 * knows the callee leaves edx alone and keeps k there across the call. */
float __cdecl fcn_005101e0(unsigned char* p, int k, int a, int b)
{
	int c;

	c = fcn_00507910(g_868050[k].type);
	if (c != 10 && c != 11 && c != 12) {
		return fcn_0050b8d0(p, k, a, b) * 3.0f;
	}
	return fcn_0050b8d0(p, k, a, b) * 9.0f;
}
