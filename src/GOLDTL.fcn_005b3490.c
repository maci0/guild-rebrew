// FUNCTION: GOLDTL 0x005b3490
// SIZE: 455

#include <string.h>

typedef struct
{
	char pad0[0x27c];
	int x27c;
	char pad280[0x14c];
} Win;
// SIZE 0x3cc

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern int g_67a370;
extern int g_775280;
extern char* g_778b20[];
extern int g_772514;
extern int g_14ce8e0;
extern int g_774654;
extern char s_6ab5f8[];
extern char s_6ab5cc[];
extern char s_6ab588[];

int __cdecl fcn_0046e940(int, int, int, int, int);
void __cdecl fcn_00472900(int, int);
void __cdecl fcn_004379a0(char*, int, int, void*, int);
int __cdecl fcn_00519190(char*, ...);
void __cdecl fcn_00455350(char*, char*, float*);
char __cdecl fcn_0045b990(char*, float*, int*, int*, int*);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_005b0f00(Win*);
void __cdecl fcn_0046f280(int);
void __cdecl fcn_005b3460(void);

void __cdecl fcn_005b3490(void)
{
	int w;
	int x;
	int y;
	int z;
	float v[4];
	char buf[0x80];
	int i;
	char* map;
	char* e;
	int c;
	Win* win;

	w = fcn_0046e940(0x20, 0x60, 0x280, 0x190, 0x414);
	fcn_00472900(((Win*)g_1015f40)[w].x27c, 0x54);
	g_775280 = 0;
	fcn_004379a0(((char*)g_67a370), 0, 0x100, (void*) fcn_005b3460, 0);
	fcn_00519190(s_6ab5f8);
	fcn_00519190(s_6ab5cc);
	for (i = 0; i < g_775280; i++) {
		memset(buf, 0, sizeof(buf));
		g_772514 = w;
		map = *(char**) (((char*)g_67a370) + 0xb0);
		e = g_778b20[i];
		fcn_00455350(e, e + 0x4c, v);
		if (map != 0 && fcn_0045b990(map, v, &x, &y, &z)) {
			c = *(int*) (*(char**) (map + 0x24) + (*(int*) (map + 0x20) * y + x) * 28);
			if (c == 0 || c == 10) {
				strcat(buf, "smap-pos is blocked  ");
			}
		}
		else {
			strcat(buf, "No smap or pos out of range  ");
		}
		fcn_00519190(s_6ab588, g_778b20[i], buf);
	}
	if (fcn_005373e0((void*) fcn_005b3490, 0x657c7) != 0) {
		win = &((Win*)g_1015f40)[w];
		do {
			if (g_14ce8e0 != 0) {
				g_774654 = 1;
			}
			fcn_005b0f00(win);
		} while (fcn_005373e0((void*) fcn_005b3490, 0x657c7) != 0);
	}
	fcn_0046f280(w);
}
