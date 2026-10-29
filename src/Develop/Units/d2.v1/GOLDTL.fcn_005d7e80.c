


#include <string.h>

// SIZE 0x50
typedef struct {
	int a;
	int size;
	__int64 cd;
	int kind;
	int pad14[15];
} Req;

extern __int64 g_666018;
extern char s_6acd74[];
extern char s_6a59fc[];
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;
extern int g_67d370;

unsigned char* __cdecl fcn_00508e40(int);
void __cdecl fcn_004c6ae0(int, int);
int __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
void __cdecl fcn_00526120(char*, int);
unsigned char* __cdecl fcn_005cd440(Req*, char*, int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00525f60(unsigned char*, int);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00535960(void);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005d7e80(unsigned char* e, unsigned char* a2)
{
	int result;
	int cancel;
	int ok;
	Req req;
	char text[0x200];
	unsigned char* o;
	int dlg;
	int id;
	int h;

	if (e[2] != 6) {
		if (*(int*) (e + 0x194) < 2) {
			return 0x20;
		}
		if (*(int*) (e + 0x1c8) & 0x8000) {
			return 0x20;
		}
		o = fcn_00508e40(*(int*) (a2 + 0x214));
		if (o == 0) {
			return 0x60;
		}
		fcn_004c6ae0(*(int*) (e + 4), -2);
		fcn_004c6ae0(*(int*) (o + 4), -3);
		fcn_004c5420(*(int*) (e + 4), 0x1c8, 4, 0x8000, 0);
		if (o[2] == 6 || o[2] == 7) {
			fcn_0051af00(text, 0x1dda, *(unsigned short*) e, 3);
			fcn_00545d40(*(int*) (o + 4), *(int*) (o + 4), text, 0, 0x5fb, s_6a59fc);
		}
		return 0x10;
	}
	result = 2;
	memset(&req, 0, sizeof(req));
	if (*(int*) (e + 0x1c8) & 0x8000) {
		fcn_0051af00(text, 0x1ce0);
		fcn_00526120(text, 0);
		return 0x81;
	}
	req.size = 0x400;
	req.kind = 6;
	req.cd = g_666018;
	fcn_0051af00(text, 0x1dd7);
	o = fcn_005cd440(&req, text, 0, 0);
	if (o == 0) {
		return 2;
	}
	dlg = fcn_00470820(0, 0, s_6acd74);
	fcn_00473a90(0, 0);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 1);
	id = fcn_00519190(0x1dd8, 2, *(unsigned short*) o, *(unsigned short*) o, 3, 2);
	ok = fcn_00472250(dlg, 1, id);
	cancel = fcn_00472250(dlg, 1, id + 1);
	g_100f1dc = -1;
	do {
		if (g_100f1dc != -1) {
			if (g_67d370 == ok) {
				if (fcn_00525f60(e, 2)) {
					fcn_004c6ae0(*(int*) (e + 4), -2);
					fcn_004c6ae0(*(int*) (o + 4), -3);
					h = fcn_004c5420(*(int*) (e + 4), 0x1c8, 4, 0x8000, 0);
					while (fcn_004c4450(h) == 0) {
						fcn_00535960();
					}
					fcn_0051af00(text, 0x1dd9, *(unsigned short*) o, *(unsigned short*) o, 3,
						*(unsigned short*) o, 3);
					fcn_00526120(text, 0);
					if (o[2] == 6 || o[2] == 7) {
						fcn_0051af00(text, 0x1dda, *(unsigned short*) e, 3);
						fcn_00545d40(*(int*) (o + 4), *(int*) (o + 4), text, 0, 0x5fb, s_6a59fc);
					}
					g_774654 = 1;
					result = 0x81;
				}
			} else if (g_67d370 == cancel) {
				g_774654 = 1;
			}
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0((void*) fcn_005d7e80, 0x657c7) != 0);
	fcn_00471e30(dlg);
	return result;
}
