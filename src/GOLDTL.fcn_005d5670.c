// FUNCTION: GOLDTL 0x005d5670

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
	char pad60[0x98];
};

extern pos14_7f4c00 g_7f4c00;
extern char s_6acc74[];
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;

int __cdecl fcn_004f6470(int, char*, unsigned short);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
unsigned short __cdecl fcn_0042e410(int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
int __cdecl fcn_004c5530(struct msg*);
int __cdecl fcn_004c4450(int);
char* __cdecl fcn_004c4480(int);
void __cdecl fcn_00535960(void);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00526120(char*, int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_004c6ae0(int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005d5670(unsigned char* e, unsigned char* o)
{
	int chance;
	int dlg;
	pos14_7f4c00 pos;
	struct msg m;
	char text[0x100];
	char buf[0x80];
	int result;
	int h;
	char* p;

	if (e == 0 || o == 0) {
		return 0;
	}
	if (e[2] != 6 && e[2] != 7) {
		return 0;
	}
	chance = fcn_004f6470(*(int*) (o + 4), buf, *(unsigned short*) e);
	dlg = fcn_00470820(0, 0, s_6acc74);
	fcn_00473a90(0, 0);
	fcn_00471b60(dlg);
	fcn_004727a0(dlg, 1);
	fcn_00519190(0x1d57, *(unsigned short*) o, *(unsigned short*) o, *(unsigned short*) o,
		*(unsigned short*) o, 2);
	fcn_00519190(0x1d58);
	g_100f1dc = -1;
	result = 0;
	do {
		if (g_100f1dc != -1) {
			if (g_100f1dc == 2) {
				if (chance >= fcn_0042e410(8)) {
					pos = g_7f4c00;
					fcn_00500bb0(&pos, 0x60, 0, 0);
					memset(&m, 0, sizeof(m));
					m.b4 = 0x45;
					m.b36 = 2;
					m.f8 = *(int*) (e + 4);
					m.pos = g_7f4c00;
					m.fc = *(int*) (e + 4);
					m.f58 = *(int*) (e + 4);
					m.f5c = *(int*) (o + 4);
					h = fcn_004c5530(&m);
					while (h != -1 && fcn_004c4450(h) == 0) {
						fcn_00535960();
					}
					p = fcn_004c4480(h);
					while (!(*(int*) (e + 0x1c8) & 0x100) && *(int*) (p + 0x70) != -1) {
						fcn_00535960();
					}
					if (*(int*) (e + 0x1c8) & 0x100) {
						fcn_0051af00(text, 0x1d5a, *(unsigned short*) o, &pos);
						fcn_00526120(text, 0);
					}
					result = 1;
					g_774654 = 1;
				} else {
					fcn_004c54c0(*(int*) (e + 4), *(int*) (o + 4), -0x1a, 1);
					fcn_004c6ae0(*(int*) (e + 4), -2);
					fcn_0051af00(text, 0x1d59, *(unsigned short*) o);
					fcn_00526120(text, 0);
					result = 0;
					g_774654 = 1;
				}
			} else if (g_100f1dc == 1) {
				result = 0;
				g_774654 = 1;
			}
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0((void*) fcn_005d5670, 0x657c7) != 0);
	fcn_00471e30(dlg);
	return result;
}
