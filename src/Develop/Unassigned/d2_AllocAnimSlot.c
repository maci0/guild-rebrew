/* ADDRESS: GOLD 0x0047cd10 */
int __cdecl d2_AllocAnimSlot(unsigned short a, unsigned short b, int rec, unsigned char flags)
{
	int i;
	char* slot;

	i = 0;
	for (slot = (char*) 0xf8a520; (int) slot < 0xf8a630; slot += 0x11) {
		if (*(int*) slot == 0) {
			break;
		}
		i++;
	}
	if ((int) slot >= 0xf8a630) {
		return -1;
	}
	if (i >= 0x10) {
		return -1;
	}
	*(unsigned short*) (0xf8a52d + i * 0x11) = a;
	*(int*) (0xf8a520 + i * 0x11) = rec;
	*(char*) (0xf8a524 + i * 0x11) = 0;
	*(char*) (0xf8a525 + i * 0x11) = 0;
	*(unsigned short*) (0xf8a52f + i * 0x11) = b;
	*(unsigned short*) (0xf8a526 + i * 0x11) = 0;
	*(unsigned short*) (0xf8a526 + i * 0x11) = *(unsigned char*) (*(int*) (rec + 0x3e) + rec);
	if (flags & 1) {
		*(int*) (0xf8a528 + i * 0x11) = 1;
	}
	return i;
}
