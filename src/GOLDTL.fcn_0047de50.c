#include "Develop/DieGildeAddOn/game/spiel.h"


#include <stdio.h>

#pragma pack(push, 1)
// SIZE 0x29
typedef struct {
	unsigned char office;
	char pad1[4];
	char name[0x22];
	unsigned short owner;
} Bld47de;

// SIZE 0x24d
typedef struct {
	unsigned char kind;
	char pad1[0x24c];
} Office47de;
#pragma pack(pop)

// SIZE 0x21c
typedef struct {
	char pad0[0x21c];
} Ent47de;

// SIZE 0x1bc
typedef struct {
	unsigned short id;
	char pad2[0x2e];
	char name[0x13c];
	Bld47de* bld;
	char pad170[0x44];
	unsigned char flags;
	char pad1b5[3];
	int budget;
} Master47de;

#pragma pack(push, 2)
// SIZE 0xe
typedef struct {
	int day;
	unsigned short hour;
	int min;
	int sec;
} Time47de;
#pragma pack(pop)

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern Master47de* g_100e748;
extern char g_7f4ca0[];
extern char* g_7746c4;
extern unsigned char* g_7746c8;
extern LightState g_100dc20;
extern Master47de* g_100dc28;
extern Ent47de* g_100dc2c;
extern int g_100dc30;
extern unsigned char* g_868050;

int __cdecl gm_CanEvaluateMaster(char*);
int __cdecl gm_AccumulateTyped2(void*);

void __cdecl fcn_0047f6b0(Master47de*);
void __cdecl fcn_00480330(Master47de*);
void __cdecl fcn_004813b0(Master47de*);
void __cdecl fcn_004823c0(Master47de*);
void __cdecl fcn_00482b60(Master47de*);
void __cdecl fcn_00482f20(Master47de*);
void __cdecl fcn_00483480(Master47de*);
void __cdecl fcn_00483f20(Master47de*);
void __cdecl fcn_0047e270(Master47de*);
void __cdecl fcn_0047ebc0(Master47de*);

void __cdecl fcn_0047de50(Master47de* m)
{
	char buf[0x100];
	unsigned char k;

	if ((*(Time47de*)&g_7f4c00).hour < 6 || ((*(Time47de*)&g_7f4c00).hour == 6 && (*(Time47de*)&g_7f4c00).min < 30)) {
		return;
	}
	if (gm_CanEvaluateMaster((char*) m) == 0) {
		return;
	}
	if (!(m->flags & 1)) {
		return;
	}
	if (m == g_100e748) {
		sprintf(buf, "Evaluation von Meister %s in %s beginnt...", g_100e748->name, g_100e748->bld->name);
		sprintf(buf, "Aktuelles Budget: %li", g_100e748->budget);
		sprintf(buf, "Tats\xe4" "chlich verf\xfcgbares Budget: %li", gm_AccumulateTyped2(&((Ent47de*)g_7f4ca0)[m->bld->owner]));
	}
	if (m->bld->owner == m->id) {
		m->budget = gm_AccumulateTyped2(m);
	}
	if (m->bld == ((Bld47de*)g_7746c4) || m->bld == ((Bld47de*)g_7746c8)) {
		g_100dc20.owner = (char*) m->bld;
		g_100dc28 = m;
		g_100dc2c = &((Ent47de*)g_7f4ca0)[m->bld->owner];
		g_100dc30 = m->budget;
	}
	if (gm_GetBuildingTypeCategory(m->bld->office) == 1 || gm_GetBuildingTypeCategory(m->bld->office) == 4) {
		k = ((Office47de*)g_868050)[m->bld->office].kind;
		if (k == 0xe || k == 8 || k == 0x20) {
			fcn_0047ebc0(m);
		} else if (k == 0x1d) {
			fcn_00483480(m);
		} else if (k == 0x1f) {
			fcn_00483f20(m);
		} else {
			fcn_0047e270(m);
		}
	} else if (gm_GetBuildingTypeCategory(m->bld->office) == 2) {
		fcn_0047f6b0(m);
	} else {
		k = ((Office47de*)g_868050)[m->bld->office].kind;
		if (k == 0x13) {
			fcn_00480330(m);
		} else if (k == 4) {
			fcn_004813b0(m);
		} else if (k == 0x10) {
			fcn_004823c0(m);
		} else if (k == 5) {
			fcn_00482b60(m);
		} else if (k == 9) {
			fcn_00482f20(m);
		}
	}
}
