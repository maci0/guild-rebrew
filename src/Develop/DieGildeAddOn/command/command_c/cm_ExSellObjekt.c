// FUNCTION: SERVER 0x1000d930

#include "../command_internal.h"
#include "../../../Units/Error/error.h"
#include "../../game/entity.h"

extern char* g_item_def_table; /* 0x101de450, attested in rebrew-data.toml */
extern unsigned char g_current_season;
extern unsigned char g_connections[]; /* 0x101deb00 */

extern char g_error_msg_sell_no_source[];
extern char g_error_msg_sell_no_dest[];
extern char g_error_msg_sell_failed[];

short* __cdecl gm_ResolveParentEntity(short*);
int __cdecl compute_size(char*, int);
int __cdecl gm_RemoveObjectWrapper(int, uint);
void* __cdecl gm_AddObjekt(int, uint, int);
void* __cdecl gm_AllocRaum(char*, uint);
int __cdecl sprintf(char*, const char*, ...);

extern char s_cm_ExSellObjekt___Invalid__quell_1002cec4[];
extern char s_cm_ExSellObjekt___Invalid__gm_ev_1002ce90[];
extern char s_cm_ExSellObjekt____Object_not_fo_1002ce4c[];
extern char s_cm_ExSellObjekt___Not_enough_Obj_1002cdfc[];
extern char s_cm_ExSellObjekt___Invalid__ziel__1002cdcc[];
extern char s_cm_ExSellObjekt___Lager_voll_1002cdac[];
extern char s_cm_ExSellObjekt___Not_enough_Cre_1002cd78[];
extern char s_cm_ExSellObjekt____gm_AllocRaum_f_1002ccc0[];
extern char s_cm_ExSellObjekt____gm_AllocObjek_1002cce8[];
unsigned short* __cdecl gm_ff_Objekt(int, int, int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
int __cdecl gm_RemoveObjectByType(void**, unsigned int);

/* Execution handler: sells an object (Objekt) from one entity to another.
 * Handles object type validation, inventory transfers, production slot
 * updates, and building ownership changes.
 *
 * Load-bearing shapes (each checked against an aligned listing of the
 * reference; changing one moves the linked residue):
 *  - Error sites call LogMessageInternal(...) and return 1 inline; msvc6
 *    tail-merges them into the reference's shared call tail at 0x1000e00e.
 *  - The dest gm_ResolveEntityById call reuses the source's
 *    resolved_dynamic out-param, so the dest block re-checks the DEST's
 *    dynamic entity (semantic: the other order fails symbolic proving).
 *  - The source-weight check is ONE expression with both calls in it.
 *    msvc6 evaluates the compute_size product first and keeps it in a
 *    compiler temporary across the gm_GetMsgField call: that temporary is
 *    the 4-byte frame slot between the locals and log_buffer
 *    (`mov [esp+0x44],edx` / `mov ecx,[esp+0x44]`), and it is what makes
 *    the frame 0x228 with a plain `char[512]`.  Split into statements, the
 *    product becomes a colourer variable that takes edi and displaces
 *    source_dynamic_entity, which permutes every frame slot.
 *  - gm_QueryEntitySum is called through an `(int, unsigned char)` pointer
 *    cast: the reference passes the byte with a bare `mov al`/`mov cl`.
 *    The shared header declares `(int, int)`.
 *  - The source object count is stored and then re-read into `amount`
 *    (reference: `sub ecx,edx; mov eax,ecx; mov [ebx+0xe],ecx`).
 *  - The `= 0` initialisers follow the reference's store order.
 *  - dest-finalize works on dest_game_object itself, never copied into
 *    source_object: the reference loads it
 *    into ebx before the `cmd+0x10` test because the final `result+6`
 *    store reads it on both paths.
 *  - The gm_AllocRaum null check is success-first, which lays the three
 *    dest error tails out in the reference's order.
 *  - After the dest join, dest_dynamic_entity and dest_owner_entity are
 *    read through volatile (one load each into a temp where the reference
 *    loads once): the reference holds neither in a register across the
 *    join.  Plain reads keep them in ebp/edi and move the join block.
 *
 * Remaining differences (linked): the 0x1dd arm layout at 0x1000dc16,
 * ecx/edx swapped in the source-finalize category load at 0x1000de2b,
 * two load placements (0x1000df90, 0x1000e0f5) and the
 * dest `+0xe` increment at 0x1000e04a (reference folds the table address
 * and reuses edi; we keep edi and use ebp, one byte shorter).
 *
 * Semantically PROVEN equivalent (Z3, EAX) as of 2026-08-29; not
 * re-proven after the 2026-09-25 reshaping, whose edits keep every call,
 * load and store (the weight check relies on msvc6 evaluating the
 * compute_size operand first, as the reference does). */

uint cm_ExSellObjekt(char* cmd, uchar* result)
{
	int amount;
	int resolve_result;
	char* capacity_check;
	short* parent_check;
	ushort* source_object;
	short* source_owner_entity;
	int* linked_list_ptr;
	short* dest_owner_entity;
	short* resolved_dynamic;
	short* source_dynamic_entity;
	char* dest_existing_entity;
	short* dest_dynamic_entity;
	short* source_static_entity;
	char** source_container_ptr;
	ushort* dest_game_object;
	void* source_existing_entity;
	char log_buffer[512];
	short entity_type;
	short* dest_dyn_reload;
	short* owner_reload;
	char obj_category;

	source_owner_entity = (short*)0;
	*(int*)(cmd + 0x1a) = g_next_object_id;
	dest_owner_entity = (short*)0;
	resolved_dynamic = (short*)0;
	dest_game_object = (ushort*)0;
	source_dynamic_entity = (short*)0;
	source_object = (ushort*)0;
	dest_dynamic_entity = (short*)0;
	source_container_ptr = (char**)0;
	source_existing_entity = (void*)0;
	dest_existing_entity = (char*)0;
	source_static_entity = (short*)0;
	if (*(int*)(cmd + 0x14) != -1) {
		resolve_result = gm_GetFieldByType(cmd, *(int*)(cmd + 0x14));
		*(int*)(cmd + 0x14) = resolve_result;
		resolve_result = gm_ResolveEntityById(
			&source_existing_entity,
			(void**)&resolved_dynamic,
			(void**)&source_static_entity,
			resolve_result
		);
		if (resolve_result == 0) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2c05, "cm_ExSellObjekt() Invalid 'quell_besitzer_id'", 8);
			return 1;
		}
		if (source_existing_entity != (void*)0) {
			source_container_ptr = (char**)((int)source_existing_entity + 0x5d);
			if (*(ushort*)((int)source_existing_entity + 0x27) != 0xffff) {
				source_owner_entity = (short*)(g_slot_table +
					(uint)*(ushort*)((int)source_existing_entity + 0x27) * 0x21c);
			} else {
				source_owner_entity = (short*)0;
			}
		} else if (resolved_dynamic != (short*)0) {
			entity_type = *resolved_dynamic;
			if (entity_type == 0x2a || entity_type == 0x1db ||
				entity_type == 0x1dc || entity_type == 0x116 ||
				entity_type == 0x1dd) {
				source_dynamic_entity = resolved_dynamic;
			}
			source_container_ptr = (char**)(resolved_dynamic + 10);
			source_owner_entity = gm_ResolveParentEntity(resolved_dynamic);
			if (source_owner_entity == (short*)0) {
				LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2c2f, "cm_ExSellObjekt() Invalid 'gm_eval_ObjektBesitzer'", 8);
				return 1;
			}
		} else {
			source_owner_entity = source_static_entity;
			source_container_ptr = (char**)(source_static_entity + 0xbc);
		}
		source_object = (ushort*)gm_ff_Objekt((int)*source_container_ptr, 1, 0, (uint)*(ushort*)(cmd + 0x18));
		if (source_object == (ushort*)0) {
			sprintf(
				log_buffer,
				"cm_ExSellObjekt(): Object not found: ObjProt:%i Menge:%i CmdCnt:",
				(uint)*(ushort*)(cmd + 0x18),
				*(int*)(cmd + 0x1f),
				*(int*)(cmd + 8)
			);
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2c53, log_buffer, 8);
			return 1;
		}
		if (source_dynamic_entity != (short*)0) {
			resolve_result = *(int*)(cmd + 0x1f);
			amount = gm_GetMsgField((int)source_dynamic_entity, (int)source_object);
			if (amount < resolve_result) {
				sprintf(
					log_buffer,
					"cm_ExSellObjekt() Not enough Objekts at source: ObjProt:%i Menge:%i CmdCnt:%i",
					(uint)*(ushort*)(cmd + 0x18),
					resolve_result,
					*(int*)(cmd + 8)
				);
				LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2c75, log_buffer, 8);
				return 1;
			}
		}
		if (*(int*)(source_object + 7) < *(int*)(cmd + 0x1f)) {
			sprintf(
				log_buffer,
				"cm_ExSellObjekt() Not enough Objekts at source: ObjProt:%i Menge:%i CmdCnt:%i",
				(uint)*(ushort*)(cmd + 0x18),
				*(int*)(cmd + 0x1f),
				*(int*)(cmd + 8)
			);
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2c97, log_buffer, 8);
			return 1;
		}
		if (*(int*)(cmd + 0x23) != 0 && source_owner_entity != (short*)0) {
			((int (__cdecl*)(int, unsigned char))gm_QueryEntitySum)(*(int*)(source_owner_entity + 0xbc), cmd[0x1e]);
		}
	}
	if (*(int*)(cmd + 0x10) != -1) {
		resolve_result = gm_GetFieldByType(cmd, *(int*)(cmd + 0x10));
		*(int*)(cmd + 0x10) = resolve_result;
		resolve_result = gm_ResolveEntityById(
			(void**)&dest_existing_entity,
			(void**)&resolved_dynamic,
			(void**)&source_static_entity,
			resolve_result
		);
		if (resolve_result == 0) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2cdd, "cm_ExSellObjekt() Invalid 'ziel_besitzer_id'", 8);
			return 1;
		}
		if (dest_existing_entity != (char*)0) {
			linked_list_ptr = (int*)(dest_existing_entity + 0x5d);
			if (*(ushort*)(dest_existing_entity + 0x27) != 0xffff) {
				dest_owner_entity = (short*)(g_slot_table +
					(uint)*(ushort*)(dest_existing_entity + 0x27) * 0x21c);
			} else {
				dest_owner_entity = (short*)0;
			}
		} else if (resolved_dynamic != (short*)0) {
			entity_type = *resolved_dynamic;
			if (entity_type == 0x2a || entity_type == 0x1db ||
				entity_type == 0x1dc || entity_type == 0x116) {
				dest_dynamic_entity = resolved_dynamic;
			check_producible:
				resolve_result = gm_eval_SlotVoll(
					(char*)resolved_dynamic,
					(uint)*(ushort*)(cmd + 0x18),
					*(int*)(cmd + 0x1f)
				);
				if (resolve_result < *(int*)(cmd + 0x1f)) {
					LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2d1b, "cm_ExSellObjekt() Lager voll", 8);
					return 1;
				}
			} else if (entity_type == 0x1dd) {
				goto check_producible;
			}
			linked_list_ptr = (int*)(resolved_dynamic + 10);
			dest_owner_entity = gm_ResolveParentEntity(resolved_dynamic);
		} else {
			linked_list_ptr = (int*)(source_static_entity + 0xbc);
			dest_owner_entity = source_static_entity;
		}
		if (*(g_item_def_table + (uint)*(ushort*)(cmd + 0x18) * 0x41) == '\x1d') {
			dest_game_object = (ushort*)0;
		} else {
			dest_game_object = (ushort*)gm_ff_Objekt(*linked_list_ptr, 1, 0, (uint)*(ushort*)(cmd + 0x18));
		}
		if (*(int*)(cmd + 0x23) != 0 && dest_owner_entity != (short*)0) {
			resolve_result = ((int (__cdecl*)(int, unsigned char))gm_QueryEntitySum)(*(int*)(dest_owner_entity + 0xbc), cmd[0x1e]);
			if (resolve_result < *(int*)(cmd + 0x1f) * *(int*)(cmd + 0x23)) {
				LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2d4f, "cm_ExSellObjekt() Not enough Credits at destination", 8);
				return 1;
			}
		}
	}
	if (source_dynamic_entity != (short*)0) {
		if (dest_owner_entity != (short*)0) {
			parent_check = gm_ResolveParentEntity((short*)source_object);
			if (parent_check != dest_owner_entity && *(int*)(source_object + 0xe) != 0) {
				if ((uint)gm_GetMsgField((int)source_dynamic_entity, (int)source_object) -
					((uint)(compute_size((char*)source_dynamic_entity, (int)*(ushort*)source_object) * *(int*)(source_object + 0xe)) >> 2) <
					(uint)*(int*)(cmd + 0x1f)) {
					LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2d79, g_error_msg_sell_no_source, 8);
					return 1;
				}
			}
			goto finalize_transfer;
		}
	} else {
	finalize_transfer:
		if (dest_owner_entity != (short*)0 &&
			dest_existing_entity == (char*)0 &&
			dest_dynamic_entity == (short*)0 &&
			resolved_dynamic == (short*)0) {
			resolve_result = gm_CheckInventoryCapacity(
				(char*)dest_owner_entity,
				(uint)*(ushort*)(cmd + 0x18),
				*(int*)(cmd + 0x1f)
			);
			*(int*)(cmd + 0x1f) = resolve_result;
			if (resolve_result == 0) {
				return 1;
			}
		}
	}
	if (*(int*)(cmd + 0x23) != 0) {
		if (dest_dynamic_entity == (short*)0 && resolved_dynamic != (short*)0 &&
			*resolved_dynamic == 0x1dd) {
			capacity_check = gm_FindSlotById((uint)g_current_season, (uint)*(ushort*)(cmd + 0x18));
			if (capacity_check != (char*)0) {
				*(int*)(capacity_check + 0x18) = *(int*)(capacity_check + 0x18) + *(int*)(cmd + 0x1f);
			}
		}
		if (source_dynamic_entity != (short*)0 && *source_dynamic_entity == 0x1dd) {
			capacity_check = gm_FindSlotById((uint)g_current_season, (uint)*(ushort*)(cmd + 0x18));
			if (capacity_check != (char*)0) {
				*(int*)(capacity_check + 0x1c) = *(int*)(capacity_check + 0x1c) + *(int*)(cmd + 0x1f);
			}
		}
	}
	if (*(int*)(cmd + 0x14) != -1) {
		*(int*)(source_object + 7) = *(int*)(source_object + 7) - *(int*)(cmd + 0x1f);
		amount = *(int*)(source_object + 7);
		if (amount <= 0) {
			obj_category = *(g_item_def_table + (uint)*(ushort*)(cmd + 0x18) * 0x41);
			if (obj_category == '\x02' || obj_category == '\x06') {
				if (source_existing_entity != (void*)0) {
					gm_RemoveObjectWrapper((int)source_existing_entity, (uint)*(ushort*)(cmd + 0x18));
				} else {
					LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2def, g_error_msg_sell_no_dest, 8);
					return 1;
				}
			} else {
				gm_RemoveObjectByType(source_container_ptr, (uint)*(ushort*)(cmd + 0x18));
			}
		}
		if (*(int*)(cmd + 0x23) != 0) {
			gm_AddObjekt(
				*(int*)(source_owner_entity + 2),
				(uint) (unsigned short) g_entity_slot_table[(unsigned char) cmd[0x1e] * 189],
				*(int*)(cmd + 0x23) * *(int*)(cmd + 0x1f)
			);
			if (source_dynamic_entity != (short*)0) {
				if (*source_dynamic_entity == 0x1db) {
					*(int*)(source_owner_entity + 0xd2) =
						*(int*)(source_owner_entity + 0xd2) + *(int*)(cmd + 0x23) * *(int*)(cmd + 0x1f);
				} else if (*source_dynamic_entity == 0x1dc) {
					*(int*)(source_owner_entity + 0xd0) =
						*(int*)(source_owner_entity + 0xd0) + *(int*)(cmd + 0x23) * *(int*)(cmd + 0x1f);
				} else {
					goto LAB_1000def2;
				}
			} else {
			LAB_1000def2:
				*(int*)(source_owner_entity + 0xce) =
					*(int*)(source_owner_entity + 0xce) + *(int*)(cmd + 0x23) * *(int*)(cmd + 0x1f);
			}
		}
	}
	if (*(int*)(cmd + 0x10) != -1) {
		if (dest_game_object != (ushort*)0) {
			*(int*)(dest_game_object + 7) = *(int*)(dest_game_object + 7) + *(int*)(cmd + 0x1f);
		} else {
			obj_category = *(g_item_def_table + (uint)*(ushort*)(cmd + 0x18) * 0x41);
			if (obj_category == '\x02' || obj_category == '\x06') {
				if (dest_existing_entity != (char*)0) {
					dest_game_object = (ushort*)gm_AllocRaum(dest_existing_entity, (uint)*(ushort*)(cmd + 0x18));
					if (dest_game_object == (ushort*)0) {
						LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2e39, "cm_ExSellObjekt(): gm_AllocRaum failed", 8);
						return 1;
					}
				} else {
					LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2e45, "cm_ExSellObjekt(): Ziel-Besitzer ist kein Geb\xe4ude", 8);
					return 1;
				}
			} else {
				dest_game_object = (ushort*)gm_AllocObjekt(*(int*)(cmd + 0x10), (uint)*(ushort*)(cmd + 0x18), *(int*)(cmd + 0x1f));
				if (dest_game_object == (ushort*)0) {
					LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2e5d, "cm_ExSellObjekt(): gm_AllocObjekt failed", 8);
					return 1;
				}
				if (dest_dynamic_entity != (short*)0) {
					*(int*)(dest_game_object + 7) = *(int*)(dest_game_object + 7) + 1;
					obj_category = *(g_item_def_table + (uint)*(ushort*)(cmd + 0x18) * 0x41);
					if ((obj_category == '\x17' || obj_category == '%') &&
						(*dest_dynamic_entity == 0x2a || *dest_dynamic_entity == 0x116) &&
						(owner_reload = *(short* volatile*)&dest_owner_entity) != (short*)0 &&
						((char)owner_reload[1] == '\x06' || (char)owner_reload[1] == '\a')) {
						*(int*)(dest_game_object + 0xe) = 4;
					}
				}
			}
		}
		*(int*)(((PlayerSlot*)g_connections)[(unsigned char)cmd[3]].data + 0x264200) = *(int*)(dest_game_object + 1);
		if (*(int*)(cmd + 0x23) != 0 && *(short* volatile*)&dest_owner_entity != (short*)0) {
			gm_SubObjekt(
				*(void**)(dest_owner_entity + 2),
				(uint) (unsigned short) g_entity_slot_table[(unsigned char) cmd[0x1e] * 189],
				*(int*)(cmd + 0x23) * *(int*)(cmd + 0x1f)
			);
			dest_dyn_reload = *(short* volatile*)&dest_dynamic_entity;
			if (dest_dyn_reload != (short*)0) {
				if (*dest_dyn_reload == 0x1db) {
					*(int*)(dest_owner_entity + 0xd0) =
						*(int*)(dest_owner_entity + 0xd0) + *(int*)(cmd + 0x23) * *(int*)(cmd + 0x1f);
					goto LAB_1000e0e7;
				}
				if (*dest_dyn_reload == 0x1dc) {
					*(int*)(dest_owner_entity + 0xd2) =
						*(int*)(dest_owner_entity + 0xd2) + *(int*)(cmd + 0x23) * *(int*)(cmd + 0x1f);
					goto LAB_1000e0e7;
				}
			}
			*(int*)(dest_owner_entity + 0xcc) =
				*(int*)(dest_owner_entity + 0xcc) + *(int*)(cmd + 0x23) * *(int*)(cmd + 0x1f);
		}
	}
LAB_1000e0e7:
	if (result != (uchar*)0) {
		*result = 1;
		if (*(int*)(cmd + 0x10) != -1) {
			result[1] = 3;
			*(ushort**)(result + 6) = dest_game_object;
		}
	}
	return 0;
}
