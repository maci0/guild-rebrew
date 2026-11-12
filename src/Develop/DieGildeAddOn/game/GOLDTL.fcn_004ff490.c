#include <string.h>

#pragma pack(push, 2)
typedef struct {
	int day;
	unsigned short hour;
	int min;
	int sec;
} Time;
#pragma pack(pop)

extern float g_6628a0;
extern float g_664158;
extern int g_773d48;
extern int g_7f4c00;
extern float g_696444[];

char* __cdecl gm_LookupEntityRecordById(int);
float __cdecl gm_RandomFloat01(void);
void __cdecl fcn_004c5480(int, int, float);
void __cdecl fcn_00500bb0(void*, int, int, int);
unsigned short __cdecl gm_RandomMod(int);
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
	Time t;
	int mode;
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
	if ((unsigned char) a0[0x1b1] > 0) {
		return;
	}
	if ((*(unsigned int*) (a0 + 0x1c8)) & 0x40000) {
		return;
	}

	ent = gm_LookupEntityRecordById(*(unsigned int*) (a0 + 0x5c));
	if (*(float*) (a0 + 0x7c) > 1.0f) {
		fcn_004c5480(*(unsigned int*) (a0 + 4), 0x7c, gm_RandomFloat01() * g_664158 - *(float*) (a0 + 0x7c));
		g_773d48++;
		if (ent == 0) {
			return;
		}

		t = *(Time*) &g_7f4c00;
		extra = 2;
		fcn_00500bb0(&t, 8, 0, 0);

		other = 0;
		t.hour = gm_RandomMod(4) + 8;
		t.min = 0;
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
			if (*(int*) (ent + 0x170) != 0) {
				id = *(int*) (*(int*) (ent + 0x170) + 1);
			} else if (handle != 0) {
				id = *(int*) (handle + 1);
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
			mode = 0x12;
			memset(pkt, 0, 0x114);
			pkt[8] = 7;
			*(int*) (pkt + 0xc) = *(int*) (other + 4);
			*(int*) (pkt + 0x14) = -1;
			*(Time*) (pkt + 0x18) = t;
			pkt[0x26] = 0xa0;
			pkt[0x30] = 2;
			*(int*) (pkt + 0x34) = *(int*) (other + 4);
			*(int*) (pkt + 0x38) = *(int*) (handle + 4);
			fcn_004c4510(handle, *(int*) (handle + 4));
			fcn_004c4570(1, 1, 2, &mode);
			fcn_004c5360();
			fcn_004c5980(pkt);
			g_773d48++;
			return;
		}
	}

	if (ent != 0 && ent[8] != 0 && *(unsigned short*) (a0 + 0xa) <= 0x26) {
		count = 0;
		p = a0 + 0x68;
		for (i = 0; i < 5; i++) {
			if (*(int*) p != -1) {
				e = gm_LookupEntityRecordById(*(int*) p);
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
					e = gm_LookupEntityRecordById(*(int*) p);
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
		f = (gm_RandomFloat01() + 1.0f) * g_696444[count];
		fcn_004c5480(*(unsigned int*) (a0 + 4), 0x7c, f);
		g_773d48++;
		return;
	}
}
