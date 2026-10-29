/* id in 0x605..0x60d tests a bit of [0x6f263c]; anything else returns 0.
 * 0x605 is bit 0. 0x606's test is the tail of this range. */
/* ADDRESS: GOLD 0x00575900 */
int __cdecl fcn_00575900(unsigned int id)
{
	unsigned int v;

	switch (id) {
	case 0x605:
		if (*(unsigned char*) 0x6f263c & 1)
			return 1;
		break;
	case 0x606:
		if (*(unsigned char*) 0x6f263c & 2)
			return 1;
		break;
	case 0x607:
		if (*(unsigned char*) 0x6f263c & 4)
			return 1;
		break;
	case 0x608:
		if (*(unsigned char*) 0x6f263c & 8)
			return 1;
		break;
	case 0x609:
		if (*(unsigned char*) 0x6f263c & 0x10)
			return 1;
		break;
	case 0x60a:
		if (*(unsigned char*) 0x6f263c & 0x20)
			return 1;
		break;
	case 0x60b:
		v = *(signed char*) 0x6f263c;
		return (v & 0x40) >> 6;
	case 0x60c:
		if (*(signed char*) 0x6f263c < 0)
			return 1;
		break;
	case 0x60d:
		if (*(unsigned int*) 0x6f263c & 0x100)
			return 1;
		break;
	}
	return 0;
}
