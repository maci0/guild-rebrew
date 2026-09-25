// FUNCTION: GOLDTL 0x004eb320
// SIZE: 192

extern unsigned char* g_868050;

unsigned char* __cdecl gm_StartFilteredEntitySearch(int a, int b, int kind);

int __cdecl fcn_004eb320(unsigned char* obj)
{
	unsigned char* r;
	int kind;

	if (obj[0x169] < 0x1e || obj[0x169] > 0x21) {
		return 0;
	}
	switch (obj[0x169]) {
	case 0x1f:
		kind = 0x18;
		break;
	case 0x20:
		kind = 0x19;
		break;
	case 0x21:
		kind = 0x1a;
		break;
	case 0x1e:
		kind = 0x17;
		break;
	default:
		return 0;
	}
	r = gm_StartFilteredEntitySearch(1, 5, kind);
	if (r == 0 || (r[0x5a] & 1) != 0) {
		return 0;
	}
	if (g_868050[*r * 0x24d + 0x247] < 3) {
		return 0;
	}
	if (*(unsigned int*) (obj + 0x1c8) & 0x10000000) {
		return -1;
	}
	return *(int*) (obj + 0x194) < 8 ? -2 : 1;
}
