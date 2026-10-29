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
extern signed char g_6a3440;

Spec* __cdecl fcn_004b3c50(int op);
void __cdecl fcn_004b5630(Spec* s, int flags);
void __cdecl fcn_005448e0(void);
int __cdecl fcn_004b43f0(int n);
int __cdecl fcn_004b3e10(int a1, int a2, int a3);
int __cdecl fcn_004c5790(int, Req*);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00535960(void);
void __cdecl fcn_004b5b20(int flags);

/* ADDRESS: GOLDTL 0x004b62e0 */
void __cdecl fcn_004b62e0(int flags)
{
	int level;
	Req m;
	Ent* ent;
	Spec* s;
	int h;
	int i;
	int r;

	s = 0;
	level = -1;
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
	fcn_005448e0();
	r = fcn_004b43f0(level);
	if (r == 0) {
		g_6a3440 = -1;
		m.id = ent->x4;
		m.x10 = 0;
		h = fcn_004c5790(10, &m);
		while (fcn_004c4450(h) == 0) {
			fcn_00535960();
		}
	} else if (r == 0xff) {
		g_6a3440 = -1;
		m.id = ent->x4;
		m.x10 = 1;
		h = fcn_004c5790(10, &m);
		while (fcn_004c4450(h) == 0) {
			fcn_00535960();
		}
		fcn_004b5b20(flags);
	} else {
		fcn_004b3e10(ent->x4, r, 1);
		m.id = ent->x4;
		m.x10 = 0;
		h = fcn_004c5790(10, &m);
		while (fcn_004c4450(h) == 0) {
			fcn_00535960();
		}
	}
}
