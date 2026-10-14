

#include <string.h>

typedef struct
{
	void* x0;
	char pad4[0xc];
	int x10;
	int x14;
	char pad18[0x18];
	int x30;
	int x34;
} Item;
// SIZE 0x38

typedef struct
{
	char pad[0x21c];
} Player;
// SIZE 0x21c

extern char g_7f4ca0[];
extern char* g_77255c;
extern char* g_772500;
extern char* g_14a6554;
extern int g_772514;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;
extern char s_6ab048[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_005340f0(int);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_0050e670(int*, int*);
void __cdecl fcn_0046f2c0(int, int);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_005ca560(Item*);
void __cdecl fcn_005caaa0(int, int, int, Item*);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_005c91c0(char*, int, int, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00532ef0(void);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_005abd60(void)
{
	int dlg;
	int b[5];
	int a[5];
	int pb[5];
	int pa[5];
	char buf[0x200];
	Item items[5];
	int dirty;
	int i;
	int half;
	int x;
	int left;

	dlg = fcn_00470820(0, 0, s_6ab048);
	fcn_00471b60(dlg);
	fcn_004727a0(dlg, 0);
	fcn_005340f0(g_772514);
	fcn_00473a90(0, 0);
	dirty = 1;
	g_100f1dc = -1;
	do {
		fcn_0050e670(a, b);
		for (i = 0; i < 5; i++) {
			if (pa[i] != a[i] || pb[i] != b[i]) {
				dirty = 1;
			}
			pa[i] = a[i];
			pb[i] = b[i];
			items[i].x0 = 0;
			if (a[i] != 0xffff) {
				items[i].x0 = &((Player*)g_7f4ca0)[a[i]];
			}
		}
		if (dirty != 0) {
			fcn_004727a0(dlg, 1);
			fcn_0046f2c0(g_772514, 1);
			fcn_00519190(0x196b);
			half = *(int*) (g_77255c + 0xc) / 2;
			x = half - *(short*) (g_772500 + 0x1ebd8) - 0x87;
			left = half - 0x64;
			for (i = 0; i < 5; i++) {
				items[i].x14 = i * 0x4c + 0x2c;
				items[i].x10 = x;
				items[i].x30 = items[i].x0 != 0;
				fcn_005ca560(&items[i]);
				items[i].x30 = items[i].x0 != 0;
				fcn_005caaa0(items[i].x10, items[i].x14, g_772514, &items[i]);
				if (items[i].x0 != 0) {
					fcn_0051af00(buf, 0x196d, a[i]);
				}
				else {
					strcpy(buf, g_14a6554);
				}
				fcn_005c91c0(buf, left, i * 0x4c + 0x34, *(int*) (g_77255c + 0xc) - left + 0x14, 0x53);
				fcn_0051af00(buf, 0x196e, b[i]);
				fcn_005c91c0(buf, left, i * 0x4c + 0x4d, *(int*) (g_77255c + 0xc) - left + 0x14, 0x53);
			}
			dirty = 0;
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0((void*) fcn_005abd60, 0x677c7) != 0);
	fcn_00532ef0();
	fcn_00471e30(dlg);
}
