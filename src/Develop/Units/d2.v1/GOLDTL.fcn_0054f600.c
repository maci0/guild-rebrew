#include "client_types.h"

typedef struct {
	char* e;
	int tile;
	int bar;
	char pad0c[0x2c];
} SEL_54f600;

typedef struct {
	char pad0[0x5c];
	int f5c;
	char pad60[0x1d0 - 0x60];
	int f1d0;
	char pad1d4[0x2f0 - 0x1d4];
	char* owner;
} TILE_54f600;

extern pos14_7f4c00 g_7f4c00;
extern char* g_77255c;
extern int g_772514;
extern char* g_1015ea0;
extern int g_100f884;
extern int g_100f1dc;
extern char g_774964;
extern char* g_7747b8;

int __cdecl fcn_005463a0(int, int, int);
char* __cdecl fcn_00508e40(int);
int __cdecl fcn_00500cb0(void*, void*);
void __cdecl fcn_0054f4a0(char*, char*, unsigned char*);
void __cdecl fcn_0054f3b0(char*, char*, char*);
void __cdecl fcn_00545780(char*);
void __cdecl fcn_00546190(char*);
int __cdecl fcn_00545670(char*, int, int, char*, int);
void __cdecl fcn_004234e0(char*, char*, int, int, int, int, int);
int __cdecl d2_SetForm(int, int);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_00500bb0(char*, int, int, int);
int __cdecl fcn_005ca560(SEL_54f600*);
int __cdecl fcn_005caaa0(int, int, int, SEL_54f600*);
void __cdecl fcn_004c5620(int, void*);

/* ADDRESS: GOLDTL 0x0054f600 */
void __cdecl fcn_0054f600(char* o)
{
	char* v3;
	char* v4;
	char* v6;
	SEL_54f600 s;
	int v1;

	v6 = 0;
	v4 = 0;
	v3 = fcn_005463a0(1, 1, *(int*) (o + 0xac));
	if (v3 != 0) {
		v6 = fcn_00508e40(*(int*) (v3 + 0xb0));
		v4 = fcn_00508e40(*(int*) (v3 + 0xac));
	}
	v1 = *(int*) (o + 0x70);
	if (v1 != -1 && v1 != -2 && v3 != 0 && v6 != 0 && v4 != 0) {
		switch (v1) {
		case 1:
			if (fcn_00500cb0(&g_7f4c00, o + 0x52) > 0) {
				fcn_0054f4a0(v3, v4, (unsigned char*) v6);
				fcn_00545780(o);
				fcn_00546190(o);
				return;
			}
			if (g_100f884 != *(int*) (*(int*) (o + 0x74) + 8)) {
				return;
			}
			if (g_100f1dc == -1) {
				return;
			}
			if (g_100f1dc == 2) {
				fcn_0054f3b0(v3, v4, v6);
			} else if (g_100f1dc == 1) {
				fcn_0054f4a0(v3, v4, (unsigned char*) v6);
			}
			fcn_00545780(o);
			fcn_00546190(o);
			return;
		case 0:
			fcn_00545670(o, 0, 0, "_DUELL_INTRO_EVENT_DUELLANTEN_HS_00", 0x5ec);
			if (*(int*) (o + 0x74) != 0) {
				if (g_774964 != 2) {
					fcn_004234e0(g_7747b8, "NeueMessage_s_01", 1, 0x3f, 0x7f, 0, 0);
				}
				d2_SetForm(*(int*) (*(int*) (o + 0x74) + 8), 1);
				fcn_00519190(0x1d6c);
				d2_SetForm(*(int*) (*(int*) (o + 0x74) + 8), 2);
				s.e = v4;
				if (fcn_005ca560(&s) != 0) {
					fcn_005caaa0(*(int*) (g_77255c + 0xc) / 2 - 0x28, 0, g_772514, &s);
					((TILE_54f600*) (void*) g_1015ea0)[s.tile].f5c = 1;
					((TILE_54f600*) (void*) g_1015ea0)[s.tile].f1d0 = 3;
					((TILE_54f600*) (void*) g_1015ea0)[s.tile].owner = s.e;
				}
				d2_SetForm(*(int*) (*(int*) (o + 0x74) + 8), 3);
				fcn_00519190(0x1d6b, (int) *(unsigned short*) (v3 + 0xb4),
				    (int) *(unsigned short*) v4, (int) *(unsigned short*) (v3 + 0xb6),
				    (int) *(unsigned short*) v4);
				*(pos14_7f4c00*) (o + 0x44) = g_7f4c00;
				*(pos14_7f4c00*) (o + 0x52) = g_7f4c00;
				fcn_00500bb0(o + 0x52, 2, 0, 0);
				(*(int*) (o + 0x70))++;
				return;
			}
			break;
		default:
			return;
		}
	} else {
		if (*(int*) (o + 0x74) != 0) {
			fcn_00545780(o);
		}
		if (v3 != 0) {
			*(pos14_7f4c00*) (v3 + 0x52) = g_7f4c00;
			fcn_004c5620(-1, v3);
		}
	}
	fcn_00546190(o);
}
