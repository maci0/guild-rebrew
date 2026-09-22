
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wpointer-to-int-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

/* Round-532: ascending REF VA decl order (R521/R531 mid-pocket lever; abuts ChkSellObjekt). */
// DATA: SERVER 0x1002c90c
char s_cm_ChkChangeAttribute___Target_obj_1002c90c[] = "cm_ChkChangeAttribute() Invalid action on player <<PartnerID already set>>";
// DATA: SERVER 0x1002c958
char s_cm_ChkChangeAttribute___Source_obj_1002c958[] = "cm_ChkChangeAttribute() Invalid action on player <<ID does not exist>>";
// DATA: SERVER 0x1002c9a0
char s_cm_ChkChangeAttribute___Error_i_1002c9a0[] = "cm_ChkChangeAttribute() Invalid action on player <<Change ID>>";
// DATA: SERVER 0x1002c9e0
char s_cm_ChkChangeAttribute___Invalid_I_1002c9e0[] = "cm_ChkChangeAttribute() Invalid Id";

/* Validation handler: resolves entity by ID and validates each
 * attribute field descriptor (kind/value/offset) in the command
 * payload. Returns 1 on invalid entity ID. */

// FUNCTION: SERVER 0x1000cde0
// cm_ChkChangeAttribute

int __cdecl cm_ChkChangeAttribute(int cmd, char* result)
{
	char* t_a;
	char* t_b;
	char* t_d;
	unsigned int i;
	char* field_cursor;
	char* base;
	int addr;
	int kind;
	int n;
	char* rec;
	int entity_id;

	*(int *) (cmd + 0x10) = gm_GetFieldByType((char *) cmd, *(int *) (cmd + 0x10));
	if (!gm_ResolveEntityById((void **) &t_b, (void **) &t_a, (void **) &t_d, *(int *) (cmd + 0x10))) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x243d, s_cm_ChkChangeAttribute___Invalid_I_1002c9e0, 1);
		return 1;
	}
	if (t_b)
		base = t_b;
	else if (t_a)
		base = t_a;
	else
		base = t_d;
	field_cursor = (char *) cmd + 0x15;
	for (i = 0; i < *(unsigned char *) (cmd + 0x14); i++) {
		kind = *(signed char *) field_cursor;
		field_cursor++;
		n = *(signed char *) field_cursor;
		field_cursor++;
		addr = *(unsigned short *) field_cursor + (int) base;
		field_cursor += 2;
		if (t_d != 0) {
			if (addr == (int) t_d + 4) {
				LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x2479, s_cm_ChkChangeAttribute___Error_i_1002c9a0, 1);
				return 1;
			}
			if (addr == (int) t_d + 0x5c) {
				entity_id = *(int *) field_cursor + *(int *) (t_d + 0x5c);
				rec = (char *) gm_LookupEntityRecordById(entity_id);
				if (rec == 0) {
					LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x249b, s_cm_ChkChangeAttribute___Source_obj_1002c958, 1);
					return 1;
				}
				if (*(int *) (rec + 0x5c) != -1 && *(int *) (rec + 0x5c) != *(int *) (t_d + 4)) {
					LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x24a5, s_cm_ChkChangeAttribute___Target_obj_1002c90c, 1);
					return 1;
				}
			}
		}
		switch (kind) {
		case 1:
			if ((unsigned) n > 0) field_cursor += n;
			break;
		case 2:
			if ((unsigned) n > 0) field_cursor += 2 * n;
			break;
		case 4:
			if ((unsigned) n > 0) field_cursor += 4 * n;
			break;
		}
	}
	return 0;
}
