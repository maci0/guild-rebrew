// FUNCTION: GOLDTL 0x005d71f0
// SIZE: 979

#include <stdio.h>
#include <string.h>

#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

// SIZE 0xf8
struct msg {
	int f0;
	char b4;
	char pad5[3];
	int f8;
	int fc;
	char pad10[0x18];
	struct pos14 pos;
	char b36;
	char pad37[0x39];
	int f70;
	char pad74[0x84];
};

#pragma pack(2)
// SIZE 0xd6
typedef struct {
	char pad0[8];
	unsigned short w8;
	char pada[0x48];
	struct pos14 pos52;
	char pad60[0x10];
	int f70;
	char pad74[0x50];
	int fc4;
	struct pos14 posc8;
} Obj;
#pragma pack()

// SIZE 0x21c
typedef struct {
	int f0;
	int f4;
	char pad8[0x214];
} House;

extern struct pos14 g_7f4c00;
extern House g_7f4ca0[];
extern char s_6acd1c[];
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;
extern int g_67d370;

void __cdecl fcn_004c6ae0(int, int);
Obj* __cdecl fcn_005463a0(int, int, int);
Obj* __cdecl fcn_005462a0(void);
void __cdecl fcn_004c5620(int, Obj*);
void __cdecl fcn_004c5530(struct msg*);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00525f60(unsigned char*, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00526120(char*, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005d71f0(unsigned char* e)
{
	int cancel;
	int ok;
	int dlg;
	struct msg m;
	char text[0x200];
	int result;
	int found;
	int id;
	Obj* p;
	char* t;

	result = 2;
	if (e[2] != 6 && e[2] != 7) {
		if (*(int*) (e + 0x194) < 4) {
			return 0x20;
		}
		memset(&m, 0, sizeof(m));
		m.b4 = 0x18;
		m.f8 = *(int*) (e + 4);
		m.fc = *(int*) (e + 4);
		m.b36 = 2;
		m.pos = g_7f4c00;
		fcn_004c6ae0(*(int*) (e + 4), -4);
		for (p = fcn_005463a0(1, 0, 0x18); p != 0; p = fcn_005462a0()) {
			if (p->fc4 == *(int*) (e + 4)) {
				result |= 0x10;
				p->pos52 = g_7f4c00;
				p->posc8 = g_7f4c00;
				fcn_004c5620(p->f70, p);
				m.f70 = g_7f4ca0[p->w8].f4;
				fcn_004c5530(&m);
			}
		}
		return result;
	}
	dlg = fcn_00470820(0, 0, s_6acd1c);
	fcn_00473a90(0, 0);
	fcn_00471b60(dlg);
	fcn_004727a0(dlg, 1);
	id = fcn_00519190(0x1db7, 4);
	ok = fcn_00472250(dlg, 1, id);
	cancel = fcn_00472250(dlg, 1, id + 1);
	g_100f1dc = -1;
	do {
		if (g_100f1dc != -1) {
			if (g_67d370 == ok) {
				if (fcn_00525f60(e, 4)) {
					found = 0;
					fcn_0051af00(text, 0x1db8);
					t = text + strlen(text);
					memset(&m, 0, sizeof(m));
					m.b4 = 0x18;
					m.f8 = *(int*) (e + 4);
					m.fc = *(int*) (e + 4);
					m.b36 = 2;
					m.pos = g_7f4c00;
					fcn_004c6ae0(*(int*) (e + 4), -4);
					for (p = fcn_005463a0(1, 0, 0x18); p != 0; p = fcn_005462a0()) {
						if (p->fc4 == *(int*) (e + 4)) {
							p->pos52 = g_7f4c00;
							found |= 1;
							fcn_004c5620(0, p);
							m.f70 = g_7f4ca0[p->w8].f4;
							fcn_004c5530(&m);
							fcn_0051af00(t, 0x1db9, p->w8);
							t = text + strlen(text);
						}
					}
					if (!found) {
						fcn_0051af00(text, 0x1dba);
					}
					fcn_00526120(text, 0);
					g_774654 = 1;
				}
			} else if (g_67d370 == cancel) {
				g_774654 = 1;
			}
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0((void*) fcn_005d71f0, 0x657c7) != 0);
	fcn_00471e30(dlg);
	return 2;
}
