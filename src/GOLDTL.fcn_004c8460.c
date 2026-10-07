extern char* g_item_def_table;

#include "Develop/DieGildeAddOn/command/command_internal.h"

extern unsigned char g_current_season;

short* __cdecl gm_ResolveParentEntity(short*);
double __cdecl gm_CalculateProductionValue(uint, int);
int __cdecl gm_EntityAccumulate(void*);

unsigned short* __cdecl gm_ff_Objekt(int, int, int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
int __cdecl gm_RemoveObjectByType(void**, unsigned int);

extern int g_14cbca0;
extern int g_699364;

// FUNCTION: GOLD 0x4c78c0
// FUNCTION: GOLDTL 0x004c8460

int __cdecl fcn_004c8460(int msg, char* result)
{
	int quantity;
	int loop_count;
	ushort* obj_entry;
	char* recipe;
	int production_cap;
	ushort* material_iter;
	long production_value;
	short* player_entry;
	short* lager;
	char* recipe_def;
	short* owner;
	char* recipe_shift;
	uint recipe_idx;

	if (g_14cbca0 != -1)
		g_699364 = *(int*) (msg + 0x1a);
	quantity = gm_GetFieldByType((char*)msg, *(int*)(msg + 0x10));
	*(int*)(msg + 0x10) = quantity;
	quantity = gm_ResolveEntityById((void**)0, (void**)&lager, (void**)0, quantity);
	if (quantity == 0) {
		return 1;
	}
	if ((*lager != 0x2a) && (*lager != 0x116)) {
		return 1;
	}
	owner = gm_ResolveParentEntity(lager);
	if (owner == (short*)0) {
		return 1;
	}
	recipe_idx = (uint)*(ushort*)(msg + 0x14);
	quantity = *(int*)(msg + 0x16);
	recipe_shift = g_item_def_table + (recipe_idx << 6);
	recipe_def = recipe_shift + recipe_idx;
	material_iter = (ushort*)(recipe_def + 0x26);
	for (loop_count = 0; loop_count < 4; loop_count++) {
		if (material_iter[4] != 0) {
			obj_entry = (ushort*)gm_ff_Objekt(*(int*)(lager + 10), 1, 0, (uint)material_iter[4]);
			if (obj_entry != (ushort*)0) {
				recipe = (char*)gm_GetMsgField((int)lager, (int)obj_entry);
				if (quantity >= (int)recipe / (int)(uint)*material_iter) {
					recipe = (char*)gm_GetMsgField((int)lager, (int)obj_entry);
					quantity = (int)recipe / (int)(uint)*material_iter;
				}
			}
			else {
				quantity = 0;
			}
		}
		material_iter = material_iter + 1;
	}
	recipe = recipe_def;
	production_cap = gm_eval_SlotVoll(
		(char*)lager,
		(uint)*(ushort*)(msg + 0x14),
		(uint)*(ushort*)(recipe_def + 0x36) * quantity
	);
	production_cap = production_cap / (int)(uint)*(ushort*)(recipe + 0x36);
	if (quantity >= production_cap) {
		quantity = production_cap;
	}
	if (quantity == 0) {
		if (result != (char*)0) {
			result[1] = '\b';
		}
		return 1;
	}
	production_cap = 0;
	material_iter = (ushort*)(recipe_def + 0x2e);
	for (; production_cap < 4; production_cap++, material_iter++) {
		if (*material_iter != 0) {
			obj_entry = (ushort*)gm_ff_Objekt(*(int*)(lager + 10), 1, 0, (uint)*material_iter);
			if (obj_entry == (ushort*)0) {
				if (result != (char*)0) {
					result[1] = '\b';
				}
				return 1;
			}
			*(uint*)(obj_entry + 7) = *(int*)(obj_entry + 7) - (uint)material_iter[-4] * quantity;
			recipe = gm_FindSlotById((uint)g_current_season, (uint)*material_iter);
			if (recipe != (char*)0) {
				*(uint*)(recipe + 0x14) = *(int*)(recipe + 0x14) + (uint)*(ushort*)(recipe_def + 0x36) * quantity;
			}
			if (*(int*)(obj_entry + 7) == 0) {
				gm_RemoveObjectByType((char**)(lager + 10), (uint)*material_iter);
			}
		}
	}
	material_iter = (ushort*)gm_ff_Objekt(*(int*)(lager + 10), 1, 0, (uint)*(ushort*)(msg + 0x14));
	recipe = recipe_def;
	if (material_iter != (ushort*)0) {
		*(uint*)(material_iter + 7) = *(int*)(material_iter + 7) + (uint)*(ushort*)(recipe_def + 0x36) * quantity;
	}
	else {
		material_iter = (ushort*)gm_AllocObjekt(
			*(int*)(lager + 1),
			(uint)*(ushort*)(msg + 0x14),
			(uint)*(ushort*)(recipe_def + 0x36) * quantity
		);
		if (material_iter == (ushort*)0) {
			if (result != (char*)0) {
				result[1] = '\x06';
			}
			return 1;
		}
		if (*lager == 0x2a) {
			*(int*)(material_iter + 7) = *(int*)(material_iter + 7) + 1;
		}
		if (((*recipe == '\x17') || (*recipe == '%')) &&
			((*lager == 0x2a || (*lager == 0x116))) &&
			(((char)owner[1] == '\x06' || ((char)owner[1] == '\a')))) {
			*(int*)(material_iter + 0xe) = 4;
		}
	}
	production_value = (long)(gm_CalculateProductionValue((uint)*(ushort*)(msg + 0x14), 100) * quantity);
	production_cap = gm_EntityAccumulate(lager);
	if (production_cap != 0) {
		*(int*)(production_cap + 0x4d) = *(int*)(production_cap + 0x4d) + (int)production_value;
	}
	recipe = gm_FindSlotById((uint)g_current_season, (uint)*(ushort*)(msg + 0x14));
	if (recipe != (char*)0) {
		*(uint*)(recipe + 0x10) = *(int*)(recipe + 0x10) + (uint)*(ushort*)(recipe_def + 0x36) * quantity;
	}
	player_entry = gm_GetEntityTableEntry((char*)owner);
	if (player_entry != (short*)0) {
		*(int*)(player_entry + 0x12) = *(int*)(player_entry + 0x12) + (int)production_value;
	}
	if ((result != (char*)0) && ((*result = '\x01', *(int*)(msg + 0x10) != -1))) {
		result[1] = '\x03';
		*(ushort**)(result + 6) = material_iter;
	}
	return 0;
}
