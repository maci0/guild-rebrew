#include <string.h>

#pragma intrinsic(memset)

extern int g_100f1dc;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_00471f80(int);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00472380(int, int, int, int);
void __cdecl fcn_00472640(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_004c6ae0(int, int);
int __cdecl fcn_004f4830(int, void*);
int __cdecl fcn_004f4860(char*, unsigned char, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00525f60(char*, int);
void __cdecl fcn_00535960(void);
int __cdecl fcn_005373e0(void*, int);

/* ADDRESS: GOLDTL 0x005d6540 */
int __cdecl fcn_005d6540(char* a0, int* a1)
{
	int rec[9];
	int r;
	int limit;
	char* recp;
	int add;
	int keep;
	int ctl;
	int box;
	int id;
	int idx;
	int delta;
	int dlg;

	r = 0;
	if (a1[0] == 3) {
		recp = a0;
	} else if (a1[0] == 4) {
		recp = (char*) a1[0x87];
		if (recp == 0) {
			return 0x60;
		}
	} else {
		return 0x60;
	}
	if (a1[0x85] == 1) {
		limit = 0x80000;
	} else if (a1[0x85] == 2) {
		limit = 0x100000;
	} else {
		return 0x60;
	}
	if (a0[2] != 6) {
		if (*(int*) (a0 + 0x194) < 2) {
			return 0x20;
		}
		if (fcn_004f4830(a1[1], rec) == 0) {
			return 0x60;
		}
		if (a1[2] == rec[6]) {
			return 0x60;
		}
		if (a1[2] > rec[2]) {
			return 0x60;
		}
		if (a1[2] < rec[1]) {
			return 0x60;
		}
		fcn_004f4860(a0, *(unsigned char*) rec, a1[2]);
		fcn_004c6ae0(*(int*) (a0 + 4), -2);
		fcn_004c5420(*(int*) (recp + 4), 0x1c8, 4, limit, 0);
		if (a0[2] != 6) {
			return 0;
		}
	}
	memset(rec, 0, 36);
	keep = 1;
	add = 0;
	box = -1;
	if (fcn_004f4830(a1[1], rec) == 0) {
		return 0;
	}
	id = 0x13fd + *(unsigned char*) rec * 5;
	dlg = fcn_00470820(0, 0, "privillegien\\gesetz");
	d2_SetOverlayAnimation(0, 0);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1ba9);
	switch (*(unsigned char*) ((char*) rec + 1)) {
	case 0:
		id = io_AppendText(0x13d0, id, 0x13d3);
		ctl = fcn_00472250(dlg, 1, id);
		box = fcn_00472250(dlg, 1, id + 1);
		fcn_00472380(ctl, rec[1], rec[2], rec[6]);
		break;
	case 1:
		id = io_AppendText(0x13da, id, 0x13dd, rec[6] + 0x13dd);
		ctl = fcn_00472250(dlg, 1, id);
		box = fcn_00472250(dlg, 1, id + 1);
		add = 0x13dd;
		break;
	case 2:
		ctl = fcn_00472250(dlg, 1, io_AppendText(0x13e3, id, id, 0x13e7 - rec[6]));
		keep = 0;
		break;
	case 3:
		id = io_AppendText(0x13e9, 0x13ec, rec[6] + 0x13ec);
		ctl = fcn_00472250(dlg, 1, id);
		box = fcn_00472250(dlg, 1, id + 1);
		add = 0x13ec;
		break;
	default:
		return 0;
	}
	g_100f1dc = -1;
	do {
		if (keep) {
			fcn_00472640(box, (fcn_00471f80(ctl) - add != rec[6]) && box != -1);
		}
		if (*(int*) 0x14ce8e0 != 0) {
			*(int*) 0x774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (g_100f1dc == 2) {
				if (fcn_00525f60(a0, 2) != 0) {
					if (*(unsigned char*) ((char*) rec + 1) == 2) {
						delta = 1 - rec[6];
					} else {
						delta = fcn_00471f80(ctl) - add;
					}
					r = 0x80;
					idx = fcn_004f4860(a0, *(unsigned char*) rec, delta);
					if (idx != -1) {
						while (fcn_004c4450(idx) == 0) {
							fcn_00535960();
						}
						fcn_004c6ae0(*(int*) (a0 + 4), -2);
						fcn_004c5420(*(int*) (recp + 4), 0x1c8, 4, limit, 0);
					}
					*(int*) 0x774654 = 1;
				}
			} else if (g_100f1dc == 1) {
				*(int*) 0x774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) fcn_005d6540, 0x657c7) != 0);
	fcn_00471e30(dlg);
	return r;
}
