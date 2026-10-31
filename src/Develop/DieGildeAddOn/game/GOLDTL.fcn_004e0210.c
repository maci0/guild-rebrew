typedef struct {
	char c[0x18];
} Anim_4e0210;
// SIZE 0x18

extern int g_772f44;
extern int g_68bfc0;
extern char* g_9afde4;
extern char g_772f5a;
extern char g_772f5b;
extern char g_772f5c;
extern char g_772f5d;
extern Anim_4e0210 g_68cc34;

unsigned char* __cdecl fcn_004e6a70(int);
int __cdecl d2_SetForm(int, int);
char* __cdecl io_AppendText(int, ...);
int __cdecl fcn_004de610(int);
int __cdecl fcn_004c3030(int, int, char*, int);
void __cdecl fcn_004e4c90(int);
char* __cdecl fcn_0040c230(char*, void*, int, int, int);
void __cdecl fcn_004dff50(void);
#include "Develop/DieGildeAddOn/game/spiel.h"
float __cdecl fcn_004e6d20(void);
int __cdecl fcn_00406340(char*, const char*, int);


/* Duel intro: plays the challenger's opening move chosen by the duel kind. */
/* ADDRESS: GOLDTL 0x004e0210 */
void __cdecl fcn_004e0210(char* e, char* foe)
{
	unsigned char* d;
	int t;
	char* o;
	float a;
	float b;

	if (g_772f44 == 0) {
		d = fcn_004e6a70(*(int*) (e + 4));
		d2_SetForm(g_68bfc0, 0);
		io_AppendText((int) "$C");
		switch (d[0x94]) {
		case 4:
			d2_SetForm(g_68bfc0, 0);
			t = fcn_004de610(7);
			io_AppendText(t + 0x10fa, *(unsigned short*) e);
			fcn_004c3030(*(unsigned short*) e, 0, "_DUELL_INTRO_C2_AUSWAHL_SCHIESSEN", t);
			fcn_004e4c90(2);
			io_AppendText((int) "$N");
			o = fcn_0040c230(*(char**) (e + 0x184), (void*) fcn_004dff50, 6, 0x2e, 1);
			*(char**) (o + 0x17c) = foe;
			*(char**) (o + 0x180) = e;
			*(Anim_4e0210*) (o + 0xf0) = g_68cc34;
			break;
		case 3:
			d2_SetForm(g_68bfc0, 0);
			a = gm_GetEntitySkill(e, 2);
			if (fcn_004e6d20() < a) {
				if (e[2] == 6 || e[2] == 7) {
					io_AppendText(0x10f6, *(unsigned short*) e);
				} else {
					io_AppendText(0x10f7, *(unsigned short*) e);
				}
				if (e == g_9afde4) {
					g_772f5c = 1;
				} else {
					g_772f5d = 1;
				}
			} else {
				if (e[2] == 6 || e[2] == 7) {
					io_AppendText(0x10f8, *(unsigned short*) e);
				} else {
					io_AppendText(0x10f9, *(unsigned short*) e);
				}
			}
			io_AppendText((int) "$N");
			break;
		case 2:
			d2_SetForm(g_68bfc0, 0);
			io_AppendText(0x10e8, *(unsigned short*) e);
			t = fcn_004de610(8);
			io_AppendText(t + 0x10e9);
			fcn_004c3030(*(unsigned short*) e, 0, "_DUELL_INTRO_C2_AUSWAHL_LAESTERN", t);
			io_AppendText((int) "$N");
			fcn_00406340(*(char**) (e + 0x184), "gestik/abfaellig", 1);
			fcn_004e4c90(2);
			a = gm_GetEntitySkill(e, 4);
			b = gm_GetEntitySkill(foe, 4);
			a += fcn_004e6d20();
			if (fcn_004e6d20() + b < a) {
				d2_SetForm(g_68bfc0, 0);
				if (foe[2] == 6 || foe[2] == 7) {
					io_AppendText(0x10f2, *(unsigned short*) foe);
				} else {
					io_AppendText(0x10f3, *(unsigned short*) foe);
				}
				if (e == g_9afde4) {
					g_772f5a = 1;
				} else {
					g_772f5b = 1;
				}
			} else {
				d2_SetForm(g_68bfc0, 0);
				if (foe[2] == 6 || foe[2] == 7) {
					io_AppendText(0x10f4, *(unsigned short*) foe);
				} else {
					io_AppendText(0x10f5, *(unsigned short*) foe);
				}
			}
			io_AppendText((int) "$N");
			break;
		}
		fcn_004e4c90(4);
	}
}
