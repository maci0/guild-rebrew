// STATUS: MATCHING
// BLOCKER: epilogue tail-merging (3 early-return error blocks merged to shared epilogue -59 bytes), dead store elimination (mov [esp+0x18],ebx before mov [esp+0x18],4), null-check branch layout (inline vs end-of-block), jump condition swap, zero-extend pattern (xor vs mov)
// ORIGIN: GAME
// SIZE: 993
// CFLAGS: /O2 /Gd
// SYMBOL: _cm_ExecProduction

/*
// BLOCKER_DELTA: 922
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 993B
 *    CFlags:
 *    Symbol: _cm_ExecProduction
 *    Files: DieGildeAddOn/command/command.c * / *
 * int __cdecl cm_ExecProduction(int msg,char *result)
 */

#include "../command_internal.h"

extern char g_empty_string[];
extern char* unknown;
extern unsigned char g_current_season;

extern int __cdecl LogMessageInternal(const char*, uint, const char*, int);
extern short* __cdecl ResolveParentEntity(short*);
extern void* __cdecl StartEntityQuery(int, int, int, uint);
extern int __cdecl get_msg_field(int, int);
extern int __cdecl KannObjektHergestellt(char*, uint, int);
extern void __cdecl RemoveObjectByType(char**, uint);
extern char* __cdecl FindSlotById(uint, uint);
extern void* __cdecl AllocGameObject(int, uint, int);
extern double __cdecl CalculateProductionValue(uint, int);
extern int __cdecl WalkEntityChain(int);
extern short* __cdecl GetEntityTableEntry(char*);

extern char s_cm_ExecProduction___Invalid__lager_1002cf9c[];
extern char s_cm_ExecProduction___Lager_has_wron_1002cf74[];
extern char s_cm_ExecProduction___Lager_hat_kein_1002cf48[];
extern char s_cm_ExProdObjekt___Cannot_produce___1002cf1c[];
extern char s_cm_ExProdObjekt___Rohstoff_versc_1002cef4[];

// FUNCTION: SERVER 0x1000e140
int __cdecl cm_ExecProduction(int msg, char* result)
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
	int saved_quantity;
	short* owner;

	*(int*)(msg + 0x1a) = g_timestamp_0b6c;
	iVar1 = get_field_by_type((char*)msg, *(int*)(msg + 0x10));
	*(int*)(msg + 0x10) = iVar1;
	iVar1 = ResolveEntityById((void**)0, (void**)&local_10, (void**)0, iVar1);
	if (iVar1 == 0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x2f3b,
			s_cm_ExecProduction___Invalid__lager_1002cf9c,
			1
		);
		return 1;
	}
	if ((*local_10 != 0x2a) && (*local_10 != 0x116)) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x2f53,
			s_cm_ExecProduction___Lager_has_wron_1002cf74,
			1
		);
		return 1;
	}
	local_4 = ResolveParentEntity(local_10);
	if (local_4 == (short*)0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x2f6d,
			s_cm_ExecProduction___Lager_hat_kein_1002cf48,
			1
		);
		return 1;
	}
	iVar1 = *(int*)(msg + 0x16);
	local_c = unknown + (uint)*(ushort*)(msg + 0x14) * 0x41;
	local_8 = 4;
	puVar5 = (ushort*)(local_c + 0x26);
	do {
		if (puVar5[4] != 0) {
			puVar2 = (ushort*)StartEntityQuery(*(int*)(local_10 + 10), 1, 0, (uint)puVar5[4]);
			if (puVar2 == (ushort*)0) {
				iVar1 = 0;
			}
			else {
				pcVar3 = (char*)get_msg_field((int)local_10, (int)puVar2);
				if (iVar1 >= (int)pcVar3 / (int)(uint)*puVar5) {
					pcVar3 = (char*)get_msg_field((int)local_10, (int)puVar2);
					iVar1 = (int)pcVar3 / (int)(uint)*puVar5;
				}
			}
		}
		puVar5 = puVar5 + 1;
		local_8 = local_8 + -1;
	} while (local_8 != 0);
	pcVar3 = local_c;
	local_8 = iVar1;
	iVar4 = KannObjektHergestellt(
		(char*)local_10,
		(uint)*(ushort*)(msg + 0x14),
		(uint)*(ushort*)(local_c + 0x36) * iVar1
	);
	iVar4 = iVar4 / (int)(uint)*(ushort*)(pcVar3 + 0x36);
	if (iVar4 <= iVar1) {
		iVar1 = iVar4;
		local_8 = iVar1;
	}
	if (iVar1 == 0) {
		pcVar3 = s_cm_ExProdObjekt___Cannot_produce___1002cf1c;
		line = 0x2fb5;
	LAB_1000e3e1:
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, line, pcVar3, 1);
		if (result != (char*)0) {
			result[1] = '\b';
		}
		return 1;
	}
	iVar4 = 0;
	puVar5 = (ushort*)(local_c + 0x2e);
	do {
		if (*puVar5 != 0) {
			puVar2 = (ushort*)StartEntityQuery(*(int*)(local_10 + 10), 1, 0, (uint)*puVar5);
			if (puVar2 == (ushort*)0) {
				pcVar3 = s_cm_ExProdObjekt___Rohstoff_versc_1002cef4;
				line = 0x2fdd;
				goto LAB_1000e3e1;
			}
			*(uint*)(puVar2 + 7) = *(int*)(puVar2 + 7) - (uint)puVar5[-4] * iVar1;
			pcVar3 = FindSlotById((uint)g_current_season, (uint)*puVar5);
			if (pcVar3 != (char*)0) {
				*(uint*)(pcVar3 + 0x14) = *(int*)(pcVar3 + 0x14) + (uint)*(ushort*)(local_c + 0x36) * iVar1;
			}
			if (*(int*)(puVar2 + 7) == 0) {
				RemoveObjectByType((char**)(local_10 + 10), (uint)*puVar5);
			}
		}
		iVar4 = iVar4 + 1;
		puVar5 = puVar5 + 1;
	} while (iVar4 < 4);
	puVar5 = (ushort*)StartEntityQuery(*(int*)(local_10 + 10), 1, 0, (uint)*(ushort*)(msg + 0x14));
	pcVar3 = local_c;
	if (puVar5 != (ushort*)0) {
		*(uint*)(puVar5 + 7) = *(int*)(puVar5 + 7) + (uint)*(ushort*)(local_c + 0x36) * iVar1;
	}
	else {
		puVar5 = (ushort*)AllocGameObject(
			*(int*)(local_10 + 1),
			(uint)*(ushort*)(msg + 0x14),
			(uint)*(ushort*)(local_c + 0x36) * iVar1
		);
		if (puVar5 == (ushort*)0) {
			if (result != (char*)0) {
				result[1] = '\x06';
			}
			return 1;
		}
		if (*local_10 == 0x2a) {
			*(int*)(puVar5 + 7) = *(int*)(puVar5 + 7) + 1;
		}
		if (((*pcVar3 == '\x17') || (*pcVar3 == '%')) &&
			((*local_10 == 0x2a || (*local_10 == 0x116))) &&
			(((char)local_4[1] == '\x06' || ((char)local_4[1] == '\a')))) {
			*(int*)(puVar5 + 0xe) = 4;
		}
	}
	lVar6 = (long)(CalculateProductionValue((uint)*(ushort*)(msg + 0x14), 100) * local_8);
	iVar4 = WalkEntityChain((int)local_10);
	if (iVar4 != 0) {
		*(int*)(iVar4 + 0x4d) = *(int*)(iVar4 + 0x4d) + (int)lVar6;
	}
	pcVar3 = FindSlotById((uint)g_current_season, (uint)*(ushort*)(msg + 0x14));
	if (pcVar3 != (char*)0) {
		*(uint*)(pcVar3 + 0x10) = *(int*)(pcVar3 + 0x10) + (uint)*(ushort*)(local_c + 0x36) * iVar1;
	}
	psVar7 = GetEntityTableEntry((char*)local_4);
	if (psVar7 != (short*)0) {
		*(int*)(psVar7 + 0x12) = *(int*)(psVar7 + 0x12) + (int)lVar6;
	}
	if ((result != (char*)0) && ((*result = '\x01', *(int*)(msg + 0x10) != -1))) {
		result[1] = '\x03';
		*(ushort**)(result + 6) = puVar5;
	}
	return 0;
}
