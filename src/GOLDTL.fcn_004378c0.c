// FUNCTION: GOLDTL 0x4378c0
// SIZE: 216

char __cdecl fcn_004378c0(int which, unsigned int flags)
{
	switch (which) {
	case 0:
		return (flags & 0x20) == 0x20;
	case 3:
		return (flags & 1) == 1;
	case 4:
		return (flags & 0x40) == 0x40;
	case 1:
		return (flags & 0x80) == 0x80;
	case 2:
		return (flags & 0x100) == 0x100;
	case 5:
		return (flags & 2) == 2;
	case 6:
		return (flags & 4) == 4;
	case 7:
		return (flags & 8) == 8;
	case 8:
		return (flags & 0x10) == 0x10;
	}
	return 0;
}
