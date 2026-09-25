// FUNCTION: GOLDTL 0x00507400
// SIZE: 220

int __cdecl fcn_00507400(int k, int b)
{
	int d;

	if (k == 0) {
		return 0;
	}
	d = b - 1;
	switch (k) {
	case 11:
		return 0x6 - d;
	case 9:
		return 0xc - d;
	case 7:
		return 0x12 - d;
	case 6:
		return 0x18 - d;
	case 8:
		return 0x1e - d;
	case 5:
		return 0x27 - d;
	case 12:
		return 0x2d - d;
	case 1:
		return 0x33 - d;
	case 10:
		return 0x39 - d;
	case 2:
		return 0x3f - d;
	case 3:
		return 0x45 - d;
	case 4:
		return 0x4b - d;
	case 13:
		return 0x51 - d;
	case 15:
		return 0x5e - d;
	case 14:
		return 0x58 - d;
	case 16:
		return 0;
	}
	return 0;
}
