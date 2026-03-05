// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 2057
// BLOCKER: stack frame size (0x228 vs 0x224), register allocation (edi vs ebx for zero init), error handler codegen (push/jmp vs mov/jmp), merged stack cleanup, loop rotation / branch layout, comparison direction swap, instruction folding (lea vs mov), zero-extend pattern (xor vs mov)
// BLOCKER_DELTA: 1962

#include "../command_internal.h"

extern char g_currency_type_array[];
extern char* g_unknown_1de450;
extern int g_current_season;

typedef struct {
	unsigned int flags;
	unsigned int id;
	unsigned char data[0x26425C];
} TradePlayerSlot;

extern TradePlayerSlot g_player_slots_base[];
extern char g_error_msg_sell_no_source[];
extern char g_error_msg_sell_no_dest[];
extern char g_error_msg_sell_failed[];

extern short* __cdecl ResolveParentEntity(short*);
extern void* __cdecl StartEntityQuery(int, int, int, uint);
extern int __cdecl get_msg_field(int, int);
extern int __cdecl KannObjektHergestellt(char*, uint, int);
extern int __cdecl CheckInventoryCapacity(char*, uint, int);
extern char* __cdecl FindSlotById(uint, uint);
extern int __cdecl compute_size(char*, int);
extern int __cdecl RemoveObjectWrapper(int, uint);
extern int __cdecl RemoveObjectByType(char**, uint);
extern void* __cdecl AddOrAccumulateObject(int, uint, int);
extern void* __cdecl AllocBuildingContents(char*, uint);
extern void* __cdecl AllocGameObject(int, uint, int);
extern int __cdecl SubObjekt(void*, uint, int);
extern int __cdecl LogMessageInternal(const char*, uint, const char*, int);
extern int __cdecl sprintf(char*, const char*, ...);

extern char s_cm_ExSellObjekt___Invalid__quell_1002cec4[];
extern char s_cm_ExSellObjekt___Invalid__gm_ev_1002ce90[];
extern char s_cm_ExSellObjekt____Object_not_fo_1002ce4c[];
extern char s_cm_ExSellObjekt___Not_enough_Obj_1002cdfc[];
extern char s_cm_ExSellObjekt___Invalid__ziel__1002cdcc[];
extern char s_cm_ExSellObjekt___Lager_voll_1002cdac[];
extern char s_cm_ExSellObjekt___Not_enough_Cre_1002cd78[];
extern char s_cm_ExSellObjekt____gm_AllocRaum_f_1002ccc0[];
extern char s_cm_ExSellObjekt____gm_AllocObjek_1002cce8[];

// FUNCTION: SERVER 0x1000d930
uint cm_ExSellObjekt(char* param_1, uchar* param_2)
{
	int amount;
	int resolve_result;
	char* capacity_check;
	short* parent_check;
	ushort* dest_object;
	char** container_ptr;
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
	uint weight_fraction;
	char log_buffer[512];
	short entity_type;
	uint error_code;
	char obj_category;

	source_owner_entity = (short*)0;
	*(int*)(param_1 + 0x1a) = g_timestamp_0b6c;
	dest_object = (ushort*)0;
	dest_owner_entity = (short*)0;
	resolved_dynamic = (short*)0;
	dest_game_object = (ushort*)0;
	source_dynamic_entity = (short*)0;
	dest_dynamic_entity = (short*)0;
	source_container_ptr = (char**)0;
	source_existing_entity = (void*)0;
	dest_existing_entity = (char*)0;
	source_static_entity = (short*)0;
	if (*(int*)(param_1 + 0x14) != -1) {
		resolve_result = get_field_by_type(param_1, *(int*)(param_1 + 0x14));
		*(int*)(param_1 + 0x14) = resolve_result;
		resolve_result = ResolveEntityById(
			&source_existing_entity,
			(void**)&resolved_dynamic,
			(void**)&source_static_entity,
			resolve_result
		);
		if (resolve_result == 0) {
			capacity_check = s_cm_ExSellObjekt___Invalid__quell_1002cec4;
			error_code = 0x2c05;
			goto sell_error_return;
		}
		if (source_existing_entity != (void*)0) {
			container_ptr = (char**)((int)source_existing_entity + 0x5d);
			source_container_ptr = container_ptr;
			if (*(ushort*)((int)source_existing_entity + 0x27) == 0xffff) {
				source_owner_entity = (short*)0;
			} else {
				source_owner_entity = (short*)(g_static_entity_table_358a0 +
					(uint)*(ushort*)((int)source_existing_entity + 0x27) * 0x21c);
			}
		} else if (resolved_dynamic != (short*)0) {
			entity_type = *resolved_dynamic;
			if (entity_type == 0x2a || entity_type == 0x1db ||
				entity_type == 0x1dc || entity_type == 0x116 ||
				entity_type == 0x1dd) {
				source_dynamic_entity = resolved_dynamic;
			}
			container_ptr = (char**)(resolved_dynamic + 10);
			source_container_ptr = container_ptr;
			source_owner_entity = ResolveParentEntity(resolved_dynamic);
			if (source_owner_entity == (short*)0) {
				capacity_check = s_cm_ExSellObjekt___Invalid__gm_ev_1002ce90;
				error_code = 0x2c2f;
				goto sell_error_return;
			}
		} else {
			source_owner_entity = source_static_entity;
			container_ptr = (char**)(source_static_entity + 0xbc);
			source_container_ptr = container_ptr;
		}
		dest_object = (ushort*)StartEntityQuery((int)*container_ptr, 1, 0, (uint)*(ushort*)(param_1 + 0x18));
		if (dest_object == (ushort*)0) {
			sprintf(
				log_buffer,
				s_cm_ExSellObjekt____Object_not_fo_1002ce4c,
				(uint)*(ushort*)(param_1 + 0x18),
				*(int*)(param_1 + 0x1f),
				*(int*)(param_1 + 8)
			);
			LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x2c53, log_buffer, 8);
			return 1;
		}
		if (source_dynamic_entity != (short*)0) {
			resolve_result = *(int*)(param_1 + 0x1f);
			amount = get_msg_field((int)source_dynamic_entity, (int)dest_object);
			if (amount < resolve_result) {
				sprintf(
					log_buffer,
					s_cm_ExSellObjekt___Not_enough_Obj_1002cdfc,
					(uint)*(ushort*)(param_1 + 0x18),
					resolve_result,
					*(int*)(param_1 + 8)
				);
				LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x2c75, log_buffer, 8);
				return 1;
			}
		}
		if (*(int*)(dest_object + 7) < *(int*)(param_1 + 0x1f)) {
			sprintf(
				log_buffer,
				s_cm_ExSellObjekt___Not_enough_Obj_1002cdfc,
				(uint)*(ushort*)(param_1 + 0x18),
				*(int*)(param_1 + 0x1f),
				*(int*)(param_1 + 8)
			);
			LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x2c97, log_buffer, 8);
			return 1;
		}
		if (*(int*)(param_1 + 0x23) != 0 && source_owner_entity != (short*)0) {
			QueryEntitySum(*(int*)(source_owner_entity + 0xbc), param_1[0x1e]);
		}
	}
	if (*(int*)(param_1 + 0x10) != -1) {
		resolve_result = get_field_by_type(param_1, *(int*)(param_1 + 0x10));
		*(int*)(param_1 + 0x10) = resolve_result;
		resolve_result = ResolveEntityById(
			(void**)&dest_existing_entity,
			(void**)&resolved_dynamic,
			(void**)&source_static_entity,
			resolve_result
		);
		if (resolve_result == 0) {
			capacity_check = s_cm_ExSellObjekt___Invalid__ziel__1002cdcc;
			error_code = 0x2cdd;
			goto sell_error_return;
		}
		if (dest_existing_entity != (char*)0) {
			linked_list_ptr = (int*)(dest_existing_entity + 0x5d);
			if (*(ushort*)(dest_existing_entity + 0x27) == 0xffff) {
				dest_owner_entity = (short*)0;
			} else {
				dest_owner_entity = (short*)(g_static_entity_table_358a0 +
					(uint)*(ushort*)(dest_existing_entity + 0x27) * 0x21c);
			}
		} else if (resolved_dynamic != (short*)0) {
			entity_type = *resolved_dynamic;
			if (entity_type == 0x2a || entity_type == 0x1db ||
				entity_type == 0x1dc || entity_type == 0x116) {
				dest_dynamic_entity = resolved_dynamic;
			LAB_1000dc24:
				resolve_result = KannObjektHergestellt(
					(char*)resolved_dynamic,
					(uint)*(ushort*)(param_1 + 0x18),
					*(int*)(param_1 + 0x1f)
				);
				if (resolve_result < *(int*)(param_1 + 0x1f)) {
					capacity_check = s_cm_ExSellObjekt___Lager_voll_1002cdac;
					error_code = 0x2d1b;
					goto sell_error_return;
				}
			} else if (entity_type == 0x1dd) {
				goto LAB_1000dc24;
			}
			linked_list_ptr = (int*)(resolved_dynamic + 10);
			dest_owner_entity = ResolveParentEntity(resolved_dynamic);
		} else {
			dest_owner_entity = source_static_entity;
			linked_list_ptr = (int*)(source_static_entity + 0xbc);
		}
		if (*(g_unknown_1de450 + (uint)*(ushort*)(param_1 + 0x18) * 0x41) == '\x1d') {
			dest_game_object = (ushort*)0;
		} else {
			dest_game_object = (ushort*)StartEntityQuery(*linked_list_ptr, 1, 0, (uint)*(ushort*)(param_1 + 0x18));
		}
		if (*(int*)(param_1 + 0x23) != 0 && dest_owner_entity != (short*)0) {
			resolve_result = QueryEntitySum(*(int*)(dest_owner_entity + 0xbc), param_1[0x1e]);
			if (resolve_result < *(int*)(param_1 + 0x1f) * *(int*)(param_1 + 0x23)) {
				capacity_check = s_cm_ExSellObjekt___Not_enough_Cre_1002cd78;
				error_code = 0x2d4f;
				goto sell_error_return;
			}
		}
	}
	source_dynamic_ref = source_dynamic_entity;
	if (source_dynamic_entity != (short*)0) {
		if (dest_owner_entity != (short*)0) {
			parent_check = ResolveParentEntity((short*)dest_object);
			if (parent_check != dest_owner_entity && *(int*)(dest_object + 0xe) != 0) {
				resolve_result = compute_size((char*)source_dynamic_ref, (int)*(ushort*)dest_object);
				weight_fraction = (uint)(resolve_result * *(int*)(dest_object + 0xe)) >> 2;
				amount = get_msg_field((int)source_dynamic_ref, (int)dest_object);
				source_dynamic_ref = source_dynamic_entity;
				if ((uint)amount - weight_fraction < (uint)*(int*)(param_1 + 0x1f)) {
					capacity_check = g_error_msg_sell_no_source;
					error_code = 0x2d79;
					goto sell_error_return;
				}
			}
			goto LAB_1000dd58;
		}
	} else {
	LAB_1000dd58:
		if (dest_owner_entity != (short*)0 &&
			dest_existing_entity == (char*)0 &&
			dest_dynamic_entity == (short*)0 &&
			resolved_dynamic == (short*)0) {
			resolve_result = CheckInventoryCapacity(
				(char*)dest_owner_entity,
				(uint)*(ushort*)(param_1 + 0x18),
				*(int*)(param_1 + 0x1f)
			);
			*(int*)(param_1 + 0x1f) = resolve_result;
			if (resolve_result == 0) {
				return 1;
			}
		}
	}
	if (*(int*)(param_1 + 0x23) != 0) {
		if (dest_dynamic_entity == (short*)0 && resolved_dynamic != (short*)0 &&
			*resolved_dynamic == 0x1dd) {
			capacity_check = FindSlotById((uint)g_current_season, (uint)*(ushort*)(param_1 + 0x18));
			if (capacity_check != (char*)0) {
				*(int*)(capacity_check + 0x18) = *(int*)(capacity_check + 0x18) + *(int*)(param_1 + 0x1f);
			}
		}
		if (source_dynamic_ref != (short*)0 && *source_dynamic_ref == 0x1dd) {
			capacity_check = FindSlotById((uint)g_current_season, (uint)*(ushort*)(param_1 + 0x18));
			if (capacity_check != (char*)0) {
				*(int*)(capacity_check + 0x1c) = *(int*)(capacity_check + 0x1c) + *(int*)(param_1 + 0x1f);
			}
		}
	}
	if (*(int*)(param_1 + 0x14) != -1) {
		resolve_result = *(int*)(param_1 + 0x1f);
		amount = *(int*)(dest_object + 7) - resolve_result;
		*(int*)(dest_object + 7) = amount;
		if (amount <= 0) {
			obj_category = *(g_unknown_1de450 + (uint)*(ushort*)(param_1 + 0x18) * 0x41);
			if (obj_category == '\x02' || obj_category == '\x06') {
				if (source_existing_entity == (void*)0) {
					capacity_check = g_error_msg_sell_no_dest;
					error_code = 0x2def;
					goto sell_error_return;
				}
				RemoveObjectWrapper((int)source_existing_entity, (uint)*(ushort*)(param_1 + 0x18));
			} else {
				RemoveObjectByType(source_container_ptr, (uint)*(ushort*)(param_1 + 0x18));
			}
		}
		if (*(int*)(param_1 + 0x23) != 0) {
			AddOrAccumulateObject(
				*(int*)(source_owner_entity + 2),
				(uint)*(ushort*)(g_currency_type_array + (uint)(unsigned char)param_1[0x1e] * 0x2f4),
				*(int*)(param_1 + 0x23) * *(int*)(param_1 + 0x1f)
			);
			if (source_dynamic_ref != (short*)0) {
				if (*source_dynamic_ref == 0x1db) {
					*(int*)(source_owner_entity + 0xd2) =
						*(int*)(source_owner_entity + 0xd2) + *(int*)(param_1 + 0x23) * *(int*)(param_1 + 0x1f);
				} else if (*source_dynamic_ref == 0x1dc) {
					*(int*)(source_owner_entity + 0xd0) =
						*(int*)(source_owner_entity + 0xd0) + *(int*)(param_1 + 0x23) * *(int*)(param_1 + 0x1f);
				} else {
					goto LAB_1000def2;
				}
			} else {
			LAB_1000def2:
				*(int*)(source_owner_entity + 0xce) =
					*(int*)(source_owner_entity + 0xce) + *(int*)(param_1 + 0x23) * *(int*)(param_1 + 0x1f);
			}
		}
	}
	dest_object = dest_game_object;
	if (*(int*)(param_1 + 0x10) != -1) {
		if (dest_game_object != (ushort*)0) {
			*(int*)(dest_game_object + 7) = *(int*)(dest_game_object + 7) + *(int*)(param_1 + 0x1f);
		} else {
			obj_category = *(g_unknown_1de450 + (uint)*(ushort*)(param_1 + 0x18) * 0x41);
			if (obj_category == '\x02' || obj_category == '\x06') {
				if (dest_existing_entity == (char*)0) {
					capacity_check = g_error_msg_sell_failed;
					error_code = 0x2e45;
					goto sell_error_return;
				}
				dest_object = (ushort*)AllocBuildingContents(dest_existing_entity, (uint)*(ushort*)(param_1 + 0x18));
				if (dest_object == (ushort*)0) {
					capacity_check = s_cm_ExSellObjekt____gm_AllocRaum_f_1002ccc0;
					error_code = 0x2e39;
					goto sell_error_return;
				}
			} else {
				dest_object = (ushort*)AllocGameObject(*(int*)(param_1 + 0x10), (uint)*(ushort*)(param_1 + 0x18), *(int*)(param_1 + 0x1f));
				if (dest_object == (ushort*)0) {
					capacity_check = s_cm_ExSellObjekt____gm_AllocObjek_1002cce8;
					error_code = 0x2e5d;
					goto sell_error_return;
				}
				if (dest_dynamic_entity != (short*)0) {
					*(int*)(dest_object + 7) = *(int*)(dest_object + 7) + 1;
					obj_category = *(g_unknown_1de450 + (uint)*(ushort*)(param_1 + 0x18) * 0x41);
					if ((obj_category == '\x17' || obj_category == '%') &&
						(*dest_dynamic_entity == 0x2a || *dest_dynamic_entity == 0x116) &&
						dest_owner_entity != (short*)0 &&
						((char)dest_owner_entity[1] == '\x06' || (char)dest_owner_entity[1] == '\a')) {
						*(int*)(dest_object + 0xe) = 4;
					}
				}
			}
		}
		*(int*)(g_player_slots_base[(unsigned char)param_1[3]].data + 0x264200) = *(int*)(dest_object + 1);
		if (*(int*)(param_1 + 0x23) != 0 && dest_owner_entity != (short*)0) {
			SubObjekt(
				*(void**)(dest_owner_entity + 2),
				(uint)*(ushort*)(g_currency_type_array + (uint)(unsigned char)param_1[0x1e] * 0x2f4),
				*(int*)(param_1 + 0x23) * *(int*)(param_1 + 0x1f)
			);
			if (dest_dynamic_entity != (short*)0) {
				if (*dest_dynamic_entity == 0x1db) {
					*(int*)(dest_owner_entity + 0xd0) =
						*(int*)(dest_owner_entity + 0xd0) + *(int*)(param_1 + 0x23) * *(int*)(param_1 + 0x1f);
					goto LAB_1000e0e7;
				}
				if (*dest_dynamic_entity == 0x1dc) {
					*(int*)(dest_owner_entity + 0xd2) =
						*(int*)(dest_owner_entity + 0xd2) + *(int*)(param_1 + 0x23) * *(int*)(param_1 + 0x1f);
					goto LAB_1000e0e7;
				}
			}
			*(int*)(dest_owner_entity + 0xcc) =
				*(int*)(dest_owner_entity + 0xcc) + *(int*)(param_1 + 0x23) * *(int*)(param_1 + 0x1f);
		}
	}
LAB_1000e0e7:
	if (param_2 != (uchar*)0) {
		*param_2 = 1;
		if (*(int*)(param_1 + 0x10) != -1) {
			param_2[1] = 3;
			*(ushort**)(param_2 + 6) = dest_object;
		}
	}
	return 0;
sell_error_return:
	LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, error_code, capacity_check, 8);
	return 1;
}
