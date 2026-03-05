// STATUS: MATCHING
// BLOCKER: jump condition swap, loop rotation / branch layout, stack frame choice (push vs sub esp), zero-extend pattern (xor vs mov)
// ORIGIN: GAME
// SIZE: 517

#include "../../../Units/Error/error.h"
#include "../command_internal.h"

char* __cdecl gm_ResolveParentEntity(char*);

extern char s_cm_ChkSellObjekt___Invalid__quel_1002c8dc[];
extern char s_cm_ChkSellObjekt___No_Objekts_at_1002c8b4[];
extern char s_cm_ChkSellObjekt___Not_enough_Ob_1002c884[];
extern char s_cm_ChkSellObjekt___Invalid__ziel_1002c854[];
extern char s_cm_ChkSellObjekt___Inventory_vol_1002c810[];
extern char s_cm_ChkSellObjekt___Lager_voll_1002c834[];
extern char s_cm_ChkSellObjekt___Not_enough_Cr_1002c7d8[];
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);

// FUNCTION: SERVER 0x1000cbd0
int __cdecl cm_ChkSellObjekt(char* cmd)
{
	short obj_type;
	int result;
	char* cmd_ptr;
	char* parent;
	void* src_bldg;
	void* dst_bldg;

	cmd_ptr = cmd;
	if (*(int*) (cmd_ptr + 0x14) != -1) {
		result = gm_GetFieldByType(cmd_ptr, *(int*) (cmd_ptr + 0x14));
		*(int*) (cmd_ptr + 0x14) = result;
		result = gm_ResolveEntityById(&src_bldg, (void**) &cmd, (void**) &parent, result);
		if (result == 0) {
			LogMessageInternal(
				s_D__Develop_DieGildeAddOn_command_1002c748,
				0x236b,
				s_cm_ChkSellObjekt___Invalid__quel_1002c8dc,
				8
			);
			return 1;
		}
		if (src_bldg != (void*) 0) {
			result = *(int*) ((char*) src_bldg + 0x5d);
		}
		else if (cmd != (char*) 0) {
			result = *(int*) (cmd + 0x14);
		}
		else {
			result = *(int*) (parent + 0x178);
		}
		result = (int) gm_StartEntityQuery(result, 1, 0, (uint) * (ushort*) (cmd_ptr + 0x18));
		if (result == 0) {
			LogMessageInternal(
				s_D__Develop_DieGildeAddOn_command_1002c748,
				0x2383,
				s_cm_ChkSellObjekt___No_Objekts_at_1002c8b4,
				8
			);
			return 1;
		}
		if (*(int*) ((char*) result + 0xe) < *(int*) (cmd_ptr + 0x1f)) {
			LogMessageInternal(
				s_D__Develop_DieGildeAddOn_command_1002c748,
				0x238f,
				s_cm_ChkSellObjekt___Not_enough_Ob_1002c884,
				8
			);
			return 1;
		}
	}
	if (*(int*) (cmd_ptr + 0x10) != -1) {
		result = gm_GetFieldByType(cmd_ptr, *(int*) (cmd_ptr + 0x10));
		*(int*) (cmd_ptr + 0x10) = result;
		result = gm_ResolveEntityById(&dst_bldg, (void**) &cmd, (void**) &parent, result);
		if (result == 0) {
			LogMessageInternal(
				s_D__Develop_DieGildeAddOn_command_1002c748,
				0x23ab,
				s_cm_ChkSellObjekt___Invalid__ziel_1002c854,
				8
			);
			return 1;
		}
		if (dst_bldg != (void*) 0) {
			if (*(ushort*) ((char*) dst_bldg + 0x27) == (ushort) 0xffff) {
				parent = (char*) 0;
			}
			else {
				parent = g_static_entity_table_358a0 + (uint) * (ushort*) ((char*) dst_bldg + 0x27) * 0x21c;
			}
		}
		else if (cmd != (char*) 0) {
			obj_type = *(short*) cmd;
			if (obj_type == 0x2a || obj_type == 0x116 || obj_type == 0x1dd) {
				result =
					gm_KannObjektHergestellt(cmd, (int) (uint) * (ushort*) (cmd_ptr + 0x18), *(int*) (cmd_ptr + 0x1f));
				if (result < *(int*) (cmd_ptr + 0x1f)) {
					LogMessageInternal(
						s_D__Develop_DieGildeAddOn_command_1002c748,
						0x23cd,
						s_cm_ChkSellObjekt___Lager_voll_1002c834,
						8
					);
					return 1;
				}
			}
			parent = gm_ResolveParentEntity(cmd);
		}
		else {
			result = gm_CheckInventoryCapacity(parent, (uint) * (ushort*) (cmd_ptr + 0x18), *(int*) (cmd_ptr + 0x1f));
			if (result < *(int*) (cmd_ptr + 0x1f)) {
				LogMessageInternal(
					s_D__Develop_DieGildeAddOn_command_1002c748,
					0x23e3,
					s_cm_ChkSellObjekt___Inventory_vol_1002c810,
					8
				);
				return 1;
			}
		}
		if (*(int*) (cmd_ptr + 0x23) != 0 && parent != (char*) 0) {
			result = gm_QueryEntitySum(*(int*) (parent + 0x178), (int) *(unsigned char*) (cmd_ptr + 0x1e));
			if (result < *(int*) (cmd_ptr + 0x1f) * *(int*) (cmd_ptr + 0x23)) {
				LogMessageInternal(
					s_D__Develop_DieGildeAddOn_command_1002c748,
					0x23ff,
					s_cm_ChkSellObjekt___Not_enough_Cr_1002c7d8,
					8
				);
				return 1;
			}
		}
	}
	return 0;
}
