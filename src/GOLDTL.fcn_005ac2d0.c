#include <string.h>

#include "client_types.h"

#pragma pack(push, 1)
typedef struct tag7 {
	char a;
	char b;
	int id;
	char c;
} tag7;
#pragma pack(pop)
/* SIZE 0x7 */

/* packet body built for fcn_004c5530: church sermon (type 0x2b) */
typedef struct msg005ac2d0 {
	int f0;
	char b4;
	char pad5[3];
	int f8;
	int fc;
	char pad10[0x18];
	pos14_7f4c00 pos;
	char b36;
	char pad37[0x25];
	char b5c;
	char pad5d[0x9b];
} msg005ac2d0;
/* SIZE 0xf8 */

/* picture/text description passed to fcn_005ca560 and fcn_005ca740 */
typedef struct sel005ac2d0 {
	char* e;
	char pad4[0xc];
	int x;
	int y;
	char pad18[0x18];
	int f30;
	char pad34[4];
} sel005ac2d0;
/* SIZE 0x38 */

extern unsigned short g_774970;
extern char* g_773da8;
extern int g_772514;
extern char* g_772500;
extern char* g_77255c;
extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca0[];
extern char g_7f4ca4[];
extern char g_6811b0[];
extern int g_6b7fac;
extern int g_100f1dc;
extern int g_666018;
extern int g_66601c;

unsigned short* __cdecl fcn_00502cd0(int container, int count, int arg, int arg2);
char* __cdecl fcn_004c4480(int rc);
int __cdecl fcn_004c4450(int rc);
int __cdecl fcn_004c44c0(void);
int __cdecl fcn_004c3ff0(void);
int __cdecl fcn_004c4940(void);
void __cdecl cm_ExecCommand(void);
int __cdecl fcn_004c5b00(int entity_id, tag7 key);
int __cdecl fcn_004c5530(msg005ac2d0* m);
int __cdecl fcn_004c5360(void);
void __cdecl fcn_004c4510(char* base, int entity_id);
int __cdecl fcn_004c4570(unsigned char size, unsigned char count, unsigned short off, char* src);
char* __cdecl fcn_005463a0(int kind, int first, int id, int arg, int entity_id);
char* __cdecl fcn_00508e40(int description_id);
int __cdecl fcn_00470820(int x, int y, char* title);
int __cdecl fcn_00473a90(int a1, int a2);
void __cdecl fcn_00471b60(int dlg);
void __cdecl fcn_00471e30(int dlg);
void __cdecl fcn_004727a0(int dlg, int page);
int __cdecl fcn_00472250(int dlg, int page, int id);
void __cdecl fcn_00472640(int button, int state);
int __cdecl fcn_0046f2c0(int win, int keep);
void __cdecl fcn_005340f0(int win);
int __cdecl fcn_00519190(int id, ...);
int __cdecl fcn_005373e0(void* fn, int msg);
int __cdecl fcn_00525f60(char* house, int mode);
void __cdecl fcn_005100f0(int id, int amount);
int __cdecl fcn_005ca560(sel005ac2d0* sel);
int __cdecl fcn_005ca740(int x, int y, int win, int id, sel005ac2d0* sel, int flag);
int __cdecl fcn_0051af00(char* buf, int id, ...);
char* __cdecl fcn_005cd440(void* m, char* text, int a2, int a3);
int __cdecl gm_RandomMod(unsigned short range);
void __cdecl fcn_00532ef0(void);

/* ADDRESS: GOLDTL 0x005ac2d0 */
void __cdecl fcn_005ac2d0(char* a0)
{
	msg005ac2d0 pkt;
	char text[0x20];
	char pkt2[0x50];
	sel005ac2d0 sel;
	int prev;
	int btnState2;
	int btnState1;
	int btnState0;
	char* info;
	int btnCancel;
	char* unit;
	char v16;
	char v15;
	char v18;
	int state;
	char v12;
	int flag;
	char* obj;
	int rc;
	int dlg;
	int i;

	btnState1 = 0;
	btnState2 = 0;
	btnCancel = 0;
	btnState0 = 0;
	if (a0 == 0) {
		return;
	}
	if (*(unsigned short*) (a0 + 0x27) == 0xffff) {
		return;
	}
	if (*(unsigned short*) (a0 + 0x27) != g_774970) {
		return;
	}
	obj = (char*) fcn_00502cd0(*(int*) (a0 + 0x5d), 1, 0, 0x1b5);
	if (obj == 0) {
		tag7 t;

		t.a = -1;
		t.b = -1;
		t.id = -1;
		obj = fcn_004c4480(fcn_004c5b00(*(int*) (a0 + 1), t));
		while (fcn_004c44c0() == 0) {
			fcn_004c3ff0();
			fcn_004c4940();
			cm_ExecCommand();
		}
	}
	unit = fcn_005463a0(2, 0, 0x2b, 3, *(int*) (a0 + 1));
	if (unit == 0) {
		pkt.pos = g_7f4c00;
		pkt.b4 = 0x2b;
		pkt.b36 = 2;
		pkt.f8 = *(int*) (g_773da8 + 4);
		pkt.fc = *(int*) (a0 + 1);
		pkt.b5c = 0;
		rc = fcn_004c5530(&pkt);
		if (rc != -1) {
			while (fcn_004c4450(rc) == 0) {
				fcn_005373e0((void*) 0, 0x677c7);
			}
		}
		unit = fcn_004c4480(rc);
	}
	info = 0;
	if (*(char*) (obj + 0x22) == 0) {
		state = 0;
	} else if (*(char*) (obj + 0x1c) == -1 || *(char*) (obj + 0x1d) == -1) {
		state = 1;
	} else {
		info = fcn_00508e40(*(int*) (obj + 0x1e));
		state = 2;
		if (info == 0) {
			state = 1;
		}
	}
	dlg = fcn_00470820(0, 0, "Locations\\Kirche\\Predigt");
	fcn_00473a90(0, 0);
	fcn_00471b60(dlg);
	fcn_004727a0(dlg, 0);
	fcn_005340f0(g_772514);
	flag = 1;
	g_100f1dc = -1;
	prev = g_6b7fac;
	do {
		if ((unsigned int) (g_6b7fac - prev) > 0x64 && state != 3) {
			flag = 1;
			prev = g_6b7fac;
			obj = (char*) fcn_00502cd0(*(int*) (a0 + 0x5d), 1, 0, 0x1b5);
			if (obj == 0 || *(unsigned short*) (a0 + 0x27) != g_774970) {
				state = 3;
				flag = 0;
				goto post;
			}
			if (*(char*) (obj + 0x22) == 0) {
				state = 0;
			} else if (*(char*) (obj + 0x1c) != -1 && *(char*) (obj + 0x1d) != -1
			    && *(int*) (obj + 0x1e) != -1) {
				info = fcn_00508e40(*(int*) (obj + 0x1e));
				state = (info != 0) + 1;
			}
		} else if (flag == 0) {
			goto post;
		}
		if (state == 3) {
			goto post;
		}
		btnState0 = -1;
		btnState2 = -1;
		btnState1 = -1;
		btnCancel = -1;
		if (state == 0) {
			fcn_004727a0(dlg, 1);
			fcn_00519190((int) g_6811b0);
			fcn_00519190(0x19a5, 1, unit + 0x52);
			fcn_004727a0(dlg, 2);
			fcn_00519190((int) g_6811b0);
			i = fcn_00519190(0x19a6);
			btnState0 = fcn_00472250(dlg, 2, i);
			btnCancel = fcn_00472250(dlg, 2, i + 1);
		} else if (state == 1) {
			fcn_004727a0(dlg, 1);
			fcn_0046f2c0(g_772514, 1);
			fcn_00519190((int) g_6811b0);
			fcn_00519190(0x19a0, unit + 0x52);
			fcn_004727a0(dlg, 2);
			fcn_0046f2c0(g_772514, 1);
			fcn_00519190((int) g_6811b0);
			i = fcn_00519190(0x19a1);
			btnState1 = fcn_00472250(dlg, 2, i);
			btnCancel = fcn_00472250(dlg, 2, i + 1);
			if (*(int*) (unit + 0x70) > 0) {
				fcn_00472640(btnState1, 0);
			} else {
				fcn_00472640(btnState1, 1);
			}
		} else if (state == 2) {
			fcn_004727a0(dlg, 1);
			fcn_0046f2c0(g_772514, 1);
			fcn_00519190((int) g_6811b0);
			fcn_00519190(0x198e, unit + 0x52, *(char*) (obj + 0x1c) + 0x1990,
			    *(char*) (obj + 0x1d) + 0x1998, *(unsigned short*) info);
			sel.e = info;
			sel.x = *(int*) (g_77255c + 0xc) / 2 - *(short*) (g_772500 + 0x1ebd8) / 2;
			sel.y = 0xc3;
			sel.f30 = 1;
			fcn_005ca560(&sel);
			fcn_005ca740(sel.x, sel.y, g_772514, 0x54, &sel, 1);
			fcn_004727a0(dlg, 2);
			fcn_0046f2c0(g_772514, 1);
			fcn_00519190((int) g_6811b0);
			i = fcn_00519190(0x198f);
			btnState2 = fcn_00472250(dlg, 2, i);
			btnCancel = fcn_00472250(dlg, 2, i + 1);
			if (*(int*) (unit + 0x70) > 0) {
				fcn_00472640(btnState2, 0);
			} else {
				fcn_00472640(btnState2, 1);
			}
		}
		flag = 0;
	post:
		if (*(int*) 0x14ce8e0 != 0 || state == 3) {
			*(int*) 0x774654 = 1;
		} else if (g_100f1dc != -1) {
			if (*(int*) 0x67d370 == btnState0) {
				if (fcn_00525f60(g_7f4ca0 + g_774970 * 0x21c, 1) != 0) {
					v12 = 1;
					fcn_005100f0(*(int*) (g_7f4ca4 + g_774970 * 0x21c), -1);
					fcn_004c4510(obj, *(int*) (obj + 2));
					fcn_004c4570(1, 1, 0x22, &v12);
					rc = fcn_004c5360();
					flag = 1;
					state = 1;
					if (rc != -1) {
						while (fcn_004c4450(rc) == 0) {
							fcn_005373e0((void*) 0, 0x677c7);
						}
					}
				}
			} else if (*(int*) 0x67d370 == btnState1) {
				memset(pkt2, 0, 0x50);
				*(int*) (pkt2 + 4) = 0x400;
				*(int*) (pkt2 + 0x10) = 6;
				*(int*) (pkt2 + 8) = g_666018;
				*(int*) (pkt2 + 0xc) = g_66601c;
				fcn_0051af00(text, 0x19a2);
				info = fcn_005cd440(pkt2, text, 0, 0);
				obj = (char*) fcn_00502cd0(*(int*) (a0 + 0x5d), 1, 0, 0x1b5);
				if (info != 0 && *(int*) (info + 4) != -1 && obj != 0) {
					v15 = (char) gm_RandomMod(8);
					v16 = (char) gm_RandomMod(8);
					fcn_004c4510(obj, *(int*) (obj + 2));
					fcn_004c4570(4, 1, 0x1e, info + 4);
					fcn_004c5360();
					fcn_004c4510(obj, *(int*) (obj + 2));
					fcn_004c4570(1, 1, 0x1c, &v15);
					fcn_004c5360();
					fcn_004c4510(obj, *(int*) (obj + 2));
					fcn_004c4570(1, 1, 0x1d, &v16);
					rc = fcn_004c5360();
					state = 2;
					flag = 1;
					if (rc != -1) {
						while (fcn_004c4450(rc) == 0) {
							fcn_005373e0((void*) 0, 0x677c7);
						}
					}
				}
			} else if (*(int*) 0x67d370 == btnState2) {
				int id;

				v12 = -1;
				v18 = -1;
				id = -1;
				fcn_004c4510(obj, *(int*) (obj + 2));
				fcn_004c4570(4, 1, 0x1e, (char*) &id);
				fcn_004c5360();
				fcn_004c4510(obj, *(int*) (obj + 2));
				fcn_004c4570(1, 1, 0x1c, &v12);
				fcn_004c5360();
				fcn_004c4510(obj, *(int*) (obj + 2));
				fcn_004c4570(1, 1, 0x1d, &v18);
				rc = fcn_004c5360();
				flag = 1;
				state = 1;
				if (rc != -1) {
					while (fcn_004c4450(rc) == 0) {
						fcn_005373e0((void*) 0, 0x677c7);
					}
				}
			} else if (*(int*) 0x67d370 == btnCancel) {
				*(int*) 0x774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) fcn_005ac2d0, 0x677c7) != 0);
	fcn_00471e30(dlg);
	fcn_00532ef0();
}
