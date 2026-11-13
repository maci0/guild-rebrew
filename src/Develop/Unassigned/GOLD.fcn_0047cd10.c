/* ADDRESS: GOLD 0x0047cd10 */
int __cdecl fcn_0047cd10(unsigned short a, unsigned short b, int rec, unsigned char flags)
{
	int i;
	char* slot;

	i = 0;
	slot = (char*) 0xf8a520;
	for (; i < 0x10; i++) {
		if (*(int*) slot == 0) {
			break;
		}
		slot += 0x11;
	}
	if (i >= 0x10) {
		return -1;
	}
	*(unsigned short*) (0xf8a52d + i * 0x11) = a;
	*(int*) slot = rec;
	slot[4] = 0;
	slot[5] = 0;
	*(unsigned short*) (slot + 0xf) = b;
	*(unsigned short*) (slot + 6) = *(unsigned char*) (*(int*) (rec + 0x3e) + rec);
	if (flags & 1) {
		*(int*) (slot + 8) = 1;
	}
	return i;
}
