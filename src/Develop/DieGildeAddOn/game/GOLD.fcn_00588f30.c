

// SIZE 0x38
struct sel {
	char* who;
	char pad4[0x34];
};

#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText();
int __cdecl d2_BuildPersonStatusDesc(struct sel*);
void __cdecl fcn_005caaa0(int, int, int, struct sel*);
float __cdecl fcn_00505e30(unsigned short);
int __cdecl gm_GetOppositeStatIndex(int);
#include "Develop/DieGildeAddOn/game/spiel.h"
char* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl he_StartHandlungSearch(int, int, int);
char* __cdecl he_fn_Handlung(void);
void __cdecl io_FormatTextBuffer(char*, char*, ...);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_DrawSkillBar(int, int, char*, int, int);
void __cdecl fcn_0057e880(int, char*, int, int);

int __cdecl d2_CreatePersonTooltip(char* entity)
{
	int dlg;
	struct sel info;
	char buf[0x100];
	char* target;
	char* action;
	int any;
	int i;
	int roleOffset;

	dlg = d2_LoadForm(0, 0, "ToolTip\\ToolTip_Personen");
	d2_CenterDialogWindows(dlg);
	d2_SetForm(0, 1);
	io_AppendText("$Z$[%1N3$]", *(unsigned short*) entity);
	d2_SetForm(0, 4);
	info.who = entity;
	if (d2_BuildPersonStatusDesc(&info) != 0) {
		fcn_005caaa0(0xa6, 5, d2_CurrentWindowId, &info);
	}
	d2_SetForm(0, 2);
	if (entity[2] != 0x14) {
		io_AppendText(0x2b, (int) fcn_00505e30(*(unsigned short*) entity));
	}
	if (entity[0x166] == 0 && entity[0x169] == 0 && (*(int*) (entity + 0x1cc) & 0xe00) == 0) {
		if ((*(int*) (entity + 0x1cc) & 0x3000) != 0) {
			if ((*(int*) (entity + 0x1cc) & 0x1000) != 0) {
				roleOffset = 0x26;
			} else if ((*(int*) (entity + 0x1cc) & 0x2000) != 0) {
				roleOffset = 0x27;
			} else if ((*(int*) (entity + 0x1cc) & 0x800) != 0) {
				roleOffset = 0x25;
			} else if ((*(int*) (entity + 0x1cc) & 0x400) != 0) {
				roleOffset = 0x24;
			} else {
				roleOffset = (*(int*) (entity + 0x1cc) & 0x200) != 0 ? 0x23 : 0;
			}
			io_AppendText(0x2d);
			io_AppendText("$3>%s$A", (entity[9] != 0 ? 0x27b : 0x253) + roleOffset);
			io_AppendText("$A");
		} else {
			io_AppendText(0x2c, (entity[9] != 0 ? 0x18f : 0x130) + *(unsigned char*) (entity + 0x164),
			    gm_GetOppositeStatIndex(*(unsigned char*) (entity + 0x164)));
		}
	} else {
		if ((*(int*) (entity + 0x1cc) & 0x1000) != 0) {
			roleOffset = 0x26;
		} else if ((*(int*) (entity + 0x1cc) & 0x2000) != 0) {
			roleOffset = 0x27;
		} else if ((*(int*) (entity + 0x1cc) & 0x800) != 0) {
			roleOffset = 0x25;
		} else if ((*(int*) (entity + 0x1cc) & 0x400) != 0) {
			roleOffset = 0x24;
		} else {
			roleOffset = (*(int*) (entity + 0x1cc) & 0x200) != 0 ? 0x23 : 0;
		}
		io_AppendText(0x2c, (entity[9] != 0 ? 0x18f : 0x130) + *(unsigned char*) (entity + 0x164),
		    gm_GetOppositeStatIndex(*(unsigned char*) (entity + 0x164)));
		io_AppendText(0x2d);
		if ((*(int*) (entity + 0x1cc) & 0xe00) != 0) {
			io_AppendText("$3>%s$A", (entity[9] != 0 ? 0x27b : 0x253) + roleOffset);
		}
		if (entity[0x166] != 0) {
			io_AppendText("$3>%s$A", (entity[9] != 0 ? 0x27b : 0x253) + *(unsigned char*) (entity + 0x166));
		}
		if (entity[0x169] != 0) {
			io_AppendText("$3>%s$A", (entity[9] != 0 ? 0x27b : 0x253) + *(unsigned char*) (entity + 0x169));
		}
	}
	if ((*(int*) (entity + 0x1cc) & 0x3000) == 0) {
		io_AppendText(0x37, (entity[9] != 0 ? 0x11e : 0x114) + *(unsigned char*) (entity + 0xd));
	}
	io_AppendText(0x2e, gm_WalkEntityChain(*(unsigned short*) entity));
	if ((*(int*) (entity + 0x1cc) & 0x3000) == 0) {
		io_AppendText(0x2f);
		target = gm_LookupEntityRecordById(*(int*) (entity + 0x5c));
		if (target != 0 && *(unsigned char*) (target + 8) > 0) {
			io_AppendText(0x30, *(unsigned short*) target);
		} else {
			for (action = he_StartHandlungSearch(1, 0, 0x41); action != 0; action = he_fn_Handlung()) {
				if (*(int*) (action + 0xac) == *(int*) (entity + 4)) {
					break;
				}
			}
			if (action != 0 && (target = gm_LookupEntityRecordById(*(int*) (action + 0xb0))) != 0) {
				io_AppendText(0x31, *(unsigned short*) target);
			} else {
				io_AppendText(0x32);
			}
		}
	}
	io_AppendText(0x33, *(unsigned char*) (entity + 0xc) + 0x486);
	if ((*(int*) (entity + 0x1cc) & 0x3000) == 0) {
		any = 0;
		io_AppendText(0x34);
		for (i = 0; i < 5; i++) {
			target = gm_LookupEntityRecordById(((int*) (entity + 0x68))[i]);
			if (target != 0) {
				io_AppendText("$3>%1N1$A", *(unsigned short*) target);
				any = 1;
			}
		}
		if (any == 0) {
			io_AppendText("$3>%s$A", 0x35);
		}
	}
	d2_SetForm(0, 3);
	for (i = 0; i < 5; i++) {
		io_FormatTextBuffer(buf, "%s:", i + 0x16b7);
		d2_ShowTxt(0, i * 15, buf, d2_CurrentWindowId);
		d2_DrawSkillBar(0x64, i * 15 + 2, entity, i, 0x4df);
	}
	fcn_0057e880(7, entity, 0, 0);
	return dlg;
}
