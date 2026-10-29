


#include <string.h>

typedef struct
{
	int x0;
	int x4;
	__int64 mask;
	int x10;
	char pad14[0x3c];
} Query;
// SIZE 0x50

extern __int64 g_666018;
extern int g_14ac6a0;
extern int g_14acb40;
extern int g_100f1dc;
extern int g_67d370;
extern int g_774654;
extern int g_14ce8e0;

char* __cdecl fcn_00508e40(int);
void __cdecl fcn_005dab30(char*, char*);
void __cdecl fcn_00526120(int, int);
unsigned short* __cdecl fcn_005cd440(Query*, int, int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005dac90(char* e, char* o)
{
	Query q;
	int cancel;
	char* p;
	unsigned short* h;
	int dlg;
	int id;
	int ok;
	int r;

	if (e[2] != 6) {
		if (*(int*) (e + 0x1cc) & 0x80000) {
			return 0x20;
		}
		p = fcn_00508e40(*(int*) (o + 0x214));
		if (p == 0) {
			return 0x60;
		}
		if (p[0x166] == 0) {
			return 0x60;
		}
		fcn_005dab30(e, p);
		return 0x10;
	}
	r = 2;
	memset(&q, 0, sizeof(q));
	if (*(int*) (e + 0x1cc) & 0x80000) {
		fcn_00526120(g_14ac6a0, 0);
		return 0x81;
	}
	q.x10 = 6;
	q.x4 = 0xc00;
	q.mask = g_666018;
	h = fcn_005cd440(&q, g_14acb40, 0, 0);
	if (h == 0) {
		return 2;
	}
	dlg = fcn_00470820(0, 0, "privillegien\\verhoer");
	fcn_00473a90(0, 0);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 1);
	id = fcn_00519190(0x1e09, *h);
	ok = fcn_00472250(dlg, 1, id);
	cancel = fcn_00472250(dlg, 1, id + 1);
	g_100f1dc = -1;
	do {
		if (g_100f1dc != -1) {
			if (g_67d370 == ok) {
				fcn_005dab30(e, (char*) h);
				r = 0x91;
				g_774654 = 1;
			} else if (g_67d370 == cancel) {
				g_774654 = 1;
			}
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0((void*) fcn_005dac90, 0x657c7) != 0);
	fcn_00471e30(dlg);
	return r;
}
