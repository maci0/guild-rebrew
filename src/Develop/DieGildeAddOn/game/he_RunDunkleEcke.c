#include "Develop/Units/d2.v1/client_dialog_helpers.h"
#include "Develop/client_types.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"
/* Dark corner dialog ("Dunkle Ecke"). Resolves the current target, offers
 * the neighbouring entities as the next target and books the skill checks
 * that decide whether the corner stays dark. */

#include "Develop/DieGildeAddOn/game/client_straftat.h"
extern int gm_RandomSearchSteps[];
extern char* cm_PacketDeltaBase;
typedef struct BuildingRow557460 { unsigned char kind; char fields[0x24c]; } BuildingRow557460;

int __cdecl cm_GetCommandStatus(int h);
int* __cdecl cm_GetCommandResult(int h);
int __cdecl cm_SendSetHE(int a, char* dlg);
void __cdecl cm_SendCancelCharacterActions(int a);
void __cdecl ch_StartMovement(int a, int b, int c, int d, int e, char* s);
void __cdecl he_FreeAction(char* dlg);
void __cdecl fcn_005015e0(int* out, int a, int b, int c);
int __cdecl gm_IsEntityAtBuilding(char* e, char* h);
char* __cdecl gm_QueryEntities(int a, int b, int c, int d, int e);
int __cdecl gm_CompareGameTime(char* a, char* b);
void __cdecl gm_AddTime(int* r, int a, int b, int c);
float __cdecl gm_GetEntitySkill(char* e, int i);
float __cdecl fcn_0042e450(void);
int __cdecl fcn_0042e410(int n);
void __cdecl cm_RequestLinkEvidence(int a, int b);

/* ADDRESS: GOLDTL 0x00557460 */
/* ADDRESS: GOLDDE 0x0053d7c0 */
void __cdecl he_RunDunkleEcke(char* dlg)
{
	char* hit;
	char text[0x400];

	if (*(int*) (dlg + 0x70) == -1 || *(int*) (dlg + 0x70) == -2) {
		if (*(unsigned char*) (dlg + 0x78) & 2) {
			char* e;

			e = gm_LookupEntityRecordById(*(int*) (dlg + 0xac));
			if (e != 0) {
				cm_SendCancelCharacterActions(*(int*) (e + 4));
				cm_RequestKillSpieler(*(int*) (e + 4), 1);
			}
		}
		he_FreeAction(dlg);
		return;
	}
	if (*(unsigned char*) (dlg + 0x78) & 4) {
		return;
	}
	if (*(int*) (dlg + 0x84) != -1) {
		if (cm_GetCommandStatus(*(int*) (dlg + 0x84)) == 0) {
			return;
		}
	}
	switch (*(int*) (dlg + 0x70)) {
	case 0: {
		int* p;
		int v;

		if (cm_GetCommandStatus(*(int*) (dlg + 0xac)) == 1) {
			p = cm_GetCommandResult(*(int*) (dlg + 0xac));
			v = *(int*) ((char*) p + 4);
			*(int*) (dlg + 0xac) = v;
			gm_AddTime((int*) (dlg + 0x52), 0, 1, 0);
			*(int*) (dlg + 0x84) = cm_SendSetHE(1, dlg);
			return;
		}
		gm_AddTime((int*) (dlg + 0x52), 0x18, 0, 0);
		*(int*) (dlg + 0x84) = cm_SendSetHE(4, dlg);
		return;
	}
	case 1: {
		int scan;
		int tries;
		unsigned char kind;
		unsigned int mask;
		unsigned int mask2;
		char* e;

		scan = *(int*) (dlg + 0xc4);
		tries = 0x100;
		do {
			hit = (char*) (lpGebaeudeINST + scan * 0xa9);
			kind = ((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*(unsigned char*) hit].category;
			mask = 0;
			mask2 = 0;
			if (kind > 0x1f) {
				mask2 = 1u << ((kind - 0x20) & 0x1f);
			} else {
				mask = 1u << kind;
			}
			if (((mask & 0xa7fcc3a6) || (mask2 & 1))
			    && *(int*) (hit + 1) != *(int*) (dlg + 0xb0)) {
				break;
			}
			hit = 0;
			tries--;
			scan = (scan + *(int*) (dlg + 0xc8)) % 0x100;
		} while (tries != 0);
		scan = (scan + *(int*) (dlg + 0xc8)) % 0x100;
		*(int*) (dlg + 0xc4) = scan;
		if (hit == 0) {
			gm_AddTime((int*) (dlg + 0x52), 0, 1, 0);
			*(int*) (dlg + 0x84) = cm_SendSetHE(-1, dlg);
			return;
		}
		io_FormatTextBuffer(text, 0x6a5f7c, (void*) hit);
		e = gm_LookupEntityRecordById(*(int*) (dlg + 0xac));
		if (e != 0) {
			cm_SendCancelCharacterActions(*(int*) (e + 4));
			ch_StartMovement(*(int*) (e + 4), *(int*) (hit + 1), -1, 0, 1,
			    "Dunkle Ecke");
			gm_AddTime((int*) (dlg + 0x52), 0, 5, 0);
			*(int*) (dlg + 0xb8) = *(int*) (hit + 1);
			*(int*) (dlg + 0x84) = cm_SendSetHE(2, dlg);
			return;
		}
		gm_AddTime((int*) (dlg + 0x52), 0, 1, 0);
		*(int*) (dlg + 0x84) = cm_SendSetHE(-1, dlg);
		return;
	}
	case 2: {
		char* e;
		float f;

		fcn_005015e0((int*) &hit, 0, 0, *(int*) (dlg + 0xb8));
		gm_AddTime((int*) (dlg + 0x52), 0, 5, 0);
		if (hit == 0) {
			*(int*) (dlg + 0x84) = cm_SendSetHE(-1, dlg);
			return;
		}
		e = gm_LookupEntityRecordById(*(int*) (dlg + 0xac));
		if (e == 0) {
			gm_AddTime((int*) (dlg + 0x52), 0, 1, 0);
			*(int*) (dlg + 0x84) = cm_SendSetHE(-1, dlg);
			return;
		}
		if (gm_IsEntityAtBuilding(e, (char*) hit) == 0) {
			*(int*) (dlg + 0x70) = 2;
			gm_AddTime((int*) (dlg + 0x52), 0, 5, 0);
			*(int*) (dlg + 0x84) = cm_SendSetHE(2, dlg);
			return;
		}
		*(int*) (dlg + 0xbc) = *(int*) (dlg + 0xbc) - 1;
		f = gm_GetEntitySkill(gm_EntitySlotTable
		    + *(unsigned short*) (hit + 0x27) * 0x21c, 2);
		if (*(int*) (dlg + 0xc0) < 1) {
			*(int*) (dlg + 0xc0) = *(int*) (dlg + 0xc0) + 1;
		} else {
			*(int*) (dlg + 0xc0) +=
			    (fcn_0042e450() * 0.5f < f);
		}
		if (*(int*) (dlg + 0xc0) > 2) {
			*(int*) (dlg + 0xbc) = 0;
		}
		fcn_005015e0((int*) &hit, 0, 0, *(int*) (dlg + 0xb0));
		if (hit == 0) {
			goto fail;
		}
		if (*(short*) (hit + 0x27) == -1) {
			goto fail;
		}
		if (*(int*) (dlg + 0xbc) > 0) {
			*(int*) (dlg + 0x84) = cm_SendSetHE(1, dlg);
			return;
		}
		cm_SendCancelCharacterActions(*(int*) (e + 4));
		ch_StartMovement(*(int*) (e + 4), *(int*) (hit + 1),
		    *(int*) (dlg + 0xb4), 0, 0, "Dunkle Ecke");
		*(int*) (dlg + 0x84) = cm_SendSetHE(3, dlg);
		return;
	}
	case 3: {
		char* e;
		char* rec;
		int found[3];
		int idx;
		int step;
		int tries;
		int i;
		int j;
		unsigned int off;

		gm_AddTime((int*) (dlg + 0x52), 0, 5, 0);
		fcn_005015e0((int*) &hit, 0, 0, *(int*) (dlg + 0xb0));
		if (hit == 0) {
			goto fail;
		}
		if (*(short*) (hit + 0x27) == -1) {
			goto fail;
		}
		e = gm_LookupEntityRecordById(*(int*) (dlg + 0xac));
		if (e != 0 && gm_IsEntityAtBuilding(e, (char*) hit) == 0) {
			*(int*) (dlg + 0x70) = 3;
			gm_AddTime((int*) (dlg + 0x52), 0, 5, 0);
			*(int*) (dlg + 0x84) = cm_SendSetHE(3, dlg);
			return;
		}
		{
			int selectedCount;

			selectedCount = *(int*) (dlg + 0xc0);
			if (selectedCount >= 3) {
				selectedCount = 3;
			} else if (selectedCount <= 0) {
				selectedCount = 0;
			}
			*(int*) (dlg + 0xc0) = selectedCount;
		}
		if (*(int*) (dlg + 0xc0) != 0) {
			found[0] = -1;
			found[1] = -1;
			found[2] = -1;
			idx = (unsigned short) fcn_0042e410(0x200);
			step = gm_RandomSearchSteps[fcn_0042e410(8) & 0xffff];
			tries = 0x200;
			i = 0;
			do {
				if (i >= *(int*) (dlg + 0xc0)) {
					break;
				}
				rec = (char*) &cm_CrimeRecords[idx];
				if (*(int*) rec != -1 && *(int*) (rec + 0x25) == 1
				    && *(int*) (rec + 0x16) != *(int*) (gm_EntitySlotTable
				    + *(unsigned short*) (hit + 0x27) * 0x21c + 4)
				    && gm_CompareGameTime(dlg + 0x44, rec + 4) != 1) {
					found[i] = *(int*) rec;
					i++;
				}
				idx = (idx + step) % 0x200;
				tries--;
			} while (tries != 0);
			*(int*) (dlg + 0xc0) = i;
			j = 0;
			while (j < i) {
				cm_RequestLinkEvidence(found[j], *(int*) (gm_EntitySlotTable
				    + *(unsigned short*) (hit + 0x27) * 0x21c + 4));
				j++;
			}
			rec = gm_QueryEntities(*(int*) (hit + 0x5d), 2, 6, 0, 0x12c);
			if (rec != 0) {
				cm_BeginPacketFieldDelta(rec, *(int*) (rec + 2));
				j = 0;
				while (j < 3) {
					off = (unsigned int) (rec + 0x1c + j * 4 - cm_PacketDeltaBase);
					cm_AppendPacketFieldDelta(4, 1, (int) off, &found[j]);
					j++;
				}
				cm_RequestChangeAttribute();
			}
		}
		io_FormatTextBuffer(text,
		    *(int*) (dlg + 0xc0) != 0 ? 0x18a9 : 0x18aa);
		((void (__cdecl*) (int, int, char*, int, int, int, int, int, char*))
		    fcn_00545e80)(*(int*) (gm_EntitySlotTable
		    + *(unsigned short*) (hit + 0x27) * 0x21c + 4), -1, text, 0,
		    0x5ec, *(int*) (hit + 1), *(int*) (dlg + 0xb4), 0,
		    (char*) 0x6b5c60);
fail:
		*(int*) (dlg + 0x84) = cm_SendSetHE(-1, dlg);
		return;
	}
	case 4: {
		char* rec;
		int found[3];
		int idx;
		int step;
		int tries;
		int i;
		int j;
		int k;
		float f;

		fcn_005015e0((int*) &hit, 0, 0, *(int*) (dlg + 0xb0));
		if (hit == 0) {
			goto fail;
		}
		if (*(short*) (hit + 0x27) == -1) {
			goto fail;
		}
		*(int*) (dlg + 0xc0) = 0;
		k = 3;
		do {
			f = gm_GetEntitySkill(gm_EntitySlotTable
			    + *(unsigned short*) (hit + 0x27) * 0x21c, 2);
			*(int*) (dlg + 0xc0) = *(int*) (dlg + 0xc0)
			    + (fcn_0042e450() * 0.66f < f);
			k--;
		} while (k != 0);
		if (*(int*) (dlg + 0xc0) != 0) {
			found[0] = -1;
			found[1] = -1;
			found[2] = -1;
			idx = (unsigned short) fcn_0042e410(0x200);
			step = gm_RandomSearchSteps[fcn_0042e410(8) & 0xffff];
			tries = 0x200;
			i = 0;
			do {
				if (i >= *(int*) (dlg + 0xc0)) {
					break;
				}
				rec = (char*) &cm_CrimeRecords[idx];
				if (*(int*) rec != -1 && *(int*) (rec + 0x25) == 1
				    && *(int*) (rec + 0x16) != *(int*) (gm_EntitySlotTable
				    + *(unsigned short*) (hit + 0x27) * 0x21c + 4)
				    && gm_CompareGameTime(dlg + 0x44, rec + 4) != 1) {
					found[i] = *(int*) rec;
					i++;
				}
				idx = (idx + step) % 0x200;
				tries--;
			} while (tries != 0);
			*(int*) (dlg + 0xc0) = i;
			j = 0;
			while (j < i) {
				cm_RequestLinkEvidence(found[j], *(int*) (gm_EntitySlotTable
				    + *(unsigned short*) (hit + 0x27) * 0x21c + 4));
				j++;
			}
			rec = gm_QueryEntities(*(int*) (hit + 0x5d), 2, 6, 0, 0x12c);
			if (rec != 0) {
				cm_BeginPacketFieldDelta(rec, *(int*) (rec + 2));
				j = 0;
				while (j < 3) {
					cm_AppendPacketFieldDelta(4, 1, (int) (rec + 0x1c + j * 4 - cm_PacketDeltaBase),
					    &found[j]);
					j++;
				}
				cm_RequestChangeAttribute();
			}
		}
		io_FormatTextBuffer(text,
		    *(int*) (dlg + 0xc0) != 0 ? 0x18a9 : 0x18aa);
		((void (__cdecl*) (int, int, char*, int, int, int, int, int, char*))
		    fcn_00545e80)(*(int*) (gm_EntitySlotTable
		    + *(unsigned short*) (hit + 0x27) * 0x21c + 4), -1, text, 0,
		    0x5ec, *(int*) (hit + 1), *(int*) (dlg + 0xb4), 0,
		    (char*) 0x6b5c60);
		*(pos14_7f4c00*) (dlg + 0x52) = *(pos14_7f4c00*) &gm_GameTime;
		goto fail;
	}
	}
}
