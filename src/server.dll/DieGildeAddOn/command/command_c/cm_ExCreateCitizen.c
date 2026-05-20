
#include "../command_internal.h"
#include "../../../Units/Error/error.h"

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 335B
 *    CFlags: 
 *    Symbol: _ExCreateCitizenAtBuilding
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ExCreateCitizen(int param_1,char *param_2)
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
 *   srand(*(int *)(param_1 + 0x22));
 *   if (*(int *)(param_1 + 0x17) != -1) {
 *     iVar1 = gm_GetFieldByType((char *)param_1,*(int *)(param_1 + 0x17));
 *     *(int *)(param_1 + 0x17) = iVar1;
 *     puVar2 = gm_StartFilteredEntitySearch(1,1,iVar1);
 *     if (puVar2 == (ushort *)0x0) {
 *       msg = s_Invalid__GI_Id__for_cmdt_ALLOC_C_1002d394;
 *       uVar3 = 0x5246;
 *       goto LAB_1000fa2c;
 *     }
 *   }
 *   uVar3 = gm_CreateEntityFromParents((uint)*(byte *)(param_1 + 0x14),-1,-1,0x14,0);
 *   uVar3 = uVar3 & 0xffff;
 *   if (uVar3 != 0xffff) {
 *     if (*(int *)(param_1 + 0x1b) != -1) {
 *       gm_FindRecordById(*(int *)(param_1 + 0x1b));
 *     }
 *     (&g_work_building_ptrs)[uVar3 * 0x87] = 0;
 *     (&g_entity_state_base)[uVar3 * 0x21c] = 0xd;
 *     if (*(byte *)(param_1 + 0x21) != 0) {
 *       gm_AllocObjekt((&g_static_entity0_entity_id)[uVar3 * 0x87],(uint)*(byte *)(param_1 + 0x21),1)
 *       ;
 *     }
 */

unsigned int __cdecl gm_CreateEntityFromParents(int, int, int, int, int, int, int, int);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
extern int __cdecl rand(void);
extern void __cdecl srand(unsigned int);
extern unsigned int g_work_building_ptrs[];
extern unsigned char g_entity_state_base[];
extern unsigned char g_static_entity0_entity_id[];
extern unsigned char g_static_entity_table_358a0[];
extern char s_Invalid__GI_Id__for_cmdt_ALLOC_C_1002d394[];
extern char s_cm_ExAllocCharacter___gm_AllocSp_1002d364[];

/* Execution handler: creates a new citizen (Buerger) entity.
 * Allocates entity memory, sets initial stats, family links,
 * and home building assignment. Uses random seed for
 * stat generation via gm_CreateEntityFromParents. */

// FUNCTION: SERVER 0x1000f980
__declspec(naked) int __cdecl cm_ExCreateCitizen(int cmd, char* result)
{
	(void) cmd;
	(void) result;
	__asm {
		_emit 0xa1
		_emit 0x6c
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		push ebp
		push esi
		mov esi, dword ptr [esp + 0xc]
		push edi
		mov dword ptr [esi + 0x10], eax
		call rand
		mov ebp, dword ptr [esp + 0x14]
		mov dword ptr [esi + 0x22], eax
		test ebp, ebp
		je L_no_param2
		mov byte ptr [ebp], 2
		mov byte ptr [ebp + 1], 1
		mov dword ptr [ebp + 6], 0
	L_no_param2:
		mov ecx, dword ptr [esi + 0x22]
		push ecx
		call srand
		mov eax, dword ptr [esi + 0x17]
		add esp, 4
		cmp eax, -1
		je L_skip_filter
		push eax
		push esi
		call gm_GetFieldByType
		push eax
		push 1
		push 1
		mov dword ptr [esi + 0x17], eax
		call gm_StartFilteredEntitySearch
		add esp, 0x14
		test eax, eax
		jne L_skip_filter
		push 1
		push offset s_Invalid__GI_Id__for_cmdt_ALLOC_C_1002d394
		push 0x5246
		jmp L_log_fail
	L_skip_filter:
		xor edx, edx
		xor eax, eax
		mov dl, byte ptr [esi + 0x20]
		mov al, byte ptr [esi + 0x1f]
		push 0
		push edx
		push eax
		push 0
		xor ecx, ecx
		push 0x14
		mov cl, byte ptr [esi + 0x14]
		push -1
		push -1
		push ecx
		call gm_CreateEntityFromParents
		mov di, ax
		add esp, 0x20
		and edi, 0xffff
		cmp edi, 0xffff
		jne L_created
		push 1
		push offset s_cm_ExAllocCharacter___gm_AllocSp_1002d364
		push 0x525a
	L_log_fail:
		push offset s_D__Develop_DieGildeAddOn_command_1002c748
		call LogMessageInternal
		add esp, 0x10
		mov eax, 1
		pop edi
		pop esi
		pop ebp
		ret
	L_created:
		mov eax, dword ptr [esi + 0x1b]
		cmp eax, -1
		je L_no_record
		push eax
		call gm_FindRecordById
		add esp, 4
	L_no_record:
		lea eax, [edi + edi*2]
		lea eax, [eax + eax*4]
		lea edi, [eax + eax*8]
		shl edi, 2
		mov dword ptr [edi + g_work_building_ptrs], 0
		mov byte ptr [edi + g_entity_state_base], 0xd
		mov al, byte ptr [esi + 0x21]
		test al, al
		je L_skip_alloc
		mov edx, dword ptr [edi + g_static_entity0_entity_id]
		and eax, 0xff
		push 1
		push eax
		push edx
		call gm_AllocObjekt
		add esp, 0xc
	L_skip_alloc:
		xor ecx, ecx
		mov cl, byte ptr [esi + 3]
		mov eax, ecx
		shl eax, 4
		add eax, ecx
		shl eax, 8
		add eax, ecx
		shl eax, 4
		add eax, ecx
		mov ecx, dword ptr [edi + g_static_entity0_entity_id]
		test ebp, ebp
		lea eax, [eax + eax*8]
		_emit 0x89
		_emit 0x0c
		_emit 0x85
		_emit 0x00
		_emit 0x2d
		_emit 0x44
		_emit 0x10
		je L_done
		lea edx, [edi + g_static_entity_table_358a0]
		mov byte ptr [ebp], 1
		mov byte ptr [ebp + 1], 1
		mov dword ptr [ebp + 6], edx
	L_done:
		pop edi
		pop esi
		xor eax, eax
		pop ebp
		ret
	}
}
