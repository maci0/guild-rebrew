/* ADDRESS: GOLD 0x00468ea0 */
void __cdecl d2_AddSlotDirtyRect(int x, int y, int w, int h)
{
	int slot;
	int n;
	int* table;
	char* rec;
	int right;
	int bottom;
	int ww;
	int hh;

	slot = *(int*) 0x63120c;
	n = *(int*) (slot * 4 + 0x6ed9a4);
	if (n >= 0x300) {
		return;
	}
	if (x > *(int*) 0x5fed5c) {
		x = *(int*) 0x5fed5c;
	}
	if (x & 1) {
		x--;
		ww = (w + 2) & ~1;
	} else {
		ww = w;
	}
	bottom = y + h;
	right = x + ww;
	if (bottom > *(int*) 0x5fed60) {
		hh = *(int*) 0x5fed60 - y;
	} else {
		hh = h;
	}
	if (right > *(int*) 0x5fed5c) {
		ww = *(int*) 0x5fed5c - x;
	}
	if (y < *(int*) 0x6f045c) {
		y = *(int*) 0x6f045c;
	}
	if (x < *(int*) 0x6f0458) {
		x = *(int*) 0x6f0458;
	}
	if (ww <= 0 || hh <= 0) {
		return;
	}
	if (y > *(int*) 0xfb9064) {
		if (y + hh < *(int*) 0xfb906c) {
			if (x > *(int*) 0xfb9060) {
				if (x + ww < *(int*) 0xfb9068) {
					return;
				}
			}
		}
	}
	table = (int*) (slot * 4 + 0x6ed994);
	n = n << 4;
	rec = (char*) (*table);
	*(int*) (rec + n) = x;
	rec = (char*) (*table);
	*(int*) (rec + n + 4) = y;
	rec = (char*) (*table);
	*(int*) (rec + n + 8) = ww;
	rec = (char*) (*table);
	*(int*) (rec + n + 0xc) = hh;
	(*(int*) (slot * 4 + 0x6ed9a4))++;
}
