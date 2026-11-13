/* ADDRESS: GOLD 0x0046cd90 */
void __cdecl fcn_0046cd90(short x, short y, int id)
{
	int slot;
	char* rec;
	int kind;
	char* box;
	int i;
	int child;
	short w;
	short h;

	slot = ((id << 5) - id + ((id << 5) - id) * 2) * 2 + id;
	rec = (char*) (*(int*) 0xf8f080 + slot * 4);
	kind = *(int*) (rec + 0x18);
	*(short*) (rec + 0x10) = x;
	*(short*) (rec + 0x12) = y;
	*(unsigned char*) (rec + 0x6c) = 8;
	*(unsigned char*) (rec + 0x6d) = 8;
	if (kind == 0x40) {
		*(short*) (rec + 0x22) = y;
		*(short*) (rec + 0x24) = (short) (*(short*) (rec + 0x16) + y);
		*(short*) (rec + 0x1e) = x;
		*(short*) (rec + 0x20) = (short) (*(short*) (rec + 0x14) + x);
	} else {
		*(short*) (rec + 0x22) = 0;
		*(short*) (rec + 0x24) = *(short*) 0xfb9070;
		*(short*) (rec + 0x1e) = 0;
		*(short*) (rec + 0x20) = *(short*) 0xfb9072;
	}
	box = *(char**) (rec + 0x30);
	if (box != 0) {
		w = *(short*) (box + 6);
		if (w <= *(short*) (rec + 0x22)) {
			w = *(short*) (rec + 0x22);
		}
		*(short*) (rec + 0x22) = w;
		h = (short) (*(short*) (box + 0xa) + *(short*) (box + 6));
		if (*(short*) (rec + 0x24) < h) {
			h = *(short*) (rec + 0x24);
		}
		*(short*) (rec + 0x24) = h;
		if (*(short*) 0xfb9070 < h) {
			h = *(short*) 0xfb9070;
		}
		*(short*) (rec + 0x24) = h;
		w = *(short*) (box + 4);
		if (w <= *(short*) (rec + 0x1e)) {
			w = *(short*) (rec + 0x1e);
		}
		*(short*) (rec + 0x1e) = w;
		h = (short) (*(short*) (box + 8) + *(short*) (box + 4));
		if (*(short*) (rec + 0x20) < h) {
			h = *(short*) (rec + 0x20);
		}
		*(short*) (rec + 0x20) = h;
		if (*(short*) 0xfb9072 < h) {
			h = *(short*) 0xfb9072;
		}
		*(short*) (rec + 0x20) = h;
	}
	if (kind == 4) {
		slot = *(int*) (rec + 0x78);
		*(short*) (0xf8a52d + slot * 17) = x;
		*(short*) (0xf8a52f + slot * 17) = *(short*) (rec + 0x12);
		return;
	}
	if (kind == 0x40) {
		slot = *(int*) (rec + 0x78);
		box = (char*) (0xf8f120 + slot * 0x34);
		*(short*) (box + 6) = y;
		*(short*) (box + 4) = x;
		if (*(short*) 0xfb9072 < *(short*) (rec + 0x20)) {
			*(short*) (rec + 0x20) = *(short*) 0xfb9072;
		}
		if (*(short*) 0xfb9070 < *(short*) (rec + 0x24)) {
			*(short*) (rec + 0x24) = *(short*) 0xfb9070;
		}
		i = 0;
		while (i < *(short*) (box + 0x1c)) {
			child = *(int*) (*(int*) (box + 0x18) + i * 4);
			fcn_0046cd90(
				(short) (*(short*) ((char*) (*(int*) 0xf8f080
					+ ((((child << 5) - child) * 3) * 2 + child) * 4)
					+ 0x10) - *(short*) (0xf8f124 + slot * 0x34)
					+ *(short*) (box + 4)),
				(short) (*(short*) ((char*) (*(int*) 0xf8f080
					+ ((((child << 5) - child) * 3) * 2 + child) * 4)
					+ 0x12) - *(short*) (0xf8f126 + slot * 0x34)
					+ *(short*) (box + 6)),
				child);
			i++;
		}
		return;
	}
	if (kind == 0x41) {
		slot = *(int*) (rec + 0x78);
		*(int*) (0xfa6024 + slot * 0x160) = x;
		*(int*) (0xfa6028 + slot * 0x160) = *(short*) (rec + 0x12);
	}
}
