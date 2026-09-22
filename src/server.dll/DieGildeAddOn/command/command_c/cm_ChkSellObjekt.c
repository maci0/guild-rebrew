
#include "../../../Units/Error/error.h"
#include "../command_internal.h"

char* __cdecl gm_ResolveParentEntity(char*);

/* Round-531: ascending REF VA decl order (R521 amt_fio lever; mid-pocket after alchemistry). */
// DATA: SERVER 0x1002c7d8
char s_cm_ChkSellObjekt___Not_enough_Cr_1002c7d8[] = "cm_ChkSellObjekt() Not enough Credits at destination";
// DATA: SERVER 0x1002c810
char s_cm_ChkSellObjekt___Inventory_vol_1002c810[] = "cm_ChkSellObjekt() Inventory voll";
// DATA: SERVER 0x1002c834
char s_cm_ChkSellObjekt___Lager_voll_1002c834[] = "cm_ChkSellObjekt() Lager voll";
// DATA: SERVER 0x1002c854
char s_cm_ChkSellObjekt___Invalid__ziel_1002c854[] = "cm_ChkSellObjekt() Invalid 'ziel_besitzer_id'";
// DATA: SERVER 0x1002c884
char s_cm_ChkSellObjekt___Not_enough_Ob_1002c884[] = "cm_ChkSellObjekt() Not enough Objekts at source";
// DATA: SERVER 0x1002c8b4
char s_cm_ChkSellObjekt___No_Objekts_at_1002c8b4[] = "cm_ChkSellObjekt() No Objekts at source";
// DATA: SERVER 0x1002c8dc
char s_cm_ChkSellObjekt___Invalid__quel_1002c8dc[] = "cm_ChkSellObjekt() Invalid 'quell_besitzer_id'";
unsigned short* __cdecl gm_ff_Objekt(int, int, int, ...);

/* Validation handler: checks preconditions for selling an object.
 * Resolves source/destination entities, verifies entity types
 * match, and checks inventory capacity. Logs error on invalid ID
 * or type mismatch. */

extern int __cdecl gm_eval_SlotVoll(char*, int, int);

// FUNCTION: SERVER 0x1000cbd0
// cm_ChkSellObjekt

int __cdecl cm_ChkSellObjekt(char* cmd)
{
	char* t_a;
	char* t_b;
	char* t_c;
	char* t_d;
	char* query_result;
	char* list_head;
	int field;
	unsigned short slot_index;

	if (*(int *) (cmd + 0x14) != -1) {
		*(int *) (cmd + 0x14) = gm_GetFieldByType(cmd, *(int *) (cmd + 0x14));
		if (!gm_ResolveEntityById((void **) &t_b, (void **) &t_d, (void **) &t_a, *(int *) (cmd + 0x14))) {
			LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x236b, s_cm_ChkSellObjekt___Invalid__quel_1002c8dc, 8);
			return 1;
		}
		list_head = t_b ? t_b + 0x5d : (t_d ? t_d + 0x14 : t_a + 0x178);
		query_result = (char *) gm_ff_Objekt(*(int *) list_head, 1, 0, *(unsigned short *) (cmd + 0x18));
		if (query_result == 0) {
			LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x2383, s_cm_ChkSellObjekt___No_Objekts_at_1002c8b4, 8);
			return 1;
		}
		if (*(int *) (query_result + 0xe) < *(int *) (cmd + 0x1f)) {
			LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x238f, s_cm_ChkSellObjekt___Not_enough_Ob_1002c884, 8);
			return 1;
		}
	}
	if (*(int *) (cmd + 0x10) != -1) {
		*(int *) (cmd + 0x10) = gm_GetFieldByType(cmd, *(int *) (cmd + 0x10));
		if (!gm_ResolveEntityById((void **) &t_c, (void **) &t_d, (void **) &t_a, *(int *) (cmd + 0x10))) {
			LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x23ab, s_cm_ChkSellObjekt___Invalid__ziel_1002c854, 8);
			return 1;
		}
		if (t_c) {
			slot_index = *(unsigned short *) (t_c + 0x27);
			if (slot_index != 0xffff) {
				list_head = (char *) (0x100358a0 + slot_index * 0x21c);
			} else {
				list_head = 0;
			}
		} else if (t_d) {
			slot_index = *(unsigned short *) t_d;
			if (slot_index == 0x2a || slot_index == 0x116 || slot_index == 0x1dd) {
				if (gm_eval_SlotVoll(t_d, *(unsigned short *) (cmd + 0x18), *(int *) (cmd + 0x1f)) < *(int *) (cmd + 0x1f)) {
					LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x23cd, s_cm_ChkSellObjekt___Lager_voll_1002c834, 8);
					return 1;
				}
			}
			list_head = gm_ResolveParentEntity(t_d);
		} else {
			if (gm_CheckInventoryCapacity(t_a, *(unsigned short *) (cmd + 0x18), *(int *) (cmd + 0x1f)) < *(int *) (cmd + 0x1f)) {
				LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x23e3, s_cm_ChkSellObjekt___Inventory_vol_1002c810, 8);
				return 1;
			}
			list_head = t_a;
		}
		if (*(int *) (cmd + 0x23) != 0 && list_head != 0) {
			if (((int (__cdecl *) (int, unsigned char)) gm_QueryEntitySum)(*(int *) (list_head + 0x178), *(unsigned char *) (cmd + 0x1e)) < *(int *) (cmd + 0x1f) * *(int *) (cmd + 0x23)) {
				LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x23ff, s_cm_ChkSellObjekt___Not_enough_Cr_1002c7d8, 8);
				return 1;
			}
		}
	}
	return 0;
}
char s_D__Develop_DieGildeAddOn_command_1002c748[43] = {
    0x44, 0x3a, 0x5c, 0x44, 0x65, 0x76, 0x65, 0x6c, 0x6f, 0x70, 0x5c, 0x44, 0x69, 0x65, 0x47, 0x69,
    0x6c, 0x64, 0x65, 0x41, 0x64, 0x64, 0x4f, 0x6e, 0x5c, 0x63, 0x6f, 0x6d, 0x6d, 0x61, 0x6e, 0x64,
    0x5c, 0x63, 0x6f, 0x6d, 0x6d, 0x61, 0x6e, 0x64, 0x2e, 0x63, 0x00,
};
