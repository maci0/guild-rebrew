#include <string.h>

#include "client_types.h"

extern pos14_7f4c00 gm_GameTime;
extern unsigned char g_773d75;
extern float g_664168;

char* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl fcn_00502cd0(int, int, int, int);
int __cdecl fcn_0050b750(int, unsigned char);
int __cdecl gm_RandomMod(int);
int __cdecl cm_SendSetHE(int, char*);
void __cdecl gm_AddTime(char*, int, int, int);
void __cdecl cm_SendCancelCharacterActions(int);
void __cdecl ch_StartMovement(int, int, int, int, int, char*);
void __cdecl cm_RequestPlayAnimation(int, char*, int);
void __cdecl he_AssignActionSlot(int, int, int, char*);
void __cdecl he_FreeAction(char*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, int);
void __cdecl cm_RequestMoveCredits(int, int, unsigned char, int);
int __cdecl gm_GetElapsedMinutes(char*, char*);
int __cdecl sprintf(char*, const char*, ...);

/* ADDRESS: GOLDTL 0x0054da10 */
void __cdecl he_UpdateRobberyAction(char* action)
{
	char text[0x40];
	char buf[0x200];
	int n = 0;
	int i = 0;
	char* ent;
	char* targetSlot;
	char* actor;
	char* memberPtr;
	int flags = 0;
	int idx;
	int hits;
	int damage;
	int base;
	int kind;
	int dmg;

	if (*(int*) (action + 0x70) == -1) {
		he_FreeAction(action);
		return;
	}
	if (*(unsigned char*) (action + 0x78) & 4) {
		if (*(int*) (action + 0x70) != -2) {
			return;
		}
		he_FreeAction(action);
		return;
	}
	memberPtr = action + 0xc4;
	do {
		if (gm_LookupEntityRecordById(*(int*) memberPtr) != 0) {
			break;
		}
		n++;
		i++;
		memberPtr += 4;
	} while (i < 4);
	if (n == 4) {
		gm_AddTime(action + 0x52, 0, 1, 0);
		*(int*) (action + 0x84) = cm_SendSetHE(-1, action);
		return;
	}
	if (*(int*) (action + 0x70) == -2) {
		flags = 1;
		*(int*) (action + 0x70) = 1;
	}
	if (*(int*) (action + 0xd4) != -1) {
		*(int*) (action + 0x70) = 0x400;
	}
	idx = *(int*) (action + 0x70);
	switch (idx) {
	case 1:
		ent = gm_StartFilteredEntitySearch(1, 1, *(int*) (action + 0xb0));
		if (ent == 0) {
			goto ent0;
		}
		targetSlot = fcn_00502cd0(*(int*) (ent + 0x5d), 1, 0, 0x146);
		hits = 0;
		damage = 0;
		memberPtr = action + 0xc4;
		for (i = 4; i != 0; i--) {
			if (*(int*) memberPtr != -1) {
				actor = gm_LookupEntityRecordById(*(int*) memberPtr);
				if (actor != 0 && *(int*) (actor + 0x184) != 0) {
					base = (int) ((float) *(unsigned char*) (actor + 0x82) * 0.023809524f
					    + 1.0f);
					kind = (gm_RandomMod(4) & 0xffff) + 3;
					while (kind > 0) {
						damage += (gm_RandomMod((base + 1) * base)
						    & 0xffff) + base * 2;
						kind--;
					}
					hits++;
					cm_SendCancelCharacterActions(*(int*) memberPtr);
					ch_StartMovement(*(int*) memberPtr, *(int*) (ent + 1), *(int*) (targetSlot + 2),
					    0, 0, (char*) 0x6a5ad0);
					he_AssignActionSlot(0, 0, *(unsigned short*) actor, action);
				} else {
					*(int*) memberPtr = -1;
				}
			}
			memberPtr += 4;
		}
		if (flags) {
			he_FreeAction(action);
			return;
		}
		if (hits != 0) {
			dmg = fcn_0050b750(damage, g_773d75);
			io_FormatTextBuffer(buf, 0x1a6a, dmg);
			he_MessageBoxQuickjump(*(int*) ((char*) 0x7f4ca4 + *(unsigned short*) (action + 8) * 0x21c),
			    -1, buf, 0, 0x5ec, *(int*) (ent + 1), -1, 0, 0);
			cm_RequestMoveCredits(*(int*) ((char*) 0x7f4ca4 + *(unsigned short*) (action + 8) * 0x21c),
			    -1, g_773d75, dmg);
		}
		*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
		gm_AddTime(action + 0x52, 0, 2, 0);
		*(int*) (action + 0x84) = cm_SendSetHE(-1, action);
		sprintf(text, (char*) 0x6a5ac0, *(int*) (ent + 1));
		return;
	case 0:
		ent = gm_StartFilteredEntitySearch(1, 1, *(int*) (action + 0xac));
		if (ent == 0) {
ent0:
			*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
			gm_AddTime(action + 0x52, 0, 1, 0);
			*(int*) (action + 0x84) = cm_SendSetHE(-1, action);
			return;
		}
		memberPtr = action + 0xc4;
		for (i = 4; i != 0; i--) {
			if (*(int*) memberPtr != -1) {
				actor = gm_LookupEntityRecordById(*(int*) memberPtr);
				if (actor != 0 && *(int*) (actor + 0x184) != 0) {
					he_AssignActionSlot(0, 0, *(unsigned short*) actor, action);
					cm_SendCancelCharacterActions(*(int*) memberPtr);
					ch_StartMovement(*(int*) memberPtr, *(int*) (ent + 1), -1, 0, 1,
					    (char*) 0x6a5ad0);
				} else {
					*(int*) memberPtr = -1;
				}
			}
			memberPtr += 4;
		}
		sprintf(text, (char*) 0x6a5ab0, *(int*) (ent + 1));
		*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
		gm_AddTime(action + 0x52, 0, 2, 0);
		*(int*) (action + 0x84) = cm_SendSetHE(2, action);
		return;
	case 2:
		i = 0;
		memberPtr = action + 0xc4;
		do {
			if (*(int*) memberPtr != -1) {
				actor = gm_LookupEntityRecordById(*(int*) memberPtr);
				if (actor != 0 && *(int*) (actor + 0x184) != 0
				    && *(int*) (*(int*) (actor + 0x184) + 0x128) != 0) {
					return;
				}
			}
			i++;
			memberPtr += 4;
		} while (i < 4);
		*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
		gm_AddTime(action + 0x52, 0, 2, 0);
		*(int*) (action + 0x84) = cm_SendSetHE(3, action);
		return;
	case 0x400:
		memberPtr = action + 0xc4;
		i = 0;
		do {
			if (*(int*) memberPtr != -1) {
				actor = gm_LookupEntityRecordById(*(int*) memberPtr);
				if (actor != 0 && *(int*) (actor + 0x184) != 0
				    && *(int*) (*(int*) (actor + 0x184) + 0x128) != 0) {
					gm_AddTime(action + 0x52, 0, 4, 0);
					*(int*) (action + 0x84) = cm_SendSetHE(0x400, action);
					return;
				}
			}
			i++;
			memberPtr += 4;
		} while (i < 4);
		*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
		*(int*) (action + 0xd4) = -1;
		gm_AddTime(action + 0x52, 0, 2, 0);
		*(int*) (action + 0x84) = cm_SendSetHE(3, action);
		return;
	case 3:
		i = *(int*) (action + 0xd8);
		if (i <= 3 && *(int*) (action + 0xb4 + i * 4) != -1) {
			if (gm_GetElapsedMinutes(action + 0x44, (char*) 0x7f4c00) > 0x1e0) {
				*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
				gm_AddTime(action + 0x52, 0, 2, 0);
				*(int*) (action + 0x84) = cm_SendSetHE(1, action);
				return;
			}
			ent = gm_StartFilteredEntitySearch(1, 1, *(int*) (action + 0xb4 + *(int*) (action + 0xd8) * 4));
			*(int*) (action + 0xd8) = *(int*) (action + 0xd8) + 1;
			if (ent == 0) {
				*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
				gm_AddTime(action + 0x52, 0, 2, 0);
				*(int*) (action + 0x84) = cm_SendSetHE(1, action);
				return;
			}
			memberPtr = action + 0xc4;
			for (i = 4; i != 0; i--) {
				if (*(int*) memberPtr != -1) {
					actor = gm_LookupEntityRecordById(*(int*) memberPtr);
					if (actor != 0 && *(int*) (actor + 0x184) != 0) {
						char gest[3][0x20] = {
							"gestik/kopf_kratzen",
							"gestik/durch_haar_fahr",
							"gestik/kinn_kratzen"
						};

						he_AssignActionSlot(0, 0, *(unsigned short*) actor, action);
						cm_SendCancelCharacterActions(*(int*) memberPtr);
						ch_StartMovement(*(int*) memberPtr, *(int*) (ent + 1),
						    -1, 0, 1, (char*) 0x6a5ad0);
						cm_RequestPlayAnimation(*(int*) memberPtr,
						    gest[gm_RandomMod(3) & 0xffff],
						    (gm_RandomMod(2) & 0xffff) + 1);
					} else {
						*(int*) memberPtr = -1;
					}
				}
				memberPtr += 4;
			}
			*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
			gm_AddTime(action + 0x52, 0, 2, 0);
			*(int*) (action + 0x84) = cm_SendSetHE(2, action);
			sprintf(text, (char*) 0x6a5a8c, *(int*) (ent + 1));
			return;
		}
		if (gm_GetElapsedMinutes(action + 0x44, (char*) 0x7f4c00) > 0x1e0) {
			*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
			gm_AddTime(action + 0x52, 0, 2, 0);
			*(int*) (action + 0x84) = cm_SendSetHE(1, action);
			return;
		}
		*(int*) (action + 0xd8) = 0;
		*(char*) (action + 0xdc) = (char) (*(char*) (action + 0xdc) + 1);
		*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
		gm_AddTime(action + 0x52, 0, 2, 0);
		*(int*) (action + 0x84) = cm_SendSetHE(0, action);
		return;
	default:
		return;
	}
}
