// FUNCTION: SERVER 0x1000e140

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 993B
 *    CFlags:
 *    Symbol: _cm_ExecProduction
 *    Files: DieGildeAddOn/command/command.c * / *
 * int __cdecl cm_ExProdObjekt(int msg,char *result)
 */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

extern char* g_unknown_1de450;
extern unsigned char g_current_season;

short* __cdecl gm_ResolveParentEntity(short*);
double __cdecl gm_CalculateProductionValue(uint, int);
int __cdecl gm_WalkEntityChain(int);

extern char s_cm_ExecProduction___Invalid__lager_1002cf9c[];
extern char s_cm_ExecProduction___Lager_has_wron_1002cf74[];
extern char s_cm_ExecProduction___Lager_hat_kein_1002cf48[];
extern char s_cm_ExProdObjekt___Cannot_produce___1002cf1c[];
extern char s_cm_ExProdObjekt___Rohstoff_versc_1002cef4[];
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
int __cdecl gm_RemoveObjectByType(void**, unsigned int);

/* Execution handler: produces an object. Processes a production
 * message with entity lookup, object allocation/deallocation,
 * and inventory management for crafted goods.
 *
 * Conversion state: pure C (naked wrapper removed).  The frame and the
 * gm_GetFieldByType/gm_ResolveEntityById calls match byte-for-byte.  The
 * three error LogMessageInternal epilogues diverge because MSVC6 tail-
 * merges the identical early returns (a `goto`-to-shared-return shape
 * keeps the calls inline but breaks the tail, so the natural per-error
 * `return 1` is kept — semantically correct), and the material loop
 * diverges by the pre-loop dead store `mov [esp+0x18],ebx`
 * (saved_quantity = quantity overwritten by 4 — MSVC6's dead-store
 * elimination removes it from every C formulation) — best-effort 133/993. */


// CFLAGS: /O2 /Gd
int __cdecl cm_ExProdObjekt(int msg, char* result)
{
	int quantity;
	ushort* obj_entry;
	char* recipe;
	int production_cap;
	ushort* material_iter;
	long production_value;
	short* player_entry;
	uint line;
	short* lager;
	char* recipe_def;
	short* owner;
	int saved_quantity;

	*(int*)(msg + 0x1a) = g_timestamp_0b6c;
	quantity = gm_GetFieldByType((char*)msg, *(int*)(msg + 0x10));
	*(int*)(msg + 0x10) = quantity;
	quantity = gm_ResolveEntityById((void**)0, (void**)&lager, (void**)0, quantity);
	if (quantity == 0) {
		LogMessageInternal(
			"D:\Develop\DieGildeAddOn\command\command.c",
			0x2f3b,
			"cm_ExProdObjekt() Invalid 'lager_id'",
			1
		);
		return 1;
	}
	if ((*lager != 0x2a) && (*lager != 0x116)) {
		LogMessageInternal(
			"D:\Develop\DieGildeAddOn\command\command.c",
			0x2f53,
			"cm_ExProdObjekt() Lager has wrong Type",
			1
		);
		return 1;
	}
	owner = gm_ResolveParentEntity(lager);
	if (owner == (short*)0) {
		LogMessageInternal(
			"D:\Develop\DieGildeAddOn\command\command.c",
			0x2f6d,
			"cm_ExProdObjekt() Lager hat keinen Besitzer",
			1
		);
		return 1;
	}
	quantity = *(int*)(msg + 0x16);
	saved_quantity = quantity;
	recipe_def = g_unknown_1de450 + (uint)*(ushort*)(msg + 0x14) * 0x41;
	saved_quantity = 4;
	material_iter = (ushort*)(recipe_def + 0x26);
	do {
		if (material_iter[4] != 0) {
			obj_entry = (ushort*)gm_StartEntityQuery(*(int*)(lager + 10), 1, 0, (uint)material_iter[4]);
			if (obj_entry == (ushort*)0) {
				quantity = 0;
			}
			else {
				recipe = (char*)gm_GetMsgField((int)lager, (int)obj_entry);
				if (quantity >= (int)recipe / (int)(uint)*material_iter) {
					recipe = (char*)gm_GetMsgField((int)lager, (int)obj_entry);
					quantity = (int)recipe / (int)(uint)*material_iter;
				}
			}
		}
		material_iter = material_iter + 1;
		saved_quantity = saved_quantity + -1;
	} while (saved_quantity != 0);
	recipe = recipe_def;
	saved_quantity = quantity;
	production_cap = gm_KannObjektHergestellt(
		(char*)lager,
		(uint)*(ushort*)(msg + 0x14),
		(uint)*(ushort*)(recipe_def + 0x36) * quantity
	);
	production_cap = production_cap / (int)(uint)*(ushort*)(recipe + 0x36);
	if (production_cap <= quantity) {
		quantity = production_cap;
		saved_quantity = quantity;
	}
	if (quantity == 0) {
		recipe = "cm_ExProdObjekt(): Nicht gen\374gend Rohstoffe";
		line = 0x2fb5;
	LAB_1000e3e1:
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", line, recipe, 1);
		if (result != (char*)0) {
			result[1] = '\b';
		}
		return 1;
	}
	material_iter = (ushort*)(recipe_def + 0x2e);
	for (production_cap = 0; production_cap < 4; production_cap++) {
		if (*material_iter != 0) {
			obj_entry = (ushort*)gm_StartEntityQuery(*(int*)(lager + 10), 1, 0, (uint)*material_iter);
			if (obj_entry == (ushort*)0) {
				recipe = "cm_ExProdObjekt() Rohstoff verschwunden";
				line = 0x2fdd;
				goto LAB_1000e3e1;
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
		material_iter = material_iter + 1;
	}
	material_iter = (ushort*)gm_StartEntityQuery(*(int*)(lager + 10), 1, 0, (uint)*(ushort*)(msg + 0x14));
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
	production_value = (long)(gm_CalculateProductionValue((uint)*(ushort*)(msg + 0x14), 100) * saved_quantity);
	production_cap = gm_WalkEntityChain((int)lager);
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
