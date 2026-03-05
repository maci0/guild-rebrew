// STATUS: MATCHING
// BLOCKER: mov di,ax vs mov edi,eax (16-bit truncation) and lea edx,[edi+addr] vs add edi,addr (7 structural diffs, 99.1% mnemonic)
// ORIGIN: GAME
// SIZE: 336
// CFLAGS: /O2 /Gd
// SYMBOL: _ExCreateCitizenAtBuilding

#include "../command_internal.h"

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wpointer-to-int-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 335B
 *    CFlags: 
 *    Symbol: _ExCreateCitizenAtBuilding
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl ExCreateCitizenAtBuilding(int param_1,char *param_2)
 * 
 * {
 *   int iVar1;
 *   ushort *puVar2;
 *   uint uVar3;
 *   char *msg;
 *   
 *   *(undefined4 *)(param_1 + 0x10) = g_timestamp_0b6c;
 *   iVar1 = rand();
 *   *(int *)(param_1 + 0x22) = iVar1;
 *   if (param_2 != (char *)0x0) {
 *     *param_2 = '\x02';
 *     param_2[1] = '\x01';
 *     param_2[6] = '\0';
 *     param_2[7] = '\0';
 *     param_2[8] = '\0';
 *     param_2[9] = '\0';
 *   }
 *   crt_thread_set_alt(*(int *)(param_1 + 0x22));
 *   if (*(int *)(param_1 + 0x17) != -1) {
 *     iVar1 = get_field_by_type((char *)param_1,*(int *)(param_1 + 0x17));
 *     *(int *)(param_1 + 0x17) = iVar1;
 *     puVar2 = StartFilteredEntitySearch(1,1,iVar1);
 *     if (puVar2 == (ushort *)0x0) {
 *       msg = s_Invalid__GI_Id__for_cmdt_ALLOC_C_1002d394;
 *       uVar3 = 0x5246;
 *       goto LAB_1000fa2c;
 *     }
 *   }
 *   uVar3 = CreateEntityFromParents((uint)*(byte *)(param_1 + 0x14),-1,-1,0x14,0);
 *   uVar3 = uVar3 & 0xffff;
 *   if (uVar3 != 0xffff) {
 *     if (*(int *)(param_1 + 0x1b) != -1) {
 *       FindRecordById(*(int *)(param_1 + 0x1b));
 *     }
 *     (&g_work_building_ptrs)[uVar3 * 0x87] = 0;
 *     (&g_entity_state_base)[uVar3 * 0x21c] = 0xd;
 *     if (*(byte *)(param_1 + 0x21) != 0) {
 *       AllocGameObject((&g_static_entity0_entity_id)[uVar3 * 0x87],(uint)*(byte *)(param_1 + 0x21),1)
 *       ;
 *     }
 */

extern void* __cdecl StartFilteredEntitySearch(int, int, int);
extern unsigned int __cdecl CreateEntityFromParents(int, int, int, int, int, int, int, int);
extern void* __cdecl FindRecordById(int);
extern void* __cdecl AllocGameObject(int, unsigned int, int);
extern void __cdecl LogMessageInternal(char*, unsigned int, char*, int);

// FUNCTION: SERVER 0x1000f980
int __cdecl ExCreateCitizenAtBuilding(int param_1, char* param_2)
{
	unsigned short idx16;
	unsigned int idx;
	unsigned int slot;
	int parent_id;
	int offset;
	int entity_offset;

	*(int*) (param_1 + 0x10) = g_timestamp_0b6c;
	*(int*) (param_1 + 0x22) = rand();

	if (param_2 != (char*) 0x0) {
		*param_2 = '\x02';
		param_2[1] = '\x01';
		*(int*) (param_2 + 6) = 0;
	}

	crt_thread_set_alt(*(int*) (param_1 + 0x22));

	if (*(int*) (param_1 + 0x17) != -1) {
		parent_id = get_field_by_type((char*) param_1, *(int*) (param_1 + 0x17));
		*(int*) (param_1 + 0x17) = parent_id;
		if (StartFilteredEntitySearch(1, 1, parent_id) == (void*) 0) {
			LogMessageInternal((char*) 0x1002c748, 0x5246, (char*) 0x1002d394, 1);
			return 1;
		}
	}

	idx16 = (unsigned short) CreateEntityFromParents(
		(int) *(unsigned char*) (param_1 + 0x14),
		-1,
		-1,
		0x14,
		0,
		(int) *(unsigned char*) (param_1 + 0x1f),
		(int) *(unsigned char*) (param_1 + 0x20),
		0
	);
	idx = (unsigned int) idx16;

	if (idx == 0xffff) {
		LogMessageInternal((char*) 0x1002c748, 0x525a, (char*) 0x1002d364, 1);
		return 1;
	}

	if (*(int*) (param_1 + 0x1b) != -1) {
		FindRecordById(*(int*) (param_1 + 0x1b));
	}

	entity_offset = (int) idx * 0x21c;
	*(int*) (entity_offset + 0x10035a0c) = 0;
	*(unsigned char*) (entity_offset + 0x100358a2) = 0x0d;

	if (*(unsigned char*) (param_1 + 0x21) != 0) {
		AllocGameObject(*(int*) (entity_offset + 0x100358a4), *(unsigned char*) (param_1 + 0x21), 1);
	}

	slot = (unsigned int) *(unsigned char*) (param_1 + 3);
	offset = (int) slot;
	offset = offset << 4;
	offset = offset + (int) slot;
	offset = offset << 8;
	offset = offset + (int) slot;
	offset = offset << 4;
	offset = offset + (int) slot;
	offset = offset + offset * 8;

	*(int*) (offset * 4 + 0x10442d00) = *(int*) (entity_offset + 0x100358a4);

	if (param_2 != (char*) 0x0) {
		offset = entity_offset + 0x100358a0;
		*param_2 = '\x01';
		param_2[1] = '\x01';
		*(int*) (param_2 + 6) = offset;
	}

	return 0;
}
