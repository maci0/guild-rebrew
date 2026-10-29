#include <string.h>

// SIZE 0xf8
typedef struct {
	char pad0[4];
	unsigned char type;
	char pad5[7];
	int owner;
	int key;
	char pad14[0x22];
	unsigned char flags;
	char pad37[0x21];
	int other;
	char pad5c[8];
	int extra;
	char pad68[0x90];
} Msg5c23b0;

extern unsigned char g_773d75;
extern int g_100f1dc;
extern unsigned short g_774970;
extern char g_7f4ca4[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
int __cdecl fcn_0050cf50(void*, int);
int __cdecl fcn_0050b710(int, unsigned char);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00519190(int, void*, int);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00472380(int, int, int, int);
void __cdecl fcn_00473a90(int, int);
int __cdecl fcn_005373e0(void*, int);
int __cdecl gm_SearchTable67(int);
int __cdecl fcn_00471f80(int);
int __cdecl fcn_0050b750(int, unsigned char);
void __cdecl fcn_004c5530(Msg5c23b0*);
int __cdecl fcn_00526120(int, int);
void __cdecl fcn_00471e30(int);

/* ADDRESS: GOLDTL 0x005c23b0 */
void __cdecl fcn_005c23b0(char* e)
{
	Msg5c23b0 m;
	int id;
	int x;
	int win;
	int p;
	int v;
	int h;
	int ret;

	id = *(int*) (e + 1);
	win = fcn_00470820(0, 0, "Panel\\Gebaeude_Verkaufen_pergament");
	fcn_00471b60(win);
	p = fcn_0050cf50(e, *(char*) (e + 0x5c));
	v = fcn_0050b710(p, g_773d75);
	d2_SetForm(win, 2);
	ret = *(unsigned short*) (g_773d75 * 0x2f4 + 0x8680b4);
	h = fcn_00472250(win, 2, fcn_00519190(0x17c5, e, ret * 2 + 0x9a8));
	fcn_00472380(h, (int) (x * 0.5), (int) (x * 1.5), v);
	fcn_00473a90(0, 0);
	fcn_005373e0(0, 0x677c7);
	do {
		ret = gm_SearchTable67(id);
		if ((*(unsigned char*) (e + 0x5b) & 4) || ret == 0) {
			*(int*) 0x774654 = 1;
		}
		if (*(int*) 0x14ce8e0 != 0) {
			*(int*) 0x774654 = 1;
		}
		if (g_100f1dc == 2) {
			memset(&m, 0, sizeof(m));
			m.type = 0x1b;
			m.owner = -1;
			m.flags = 2;
			m.other = id;
			m.key = *(int*) (g_7f4ca4 + g_774970 * 0x21c);
			m.extra = fcn_0050b750(fcn_00471f80(h), g_773d75);
			fcn_004c5530(&m);
			fcn_00526120(*(int*) 0x14ab238, 0);
			*(int*) 0x774654 = 1;
		}
		else if (g_100f1dc == 1) {
			*(int*) 0x774654 = 1;
		}
	} while (fcn_005373e0((void*) fcn_005c23b0, 0x677c7) != 0);
	fcn_00471e30(win);
}
