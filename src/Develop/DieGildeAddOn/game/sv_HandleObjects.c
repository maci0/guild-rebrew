#include <string.h>
#include "Develop/DieGildeAddOn/game/object_prototype.h"
extern char* d2_SelectedPerson;
extern char* sv_ClickedObjekt;
extern char* d2_HoveredSceneObject;
extern char* g_7746a8;
extern char* sv_HoveredObjekt;
extern char* sv_HoveredBuilding;
extern char* sv_HoveredCharacter;
extern int g_7746b8;
extern int sv_HoveredInteriorItem;
extern char* d3_FocusedEntityObject;
extern char* d2_VisitedBuilding;
extern char* d2_InteriorBuilding;
extern char* sv_SelectedBuilding;
extern int g_7746f0;
extern char g_7746f4;
extern char* g_7e431c;
extern char* g_7e4320;
extern int g_7e4318;
extern int d2_InsideBuildingActive;
extern char* d2_EnteredBuildingEntity;
extern char* d2_EnteredBuildingObjekt;
extern char g_7e2714[];
extern char* d2_SelectedItem;
extern char* d2_SelectedBuilding;
extern int g_14ce8cc;
extern int d3_ActiveCameraAnimation;
extern short io_ActiveCursorX;
extern short io_ActiveCursorY;
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
extern char gm_EntitySlotTable[];
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
/* ADDRESS: GOLDDE 0x00518f50 */
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
	sv_ClickedObjekt = 0;
	g_7e4320 = 0;
	g_7746b8 = 0;
	created = 0;
	list = 0;
	if (d2_SelectedPerson != 0 && *(char*) (d2_SelectedPerson + 0x188) == 0) {
		d2_SelectedPerson = 0;
	}
	selected = d2_HoveredSceneObject;
	if (d2_InsideBuildingActive == 0) {
		goto L744;
	}
	v7 = d2_VisitedBuilding;
	if (v7 == 0) {
		v7 = d2_InteriorBuilding;
	}
	if (v7 != d2_EnteredBuildingEntity) {
		goto L744;
	}
	if (d2_EnteredBuildingObjekt == sv_SelectedBuilding) {
		goto L66a;
	}
	if (d2_InteriorBuilding == 0 || sv_SelectedBuilding != 0 || d2_EnteredBuildingObjekt == 0) {
		goto L6cd;
	}
	if (*(short*) d2_EnteredBuildingObjekt != 0xfd) {
		goto L6cd;
	}
L66a:
	if (g_7e2714[0] != 0) {
		p = d3_FindSceneObject(0, 0x60, 0, g_7e2714);
		if (p != 0) {
			selected = p;
			d2_HoveredSceneObject = p;
			created = 1;
			d2_InsideBuildingActive = 0;
			goto L6d3;
		}
		fcn_0064d41a(buf, s_6a301c, g_7e2714);
	}
	selected = d2_HoveredSceneObject;
	d2_InsideBuildingActive = 0;
	goto L6d3;
L6cd:
	selected = d2_HoveredSceneObject;
L6d3:
	if (v7 != d2_EnteredBuildingEntity) {
		goto L744;
	}
	if (d2_EnteredBuildingObjekt != 0 && *(short*) d2_EnteredBuildingObjekt != 0xfd) {
		goto L744;
	}
	if (g_7e2714[0] != 0) {
		p = d3_FindSceneObject(0, 0x60, 0, g_7e2714);
		if (p != 0) {
			selected = p;
			created = 1;
			d2_HoveredSceneObject = p;
			d2_InsideBuildingActive = 0;
			goto L744;
		}
		fcn_0064d41a(buf, s_6a301c, g_7e2714);
		selected = d2_HoveredSceneObject;
	}
	d2_InsideBuildingActive = 0;
L744:
	if (g_14ce8cc == 0 || d3_ActiveCameraAnimation != 0
	    || io_ActiveCursorX <= g_6a3764 || io_ActiveCursorX >= g_6a376c
	    || io_ActiveCursorY <= g_6a3768 || io_ActiveCursorY >= g_6a3770
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
		if ((p != 0 && *p == 6) || sv_HoveredInteriorItem != 0) {
			match = 1;
		}
	} else {
		match = 1;
	}
	g_7e4318 = (int) sv_HoveredBuilding;
	g_7e431c = sv_HoveredObjekt;
	g_7e4320 = sv_HoveredCharacter;
	g_7746b8 = sv_HoveredInteriorItem;
	sv_ClickedObjekt = selected;
	if ((*(unsigned char*) (selected + 0x214) & 0x40) != 0 && match == 0) {
		d3_AnimateCameraToNode(selected, g_6a256c);
		g_7746a8 = d2_HoveredSceneObject;
		selected = d2_HoveredSceneObject;
		if (selected != 0) {
			p = *(char**) (selected + 0x1d4);
			if (p != 0 && *(Fn_5305d0*) (p + 0x108) != 0) {
				(*(Fn_5305d0*) (p + 0x108))(selected, 2, p + 0x10c, 0);
				selected = d2_HoveredSceneObject;
			}
		}
		g_77465c = g_774650;
		list = sv_HoveredObjekt;
	}
	g_77479c = selected;
	if (sv_HoveredCharacter != 0 && *(char*) (sv_HoveredCharacter + 8) != 0) {
		r = gm_GetEntityUiFlags((int) gm_LocalPlayerSlot, 0, 0, sv_HoveredCharacter);
		sv_ClearObjectSelection();
		p = sv_HoveredCharacter;
		if ((r & 0x800) != 0
		    && (*(char*) (p + 0x165) != 0x1c || (*(unsigned char*) (p + 0x1b4) & 1) == 0)) {
			d2_SelectedPerson = p;
			*(char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[(unsigned short) *(unsigned short*) p].unk_17c[12] = 1;
			g_7746f0 = 1;
			g_6b5c48 = *(int*)&((ENTITY_RECORD*)gm_EntitySlotTable)[(unsigned short) *(unsigned short*) p].unk_17c[8];
			d3snd_PlayObjectClickSound(p);
			p = sv_HoveredCharacter;
		}
		g_6b5c48 = *(int*)&((ENTITY_RECORD*)gm_EntitySlotTable)[(unsigned short) *(unsigned short*) p].unk_17c[8];
		selected = d2_HoveredSceneObject;
		list = sv_HoveredObjekt;
	}
	if (g_7746f0 == 0 && g_7746f4 == 0 && sv_HoveredBuilding != 0 && d2_SelectedItem == 0) {
		d3_FocusedEntityObject = selected;
	}
	d2_SelectedBuilding = sv_HoveredBuilding;
	d2_SelectedItem = sv_HoveredObjekt;
	if (sv_HoveredBuilding != 0) {
		d3_FocusedEntityObject = selected;
	}
		if (list != 0) {
			d3_FocusedEntityObject = selected;
			if (*(char*) (((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[(unsigned int) (unsigned short) *(unsigned short*) list])) == 0x1d) {
				sv_ClearObjectSelection();
			}
		}
	} else if (g_7746f4 == 0) {
		sv_ResetSelectionState();
	}
}
