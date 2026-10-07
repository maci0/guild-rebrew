// FUNCTION: GOLDTL 0x005d5d70

#include <string.h>

// SIZE 0xf8
#include "client_types.h"
struct msg {
	int f0;
	char b4;
	char pad5[3];
	int f8;
	int fc;
	char pad10[0x18];
	pos14_7f4c00 pos;
	char b36;
	char pad37[0x21];
	int f58;
	int f5c;
	unsigned short w60;
	unsigned short w62;
	char pad64[0x94];
};

// SIZE 0x21c
typedef struct {
	int f0;
	int f4;
	char pad8[0x214];
} House;

extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca0[];
extern unsigned short g_774970;
extern char s_6ac494[];
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;

void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00526120(char*, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_005c9220(int*);
int __cdecl fcn_00525f60(House*, int);
unsigned short __cdecl fcn_0042e410(int);
int __cdecl fcn_004c5530(struct msg*);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00535960(void);
void __cdecl fcn_004c6ae0(int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005d5d70(unsigned char* e)
{
	int dlg;
	char text[0x100];
	int result;
	int kind;
	unsigned short a;
	unsigned short b;
	int h;

	result = 0;
	if (*(int*) (e + 0x1c8) & 0x400) {
		fcn_0051af00(text, 0x1d7f, *(unsigned short*) e);
		fcn_00526120(text, 0);
		return 0;
	}
	kind = (e[9] != 0) + 0x1d68;
	dlg = fcn_00470820(0, 0, s_6ac494);
	fcn_00473a90(0, 0);
	fcn_00471b60(dlg);
	fcn_004727a0(dlg, 1);
	fcn_00519190(0x1d67, *(unsigned short*) e, 2, *(unsigned short*) e, kind, *(unsigned short*) e);
	{
		int arr[6];

		memset(arr, 0xff, sizeof(arr));
		arr[0] = dlg;
		arr[1] = 2;
		arr[2] = 3;
		arr[3] = 4;
		arr[4] = 4;
		arr[5] = 4;
		fcn_005c9220(arr);
	}
	g_100f1dc = -1;
	do {
		if (g_100f1dc != -1) {
			if (g_100f1dc == 2) {
				if (fcn_00525f60(&((House*)g_7f4ca0)[g_774970], 2)) {
					struct msg m;

					a = fcn_0042e410(9) + 0x1d76;
					b = fcn_0042e410(9) + 0x1d6d;
					memset(&m, 0, sizeof(m));
					m.f8 = ((House*)g_7f4ca0)[g_774970].f4;
					m.pos = g_7f4c00;
					m.b4 = 0x47;
					m.b36 = 2;
					m.w60 = b;
					m.w62 = a;
					m.f5c = *(int*) (e + 4);
					m.fc = ((House*)g_7f4ca0)[g_774970].f4;
					m.f58 = ((House*)g_7f4ca0)[g_774970].f4;
					h = fcn_004c5530(&m);
					while (fcn_004c4450(h) == 0) {
						fcn_00535960();
					}
					fcn_004c6ae0(((House*)g_7f4ca0)[g_774970].f4, -2);
					fcn_0051af00(text, 0x1d6a, b, *(unsigned short*) e, a);
					fcn_00526120(text, 0);
					g_774654 = 3;
					result = 1;
				}
			} else if (g_100f1dc == 1) {
				g_774654 = 2;
			}
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0((void*) fcn_005d5d70, 0x657c7) != 0);
	fcn_00471e30(dlg);
	return result;
}
