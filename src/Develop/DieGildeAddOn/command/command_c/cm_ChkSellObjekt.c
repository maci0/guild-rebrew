
#include "../../../Units/Error/error.h"
#include "../command_internal.h"

char* __cdecl gm_ResolveParentEntity(char*);

/* Round-531: ascending REF VA decl order (R521 amt_fio lever; mid-pocket after alchemistry). */
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
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x236b, "cm_ChkSellObjekt() Invalid 'quell_besitzer_id'", 8);
			return 1;
		}
		list_head = t_b ? t_b + 0x5d : (t_d ? t_d + 0x14 : t_a + 0x178);
		query_result = (char *) gm_ff_Objekt(*(int *) list_head, 1, 0, *(unsigned short *) (cmd + 0x18));
		if (query_result == 0) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2383, "cm_ChkSellObjekt() No Objekts at source", 8);
			return 1;
		}
		if (*(int *) (query_result + 0xe) < *(int *) (cmd + 0x1f)) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x238f, "cm_ChkSellObjekt() Not enough Objekts at source", 8);
			return 1;
		}
	}
	if (*(int *) (cmd + 0x10) != -1) {
		*(int *) (cmd + 0x10) = gm_GetFieldByType(cmd, *(int *) (cmd + 0x10));
		if (!gm_ResolveEntityById((void **) &t_c, (void **) &t_d, (void **) &t_a, *(int *) (cmd + 0x10))) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x23ab, "cm_ChkSellObjekt() Invalid 'ziel_besitzer_id'", 8);
			return 1;
		}
		if (t_c) {
			slot_index = *(unsigned short *) (t_c + 0x27);
			if (slot_index != 0xffff) {
				list_head = (char *) ((int) g_slot_table + slot_index * 0x21c);
			} else {
				list_head = 0;
			}
		} else if (t_d) {
			slot_index = *(unsigned short *) t_d;
			if (slot_index == 0x2a || slot_index == 0x116 || slot_index == 0x1dd) {
				if (gm_eval_SlotVoll(t_d, *(unsigned short *) (cmd + 0x18), *(int *) (cmd + 0x1f)) < *(int *) (cmd + 0x1f)) {
					LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x23cd, "cm_ChkSellObjekt() Lager voll", 8);
					return 1;
				}
			}
			list_head = gm_ResolveParentEntity(t_d);
		} else {
			if (gm_CheckInventoryCapacity(t_a, *(unsigned short *) (cmd + 0x18), *(int *) (cmd + 0x1f)) < *(int *) (cmd + 0x1f)) {
				LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x23e3, "cm_ChkSellObjekt() Inventory voll", 8);
				return 1;
			}
			list_head = t_a;
		}
		if (*(int *) (cmd + 0x23) != 0 && list_head != 0) {
			if (((int (__cdecl *) (int, unsigned char)) gm_QueryEntitySum)(*(int *) (list_head + 0x178), *(unsigned char *) (cmd + 0x1e)) < *(int *) (cmd + 0x1f) * *(int *) (cmd + 0x23)) {
				LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x23ff, "cm_ChkSellObjekt() Not enough Credits at destination", 8);
				return 1;
			}
		}
	}
	return 0;
}
