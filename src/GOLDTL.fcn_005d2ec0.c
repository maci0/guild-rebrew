typedef struct
{
	char* e;
	int btn;
	char pad8[8];
	int x;
	int y;
	char pad18[0x14];
	int val;
	int flag;
	char pad34[4];
} Item;
/* SIZE 0x38 */

extern char* g_772500;
extern char* g_77255c;
extern char g_7f4ca0[];
extern unsigned short g_774970;
extern int g_772514;
extern int g_67d370;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_14ce8d8;
extern int g_774654;

int __cdecl fcn_005d28e0(char*, int*, int*);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
int __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
char* __cdecl fcn_00508e40(int);
int __cdecl fcn_005ca560(Item*);
int __cdecl fcn_005d2a40(int, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_005ca740(int, int, int, int, Item*, int);
void __cdecl fcn_005c9090(int, int, int, int, int);
int __cdecl fcn_005d2d30(unsigned short*);
void __cdecl fcn_00471a30(int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

/* ADDRESS: GOLDTL 0x005d2ec0 */
int __cdecl fcn_005d2ec0(char* a0)
{
	int count;
	int res;
	int dlg;
	int off;
	int ids[9];
	char buf[0x80];
	Item items[9];
	int w;
	int i;

	res = 2;
	fcn_005d28e0(a0, &count, ids);
	dlg = fcn_00470820(0, 0, (char*) 0x6acbd4);
	fcn_00471b60(dlg);
	fcn_004727a0(dlg, 1);
	fcn_00519190(0x1ce3);
	fcn_004727a0(dlg, 2);
	w = (((int*) g_77255c)[3] - *(short*) (g_772500 + 0x1ebd8) * 3) / 4;
	off = (((int*) g_77255c)[3] - *(short*) (g_772500 + 0x1ebd8) * 3) % 4 / 2;
	for (i = 0; i < count; i++) {
		items[i].x = off + (*(short*) (g_772500 + 0x1ebd8) + 10) * (i % 3) + (i % 3 + 1) * w - 10;
		items[i].y = i / 3 * 0x41 * 2 + 5;
		items[i].e = fcn_00508e40(ids[i]);
		items[i].flag = 1;
		fcn_005ca560(&items[i]);
		items[i].val = fcn_005d2a40(*(int*) (g_7f4ca0 + g_774970 * 540 + 4), *(int*) (items[i].e + 4));
		fcn_0051af00(buf, 0x1ce4, items[i].val);
		fcn_005ca740(items[i].x, items[i].y, g_772514, 0x56, &items[i], 1);
		fcn_005c9090((int) buf, items[i].x + *(short*) (g_772500 + 0x1ebd8) / 2,
		             *(short*) (g_772500 + 0x1ebda) + items[i].y + 0x2b, 0xca, 0x56);
	}
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		else if (g_100f1dc != -1 && g_14ce8d8 != 0) {
			for (i = 0; i < count; i++) {
				if (items[i].btn == g_67d370) {
					fcn_00471a30(dlg, 0);
					if (fcn_005d2d30((unsigned short*) items[i].e) != 0) {
						res = 0x92;
						g_774654 = 1;
						break;
					}
					fcn_00471a30(dlg, 1);
				}
			}
		}
	} while (fcn_005373e0((void*) fcn_005d2ec0, 0x657c7) != 0);
	fcn_00471e30(dlg);
	return res;
}
