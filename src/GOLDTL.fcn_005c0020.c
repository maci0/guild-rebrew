
#include <stdio.h>

extern int g_772514;
extern unsigned short g_774970;
extern int g_14ce8e0;
extern int g_774654;
extern int g_100f1dc;
extern int g_67d370;
extern char g_7f4ca0[];

typedef struct {
	int x0;
	int x4;
	char pad8[8];
	int x10;
	int x14;
	char pad18[0x14];
	int x2c;
	int x30;
	int x34;
} Rec38;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190();
void __cdecl fcn_0046e830(int, int, int, int, int);
int __cdecl fcn_004f61c0(int*, int*, int*, int);
char* __cdecl fcn_00508e40(int);
void __cdecl fcn_005ca560(Rec38*);
int __cdecl fcn_005ca740(int, int, int, int, Rec38*, int);
void __cdecl fcn_005c9160(char*, int, int, int, int);
void __cdecl fcn_00473a90(int, int);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005bfdf0(char*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00532ef0(void);

/* ADDRESS: GOLDTL 0x005c0020 */
void __cdecl fcn_005c0020(void)
{
	int v12[32];
	int v11[32];
	int v10[32];
	Rec38 recs[32];
	char buf[64];
	char* ent;
	char* p;
	Rec38* rec;
	int dlg;
	int i;
	int n;
	int count;
	int v;
	int sum;
	int y;
	int h2;

	ent = (char*) 0x7f4ca0 + g_774970 * 0x21c;
	dlg = fcn_00470820(0, 0, (char*) 0x6ac4f4);
	fcn_00471b60(dlg);
	fcn_004727a0(dlg, 1);
	fcn_00519190(0x173f);
	fcn_004727a0(dlg, 2);
	fcn_004727a0(dlg, 3);
	fcn_0046e830(-1, -1, g_772514, g_772514, 0x767);
	n = fcn_004f61c0(v12, v11, v10, *(unsigned short*) ent);
	count = 0;
	for (i = 0; i < n; i++) {
		p = fcn_00508e40(v12[i]);
		if (p != 0) {
			rec = &recs[count];
			rec->x0 = (int) p;
			rec->x2c = v10[i];
			rec->x34 = v11[i];
			fcn_005ca560(rec);
			rec->x30 = 1;
			count++;
		}
	}
	fcn_004727a0(dlg, 2);
	if (count != 0) {
		if (count > 0) {
			y = 10;
			for (i = 0; i < count; i++) {
				rec = &recs[i];
				sprintf(buf, (char*) 0x6ac4e8, rec->x2c, rec->x34,
				    (rec->x2c != 1) + 0x1748);
				rec->x10 = 0x32;
				rec->x14 = y;
				fcn_005ca740(0x32, y, g_772514, 0x56, rec, 1);
				fcn_005c9160(buf,
				    *(int*) (0x1015f4c + g_772514 * 0x3cc) - 0xf,
				    y + 0x2d, 200, 0x55);
				y += 0x69;
			}
		}
	}
	else {
		fcn_00519190(0x1741, g_774970);
	}
	fcn_00473a90(0, 0);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		else if (g_100f1dc != -1) {
			for (i = 0; i < count; i++) {
				if (g_67d370 == recs[i].x4) {
					fcn_005bfdf0((char*) 0x7f4ca0 + g_774970 * 0x21c,
					    recs[i].x0);
					break;
				}
			}
		}
	} while (fcn_005373e0((void*) fcn_005c0020, 0x657c7) != 0);
	fcn_00471e30(dlg);
	fcn_00532ef0();
}
