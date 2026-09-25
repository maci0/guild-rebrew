// FUNCTION: GOLDTL 0x00504bd0
// SIZE: 181

extern unsigned char* g_868050;

int __cdecl fcn_00504bd0(int k)
{
	switch (g_868050[k * 0x24d]) {
	case 11:
	case 12:
	case 13:
		return 2;
	case 19:
		return 7;
	case 4:
	case 5:
	case 9:
		return 8;
	case 8:
	case 14:
	case 18:
	case 20:
	case 21:
	case 22:
	case 29:
	case 31:
	case 32:
		return 1;
	case 1:
	case 3:
	case 6:
	case 15:
		return 3;
	case 7:
		return 4;
	case 23:
	case 24:
	case 25:
	case 26:
		return 5;
	case 2:
	case 30:
		return 6;
	case 33:
		return 9;
	}
	return 0;
}
