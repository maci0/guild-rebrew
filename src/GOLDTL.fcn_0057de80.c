/* ADDRESS: GOLDTL 0x0057de80 */
int __cdecl fcn_0057de80(unsigned int a0)
{
	int v;

	switch (a0) {
	case 0x605:
		if (*(unsigned char*) 0x7749f4 & 1)
			return 1;
		break;
	case 0x606:
		if (*(unsigned char*) 0x7749f4 & 2)
			return 1;
		break;
	case 0x607:
		if (*(unsigned char*) 0x7749f4 & 4)
			return 1;
		break;
	case 0x608:
		if (*(unsigned char*) 0x7749f4 & 8)
			return 1;
		break;
	case 0x609:
		if (*(unsigned char*) 0x7749f4 & 0x10)
			return 1;
		break;
	case 0x60a:
		if (*(unsigned char*) 0x7749f4 & 0x20)
			return 1;
		break;
	case 0x60b:
		v = *(signed char*) 0x7749f4;
		return (v & 0x40) >> 6;
	case 0x60c:
		if (*(char*) 0x7749f4 < 0)
			return 1;
		break;
	case 0x60d:
		if (*(unsigned int*) 0x7749f4 & 0x100)
			return 1;
		break;
	}
	return 0;
}
