#include "Develop/DieGildeAddOn/game/spiel.h"
// FUNCTION: GOLD 0x0057f950
// FUNCTION: GOLDTL 0x588000

// SIZE 0x10
struct offer {
	int id;
	int pad4;
	int kind;
	float val;
};

// SIZE 0x38
struct deal {
	int state;
	int pad4;
	struct offer e[3];
};

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x214];
};

extern char g_7f4ca0[];
extern char g_77dda0[];
extern char* g_773da8;
extern int g_774a1c;
extern int g_6b7fac;

void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_00471af0(int, int);

int __cdecl fcn_00519190(int, ...);

void __cdecl fcn_00588000(char* w)
{
	int i;
	int cnt;
	char* o;
	int j;
	int msg;

	cnt = 0;
	if (*(unsigned int*) (w + 0x70) + 0x15e > (*(volatile unsigned int*)&g_6b7fac)) {
		return;
	}
	*(unsigned int*) (w + 0x70) = (*(volatile unsigned int*)&g_6b7fac);
	fcn_004727a0(*(int*) (w + 0x74), 0);
	for (i = 0; i < 3; i++) {
		if (((struct deal*)g_77dda0)[i].state != i) {
			continue;
		}
		g_774a1c = 1;
		for (j = 0; j < 3; j++) {
			gm_ResolveEntityById((void**) (&o), 0, 0, ((struct deal*)g_77dda0)[i].e[j].id);
			if (o == 0) {
				break;
			}
			msg = 0x4071;
			if (((struct deal*)g_77dda0)[i].e[j].kind == 1) {
				msg = 0x4073;
				if (!(((struct deal*)g_77dda0)[i].e[j].val > 25.0f)) {
					msg = 0x4072;
				}
			}
			if (j != 0) {
				fcn_00519190((int) "$A");
			} else {
				fcn_00519190((int) "$C");
			}
			if (*(unsigned short*) (o + 0x27) != 0xffff && &((struct house*)g_7f4ca0)[*(unsigned short*) (o + 0x27)] != ((struct house*)g_773da8)) {
				fcn_00519190(0x406d, *(unsigned short*) (o + 0x27), o, msg);
			} else {
				fcn_00519190(0x406c, o, msg);
			}
			cnt++;
		}
		if (cnt != 0) {
			g_774a1c = 0;
			((struct deal*)g_77dda0)[i].state = -1;
			fcn_00471af0(*(int*) (w + 0x74), 1);
			return;
		}
		if (g_774a1c != 0) {
			g_774a1c = 0;
			((struct deal*)g_77dda0)[i].state = -1;
			fcn_00519190((int) "$C");
			fcn_00519190(0x406e);
			fcn_00471af0(*(int*) (w + 0x74), 1);
			return;
		}
	}
	fcn_00471af0(*(int*) (w + 0x74), 0);
	g_774a1c = 0;
}
