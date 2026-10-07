// FUNCTION: GOLDTL 0x005e0930

#include <string.h>

// SIZE 0x220
typedef struct {
	int f0;
	int id;
	int slot;
	unsigned char used;
	char padd[0xc];
	char name[0x207];
} SaveItem;

extern int g_7e46ac;
extern int g_772514;
extern int g_14ce8e0;
extern int g_14ce8d8;
extern int g_774654;
extern int g_100f894;
extern char* g_1015ea0;
#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern int g_67d370;
extern char g_774964;
extern int g_14ac644;
extern char g_7e21a0[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471db0(int, int);
void __cdecl fcn_00471d80(int, int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_005340f0(int);
void __cdecl fcn_00473a90(int, int);
int __cdecl fcn_00519190(int);
int __cdecl fcn_00472830(int, int);
void __cdecl fcn_00533f40(int, int, int, int, int, int*, int*, int*);
void __cdecl fcn_005e0140(int, int, SaveItem*, char*, char*, int);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005dfe80(int, unsigned int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005e0930(void)
{
	int result;
	int style;
	int h;
	int c;
	int a;
	int b;
	SaveItem items[16];
	char buf[0x4200];
	int i;

	result = 0;
	style = g_7e46ac;
	h = fcn_00470820(0, 0, "menu\\loadgame_new");
	fcn_00471db0(h, 1);
	fcn_00471d80(h, 2);
	fcn_004727a0(h, 0);
	fcn_005340f0(g_772514);
	fcn_00473a90(0, 0);
	fcn_004727a0(0, 2);
	fcn_00519190(0x1c57);
	fcn_004727a0(0, 0);
	fcn_00533f40(0x214, 0x168, g_772514, fcn_00472830(h, 1), 0x82, &a, &b, &c);
	fcn_005e0140(h, 1, items, buf, "gamedata/network", 1);
	while (fcn_005373e0(fcn_005e0930, style) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_14ce8d8 != 0) {
			for (i = 0; i < 16; i++) {
				if (items[i].used != 0 && items[i].slot != -1
				    && (g_67d370 == items[i].id || g_100f894 == items[i].slot
				        || (g_100f894 != -1
				            && *(char**) (g_1015ea0
				                   + *(int*) (((char*)g_1015f40) + g_100f894 * 0x3cc + 0x27c) * 0x2f4 + 0x40)
				                == ((char*)g_1015f40) + items[i].slot * 0x3cc))) {
					goto found;
				}
			}
			continue;
found:
			if (g_774964 == 0 || fcn_005dfe80(g_14ac644, 0x101) != 0) {
				strcpy(g_7e21a0, items[i].name);
				g_774654 = 1;
				result = 1;
			}
		}
	}
	fcn_00471e30(h);
	return result;
}
