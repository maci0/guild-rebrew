#include <string.h>

// SIZE 0x21c
typedef struct House_554b90 {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	unsigned char level;
	char pad9[0x1b1 - 9];
	unsigned char busy;
	char pad1b2[0x21c - 0x1b2];
} House_554b90;

#pragma pack(push, 1)
// SIZE 0xe
typedef struct Pos_554b90 {
	int a;
	int b;
	int c;
	short d;
} Pos_554b90;
#pragma pack(pop)

extern House_554b90 g_7f4ca0[768];
extern unsigned short g_774970;
extern Pos_554b90 g_7f4c00;

void __cdecl fcn_00546190(char*);
int __cdecl gm_AccumulateTyped2(House_554b90*);
void __cdecl fcn_00500bb0(void*, int, int, int);
void __cdecl fcn_004c5980(void*);
int __cdecl fcn_004c5620(int, char*);
int __cdecl gm_StartFilteredEntitySearch(int, ...);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);

/* ADDRESS: GOLDTL 0x00554b90 */
void __cdecl fcn_00554b90(char* e)
{
	int n;
	int ids[8];
	int vals[8];
	char msg[0x114];
	char buf[0x200];
	House_554b90* h;
	int i;
	int k;
	int m;
	int v;
	int r;

	if (*(int*) (e + 0x70) == -1) {
		fcn_00546190(e);
		return;
	}
	if ((e[0x78] & 4) != 0) {
		return;
	}
	switch (*(int*) (e + 0x70)) {
	case 0:
		r = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0xac));
		if (r == 0) {
			fcn_004c5620(-1, e);
			return;
		}
		io_FormatTextBuffer(buf, 0x11be, r, *(int*) (e + 0xb0));
		for (i = 0; i < 768; i++) {
			h = &g_7f4ca0[i];
			if ((h->type == 6 || h->type == 7) && h->level > 0) {
				fcn_00545d40(h->handle, h->handle, buf, 0, 0x601, 0);
			}
		}
		(*(int*) (e + 0x52))++;
		*(short*) (e + 0x56) = 0xd;
		*(int*) (e + 0x58) = 0x1e;
		*(int*) (e + 0x84) = fcn_004c5620(1, e);
		return;
	case 1:
		memset(ids, 0xff, sizeof(ids));
		memset(vals, 0, sizeof(vals));
		memset(msg, 0, sizeof(msg));
		n = 0;
		for (i = 0; i < 768; i++) {
			h = &g_7f4ca0[i];
			if (n >= 8) {
				break;
			}
			if ((h->type == 6 || h->type == 7) && h->level > 0 && h->busy == 0 && gm_AccumulateTyped2(h) >= *(int*) (e + 0xb0)) {
				((int*) (msg + 0x34))[n] = h->handle;
				n++;
			}
		}
		for (i = 0; i < 768; i++) {
			if (g_7f4ca0[i].level > 0 && g_7f4ca0[i].busy == 0 && (g_7f4ca0[i].type == 5 || g_7f4ca0[i].type == 3 || g_7f4ca0[i].type == 4)) {
				v = gm_AccumulateTyped2(&g_7f4ca0[i]);
				if (v >= *(int*) (e + 0xb0)) {
					for (k = 0; k < 8; k++) {
						if (ids[k] == -1) {
							goto put;
						}
						if (v > vals[k]) {
							goto shift;
						}
					}
					continue;
shift:
					if (k < 7) {
						for (m = 7; m > k; m--) {
							ids[m] = ids[m - 1];
							vals[m] = vals[m - 1];
						}
					}
put:
					vals[k] = v;
					ids[k] = g_7f4ca0[i].handle;
				}
			}
		}
		for (k = 0; k < 8; k++) {
			if (n >= 8) {
				break;
			}
			if (ids[k] != -1) {
				((int*) (msg + 0x34))[n] = ids[k];
				n++;
			}
		}
		if (n != 0) {
			msg[8] = 0xa;
			msg[0x26] = 0x22;
			*(int*) (msg + 0x14) = -1;
			msg[0x30] = (char) n;
			*(int*) (msg + 0xc) = g_7f4ca0[g_774970].handle;
			*(int*) (msg + 0x7c) = *(int*) (e + 0xac);
			*(int*) (msg + 0x80) = *(int*) (e + 0xb0);
			*(int*) (msg + 0x84) = 0;
			*(Pos_554b90*) (msg + 0x18) = g_7f4c00;
			fcn_00500bb0(msg + 0x18, 0, 0x1e, 0);
			fcn_004c5980(msg);
		}
		*(Pos_554b90*) (e + 0x52) = g_7f4c00;
		fcn_00500bb0(e + 0x52, 0x18, 0, 0);
		*(int*) (e + 0x84) = fcn_004c5620(-1, e);
		return;
	}
}
