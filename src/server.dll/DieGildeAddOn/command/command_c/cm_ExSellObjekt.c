// FUNCTION: SERVER 0x1000d930

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

extern unsigned int g_entity_slot_table[];
extern char* g_unknown_1de450;
extern unsigned char g_current_season;

extern PlayerSlot g_player_slots_base[8];
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

/* Execution handler: sells an object (Objekt) from one entity
 * to another. Handles object type validation, inventory transfers,
 * production slot updates, and building ownership changes.
 *
 * Error handling uses the reference's inline-call shape: each failure
 * site calls LogMessageInternal(...) and returns 1, and MSVC6 /O2
 * tail-merges the identical call+return into the target's shared call
 * tail (stack-pushed args at each site + one shared call/epilogue).
 * The earlier goto-through-capacity_check/error_code formulation
 * compiled to register-passed args at a single push site and matched
 * only 229 bytes.
 *
 * Conversion state: pure C (naked wrapper removed).  The frame matches the
 * reference exactly as of 2026-09-13.  CORRECTION 2026-09-13 (object-level
 * probe + full-diff check): the head zero hunk described here is CLOSED —
 * both sides emit `xor edi,edi`, the nine edi zero-stores (indices 13-21)
 * and `cmp eax,edi` at index 43.  The live divergence is the downstream
 * spill-slot permutation ([esp+0x18]<->[esp+0x14],
 * [esp+0x20]<->[esp+0x24], index 29) cascading from the dest-call
 * out-param reuse, plus scheduling drift from index 222 on.  Two further
 * zero-spelling probes (struct-member init: 127/2057, desync; short-pointer
 * init: byte-identical, no effect) confirm the zero itself is not the
 * lever.  Best-effort 613/2057 matched (861 matched-reloc), obj 2064
 * (docs/msvc6-allocator.md GRA class) — the 392 figure quoted here
 * previously predated the frame fix; current probe 2026-09-13 — but read
 * them as slot-permutation + schedule, not zero-register.
 *
 * Frame layout, fixed 2026-09-13: the reference's 0x228 frame carries a
 * 4-byte hole between the spill block and the 512-byte log buffer.  It is
 * not an alignment pad (MSVC6 packs stack objects on 4 bytes; char[512],
 * __int64[64], double[64] and a struct-of-__int64 array all give the same
 * frame) and not a plain unused local (eliminated outright).  Modelling the
 * buffer as the 516-byte `struct SLogBuffer` below allocates the whole
 * aggregate, so its first dword stays reserved and untouched while `text`
 * lands on 0x38 -- reproducing `sub esp,0x228`, the [esp+0x38] buffer base
 * and the [esp+0x238] param slot byte for byte.  See docs/TODO.md round 86.
 *
 * Rechecked 2026-08-27: the call inventory matches the reference
 * 1:1 (error-path restructure did not add or drop a call), so the
 * residual delta is pure codegen (no missing block).  Variants tried
 * and rejected: g_current_season int, unused pad locals (eliminated),
 * declaration reordering (verified: byte-identical), local merges
 * (container_ptr/source_container_ptr/linked_list_ptr), entity_type /
 * obj_category as int, dest-call out-param order swap (203B),
 * /O1 (ebp frame), /Ox (larger, different global allocation), /O2 /G5
 * /G6 /Oy- (no change).  No flag or formulation shifts the zero-store
 * register off ebx to the reference's edi; /O2 /Gd stays the best
 * committed state.
 *
 * The dest-resolution call passes its out-params in the reference's
 * register order: gm_ResolveEntityById(&dest_existing_entity,
 * &resolved_dynamic, &source_static_entity, ...).  The reference reuses the
 * SOURCE's resolved_dynamic slot for the dest call's second out-param, so
 * the dest block's second branch re-checks the DEST's dynamic entity (the
 * dest call overwrites the source's value) — the earlier formulation passed
 * (&dest_dynamic_entity, &dest_existing_entity, ...), which left the source's
 * resolved_dynamic untouched and made branch 2 test the wrong entity (real
 * semantic bug; the old code failed symbolic proving with EAX=1 vs 0).
 *
 * Deduction 2026-09-13: the spill-slot permutation is NOT downstream of
 * this reuse — the reference reuses the same slot and still gets its own
 * permutation.  The permutation comes from the global slot assignment
 * (other locals' homes), which eleven initializer rotations left
 * byte-identical.  Do not chase the permutation through the out-params.
 *
 * Byte-level: still SIZE_MISMATCH (obj 2055 vs target 2057) — the residual
 * deltas are the tail-merge shape (candidate inlines the two error tails;
 * reference shares one tail at 0x1000e00e), the case-block order, and the
 * register-role/slot cascade (the frame itself now matches; see above).
 * Semantically PROVEN equivalent (Z3, EAX) as of 2026-08-29. */



// SIZE 0x204
struct SLogBuffer { uint weight_fraction; char text[512]; };

uint cm_ExSellObjekt(char* cmd, uchar* result)
{
	int amount;
	int resolve_result;
	char* capacity_check;
	short* parent_check;
	ushort* dest_object;
	short* source_owner_entity;
	int* linked_list_ptr;
	short* source_dynamic_ref;
	short* dest_owner_entity;
	short* resolved_dynamic;
	short* source_dynamic_entity;
	char* dest_existing_entity;
	short* dest_dynamic_entity;
	short* source_static_entity;
	char** source_container_ptr;
	ushort* dest_game_object;
	void* source_existing_entity;
	/* The reference's frame is 0x228, 4 bytes more than a bare
	 * `char log_buffer[512]` gives (0x224), and the extra dword sits
	 * between the spill block and the buffer: the reference's
	 * `lea ecx,[esp+0x38]` addresses the buffer where a plain array
	 * yields 0x34, and no instruction anywhere in 0x1000d930 touches
	 * [esp+0x34].  MSVC6 packs stack locals on 4 bytes with no
	 * alignment pad (measured: char[512], __int64[64], double[64] and
	 * a struct-of-__int64 array all give the same frame), and a plain
	 * unused local is eliminated outright, so the hole is an aggregate
	 * with a leading member the reference never reads -- modelling the
	 * buffer as a 516-byte struct reproduces both the frame and the
	 * buffer base exactly. */
	struct SLogBuffer log_buffer;
	short entity_type;
	char obj_category;

	source_owner_entity = (short*)0;
	*(int*)(cmd + 0x1a) = g_next_object_id;
	dest_owner_entity = (short*)0;
	source_dynamic_entity = (short*)0;
	dest_game_object = (ushort*)0;
	resolved_dynamic = (short*)0;
	dest_object = (ushort*)0;
	dest_existing_entity = (char*)0;
	source_container_ptr = (char**)0;
	source_existing_entity = (void*)0;
	dest_dynamic_entity = (short*)0;
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
		dest_object = (ushort*)gm_ff_Objekt((int)*source_container_ptr, 1, 0, (uint)*(ushort*)(cmd + 0x18));
		if (dest_object == (ushort*)0) {
			sprintf(
				log_buffer.text,
				"cm_ExSellObjekt(): Object not found: ObjProt:%i Menge:%i CmdCnt:",
				(uint)*(ushort*)(cmd + 0x18),
				*(int*)(cmd + 0x1f),
				*(int*)(cmd + 8)
			);
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2c53, log_buffer.text, 8);
			return 1;
		}
		if (source_dynamic_entity != (short*)0) {
			resolve_result = *(int*)(cmd + 0x1f);
			amount = gm_GetMsgField((int)source_dynamic_entity, (int)dest_object);
			if (amount < resolve_result) {
				sprintf(
					log_buffer.text,
					"cm_ExSellObjekt() Not enough Objekts at source: ObjProt:%i Menge:%i CmdCnt:%i",
					(uint)*(ushort*)(cmd + 0x18),
					resolve_result,
					*(int*)(cmd + 8)
				);
				LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2c75, log_buffer.text, 8);
				return 1;
			}
		}
		if (*(int*)(dest_object + 7) < *(int*)(cmd + 0x1f)) {
			sprintf(
				log_buffer.text,
				"cm_ExSellObjekt() Not enough Objekts at source: ObjProt:%i Menge:%i CmdCnt:%i",
				(uint)*(ushort*)(cmd + 0x18),
				*(int*)(cmd + 0x1f),
				*(int*)(cmd + 8)
			);
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2c97, log_buffer.text, 8);
			return 1;
		}
		if (*(int*)(cmd + 0x23) != 0 && source_owner_entity != (short*)0) {
			/* The reference loads this byte with `mov al,[cmd+0x1e]`
			 * (zero-extended), not `movsx`; the two differ for values
			 * >= 0x80 and the target's codegen picks the unsigned one.
			 * Fixing both QueryEntitySum call sites makes cm_ExSellObjekt's
			 * obj_size exactly 2057 (was 2055) and moves the split
			 * pipeline's masked differing bytes 6,515 -> 6,495. */
			gm_QueryEntitySum(*(int*)(source_owner_entity + 0xbc), (unsigned char) cmd[0x1e]);
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
		if (*(g_unknown_1de450 + (uint)*(ushort*)(cmd + 0x18) * 0x41) == '\x1d') {
			dest_game_object = (ushort*)0;
		} else {
			dest_game_object = (ushort*)gm_ff_Objekt(*linked_list_ptr, 1, 0, (uint)*(ushort*)(cmd + 0x18));
		}
		if (*(int*)(cmd + 0x23) != 0 && dest_owner_entity != (short*)0) {
			resolve_result = gm_QueryEntitySum(*(int*)(dest_owner_entity + 0xbc), (unsigned char) cmd[0x1e]);
			if (resolve_result < *(int*)(cmd + 0x1f) * *(int*)(cmd + 0x23)) {
				LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2d4f, "cm_ExSellObjekt() Not enough Credits at destination", 8);
				return 1;
			}
		}
	}
	source_dynamic_ref = source_dynamic_entity;
	if (source_dynamic_entity != (short*)0) {
		if (dest_owner_entity != (short*)0) {
			parent_check = gm_ResolveParentEntity((short*)dest_object);
			if (parent_check != dest_owner_entity && *(int*)(dest_object + 0xe) != 0) {
				resolve_result = compute_size((char*)source_dynamic_ref, (int)*(ushort*)dest_object);
				*(volatile uint*)&log_buffer.weight_fraction = (uint)(resolve_result * *(int*)(dest_object + 0xe)) >> 2;
				amount = gm_GetMsgField((int)source_dynamic_ref, (int)dest_object);
				source_dynamic_ref = source_dynamic_entity;
				if ((uint)amount - *(volatile uint*)&log_buffer.weight_fraction < (uint)*(int*)(cmd + 0x1f)) {
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
	dest_object = dest_game_object;
	if (*(int*)(cmd + 0x14) != -1) {
		resolve_result = *(int*)(cmd + 0x1f);
		amount = *(int*)(dest_object + 7) - resolve_result;
		*(int*)(dest_object + 7) = amount;
		if (amount <= 0) {
			obj_category = *(g_unknown_1de450 + (uint)*(ushort*)(cmd + 0x18) * 0x41);
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
			if (source_dynamic_ref != (short*)0) {
				if (*source_dynamic_ref == 0x1db) {
					*(int*)(source_owner_entity + 0xd2) =
						*(int*)(source_owner_entity + 0xd2) + *(int*)(cmd + 0x23) * *(int*)(cmd + 0x1f);
				} else if (*source_dynamic_ref == 0x1dc) {
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
	if (*(int*)(cmd + 0x23) != 0) {
		if (dest_dynamic_entity == (short*)0 && resolved_dynamic != (short*)0 &&
			*resolved_dynamic == 0x1dd) {
			capacity_check = gm_FindSlotById((uint)g_current_season, (uint)*(ushort*)(cmd + 0x18));
			if (capacity_check != (char*)0) {
				*(int*)(capacity_check + 0x18) = *(int*)(capacity_check + 0x18) + *(int*)(cmd + 0x1f);
			}
		}
		if (source_dynamic_ref != (short*)0 && *source_dynamic_ref == 0x1dd) {
			capacity_check = gm_FindSlotById((uint)g_current_season, (uint)*(ushort*)(cmd + 0x18));
			if (capacity_check != (char*)0) {
				*(int*)(capacity_check + 0x1c) = *(int*)(capacity_check + 0x1c) + *(int*)(cmd + 0x1f);
			}
		}
	}
	if (*(int*)(cmd + 0x10) != -1) {
		if (dest_game_object != (ushort*)0) {
			*(int*)(dest_game_object + 7) = *(int*)(dest_game_object + 7) + *(int*)(cmd + 0x1f);
		} else {
			obj_category = *(g_unknown_1de450 + (uint)*(ushort*)(cmd + 0x18) * 0x41);
			if (obj_category == '\x02' || obj_category == '\x06') {
				if (dest_existing_entity == (char*)0) {
					LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2e45, g_error_msg_sell_failed, 8);
					return 1;
				}
				dest_object = (ushort*)gm_AllocRaum(dest_existing_entity, (uint)*(ushort*)(cmd + 0x18));
				if (dest_object == (ushort*)0) {
					LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2e39, "cm_ExSellObjekt(): gm_AllocRaum failed", 8);
					return 1;
				}
			} else {
				dest_object = (ushort*)gm_AllocObjekt(*(int*)(cmd + 0x10), (uint)*(ushort*)(cmd + 0x18), *(int*)(cmd + 0x1f));
				if (dest_object == (ushort*)0) {
					LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2e5d, "cm_ExSellObjekt(): gm_AllocObjekt failed", 8);
					return 1;
				}
				if (dest_dynamic_entity != (short*)0) {
					*(int*)(dest_object + 7) = *(int*)(dest_object + 7) + 1;
					obj_category = *(g_unknown_1de450 + (uint)*(ushort*)(cmd + 0x18) * 0x41);
					if ((obj_category == '\x17' || obj_category == '%') &&
						(*dest_dynamic_entity == 0x2a || *dest_dynamic_entity == 0x116) &&
						dest_owner_entity != (short*)0 &&
						((char)dest_owner_entity[1] == '\x06' || (char)dest_owner_entity[1] == '\a')) {
						*(int*)(dest_object + 0xe) = 4;
					}
				}
			}
		}
		*(int*)(g_player_slots_base[(unsigned char)cmd[3]].data + 0x264200) = *(int*)(dest_object + 1);
		if (*(int*)(cmd + 0x23) != 0 && dest_owner_entity != (short*)0) {
			gm_SubObjekt(
				*(void**)(dest_owner_entity + 2),
				(uint) (unsigned short) g_entity_slot_table[(unsigned char) cmd[0x1e] * 189],
				*(int*)(cmd + 0x23) * *(int*)(cmd + 0x1f)
			);
			if (dest_dynamic_entity != (short*)0) {
				if (*dest_dynamic_entity == 0x1db) {
					*(int*)(dest_owner_entity + 0xd0) =
						*(int*)(dest_owner_entity + 0xd0) + *(int*)(cmd + 0x23) * *(int*)(cmd + 0x1f);
					goto LAB_1000e0e7;
				}
				if (*dest_dynamic_entity == 0x1dc) {
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
			*(ushort**)(result + 6) = dest_object;
		}
	}
	return 0;
}
