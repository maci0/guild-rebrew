// FUNCTION: GOLD 0x005cc400
// FUNCTION: GOLDTL 0x005d86a0

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
extern char g_6b5c60[];
extern char s_6acdac[];
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;
extern int g_67d370;

unsigned short __cdecl fcn_0042e410(int);
unsigned char* __cdecl fcn_00508e40(int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_004c6ae0(int, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
unsigned char* __cdecl fcn_005cd440(Req*, char*, int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00525f60(unsigned char*, int);
void __cdecl fcn_00526120(char*, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005d86a0(unsigned char* e, unsigned char* a2)
{
	int result;
	int dlg;
	int cancel;
	int ok;
	Req req;
	char text[0x200];
	unsigned char* o1;
	unsigned char* o2;
	int a;
	int b;
	int id;

	if (e[2] != 6) {
		a = fcn_0042e410(0x28) + 0xf;
		b = fcn_0042e410(0x28) + 0xf;
		if (*(int*) (e + 0x194) < 3) {
			return 0x20;
		}
		o1 = fcn_00508e40(*(int*) (a2 + 0x214));
		if (o1 == 0) {
			return 0x60;
		}
		o2 = fcn_00508e40(*(int*) (a2 + 0x218));
		if (o2 == 0) {
			return 0x60;
		}
		fcn_004c54c0(*(int*) (o1 + 4), *(int*) (o2 + 4), a, 1);
		fcn_004c54c0(*(int*) (o2 + 4), *(int*) (o1 + 4), b, 1);
		fcn_004c6ae0(*(int*) (e + 4), -3);
		if (o1[2] == 6 || o1[2] == 7) {
			fcn_0051af00(text, 0x1de8, *(unsigned short*) o2, *(unsigned short*) e);
			fcn_00545d40(*(int*) (o1 + 4), *(int*) (o1 + 4), text, 0, 0x5ec, g_6b5c60);
		}
		if (o2[2] == 6 || o2[2] == 7) {
			fcn_0051af00(text, 0x1de8, *(unsigned short*) o1, *(unsigned short*) e);
			fcn_00545d40(*(int*) (o2 + 4), *(int*) (o2 + 4), text, 0, 0x5ec, g_6b5c60);
		}
		return 0x10;
	}
	result = 0;
	memset(&req, 0, sizeof(req));
	req.size = 0x400;
	req.kind = 6;
	req.cd = g_666018;
	fcn_0051af00(text, 0x1de4);
	o1 = fcn_005cd440(&req, text, 0, 0);
	if (o1 == 0) {
		return 0;
	}
	fcn_0051af00(text, 0x1de5, *(unsigned short*) o1);
	o2 = fcn_005cd440(&req, text, 0, 0);
	if (o2 == 0) {
		return 0;
	}
	dlg = fcn_00470820(0, 0, s_6acdac);
	fcn_00473a90(0, 0);
	fcn_00471b60(dlg);
	fcn_004727a0(dlg, 1);
	id = fcn_00519190(0x1de6, 3, *(unsigned short*) o1, *(unsigned short*) o2);
	ok = fcn_00472250(dlg, 1, id);
	cancel = fcn_00472250(dlg, 1, id + 1);
	g_100f1dc = -1;
	do {
		if (g_100f1dc != -1) {
			if (g_67d370 == ok) {
				if (fcn_00525f60(e, 3)) {
					a = fcn_0042e410(0x28) + 0xf;
					b = fcn_0042e410(0x28) + 0xf;
					fcn_004c54c0(*(int*) (o1 + 4), *(int*) (o2 + 4), a, 1);
					fcn_004c54c0(*(int*) (o2 + 4), *(int*) (o1 + 4), b, 1);
					fcn_004c6ae0(*(int*) (e + 4), -3);
					fcn_0051af00(text, 0x1de7, *(unsigned short*) o1, *(unsigned short*) o2);
					fcn_00526120(text, 0);
					if (o1[2] == 6 || o1[2] == 7) {
						fcn_0051af00(text, 0x1de8, *(unsigned short*) o2, *(unsigned short*) e);
						fcn_00545d40(*(int*) (o1 + 4), *(int*) (o1 + 4), text, 0, 0x5ec, 0);
					}
					if (o2[2] == 6 || o2[2] == 7) {
						fcn_0051af00(text, 0x1de8, *(unsigned short*) o1, *(unsigned short*) e);
						fcn_00545d40(*(int*) (o2 + 4), *(int*) (o2 + 4), text, 0, 0x5ec, 0);
					}
					g_774654 = 1;
					result = 1;
				}
			} else if (g_67d370 == cancel) {
				g_774654 = 1;
			}
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0((void*) fcn_005d86a0, 0x657c7) != 0);
	fcn_00471e30(dlg);
	return result;
}
