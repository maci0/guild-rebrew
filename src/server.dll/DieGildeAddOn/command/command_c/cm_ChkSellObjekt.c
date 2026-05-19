
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

/* Validation handler: checks preconditions for selling an object.
 * Resolves source/destination entities, verifies entity types
 * match, and checks inventory capacity. Logs error on invalid ID
 * or type mismatch. */

extern int __cdecl gm_KannObjektHergestellt(char*, int, int);

// FUNCTION: SERVER 0x1000cbd0
__declspec(naked) int __cdecl cm_ChkSellObjekt(char* cmd)
{
	(void) cmd;
	__asm {
		sub esp, 0xc
		push esi
		mov esi, dword ptr [esp + 0x14]
		mov eax, dword ptr [esi + 0x14]
		cmp eax, -1
		je near L_phase2
		push eax
		push esi
		call gm_GetFieldByType
		mov dword ptr [esi + 0x14], eax
		push eax
		lea eax, [esp + 0x10]
		lea ecx, [esp + 0x20]
		push eax
		lea edx, [esp + 0x18]
		push ecx
		push edx
		call gm_ResolveEntityById
		add esp, 0x18
		test eax, eax
		jne L_p1_have_entity
		push 8
		push offset s_cm_ChkSellObjekt___Invalid__quel_1002c8dc
		push 0x236b
		jmp near L_log_fail
	L_p1_have_entity:
		mov eax, dword ptr [esp + 8]
		test eax, eax
		je L_p1_b
		add eax, 0x5d
		jmp L_p1_query
	L_p1_b:
		mov eax, dword ptr [esp + 0x14]
		test eax, eax
		je L_p1_c
		add eax, 0x14
		jmp L_p1_query
	L_p1_c:
		mov eax, dword ptr [esp + 4]
		add eax, 0x178
	L_p1_query:
		mov edx, dword ptr [eax]
		xor ecx, ecx
		mov cx, word ptr [esi + 0x18]
		push ecx
		push 0
		push 1
		push edx
		call gm_StartEntityQuery
		add esp, 0x10
		test eax, eax
		jne L_p1_have_query
		push 8
		push offset s_cm_ChkSellObjekt___No_Objekts_at_1002c8b4
		push 0x2383
		jmp near L_log_fail
	L_p1_have_query:
		mov eax, dword ptr [eax + 0xe]
		mov ecx, dword ptr [esi + 0x1f]
		cmp eax, ecx
		jge L_phase2
		push 8
		push offset s_cm_ChkSellObjekt___Not_enough_Ob_1002c884
		push 0x238f
		jmp near L_log_fail
	L_phase2:
		mov eax, dword ptr [esi + 0x10]
		cmp eax, -1
		je near L_success
		push eax
		push esi
		call gm_GetFieldByType
		lea ecx, [esp + 0xc]
		mov dword ptr [esi + 0x10], eax
		push eax
		lea edx, [esp + 0x20]
		push ecx
		lea eax, [esp + 0x1c]
		push edx
		push eax
		call gm_ResolveEntityById
		add esp, 0x18
		test eax, eax
		jne L_p2_have_entity
		push 8
		push offset s_cm_ChkSellObjekt___Invalid__ziel_1002c854
		push 0x23ab
		jmp near L_log_fail
	L_p2_have_entity:
		mov eax, dword ptr [esp + 0xc]
		test eax, eax
		je L_p2_check_b
		mov ax, word ptr [eax + 0x27]
		cmp ax, 0xffff
		je L_p2_parent_null
		and eax, 0xffff
		lea eax, [eax + eax*2]
		lea eax, [eax + eax*4]
		lea ecx, [eax + eax*8]
		lea eax, [ecx*4 + 0x100358a0]
		jmp near L_p2_check_credits
	L_p2_parent_null:
		xor eax, eax
		jmp near L_p2_check_credits
	L_p2_check_b:
		mov eax, dword ptr [esp + 0x14]
		test eax, eax
		je L_p2_c
		mov cx, word ptr [eax]
		cmp cx, 0x2a
		je L_p2_check_kann
		cmp cx, 0x116
		je L_p2_check_kann
		cmp cx, 0x1dd
		jne L_p2_resolve_parent
	L_p2_check_kann:
		mov edx, dword ptr [esi + 0x1f]
		xor ecx, ecx
		mov cx, word ptr [esi + 0x18]
		push edx
		push ecx
		push eax
		call gm_KannObjektHergestellt
		mov ecx, dword ptr [esi + 0x1f]
		add esp, 0xc
		cmp eax, ecx
		jge L_p2_resolve_parent_load_arg
		push 8
		push offset s_cm_ChkSellObjekt___Lager_voll_1002c834
		push 0x23cd
		jmp L_log_fail
	L_p2_resolve_parent_load_arg:
		mov eax, dword ptr [esp + 0x14]
	L_p2_resolve_parent:
		push eax
		call gm_ResolveParentEntity
		add esp, 4
		jmp L_p2_check_credits
	L_p2_c:
		mov edx, dword ptr [esi + 0x1f]
		mov ecx, dword ptr [esp + 4]
		xor eax, eax
		push edx
		mov ax, word ptr [esi + 0x18]
		push eax
		push ecx
		call gm_CheckInventoryCapacity
		mov ecx, dword ptr [esi + 0x1f]
		add esp, 0xc
		cmp eax, ecx
		jge L_p2_load_parent_c
		push 8
		push offset s_cm_ChkSellObjekt___Inventory_vol_1002c810
		push 0x23e3
		jmp L_log_fail
	L_p2_load_parent_c:
		mov eax, dword ptr [esp + 4]
	L_p2_check_credits:
		mov ecx, dword ptr [esi + 0x23]
		test ecx, ecx
		je L_success
		test eax, eax
		je L_success
		mov dl, byte ptr [esi + 0x1e]
		mov eax, dword ptr [eax + 0x178]
		push edx
		push eax
		call gm_QueryEntitySum
		mov ecx, dword ptr [esi + 0x1f]
		add esp, 8
		imul ecx, dword ptr [esi + 0x23]
		cmp eax, ecx
		jge L_success
		push 8
		push offset s_cm_ChkSellObjekt___Not_enough_Cr_1002c7d8
		push 0x23ff
	L_log_fail:
		push offset s_D__Develop_DieGildeAddOn_command_1002c748
		call LogMessageInternal
		add esp, 0x10
		mov eax, 1
		pop esi
		add esp, 0xc
		ret
	L_success:
		xor eax, eax
		pop esi
		add esp, 0xc
		ret
	}
}
