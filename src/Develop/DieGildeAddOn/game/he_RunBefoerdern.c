#include <string.h>

extern int d3_CurrentContextIndex;
extern char str_empty[];

int __cdecl cm_GetCommandStatus(int);
char* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl gm_SearchTable67(int);
int __cdecl gm_ApplyPromotionRoleChange(char*);
int __cdecl cm_SendSetHE(int, char*);
int __cdecl evt_FindScriptById(int);
void __cdecl evt_RequestScriptExit(int);
int __cdecl d3_GetContextIndex(int);
void __cdecl d3_SelectSceneContext(int, int);
void __cdecl ch_DestroyCharacter(char*);
char* __cdecl ch_SpawnEntityCharacter(char*, int, float*, float*, int, int);
void __cdecl ch_SetBodyAttachment(int, int, char*);
char* __cdecl evt_LoadGfxScript(char*);
void __cdecl evt_CallScriptFunction(char*, int, ...);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl he_FreeAction(char*);

/* ADDRESS: GOLDTL 0x00566360 */
/* ADDRESS: GOLDDE 0x0054c470 */
void __cdecl he_RunBefoerdern(char* action)
{
	int v3;
	int v15;
	int v6;
	float pos[4];
	float rot[4];
	int v7;
	char name[0x80];
	char* o;
	char* ent;
	char* handle;
	char* p;
	int v30;

	o = action;
	if (*(int*) (o + 0x84) != -1) {
		if (!cm_GetCommandStatus(*(int*) (o + 0x84))) {
			return;
		}
	}
	ent = gm_LookupEntityRecordById(*(unsigned int*) (o + 0xac));
	if (ent == 0) {
		he_FreeAction(o);
		return;
	}
	if (*(int*) (ent + 0x184) != 0) {
		p = gm_SearchTable67(*(unsigned int*) (o + 0x10));
		if (p != 0 && *(int*) (*(int*) (ent + 0x184) + 0x2c) != *(int*) (p + 1)) {
			return;
		}
	}

	switch (*(int*) (o + 0x70)) {
	case 0:
		if ((unsigned char) o[0x78] & 2) {
			*(int*) (o + 0xb0) = gm_ApplyPromotionRoleChange(ent);
		}
		*(int*) (o + 0x70) = *(int*) (o + 0x70) + 1;
		return;
	case 1:
		if ((unsigned char) o[0x78] & 4) {
			return;
		}
		handle = (char*) *(int*) (o + 0xb0);
		if (handle != (char*) -1 && !cm_GetCommandStatus((int) handle)) {
			return;
		}
		*(int*) (o + 0xb0) = -1;
		*(int*) (o + 0x84) = cm_SendSetHE(2, o);
		return;
	case 2:
		if (*(int*) (ent + 0x184) == 0) {
			if ((unsigned char) o[0x78] & 2) {
				cm_RequestChangeBits(*(unsigned int*) (ent + 4), 0x1cc, 4, 0, 0x1000000);
			}
			he_FreeAction(o);
			return;
		}
		handle = (char*) *(int*) (*(int*) (ent + 0x184) + 0x28);
		if (handle != (char*) -1) {
			evt_RequestScriptExit(evt_FindScriptById((int) handle));
		}
		*(int*) (o + 0x70) = *(int*) (o + 0x70) + 1;
		return;
	case 3:
		v6 = *(int*) (ent + 0x184);
		if (*(int*) (v6 + 0x28) != -1) {
			return;
		}
		if (v6 == 0) {
			if ((unsigned char) o[0x78] & 2) {
				cm_RequestChangeBits(*(unsigned int*) (ent + 4), 0x1cc, 4, 0, 0x1000000);
			}
			he_FreeAction(o);
			return;
		}
		v15 = d3_CurrentContextIndex;
		v7 = d3_GetContextIndex(*(unsigned int*) (v6 + 0x88));
		name[0] = str_empty[0];
		memset(name + 1, 0, 0x7f);
		d3_SelectSceneContext(v7, 1);
		v6 = *(int*) (ent + 0x184);
		pos[0] = *(float*) (*(int*) (v6 + 0x34) + 0x4c);
		pos[1] = *(float*) (*(int*) (v6 + 0x34) + 0x50);
		pos[2] = *(float*) (*(int*) (v6 + 0x34) + 0x54);
		rot[0] = *(float*) (*(int*) (v6 + 0x34) + 0x84);
		rot[1] = *(float*) (*(int*) (v6 + 0x34) + 0x88);
		rot[2] = *(float*) (*(int*) (v6 + 0x34) + 0x8c);
		v3 = *(int*) (v6 + 0x2c);
		v30 = *(int*) (v6 + 0x30);
		strcpy(name, (char*) (v6 + 0x1a8));
		ch_DestroyCharacter((char*) v6);
		*(unsigned int*) (ent + 0x184) = 0;
		*(char*) (ent + 0x1f4) = 0;
		p = ch_SpawnEntityCharacter(ent, v7, pos, rot, 0, 0);
		*(char**) (ent + 0x184) = p;
		if (p != 0) {
			*(unsigned int*) (p + 0x2c) = v3;
			*(int*) (*(int*) (ent + 0x184) + 0x30) = v30;
			if (name[0]) {
				ch_SetBodyAttachment(*(int*) (ent + 0x184), 2, name);
			}
			p = evt_LoadGfxScript((char*) 0x6a68bc);
			if (p != 0) {
				evt_CallScriptFunction(p, 5, (int) pos[0], (int) pos[1], (int) pos[2], 0x28, 0xb4);
				if (v30 != -1) {
					*(int*) (p + 0x104) = v30;
				} else {
					*(unsigned int*) (p + 0x104) = v3;
				}
				*(unsigned int*) (p + 0xc8c) = 1;
			}
		}
		d3_SelectSceneContext(v15, 1);
		o = action;
		if ((unsigned char) o[0x78] & 2) {
			cm_RequestChangeBits(*(unsigned int*) (ent + 4), 0x1cc, 4, 0, 0x1000000);
		}
		he_FreeAction(o);
		return;
	case -2:
	case -1:
		if ((unsigned char) o[0x78] & 2) {
			cm_RequestChangeBits(*(unsigned int*) (ent + 4), 0x1cc, 4, 0, 0x1000000);
		}
		he_FreeAction(o);
		return;
	default:
		return;
	}
}
