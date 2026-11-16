/* ADDRESS: GOLD 0x00468fa0 */
void __cdecl fcn_00468fa0(int x, int y, int w, int h, char* obj)
{
	int lim;
	int right;
	int bottom;
	int limy;
	int i;
	char* slot;
	char* base;

	if (*(int*) (obj + 0x190) == 0 || *(int*) (obj + 0x1a8) == 0) {
		return;
	}
	lim = *(int*) 0x5fed5c;
	if (x > lim) {
		x = lim;
	}
	if (x & 1) {
		x--;
		w = (w + 2) & ~1;
	}
	limy = *(int*) 0x5fed60;
	bottom = y + h;
	if (bottom > limy) {
		h = limy - y;
	}
	right = x + w;
	if (right > lim) {
		w = lim - x;
	}
	if (y < *(int*) 0x6f045c) {
		y = *(int*) 0x6f045c;
	}
	if (x < *(int*) 0x6f0458) {
		x = *(int*) 0x6f0458;
	}
	if (w < 0) {
		w = 1;
	}
	if (h < 0) {
		h = 1;
	}
	base = *(char**) 0x6ed9a0;
	slot = base;
	i = 0;
	while (*(int*) (slot + 8) != 0) {
		if (i >= 0x300) {
			return;
		}
		slot += 0x14;
		i++;
	}
	if (i >= 0x300) {
		return;
	}
	*(int*) (base + i * 0x14) = x;
	*(int*) (*(char**) 0x6ed9a0 + i * 0x14 + 4) = y;
	*(int*) (*(char**) 0x6ed9a0 + i * 0x14 + 0xc) = w;
	*(int*) (*(char**) 0x6ed9a0 + i * 0x14 + 0x10) = h;
	*(int*) (*(char**) 0x6ed9a0 + i * 0x14 + 8) = (int) obj;
}
