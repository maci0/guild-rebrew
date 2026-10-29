#include <string.h>

extern char* g_entity_type_table;
extern char* g_1015ea0;
extern int g_772514;
extern int g_67d370;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;

int __cdecl fcn_00502cd0(int a, int b, ...);
int __cdecl fcn_00525fb0(void* obj);
void* __cdecl fcn_005463a0(int a, int b, int c, int d, int e);
void* __cdecl he_fn_Handlung(void);
int __cdecl fcn_00470820(int a, int b, char* name);
void __cdecl fcn_00471b60(int dlg);
void __cdecl d2_SetForm(int dlg, int flag);
void __cdecl fcn_00533dc0(int ctx, int a, int b);
int __cdecl fcn_00519190(int id, ...);
void __cdecl fcn_0052a0c0(void* obj, int flag);
void __cdecl fcn_00594340(void);
int __cdecl fcn_0046f740(int a, int b, int c, int d);
void __cdecl fcn_0046f9b0(int handle, char* name);
void __cdecl fcn_00472640(int handle, int flag);
void __cdecl fcn_00595e20(void* obj, int packet);
void __cdecl fcn_005963f0(int dlg, int a, int b, void* obj);
int __cdecl fcn_005373e0(void* fn, int key);
void __cdecl fcn_0052ae70(void);
void __cdecl fcn_0052a2d0(void);
void __cdecl fcn_00471e30(int dlg);
int __cdecl fcn_004c5530(char* msg);
void __cdecl fcn_004c35f0(void);
int __cdecl fcn_004c4450(int handle);
void __cdecl fcn_004c4480(int handle);
void __cdecl fcn_0051af00(char* buf, int id, ...);
void __cdecl fcn_00526120(char* buf, int flag);
void __cdecl fcn_00532ef0(void);

/* ADDRESS: GOLDTL 0x0059e740 */
void __cdecl fcn_0059e740(unsigned char* a0, unsigned char* a1)
{
	int count;
	int ids[7];
	int y;
	int dlg;
	int handles[3];
	char pkt[0xf8];
	char buf[0x100];
	int i;
	int j;
	int h;
	int x;
	unsigned char type;
	unsigned char kind;
	char* rec;
	char* p;
	void* entity;

	ids[0] = 0x1c4;
	ids[1] = 0x1c5;
	ids[2] = 0x1c6;
	ids[6] = fcn_00502cd0(*(int*) (a0 + 0x5d), 2, 6, 0, 0x2a);
	type = *(unsigned char*) a0;
	rec = g_entity_type_table + type * 0x24d;
	kind = *(unsigned char*) rec;
	if (kind == 0x20) {
		ids[0] = 0x2af;
		count = 1;
		if (*(unsigned char*) (rec + 0x247) >= 2) {
			ids[1] = 0x2b0;
			count = 2;
		}
	} else if (kind == 0x1f) {
		ids[0] = 0x293;
		ids[1] = 0x294;
		ids[2] = 0x295;
		count = 3;
	} else {
		count = 3;
		if (kind == 8 || *(unsigned char*) (rec + 0x247) <= 1) {
			count = 2;
		}
	}
	if (fcn_00525fb0(a0) != 0) {
		return;
	}
	ids[3] = 0;
	ids[4] = 0;
	ids[5] = 0;
	entity = fcn_005463a0(2, 0, 0x14, 3, *(int*) (a0 + 1));
	while (entity != 0) {
		for (i = 0; i < 3; i++) {
			if (*(unsigned short*) ((char*) entity + 0xae) == ids[i]) {
				ids[i + 3] += *(unsigned char*) ((char*) entity + 0xac);
				break;
			}
		}
		entity = he_fn_Handlung();
	}
	dlg = fcn_00470820(0, 0, (char*) 0x6a9750);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 0);
	fcn_00533dc0(g_772514, 0x70f, 0x741);
	d2_SetForm(dlg, 3);
	fcn_00519190(0x17fe);
	fcn_0052a0c0(a0, 0);
	fcn_00594340();
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 2);
	if (count > 0) {
		y = *(int*) (g_772514 * 0x3cc + 0x1015f4c) / 2 - 0x80;
		x = 0x19;
		for (i = 0; i < count; i++) {
			h = fcn_0046f740(y, x, ids[i] + 0xdf, g_772514);
			*(int*) (g_1015ea0 + h * 0x2f4 + 0x5c) = 1;
			*(int*) (g_1015ea0 + h * 0x2f4 + 0x1d0) = 3;
			*(int*) (g_1015ea0 + h * 0x2f4 + 0x1dc) = 100;
			*(int*) (g_1015ea0 + h * 0x2f4 + 0x1e0) = 0x10;
			*(int*) (g_1015ea0 + h * 0x2f4 + 0x84) = 0x54;
			fcn_0046f9b0(h, (char*) *(int*) (ids[i] * 8 + 0x14a79c0));
			handles[i] = h;
			fcn_00472640(h, 1);
			x += 0x50;
		}
	}
	fcn_00473a90(0, 0);
	fcn_00595e20(a0, ids[6]);
	fcn_005963f0(dlg, 1, 0, a0);
	while (fcn_005373e0((void*) fcn_0059e740, 0x677c7) != 0) {
		fcn_00595e20(a0, ids[6]);
		fcn_005963f0(dlg, 1, 0, a0);
		ids[3] = 0;
		ids[4] = 0;
		ids[5] = 0;
		entity = fcn_005463a0(2, 0, 0x14, 3, *(int*) (a0 + 1));
		while (entity != 0) {
			for (i = 0; i < 3; i++) {
				if (*(unsigned short*) ((char*) entity + 0xae) == ids[i]) {
					ids[i + 3] += *(unsigned char*) ((char*) entity + 0xac);
					break;
				}
			}
			entity = he_fn_Handlung();
		}
		d2_SetForm(dlg, 2);
		if (count > 0) {
			for (i = 0; i < count; i++) {
				fcn_00472640(handles[i], 1);
				if (ids[i + 3] == 1) {
					fcn_0051af00(buf, 0x17ff, ids[i + 3], ids[i] * 2 + 0x9a8);
				} else if (ids[i + 3] > 1) {
					fcn_0051af00(buf, 0x1800, ids[i + 3], ids[i] * 2 + 0x9a8);
				} else {
					fcn_0051af00(buf, (int) 0x679060, ids[i] * 2 + 0x9a8);
				}
				fcn_0046f9b0(handles[i], buf);
			}
		}
		if (g_100f1dc != -1) {
			for (i = 0; i < count; i++) {
				if (handles[i] == g_67d370) {
					if (i == -1) {
						break;
					}
					memset(pkt, 0, sizeof(pkt));
					pkt[4] = 0x14;
					pkt[0x36] = 1;
					*(int*) (pkt + 8) = *(int*) (0x7f4ca4 + *(unsigned short*) (a0 + 0x27) * 0x21c);
					*(int*) (pkt + 0x28) = g_7f4c00;
					*(int*) (pkt + 0xc) = *(int*) (a0 + 1);
					*(int*) (pkt + 0x30) = g_7f4c08;
					*(int*) (pkt + 0x2c) = g_7f4c04;
					*(unsigned short*) (pkt + 0x5a) = (unsigned short) ids[i];
					*(short*) (pkt + 0x34) = g_7f4c0c;
					*(int*) (pkt + 0x5c) = *(int*) (a1 + 2);
					j = 0;
					for (p = (char*) 0x7f4ca4; j < 6 && p < (char*) 0x85a0a4; p += 0x21c) {
						if (*(char*) (p + 0x184) != 0) {
							*(int*) (pkt + 0x38 + j * 4) = *(int*) p;
							j++;
						}
					}
					if (j < 6) {
						memset(pkt + 0x38 + j * 4, 0xff, (6 - j) * 4);
					}
					pkt[0x58] = (char) j;
					if (j != 0) {
						fcn_004c35f0();
						fcn_0052ae70();
						h = fcn_004c5530(pkt);
						while (fcn_004c4450(h) == 0) {
							fcn_005373e0(0, 0x20007);
						}
						fcn_004c4480(h);
					} else {
						fcn_00526120((char*) *(int*) 0x14ab324, 4);
					}
					break;
				}
			}
		} else if (g_14ce8e0 != 0) {
			*(int*) 0x774654 = 1;
		}
	}
	fcn_0052ae70();
	fcn_0052a2d0();
	fcn_00471e30(dlg);
	fcn_00532ef0();
}
