extern unsigned short g_7f4c04;

/* ADDRESS: GOLDTL 0x004e8940 */
int __cdecl fcn_004e8940(char* obj)
{
	int a;
	int v;
	int ret;
	unsigned short w;

	w = g_7f4c04;
	ret = 0;
	a = 0x9a9234;
	do {
		v = *(int*) (obj + 4);
		if (*(int*) (a - 0x10) == v) {
			*(int*) (a - 0x10) = -1;
			*(int*) (a - 8) = 0;
			*(unsigned char*) (a - 4) = (unsigned char) ((w > 0xb) + 3);
			ret |= 1;
		} else if (*(int*) a == v) {
			*(unsigned char*) (a - 4) = 1;
		} else {
			a += 0x18;
			continue;
		}
		*(int*) a = -1;
		a += 0x18;
	} while (a < 0x9a9624);
	if (*(unsigned char*) (obj + 0x168) != 0) {
		a = 0x9a922c;
		do {
			if (*(unsigned char*) (a - 4) == *(unsigned char*) (obj + 0x168)) {
				v = *(int*) a;
				if (v > 0) {
					*(int*) a = v - 1;
					ret |= 1;
				}
			}
			a += 0x18;
		} while (a < 0x9a961c);
	}
	*(unsigned char*) (obj + 0x166) = 0;
	*(unsigned char*) (obj + 0x169) = 0;
	*(unsigned char*) (obj + 0x168) = 0;
	return ret;
}
