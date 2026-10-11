#include "client_sound.h"
#include "Develop/Units/Msx/msx.h"

#include <string.h>

// SIZE 0x24c
typedef struct Tpl_4c2100 {
	int kind;
	int owner;
	int cls;
	char names[6][0x60];
} Tpl_4c2100;

#include "client_types.h"
#include "g_688118.h"

extern char* g_7746c4;
extern unsigned char* g_7746c8;
extern char* g_7746cc;
extern unsigned char* g_868050;
extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_774970;
extern IdGroup g_688118[];
extern Tpl_4c2100 g_6819b8[];
extern char g_772c10[];
extern char s_68a14c[];
extern char s_68a130[];

int __cdecl fcn_00500e20(int*);
int __cdecl fcn_004c27f0(void);
int __cdecl fcn_004c2820(int);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned short __cdecl gm_RandomMod(int);
int __cdecl fcn_0064d41a(char*, char*, ...);

// FUNCTION: GOLDTL 0x4c2100
void __cdecl fcn_004c2100(void)
{
	unsigned char* e;
	int kind;
	int cls;
	int i;
	int n;
	int j;
	int c;
	char* s;
	char* name;
	Tpl_4c2100* p;
	int k;
	Chan_14cc460* track;

	e = (unsigned char*) g_7746c4;
	if (e == 0) {
		e = g_7746c8;
		if (e == 0) {
			return;
		}
	}
	j = 0;
	kind = g_868050[*e * 0x24d];
	cls = fcn_00500e20((int*) &g_7f4c00);
	i = fcn_004c27f0();
	if (i >= 0) {
		g_688118[i].active = j;
		if (g_688118[i].ids[0] != 0x2694) {
			for (; g_688118[i].ids[j] != 0; j++) {
				if (gm_StartFilteredEntitySearch(2, 4, g_774970, 5, g_688118[i].ids[j]) != 0) {
					g_688118[i].score -= 0x1e;
					break;
				}
			}
			if (g_688118[i].ids[j] == 0) {
				g_688118[i].score -= 0x14;
			}
		} else {
			g_688118[i].score -= 0x1e;
		}
	}
	n = fcn_004c2820(kind);
	if (n < 0) {
		return;
	}
	name = g_688118[n].name;
	if (strlen(name) != 0) {
		g_688118[n].active = 1;
		for (j = 0; g_688118[n].ids[j] != 0; j++) {
			if (gm_StartFilteredEntitySearch(2, 4, g_774970, 5, g_688118[n].ids[j]) != 0) {
				g_688118[n].score += 0x1e;
				break;
			}
		}
		if (g_688118[n].ids[j] == 0) {
			g_688118[n].score += 0x14;
		}
		track = fcn_0041fd70(name, 0);
		g_772d1c = g_772d20 = track;
		fcn_0064d41a(g_772c10, s_68a14c, name);
		return;
	}
	if (g_6819b8[0].kind == 0) {
		return;
	}
	for (k = 0; g_6819b8[k].kind != 0; k++) {
		p = &g_6819b8[k];
		if (p->kind == kind && (p->owner == 0 || p->owner == *(unsigned short*) g_7746cc) && (cls == p->cls || p->cls == -1)) {
			for (c = 0; c < 6; c++) {
				if (p->names[c][0] == 0) {
					break;
				}
			}
			s = p->names[gm_RandomMod(c)];
			if (strlen(s) == 0) {
				return;
			}
			strcpy(name, s);
			g_688118[n].active = 1;
			for (j = 0; g_688118[n].ids[j] != 0; j++) {
				if (gm_StartFilteredEntitySearch(2, 4, g_774970, 5, g_688118[n].ids[j]) != 0) {
					g_688118[n].score += 0x1e;
					break;
				}
			}
			if (g_688118[n].ids[j] == 0) {
				g_688118[n].score += 0x14;
			}
			track = fcn_0041fd70(name, 0);
			g_772d1c = g_772d20 = track;
			fcn_0064d41a(g_772c10, s_68a130, name);
			return;
		}
	}
}
