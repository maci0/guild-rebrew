#include <string.h>
#include "Develop/DieGildeAddOn/game/object_prototype.h"
extern char* g_7ea360;
extern char* g_7746a0;
extern char* g_7746a4;
extern char* g_7746a8;
extern char* sv_HoveredObjekt;
extern char* g_7746b0;
extern char* g_7746b4;
extern int g_7746b8;
extern int g_7746bc;
extern char* g_7746c0;
extern char* g_7746c4;
extern char* g_7746c8;
extern char* g_7746cc;
extern int g_7746f0;
extern char g_7746f4;
#include "GOLDTL.sv_HandleObjects_gconf.h"
extern char* g_7e4320;
extern int g_7e4318;
extern int g_7e2700;
extern char* g_7e2704;
extern char* g_7e2708;
extern char g_7e2714[];
extern char* g_7e2a9c;
extern char* g_7e2aa0;
extern int g_14ce8cc;
extern int d3_ActiveCameraAnimation;
extern short g_14ce8c0;
extern short g_14ce8c2;
extern int g_6a3764;
extern int g_6a376c;
extern int g_6a3768;
extern int g_6a3770;
extern int d2_HoveredWindow;
extern int g_67d8d4;
extern char* lpObjektePROT;
extern char* g_77479c;
extern int g_774650;
extern int g_77465c;
extern int g_6b5c48;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char g_7f4ca0[];
extern char s_6a3004[];
extern char s_6a301c[];
extern int g_6a256c;
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern char* __cdecl d3_FindSceneObject(int, int, int, char*);
extern int __cdecl fcn_0064d41a(char*, char*, ...);
extern void __cdecl d3_AnimateCameraToNode(char*, int);
extern int __cdecl gm_GetEntityUiFlags(int, int, int, void*);
extern void __cdecl sv_ClearObjectSelection(void);
extern void __cdecl d3snd_PlayObjectClickSound(char*);
extern void __cdecl sv_ResetSelectionState(void);

typedef int (__cdecl* Fn_5305d0)(char*, int, char*, int);


/* Aktualisiert die Szenenauswahl aus den Quickjump-Kontaktfeldern; die
 * Auswahl wird auf die Objektliste abgebildet und neu gezeichnet. */
/* ADDRESS: GOLDTL 0x005305d0 */
void __cdecl sv_HandleObjects(void)
{
	char buf[0x80];
	char* selected;
	char* v7;
	char* p;
	char* list;
	int created;
	int match;
	int r;
	int i;

	match = 0;
	p = 0;
	g_7e4318 = 0;
	g_7e431c = 0;
	g_7746a0 = 0;
	g_7e4320 = 0;
	g_7746b8 = 0;
	created = 0;
	list = 0;
	if (g_7ea360 != 0 && *(char*) (g_7ea360 + 0x188) == 0) {
		g_7ea360 = 0;
	}
	selected = g_7746a4;
	if (g_7e2700 == 0) {
		goto L744;
	}
	v7 = g_7746c4;
	if (v7 == 0) {
		v7 = g_7746c8;
	}
	if (v7 != g_7e2704) {
		goto L744;
	}
	if (g_7e2708 == g_7746cc) {
		goto L66a;
	}
	if (g_7746c8 == 0 || g_7746cc != 0 || g_7e2708 == 0) {
		goto L6cd;
	}
	if (*(short*) g_7e2708 != 0xfd) {
		goto L6cd;
	}
L66a:
	if (g_7e2714[0] != 0) {
		p = d3_FindSceneObject(0, 0x60, 0, g_7e2714);
		if (p != 0) {
			selected = p;
			g_7746a4 = p;
			created = 1;
			g_7e2700 = 0;
			goto L6d3;
		}
		fcn_0064d41a(buf, s_6a301c, g_7e2714);
	}
	selected = g_7746a4;
	g_7e2700 = 0;
	goto L6d3;
L6cd:
	selected = g_7746a4;
L6d3:
	if (v7 != g_7e2704) {
		goto L744;
	}
	if (g_7e2708 != 0 && *(short*) g_7e2708 != 0xfd) {
		goto L744;
	}
	if (g_7e2714[0] != 0) {
		p = d3_FindSceneObject(0, 0x60, 0, g_7e2714);
		if (p != 0) {
			selected = p;
			created = 1;
			g_7746a4 = p;
			g_7e2700 = 0;
			goto L744;
		}
		fcn_0064d41a(buf, s_6a301c, g_7e2714);
		selected = g_7746a4;
	}
	g_7e2700 = 0;
L744:
	if (g_14ce8cc == 0 || d3_ActiveCameraAnimation != 0
	    || g_14ce8c0 <= g_6a3764 || g_14ce8c0 >= g_6a376c
	    || g_14ce8c2 <= g_6a3768 || g_14ce8c2 >= g_6a3770
	    || d2_HoveredWindow != -1 || g_67d8d4 != -1) {
		if (created == 0) {
			return;
		}
	}
	if (selected != 0) {
		list = sv_HoveredObjekt;
	if (list != 0) {
		p = ((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[(unsigned int) (unsigned short) *(unsigned short*) list]);
	} else {
		p = 0;
	}
	if (memcmp(selected, s_6a3004, 8) != 0) {
		if ((p != 0 && *p == 6) || g_7746bc != 0) {
			match = 1;
		}
	} else {
		match = 1;
	}
	g_7e4318 = (int) g_7746b0;
	g_7e431c = sv_HoveredObjekt;
	g_7e4320 = g_7746b4;
	g_7746b8 = g_7746bc;
	g_7746a0 = selected;
	if ((*(unsigned char*) (selected + 0x214) & 0x40) != 0 && match == 0) {
		d3_AnimateCameraToNode(selected, g_6a256c);
		g_7746a8 = g_7746a4;
		selected = g_7746a4;
		if (selected != 0) {
			p = *(char**) (selected + 0x1d4);
			if (p != 0 && *(Fn_5305d0*) (p + 0x108) != 0) {
				(*(Fn_5305d0*) (p + 0x108))(selected, 2, p + 0x10c, 0);
				selected = g_7746a4;
			}
		}
		g_77465c = g_774650;
		list = sv_HoveredObjekt;
	}
	g_77479c = selected;
	if (g_7746b4 != 0 && *(char*) (g_7746b4 + 8) != 0) {
		r = gm_GetEntityUiFlags((int) g_774970, 0, 0, g_7746b4);
		sv_ClearObjectSelection();
		p = g_7746b4;
		if ((r & 0x800) != 0
		    && (*(char*) (p + 0x165) != 0x1c || (*(unsigned char*) (p + 0x1b4) & 1) == 0)) {
			g_7ea360 = p;
			*(char*)&((ENTITY_RECORD*)g_7f4ca0)[(unsigned short) *(unsigned short*) p].unk_17c[12] = 1;
			g_7746f0 = 1;
			g_6b5c48 = *(int*)&((ENTITY_RECORD*)g_7f4ca0)[(unsigned short) *(unsigned short*) p].unk_17c[8];
			d3snd_PlayObjectClickSound(p);
			p = g_7746b4;
		}
		g_6b5c48 = *(int*)&((ENTITY_RECORD*)g_7f4ca0)[(unsigned short) *(unsigned short*) p].unk_17c[8];
		selected = g_7746a4;
		list = sv_HoveredObjekt;
	}
	if (g_7746f0 == 0 && g_7746f4 == 0 && g_7746b0 != 0 && g_7e2a9c == 0) {
		g_7746c0 = selected;
	}
	g_7e2aa0 = g_7746b0;
	g_7e2a9c = sv_HoveredObjekt;
	if (g_7746b0 != 0) {
		g_7746c0 = selected;
	}
		if (list != 0) {
			g_7746c0 = selected;
			if (*(char*) (((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[(unsigned int) (unsigned short) *(unsigned short*) list])) == 0x1d) {
				sv_ClearObjectSelection();
			}
		}
	} else if (g_7746f4 == 0) {
		sv_ResetSelectionState();
	}
}
