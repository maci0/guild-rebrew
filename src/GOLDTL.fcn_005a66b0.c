// FUNCTION: GOLDTL 0x005a66b0
// SIZE: 463

#include <string.h>
#pragma intrinsic(memset)

typedef struct {
	int pad0;
	int f4;
	char pad8[0x214];
} Ent5a66;
// SIZE 0x21c

typedef struct {
	char b[0x2f4];
} Row5a66;
// SIZE 0x2f4

extern char g_7f4ca0[];
extern char g_868060[];
extern char g_6aacdc[];
extern int g_14ce8e0;
extern int g_100f1dc;
extern int g_774654;
extern double g_665fb0;
extern unsigned char g_773d75;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_00508620(int, int);
void __cdecl fcn_004c51f0(int, int, int, int, unsigned char, int);
void __cdecl fcn_004c5530(char*);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005a66b0(char* who, int n, int w, unsigned char k)
{
	int res;
	int h;
	int a;
	int b;
	float fa;
	char msg[0xf8];

	res = 0;
	h = fcn_00470820(0, 0, g_6aacdc);
	fcn_00471b60(h);
	fcn_004727a0(h, 1);
	fcn_00519190(0x1909, w, n * 2 + 0x9a8, &((Row5a66*)g_868060)[k], k);
	if (fcn_005373e0(fcn_005a66b0, 0x677c7) != 0) {
		do {
			if (g_14ce8e0 != 0 || g_100f1dc == 1) {
				g_774654 = 1;
			}
			if (g_100f1dc == 2) {
				a = fcn_00508620(w, n);
				fa = (float) (a * g_665fb0);
				b = fcn_00508620(1, n);
				if (!((float) b < fa)) {
					b = fcn_00508620(1, n);
					fa = (float) b;
				}
				fcn_004c51f0(-1, *(int*) (who + 1), n, a, g_773d75, 0);
				memset(msg, 0, sizeof(msg));
				msg[4] = 0x27;
				*(int*) (msg + 0xc) = -1;
				msg[0x36] = 1;
				*(int*) (msg + 8) = ((Ent5a66*)g_7f4ca0)[*(unsigned short*) (who + 0x27)].f4;
				*(int*) (msg + 0x58) = *(int*) (who + 1);
				msg[0x5c] = k;
				*(int*) (msg + 0x60) = (int) (a - fa);
				fcn_004c5530(msg);
				res = 1;
				g_774654 = 1;
			} else if (g_100f1dc == 1) {
				g_774654 = 1;
			}
		} while (fcn_005373e0(fcn_005a66b0, 0x677c7) != 0);
	}
	fcn_00471e30(h);
	return res;
}
