#include <string.h>

typedef struct Ent {
	unsigned short id;
	char pad2[2];
	int x4;
	char pad8[0x21c - 8];
} Ent;
// SIZE 0x21c

typedef struct Job {
	int op;
	int id;
	char pad8[0x1c];
} Job;
// SIZE 0x24

typedef struct Spec {
	int op;
	int level;
} Spec;

typedef struct Req {
	int id;
	int x4;
	int x8;
	int xc;
	int x10;
	char pad14[0x68];
} Req;
// SIZE 0x7c

extern char g_7f4ca0[];
extern unsigned short g_774970;
extern char g_10069a0[];
extern int g_67d370;
extern int g_100f1dc;
extern int g_774654;
extern signed char g_6a3440;

Spec* __cdecl fcn_004b3c50(int op);
void __cdecl fcn_004b5630(Spec* s, int flags);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
int __cdecl d2_SetForm(int k, int i);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_004c5790(int, Req*);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00535960(void);
void __cdecl fcn_00471e30(int);
int* __cdecl fcn_004b3d80(int a, int b, int c);
void __cdecl fcn_004b5530(int a1, int flags);
void __cdecl fcn_004b5b20(int flags);

/* ADDRESS: GOLDTL 0x004b5df0 */
void __cdecl fcn_004b5df0(int flags)
{
	int level;
	int b_ok;
	int done;
	int cancel;
	int b_back;
	int mode;
	int b_quit;
	Req m2;
	Req m1;
	Ent* ent;
	Spec* s;
	int dlg;
	int h;
	int* p;
	int i;

	b_ok = -1;
	level = -1;
	s = 0;
	done = 0;
	cancel = 0;
	ent = &((Ent*)g_7f4ca0)[g_774970];
	for (i = 0; i < 128; i++) {
		if (((Job*)g_10069a0)[i].op != 0 && ((Job*)g_10069a0)[i].id == ent->x4) {
			s = fcn_004b3c50(((Job*)g_10069a0)[i].op);
			level = s->level + 1;
			memset(&((Job*)g_10069a0)[i], 0, sizeof(Job));
			break;
		}
	}
	flags = (flags & ~9) | 0x100;
	fcn_004b5630(s, flags);
	dlg = fcn_00470820(0, 0, "special\\mission");
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 1);
	fcn_00519190(0x1b94, ent->id);
	if (level > -1 && level < 4) {
		b_ok = fcn_00472250(dlg, 1, fcn_00519190(0x1b96, 0x1b98));
	}
	b_back = fcn_00472250(dlg, 1, fcn_00519190(0x1b96, 0x1b99));
	b_quit = fcn_00472250(dlg, 1, fcn_00519190(0x1b96, 0x1b9a));
	g_100f1dc = -1;
	mode = flags | 0x80;
	do {
		if (g_100f1dc != -1) {
			if (g_67d370 == b_ok) {
				done = 1;
				g_774654 = 1;
			} else if (g_67d370 == b_back) {
				g_6a3440 = -1;
				m1.id = ent->x4;
				m1.x10 = 0;
				h = fcn_004c5790(10, &m1);
				while (fcn_004c4450(h) == 0) {
					fcn_00535960();
				}
				g_774654 = 1;
			} else if (g_67d370 == b_quit) {
				g_6a3440 = -1;
				m2.id = ent->x4;
				cancel = 1;
				m2.x10 = 1;
				h = fcn_004c5790(10, &m2);
				while (fcn_004c4450(h) == 0) {
					fcn_00535960();
				}
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0(fcn_004b5df0, mode) != 0);
	fcn_00471e30(dlg);
	if (done) {
		p = fcn_004b3d80(ent->x4, level, 1);
		m2.id = ent->x4;
		m2.x10 = 0;
		h = fcn_004c5790(10, &m2);
		while (fcn_004c4450(h) == 0) {
			fcn_00535960();
		}
		fcn_004b5530(*p, flags);
		return;
	}
	if (cancel) {
		fcn_004b5b20(flags);
	}
}
