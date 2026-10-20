void __cdecl fcn_004695a0(int, int);
int __cdecl fcn_004125c0(int, int);

/* ADDRESS: GOLDTL 0x00469630 */
void __cdecl fcn_00469630(int a0)
{
	int count;
	int sel;
	int i;
	int alt;
	int id;
	char key;

	count = *(int*) (a0 * 0x8c + 0x102cbc4);
	if (count <= 0) {
		return;
	}
	sel = *(int*) (a0 * 0x8c + 0x102cbc8);
	if (*(int*) 0x67d3d0) {
		goto scan;
	}
	if (*(int*) 0x6b8af8 != (int) *(short*) 0x14ce8c0
		|| *(int*) 0x6b8afc != (int) *(short*) 0x14ce8c2) {
		*(int*) 0x67d3d0 = 1;
scan:
		if (!*(int*) 0x7725d0) {
			for (i = 0; i < count; i++) {
				if (*(int*) (a0 * 0x8c + 0x102cbcc + i * 4) == *(int*) 0x67d370
					&& (!(*(unsigned char*) (a0 * 0x8c + 0x102cbc0) & 1)
						|| *(int*) 0x14ce8cc)) {
					sel = i;
				}
			}
			if (sel == *(int*) (a0 * 0x8c + 0x102cbc8)) {
				*(int*) 0x67d3d0 = 0;
			}
		}
	}
	key = *(char*) 0x14cf950;
	id = *(int*) 0x67d38c;
	if (key == (char) 0xc8 || (*(int*) 0x14ce904 && id == -1)) {
		sel--;
		alt = *(int*) 0x14ce904;
	}
	else if (key == (char) 0xd0 || (*(int*) 0x14ce900 && id == -1)) {
		sel++;
		alt = *(int*) 0x14ce900;
	}
	else {
		goto skip;
	}
	*(int*) 0x67d3d0 = 0;
	*(int*) 0x6b8af8 = *(short*) 0x14ce8c0;
	*(int*) 0x6b8afc = *(short*) 0x14ce8c2;
	if (sel < 0) {
		sel = count - 1;
	}
	sel %= count;
	if (alt) {
		id = *(int*) (a0 * 0x8c + 0x102cbcc + sel * 4);
		alt = *(int*) 0x1015ea0 + id * 0x2f4;
		fcn_004125c0(
			(int) (*(int*) (alt + 0x18) * *(double*) 0x662908
				+ *(int*) (alt + 0x10)),
			(int) (*(int*) (alt + 0x1c) * *(double*) 0x662908
				+ *(int*) (alt + 0x14)));
	}
skip:
	if (sel == -1) {
		if (*(int*) (a0 * 0x8c + 0x102cbc8) != -1) {
			fcn_004695a0(a0, -1);
		}
		return;
	}
	if (sel < 0) {
		sel = *(int*) (a0 * 0x8c + 0x102cbc4) - 1;
	}
	sel %= *(int*) (a0 * 0x8c + 0x102cbc4);
	if (sel != *(int*) (a0 * 0x8c + 0x102cbc8) || !*(int*) 0x67d3d0) {
		fcn_004695a0(a0, sel);
	}
	if (*(char*) 0x14cf950 != 0x1c) {
		return;
	}
	*(int*) 0x14ce8d8 = 1;
	*(char*) 0x14cf950 = 0;
	id = *(int*) (a0 * 0x8c + 0x102cbcc + sel * 4);
	*(int*) 0x67d370 = id;
	alt = *(int*) 0x1015ea0 + id * 0x2f4;
	if (*(int*) (alt + 0x20) != 9) {
		*(int*) 0x100f1dc = *(int*) (alt + 8);
	}
	else {
		*(int*) 0x100f1dc = (*(unsigned char*) (alt + 0x1d0) & 0x10) ? 1 : 2;
	}
}
