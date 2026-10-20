#include <string.h>

extern float g_6628a0;
extern float g_664158;
extern int g_773d48;
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern unsigned short g_7f4c0c;
extern float g_696444[];

char* __cdecl fcn_00508e40(int);
float __cdecl fcn_0042e450(void);
void __cdecl fcn_004c5480(int, int, float);
void __cdecl fcn_00500bb0(void*, int, int, int);
int __cdecl fcn_0042e410(int);
int __cdecl fcn_004c4fc0(int, int, int, int, int, int, int, int);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00535960(void);
int __cdecl fcn_004c4480(int);
void __cdecl fcn_004c4510(int, int);
void __cdecl fcn_004c4570(int, int, int, void*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004c5980(void*);

/* ADDRESS: GOLDTL 0x004ff490 */
void __cdecl fcn_004ff490(char* a0)
{
	char* ent;
	char* other;
	char* p;
	char* e;
	int id;
	int handle;
	int count;
	int i;
	int extra;
	int hdr[3];
	unsigned short hdr2;
	char pkt[0x114];
	float f;

	if ((unsigned char) a0[2] >= 10) {
		return;
	}
	if (a0[8] == 0) {
		return;
	}
	if (a0[9] != 1) {
		return;
	}
	if ((unsigned char) a0[0x1b1] != 0) {
		return;
	}
	if ((*(unsigned int*) (a0 + 0x1c8)) & 0x40000) {
		return;
	}

	ent = fcn_00508e40(*(unsigned int*) (a0 + 0x5c));
	if (g_6628a0 < *(float*) (a0 + 0x7c)) {
		f = fcn_0042e450() * g_664158 - *(float*) (a0 + 0x7c);
		fcn_004c5480(*(unsigned int*) (a0 + 4), 0x7c, f);
		g_773d48++;
		if (ent == 0) {
			return;
		}

		hdr[0] = g_7f4c00;
		hdr[1] = g_7f4c04;
		hdr[2] = g_7f4c08;
		hdr2 = g_7f4c0c;
		extra = 2;
		fcn_00500bb0(hdr, 8, 0, 0);

		other = (char*) fcn_0042e410(4);
		other = other + 8;
		handle = *(int*) (a0 + 0x170);
		if (handle != 0) {
			id = *(int*) (handle + 1);
		} else {
			id = -1;
		}
		if (*(char*) (ent + 2) == 6 || *(char*) (ent + 2) == 7) {
			count = 0;
			p = ent + 0x68;
			for (i = 0; i < 4; i++) {
				if (*(int*) p != -1) {
					count++;
				}
				p += 4;
			}
			if (count == 0) {
				extra = (unsigned char) ent[9];
			}
			if (handle != 0) {
				id = *(int*) (handle + 1);
			} else if (*(int*) (ent + 0x170) != 0) {
				id = *(int*) (*(int*) (ent + 0x170) + 1);
			} else {
				id = -1;
			}
			other = ent;
		} else if (*(char*) (a0 + 2) == 6 || *(char*) (a0 + 2) == 7) {
			count = 0;
			p = a0 + 0x68;
			for (i = 0; i < 4; i++) {
				if (*(int*) p != -1) {
					count++;
				}
				p += 4;
			}
			if (count == 0) {
				extra = (unsigned char) a0[9];
			}
			if (handle != 0) {
				id = *(int*) (handle + 1);
			} else if (*(int*) (ent + 0x170) != 0) {
				id = *(int*) (*(int*) (ent + 0x170) + 1);
			} else {
				id = -1;
			}
			other = a0;
		}

		id = fcn_004c4fc0(8, *(int*) (ent + 4), *(int*) (a0 + 4), 0, id, 0, 0, extra);
		while (fcn_004c4450(id) == 0) {
			fcn_00535960();
		}
		if (fcn_004c4450(id) == 2) {
			return;
		}
		handle = fcn_004c4480(id);
		if (other != 0) {
			memset(pkt, 0, 0x114);
			pkt[8] = 7;
			*(int*) (pkt + 0xc) = *(int*) (other + 4);
			*(int*) (pkt + 0x14) = -1;
			*(int*) (pkt + 0x18) = g_7f4c00;
			*(int*) (pkt + 0x1c) = g_7f4c04;
			*(int*) (pkt + 0x20) = g_7f4c08;
			*(unsigned short*) (pkt + 0x24) = g_7f4c0c;
			pkt[0x26] = 0xa0;
			pkt[0x30] = 2;
			*(int*) (pkt + 0x34) = *(int*) (other + 4);
			*(int*) (pkt + 0x38) = *(int*) (handle + 4);
			fcn_004c4510(handle, *(int*) (handle + 4));
			fcn_004c4570(1, 1, 2, &hdr[1]);
			fcn_004c5360();
			fcn_004c5980(pkt + 0x18);
			g_773d48++;
			return;
		}
	}

	if (ent != 0 && ent[8] != 0 && *(unsigned short*) (a0 + 0xa) <= 0x26) {
		count = 0;
		p = a0 + 0x68;
		for (i = 0; i < 5; i++) {
			if (*(int*) p != -1) {
				e = fcn_00508e40(*(int*) p);
				if (*(char*) (e + 2) == 6 || *(char*) (e + 2) == 7 || *(char*) (e + 2) == 5) {
					return;
				}
				if (*(char*) (e + 2) != 0xf) {
					count++;
				}
			}
			p += 4;
		}
		if (count == 4) {
			return;
		}
		if (*(char*) (ent + 2) == 6 || *(char*) (ent + 2) == 7) {
			extra = 0;
			p = ent + 0x68;
			for (i = 0; i < 5; i++) {
				if (*(int*) p != -1) {
					e = fcn_00508e40(*(int*) p);
					if (*(char*) (e + 2) == 6 || *(char*) (e + 2) == 7 || *(char*) (e + 2) == 5) {
						return;
					}
					if (*(char*) (e + 2) != 0xf) {
						extra++;
					}
				}
				p += 4;
			}
			if (extra == 5) {
				return;
			}
		}
		f = (fcn_0042e450() + g_6628a0) * g_696444[count];
		fcn_004c5480(*(unsigned int*) (a0 + 4), 0x7c, f);
		g_773d48++;
		return;
	}
}
