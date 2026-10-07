// FUNCTION: GOLDTL 0x005b4500

typedef struct
{
	char pad0[0x27c];
	int x27c;
	char pad280[0x14c];
} Win;
// SIZE 0x3cc

typedef struct
{
	unsigned short x0;
	char pad2[0x2e];
	char name[0x148];
	int x178;
	char pad17c[0xa0];
} Player;
// SIZE 0x21c

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char g_7f4ca0[];
extern int g_14ce8e0;
extern int g_774654;
extern int g_772514;
extern char s_6811b0[];
extern char s_6ab848[];
extern char s_6ab834[];
extern char s_6ab8fc[];

int __cdecl fcn_0046e940(int, int, int, int, int);
void __cdecl fcn_00472900(int, int);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_00519190(char*, ...);
char* __cdecl fcn_00502cd0(int, int, int);
char* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl fcn_005c61e0(int);
void __cdecl fcn_005b0f00(Win*);
void __cdecl fcn_0046f280(int);

void __cdecl fcn_005b4500(void)
{
	int w;
	Win* win;
	int i;
	char* e;
	int n;

	w = fcn_0046e940(0x20, 0x60, 0x280, 0x190, 0x414);
	fcn_00472900(((Win*)g_1015f40)[w].x27c, 0x54);
	if (fcn_005373e0((void*) fcn_005b4500, 0x657c7) != 0) {
		win = &((Win*)g_1015f40)[w];
		do {
			if (g_14ce8e0 != 0) {
				g_774654 = 1;
			}
			g_772514 = w;
			fcn_00519190(s_6811b0);
			for (i = 0; i < 768; i++) {
				if (((Player*)g_7f4ca0)[i].x0 != 0xffff) {
					n = 0;
					for (e = fcn_00502cd0(((Player*)g_7f4ca0)[i].x178, 1, 5); e != 0; e = gm_NextEntityQueryMatch()) {
						if (fcn_005c61e0(*(unsigned short*) e) != 0 && *(int*) (e + 0x21) != 0) {
							if (n == 0) {
								fcn_00519190(s_6ab848, ((Player*)g_7f4ca0)[i].name);
								fcn_00519190(s_6ab834);
							}
							n++;
							fcn_00519190(s_6ab8fc, *(unsigned short*) e * 2 + 0x9a8, *(int*) (e + 0x1c));
						}
					}
				}
			}
			fcn_005b0f00(win);
		} while (fcn_005373e0((void*) fcn_005b4500, 0x657c7) != 0);
	}
	fcn_0046f280(w);
}
