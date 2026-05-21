#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <string.h>

#pragma intrinsic(memset, strcpy)

int __cdecl gv_CheckSlotActive(char*, int);
extern int g_entity_type_table;
extern int g_slot_count_cat0[]; /* 0x1002577c */
extern int g_slot_count_cat1[]; /* 0x1002578c */
extern int g_slot_count_cat2[]; /* 0x1002579c */
extern int g_slot_count_cat3[]; /* 0x100257ac */
int __cdecl cm_GetBuildingStatCount(unsigned char*);
char* __cdecl gv_FindSlotEntryFiltered(char*, unsigned char*, char*, int(__cdecl*)(char*, char*), int);
int __cdecl gm_RandomMod(int);
extern unsigned int __ftol(void);
extern int g_1002575c[];
extern int g_1002576c[];
extern char g_1002d444;
extern char g_1002d45c;
extern char g_1002d474;
int AllocGraveyardField(int);
void gv_Free3Fields(char*);
int __cdecl gm_ResolveEntityById(void** out_slot, void** out_person, void** out_building, int entity_id);
int __cdecl gv_GetSlotEntry(int, int, unsigned char);
int __cdecl gm_SubObjektNoKill(int, int, int);
void* __cdecl gm_AddOrAccumulateObject(int, int, int);
void __cdecl game_free(void*);
extern int g_entity_table_end;
extern char* g_slot_table;
int SpawnGraveyardEntities(unsigned char*, int);
extern char* g_action_table_base;
double __cdecl gm_RandomFloat01(void);
extern int g_next_object_id;
extern int g_citizen_count;
extern unsigned char g_current_season;
extern float g_gv_const_5680;
extern float g_gv_const_57c4;
extern float g_gv_const_57c8;

/* Checks if a production slot in a building is active.
 * Returns non-zero if the slot at the given index has
 * an assigned worker or active production. */

// FUNCTION: SERVER 0x10010530
// gv_CheckSlotActive
int __cdecl gv_CheckSlotActive(char* obj, int idx)
{
	if (idx == 0) {
		if (*(int*) (obj + 8) && *(obj + 0x18)) {
			return 1;
		}
		return 0;
	}
	if (idx == 1) {
		if (*(int*) (obj + 0xc) && *(obj + 0x19)) {
			return 1;
		}
		return 0;
	}
	if (idx == 2) {
		if (*(int*) (obj + 0x10) && *(obj + 0x1a)) {
			return 1;
		}
		return 0;
	}
	if (idx == 3) {
		if (*(int*) (obj + 0x14) && *(obj + 0x1b)) {
			return 1;
		}
		return 0;
	}
	return 1;
}

/* Gets a reference to a slot entry in a building's production
 * table. Returns the slot pointer at the specified index and
 * sub-type. */

// FUNCTION: SERVER 0x100105b0
// gv_GetSlotEntry

__declspec(naked) int __cdecl gv_GetSlotEntry(int arg1, int arg2, unsigned char arg3)
{
	(void) arg1;
	(void) arg2;
	(void) arg3;
	__asm {
		push esi
		mov esi, dword ptr [esp + 8]
		mov eax, dword ptr [esi + 4]
		cmp eax, 1
		jl near L_ret0
		cmp eax, 3
		jg near L_ret0
		mov eax, dword ptr [esp + 0xc]
		test eax, eax
		jne L_cat1
		push eax
		push esi
		call gv_CheckSlotActive
		add esp, 8
		test eax, eax
		je near L_ret0
		mov ecx, dword ptr [esi + 4]
		mov eax, dword ptr [esp + 0x10]
		cmp ecx, 1
		jne L_chk2_cat0
		cmp al, 8
		jae near L_ret0
	L_chk2_cat0:
		cmp ecx, 2
		jne L_chk3_cat0
		cmp al, 0xc
		jae near L_ret0
	L_chk3_cat0:
		cmp ecx, 3
		jne L_emit_cat0
		cmp al, 0x10
		jae near L_ret0
	L_emit_cat0:
		mov ecx, dword ptr [esi + 8]
		and eax, 0xff
		pop esi
		lea eax, [eax + eax*4]
		lea eax, [ecx + eax*4]
		ret
	L_cat1:
		cmp eax, 1
		jne L_cat2
		push eax
		push esi
		call gv_CheckSlotActive
		add esp, 8
		test eax, eax
		je near L_ret0
		mov ecx, dword ptr [esi + 4]
		mov eax, dword ptr [esp + 0x10]
		cmp ecx, 1
		jne L_chk2_cat1
		cmp al, 4
		jae near L_ret0
	L_chk2_cat1:
		cmp ecx, 2
		jne L_chk3_cat1
		cmp al, 6
		jae near L_ret0
	L_chk3_cat1:
		cmp ecx, 3
		jne L_emit_cat1
		cmp al, 8
		jae near L_ret0
	L_emit_cat1:
		and eax, 0xff
		lea edx, [eax + eax*4]
		mov eax, dword ptr [esi + 0xc]
		pop esi
		lea eax, [eax + edx*4]
		ret
	L_cat2:
		cmp eax, 2
		jne L_cat3
		push eax
		push esi
		call gv_CheckSlotActive
		add esp, 8
		test eax, eax
		je L_ret0
		mov ecx, dword ptr [esi + 4]
		cmp ecx, 1
		je L_ret0
		mov eax, dword ptr [esp + 0x10]
		cmp ecx, 2
		jne L_chk3_cat2
		cmp al, 2
		jae L_ret0
	L_chk3_cat2:
		cmp ecx, 3
		jne L_emit_cat2
		cmp al, 4
		jae L_ret0
	L_emit_cat2:
		mov edx, dword ptr [esi + 0x10]
		and eax, 0xff
		pop esi
		lea ecx, [eax + eax*4]
		lea eax, [edx + ecx*4]
		ret
	L_cat3:
		cmp eax, 3
		jne L_ret0
		push eax
		push esi
		call gv_CheckSlotActive
		add esp, 8
		test eax, eax
		je L_ret0
		mov eax, dword ptr [esi + 4]
		cmp eax, 1
		je L_ret0
		cmp eax, 2
		je L_ret0
		cmp eax, 3
		mov eax, dword ptr [esp + 0x10]
		jne L_emit_cat3
		cmp al, 2
		jae L_ret0
	L_emit_cat3:
		mov ecx, dword ptr [esi + 0x14]
		and eax, 0xff
		pop esi
		lea eax, [eax + eax*4]
		lea eax, [ecx + eax*4]
		ret
	L_ret0:
		xor eax, eax
		pop esi
		ret
	}
}

/* Finds a slot entry in a building with optional type filtering.
 * Searches production slots for one matching the given criteria
 * and returns a pointer to it. */

// FUNCTION: SERVER 0x10010710
// gv_FindSlotEntryFiltered

__declspec(naked) char* __cdecl gv_FindSlotEntryFiltered(char* ctx, unsigned char* obj, char* start, int(__cdecl* callback)(char*, char*), int category)
{
	(void) ctx;
	(void) obj;
	(void) start;
	(void) callback;
	(void) category;
	__asm {
		push ebx
		push ebp
		mov ebp, dword ptr [esp + 0x10]
		xor ecx, ecx
		_emit 0x8b
		_emit 0x15
		_emit 0x30
		_emit 0x8c
		_emit 0x0a
		_emit 0x10
		mov ebx, dword ptr [esp + 0x1c]
		mov cl, byte ptr [ebp]
		push esi
		add edx, ecx
		push edi
		lea eax, [ecx + ecx*2]
		mov edi, dword ptr [ebp + 0x65]
		shl eax, 4
		add eax, ecx
		cmp ebx, 0xff
		lea eax, [eax + eax*2]
		lea esi, [edx + eax*4]
		je L_skip_active
		push ebx
		push edi
		call gv_CheckSlotActive
		add esp, 8
		test eax, eax
		je near L_ret0
	L_skip_active:
		test ebx, ebx
		jne L_cat1
		xor eax, eax
		mov edx, dword ptr [edi + 8]
		mov al, byte ptr [esi + 0x247]
		mov eax, dword ptr [eax*4 + 0x1002577c]
		lea ecx, [eax + eax*4]
		lea ebp, [edx + ecx*4]
		jmp L_have_end
	L_cat1:
		cmp ebx, 1
		jne L_cat2
		xor eax, eax
		mov edx, dword ptr [edi + 0xc]
		mov al, byte ptr [esi + 0x247]
		mov eax, dword ptr [eax*4 + 0x1002578c]
		lea ecx, [eax + eax*4]
		lea ebp, [edx + ecx*4]
		jmp L_have_end
	L_cat2:
		cmp ebx, 2
		jne L_cat3
		xor eax, eax
		mov edx, dword ptr [edi + 0x10]
		mov al, byte ptr [esi + 0x247]
		mov eax, dword ptr [eax*4 + 0x1002579c]
		lea ecx, [eax + eax*4]
		lea ebp, [edx + ecx*4]
		jmp L_have_end
	L_cat3:
		cmp ebx, 3
		jne L_catff
		xor eax, eax
		mov edx, dword ptr [edi + 0x14]
		mov al, byte ptr [esi + 0x247]
		mov eax, dword ptr [eax*4 + 0x100257ac]
		lea ecx, [eax + eax*4]
		lea ebp, [edx + ecx*4]
		jmp L_have_end
	L_catff:
		cmp ebx, 0xff
		jne L_ret0
		push ebp
		call cm_GetBuildingStatCount
		mov ecx, dword ptr [edi + 0x1c]
		lea eax, [eax + eax*4]
		add esp, 4
		lea ebp, [ecx + eax*4]
	L_have_end:
		mov esi, dword ptr [esp + 0x1c]
		test esi, esi
		jne L_have_start
		test ebx, ebx
		jne L_bs_chk1
		mov esi, dword ptr [edi + 8]
		jmp L_chk_end
	L_bs_chk1:
		cmp ebx, 1
		jne L_bs_chk2
		mov esi, dword ptr [edi + 0xc]
		jmp L_chk_end
	L_bs_chk2:
		cmp ebx, 2
		jne L_bs_chk3
		mov esi, dword ptr [edi + 0x10]
		jmp L_chk_end
	L_bs_chk3:
		cmp ebx, 3
		jne L_bs_else
		mov esi, dword ptr [edi + 0x14]
		jmp L_chk_end
	L_bs_else:
		mov esi, dword ptr [edi + 0x1c]
		jmp L_chk_end
	L_have_start:
		add esi, 0x14
	L_chk_end:
		cmp esi, ebp
		jae L_ret0
		mov edi, dword ptr [esp + 0x20]
		mov ebx, dword ptr [esp + 0x14]
	L_cb_loop:
		test edi, edi
		je L_have_match
		push esi
		push ebx
		call edi
		add esp, 8
		test eax, eax
		jne L_have_match
		add esi, 0x14
		cmp esi, ebp
		jb L_cb_loop
	L_ret0:
		pop edi
		pop esi
		pop ebp
		xor eax, eax
		pop ebx
		ret
	L_have_match:
		mov eax, esi
		pop edi
		pop esi
		pop ebp
		pop ebx
		ret
	}
}

/* Spawns graveyard entities (workers, resources) for a building.
 * Initializes the graveyard's active entities based on its
 * current upgrade level and capacity. */

// FUNCTION: SERVER 0x10010850
// SpawnGraveyardEntities

/* Auto-generated Ghidra decompilation */

__declspec(naked) int SpawnGraveyardEntities(unsigned char* arg1, int arg2)
{
	(void) arg1;
	(void) arg2;
	__asm {
		mov eax, dword ptr [esp + 4]
		xor ecx, ecx
		push ebx
		push ebp
		mov cl, byte ptr [eax]
		push esi
		push edi
		lea eax, [ecx + ecx*2]
		shl eax, 4
		add eax, ecx
		lea edx, [eax + eax*2]
		_emit 0xa1
		_emit 0x30
		_emit 0x8c
		_emit 0x0a
		_emit 0x10
		add eax, ecx
		mov cl, byte ptr [eax + edx*4]
		lea eax, [eax + edx*4]
		cmp cl, 0x1d
		jne near L_ret0
		mov al, byte ptr [eax + 0x247]
		cmp al, 1
		jb near L_ret0
		cmp al, 3
		ja near L_ret0
		mov ebx, dword ptr [esp + 0x18]
		xor ebp, ebp
		test ebx, ebx
		jle near L_done
	L_spawn_loop:
		mov ecx, dword ptr [esp + 0x14]
		push 0
		push 0x10010700
		push 0
		push ecx
		push 0
		call gv_FindSlotEntryFiltered
		mov esi, eax
		add esp, 0x14
		test esi, esi
		je near L_done
		mov edx, dword ptr [esi + 0x10]
		_emit 0xa1
		_emit 0x6c
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		mov dword ptr [edx], eax
		_emit 0xa1
		_emit 0x6c
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		inc eax
		_emit 0xa3
		_emit 0x6c
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		mov ecx, dword ptr [esi + 0x10]
		mov edx, dword ptr [ecx]
		mov word ptr [esi + 8], 0x7fff
		mov dword ptr [esi + 4], edx
		_emit 0xa1
		_emit 0x80
		_emit 0x58
		_emit 0x03
		_emit 0x10
		add eax, 5
		mov byte ptr [esi + 0xc], 0xff
		mov word ptr [esi + 0xa], ax
		xor edi, edi
	L_skill_loop:
		push 8
		call gm_RandomMod
		and eax, 0xffff
		add esp, 4
		mov dword ptr [esp + 0x18], eax
		fild dword ptr [esp + 0x18]
		_emit 0xd8
		_emit 0x0d
		_emit 0xc0
		_emit 0x57
		_emit 0x02
		_emit 0x10
		_emit 0xd8
		_emit 0x05
		_emit 0xbc
		_emit 0x57
		_emit 0x02
		_emit 0x10
		call __ftol
		mov ecx, dword ptr [esi + 0x10]
		inc edi
		cmp edi, 5
		mov byte ptr [ecx + edi + 0x23], al
		jl L_skill_loop
		push 9
		call gm_RandomMod
		mov edx, dword ptr [esi + 0x10]
		and eax, 0xffff
		inc eax
		push 2
		mov dword ptr [edx + 0x2c], eax
		call gm_RandomMod
		mov ecx, dword ptr [esi + 0x10]
		and eax, 0xffff
		inc eax
		push 0x5e
		mov dword ptr [ecx + 0x30], eax
		call gm_RandomMod
		mov edx, dword ptr [esi + 0x10]
		and eax, 0xffff
		inc eax
		push 4
		mov dword ptr [edx + 0x34], eax
		call gm_RandomMod
		_emit 0x8b
		_emit 0x0d
		_emit 0x80
		_emit 0x58
		_emit 0x03
		_emit 0x10
		mov edx, dword ptr [esi + 0x10]
		and eax, 0xffff
		push 2
		sub ecx, eax
		dec ecx
		mov dword ptr [edx + 0x40], ecx
		call gm_RandomMod
		mov ecx, dword ptr [esi + 0x10]
		and eax, 0xffff
		push 0x10
		mov dword ptr [ecx + 0x38], eax
		call gm_RandomMod
		push 0x10
		call gm_RandomMod
		push 0x10
		call gm_RandomMod
		add esp, 0x20
		inc ebp
		cmp ebp, ebx
		jl near L_spawn_loop
	L_done:
		pop edi
		mov eax, ebp
		pop esi
		pop ebp
		pop ebx
		ret
	L_ret0:
		pop edi
		pop esi
		pop ebp
		xor eax, eax
		pop ebx
		ret
	}
}

extern char s_gv_AllocGraveyardField_1002d474[];
extern char s_gv_Alloc__all_graves_1002d45c[];
extern char s_gv_Alloc__all_zombies_1002d444[];

/* Allocates a single graveyard production field. Sets up the
 * field's entity type, worker assignment, and production timer. */

// FUNCTION: SERVER 0x100109d0
// AllocGraveyardField

__declspec(naked) int __cdecl AllocGraveyardField(int arg1)
{
	(void) arg1;
	__asm {
		mov eax, dword ptr [esp + 4]
		xor ecx, ecx
		push ebx
		push ebp
		mov cl, byte ptr [eax]
		push esi
		push edi
		lea eax, [ecx + ecx*2]
		shl eax, 4
		add eax, ecx
		lea edx, [eax + eax*2]
		_emit 0xa1
		_emit 0x30
		_emit 0x8c
		_emit 0x0a
		_emit 0x10
		add eax, ecx
		lea ebp, [eax + edx*4]
		mov al, byte ptr [eax + edx*4]
		cmp al, 0x1d
		jne near L_ret0_no_alloc
		mov al, byte ptr [ebp + 0x247]
		cmp al, 1
		jb near L_ret0_no_alloc
		cmp al, 3
		ja near L_ret0_no_alloc
		push offset s_gv_AllocGraveyardField_1002d474
		push 0x24
		call m_AllocTracked
		mov esi, eax
		xor ebx, ebx
		add esp, 8
		cmp esi, ebx
		je near L_ret0_no_alloc
		mov ecx, 9
		xor eax, eax
		mov edi, esi
		push offset s_gv_Alloc__all_graves_1002d45c
		rep stosd
		mov ecx, dword ptr [esp + 0x18]
		mov edx, dword ptr [ecx + 1]
		xor ecx, ecx
		mov dword ptr [esi], edx
		mov al, byte ptr [ebp + 0x247]
		mov dword ptr [esi + 4], eax
		mov cl, byte ptr [ebp + 0x247]
		mov eax, dword ptr [ecx*4 + 0x1002575c]
		lea edx, [eax + eax*4]
		shl edx, 2
		push edx
		call m_AllocTracked
		mov edi, eax
		add esp, 8
		cmp edi, ebx
		mov dword ptr [esi + 0x1c], edi
		je near L_cleanup_lvl1
		xor eax, eax
		push offset s_gv_Alloc__all_zombies_1002d444
		mov al, byte ptr [ebp + 0x247]
		mov eax, dword ptr [eax*4 + 0x1002575c]
		lea ecx, [eax + eax*4]
		xor eax, eax
		shl ecx, 2
		mov edx, ecx
		shr ecx, 2
		rep stosd
		mov ecx, edx
		and ecx, 3
		rep stosb
		xor eax, eax
		mov al, byte ptr [ebp + 0x247]
		mov eax, dword ptr [eax*4 + 0x1002576c]
		mov ecx, eax
		shl ecx, 4
		add ecx, eax
		shl ecx, 2
		push ecx
		call m_AllocTracked
		mov edi, eax
		add esp, 8
		cmp edi, ebx
		mov dword ptr [esi + 0x20], edi
		jne near L_init_slot20
	L_cleanup_lvl1:
		mov eax, dword ptr [esi + 0x1c]
		cmp eax, ebx
		je L_cleanup_lvl2
		push eax
		call m_FreeTracked
		add esp, 4
		mov dword ptr [esi + 0x1c], ebx
	L_cleanup_lvl2:
		mov eax, dword ptr [esi + 0x20]
		cmp eax, ebx
		je L_free_self
		push eax
		call m_FreeTracked
		add esp, 4
		mov dword ptr [esi + 0x20], ebx
	L_free_self:
		push esi
		call m_FreeTracked
		add esp, 4
	L_ret0_no_alloc:
		pop edi
		pop esi
		pop ebp
		xor eax, eax
		pop ebx
		ret
	L_init_slot20:
		xor edx, edx
		mov dl, byte ptr [ebp + 0x247]
		mov eax, dword ptr [edx*4 + 0x1002576c]
		mov ecx, eax
		shl ecx, 4
		add ecx, eax
		xor eax, eax
		shl ecx, 2
		mov edx, ecx
		shr ecx, 2
		rep stosd
		mov ecx, edx
		and ecx, 3
		rep stosb
		xor ecx, ecx
		xor eax, eax
		mov cl, byte ptr [ebp + 0x247]
		or edi, 0xffffffff
		cmp dword ptr [ecx*4 + 0x1002576c], ebx
		jle L_after_negones
		xor ecx, ecx
	L_negone_loop:
		mov edx, dword ptr [esi + 0x20]
		inc eax
		mov dword ptr [ecx + edx], edi
		xor edx, edx
		mov dl, byte ptr [ebp + 0x247]
		add ecx, 0x44
		cmp eax, dword ptr [edx*4 + 0x1002576c]
		jl L_negone_loop
	L_after_negones:
		mov edx, dword ptr [esi + 4]
		mov eax, dword ptr [esi + 0x1c]
		mov ecx, dword ptr [esi + 0x20]
		cmp edx, 1
		mov dword ptr [esi + 8], eax
		mov byte ptr [esi + 0x18], 1
		mov byte ptr [esi + 0x19], bl
		mov byte ptr [esi + 0x1a], bl
		mov byte ptr [esi + 0x1b], bl
		jne near L_chk_tier2
		lea edx, [eax + 0xa0]
		mov dword ptr [esi + 0x10], ebx
		mov dword ptr [esi + 0xc], edx
		mov dword ptr [esi + 0x14], ebx
		mov ebp, 8
		mov edx, 0xffff
	L_t1_loop_cat0:
		mov dword ptr [eax], ebx
		mov dword ptr [eax + 0x10], ecx
		mov dword ptr [eax + 4], edi
		mov word ptr [eax + 8], dx
		add ecx, 0x44
		add eax, 0x14
		dec ebp
		jne L_t1_loop_cat0
		mov ebp, 4
	L_t1_loop_cat1:
		mov dword ptr [eax], 1
		mov dword ptr [eax + 0x10], ecx
		mov dword ptr [eax + 4], edi
		mov word ptr [eax + 8], dx
		add ecx, 0x88
		add eax, 0x14
		dec ebp
		jne L_t1_loop_cat1
		mov eax, dword ptr [esp + 0x14]
		pop edi
		mov dword ptr [eax + 0x65], esi
		mov eax, esi
		pop esi
		pop ebp
		pop ebx
		ret
	L_chk_tier2:
		cmp edx, 2
		jne near L_tier3
		lea edx, [eax + 0xf0]
		mov dword ptr [esi + 0x14], ebx
		mov dword ptr [esi + 0xc], edx
		lea edx, [eax + 0x168]
		mov dword ptr [esi + 0x10], edx
		mov ebp, 0xc
		mov edx, 0xffff
	L_t2_loop_cat0:
		mov dword ptr [eax], ebx
		mov dword ptr [eax + 0x10], ecx
		mov dword ptr [eax + 4], edi
		mov word ptr [eax + 8], dx
		add ecx, 0x44
		add eax, 0x14
		dec ebp
		jne L_t2_loop_cat0
		mov ebp, 6
	L_t2_loop_cat1:
		mov dword ptr [eax], 1
		mov dword ptr [eax + 0x10], ecx
		mov dword ptr [eax + 4], edi
		mov word ptr [eax + 8], dx
		add ecx, 0x88
		add eax, 0x14
		dec ebp
		jne L_t2_loop_cat1
		mov ebp, 2
	L_t2_loop_cat2:
		mov dword ptr [eax], 2
		mov dword ptr [eax + 0x10], ecx
		mov dword ptr [eax + 4], edi
		mov word ptr [eax + 8], dx
		add ecx, 0x110
		add eax, 0x14
		dec ebp
		jne L_t2_loop_cat2
		mov eax, dword ptr [esp + 0x14]
		pop edi
		mov dword ptr [eax + 0x65], esi
		mov eax, esi
		pop esi
		pop ebp
		pop ebx
		ret
	L_tier3:
		lea edx, [eax + 0x140]
		mov ebp, 0x10
		mov dword ptr [esi + 0xc], edx
		lea edx, [eax + 0x1e0]
		mov dword ptr [esi + 0x10], edx
		lea edx, [eax + 0x230]
		mov dword ptr [esi + 0x14], edx
		mov edx, 0xffff
	L_t3_loop_cat0:
		mov dword ptr [eax], ebx
		mov dword ptr [eax + 0x10], ecx
		mov dword ptr [eax + 4], edi
		mov word ptr [eax + 8], dx
		add ecx, 0x44
		add eax, 0x14
		dec ebp
		jne L_t3_loop_cat0
		mov ebp, 8
	L_t3_loop_cat1:
		mov dword ptr [eax], 1
		mov dword ptr [eax + 0x10], ecx
		mov dword ptr [eax + 4], edi
		mov word ptr [eax + 8], dx
		add ecx, 0x88
		add eax, 0x14
		dec ebp
		jne L_t3_loop_cat1
		mov ebp, 4
	L_t3_loop_cat2:
		mov dword ptr [eax], 2
		mov dword ptr [eax + 0x10], ecx
		mov dword ptr [eax + 4], edi
		mov word ptr [eax + 8], dx
		add ecx, 0x110
		add eax, 0x14
		dec ebp
		jne L_t3_loop_cat2
		mov ebp, 2
	L_t3_loop_cat3:
		mov dword ptr [eax], 3
		mov dword ptr [eax + 0x10], ecx
		mov dword ptr [eax + 4], edi
		mov word ptr [eax + 8], dx
		add ecx, 0x220
		add eax, 0x14
		dec ebp
		jne L_t3_loop_cat3
		mov eax, dword ptr [esp + 0x14]
		pop edi
		mov dword ptr [eax + 0x65], esi
		mov eax, esi
		pop esi
		pop ebp
		pop ebx
		ret
	}
}

int __cdecl AllocGraveyardField_unused(int building)
{
	unsigned int btype;
	char* type_entry;
	unsigned char tier;
	char* result;
	char* slot_1c;
	char* slot_20;
	int slot_1c_size;
	int slot_20_size;
	int i;
	char* eax_ptr;
	char* ecx_ptr;

	btype = *(unsigned char*) building;
	type_entry = (char*) (g_entity_type_table + btype + btype * 0x24c);
	if (*type_entry != '\x1d') {
		return 0;
	}
	tier = *(unsigned char*) (type_entry + 0x247);
	if (tier < 1 || tier > 3) {
		return 0;
	}

	result = (char*) m_AllocTracked(0x24, &g_1002d474);
	if (result == (char*) 0) {
		return 0;
	}

	/* zero-fill the 0x24-byte struct (9 dwords) */
	{
		int* fill = (int*) result;
		for (i = 9; i != 0; i--) {
			*fill = 0;
			fill = fill + 1;
		}
	}

	*(int*) result = *(int*) (building + 1);
	*(int*) (result + 4) = (unsigned int) *(unsigned char*) (type_entry + 0x247);

	/* allocate slot_1c: g_1002575c[tier] * 0x14 bytes */
	slot_1c_size = g_1002575c[*(unsigned char*) (type_entry + 0x247)] * 0x14;
	slot_1c = (char*) m_AllocTracked(slot_1c_size, &g_1002d45c);
	*(int*) (result + 0x1c) = (int) slot_1c;
	if (slot_1c == (char*) 0) {
		goto cleanup;
	}

	/* zero-fill slot_1c */
	{
		int total = g_1002575c[*(unsigned char*) (type_entry + 0x247)] * 0x14;
		int dwords = total >> 2;
		int rem = total & 3;
		int* dp = (int*) slot_1c;
		char* bp;
		for (i = dwords; i != 0; i--) {
			*dp = 0;
			dp = dp + 1;
		}
		bp = (char*) dp;
		for (i = rem; i != 0; i--) {
			*bp = 0;
			bp = bp + 1;
		}
	}

	/* allocate slot_20: g_1002576c[tier] * 0x44 bytes */
	slot_20_size = g_1002576c[*(unsigned char*) (type_entry + 0x247)] * 0x44;
	slot_20 = (char*) m_AllocTracked(slot_20_size, &g_1002d444);
	*(int*) (result + 0x20) = (int) slot_20;
	if (slot_20 == (char*) 0) {
		goto cleanup;
	}

	/* zero-fill slot_20 */
	{
		int total = g_1002576c[*(unsigned char*) (type_entry + 0x247)] * 0x44;
		int dwords = total >> 2;
		int rem = total & 3;
		int* dp = (int*) slot_20;
		char* bp;
		for (i = dwords; i != 0; i--) {
			*dp = 0;
			dp = dp + 1;
		}
		bp = (char*) dp;
		for (i = rem; i != 0; i--) {
			*bp = 0;
			bp = bp + 1;
		}
	}

	/* init slot_20 entries: set first dword of each 0x44-byte entry to -1 */
	if (g_1002576c[*(unsigned char*) (type_entry + 0x247)] > 0) {
		int offset = 0;
		i = 0;
		do {
			*(int*) (*(int*) (result + 0x20) + offset) = -1;
			i = i + 1;
			offset = offset + 0x44;
		} while (i < g_1002576c[*(unsigned char*) (type_entry + 0x247)]);
	}

	/* set up struct fields and category pointers */
	eax_ptr = (char*) *(int*) (result + 0x1c);
	ecx_ptr = (char*) *(int*) (result + 0x20);
	*(int*) (result + 8) = (int) eax_ptr;
	*(char*) (result + 0x18) = 1;
	*(char*) (result + 0x19) = 0;
	*(char*) (result + 0x1a) = 0;
	*(char*) (result + 0x1b) = 0;

	if (*(int*) (result + 4) == 1) {
		/* Tier 1: 8 category-0 slots (stride 0x44), 4 category-1 slots (stride 0x88) */
		*(int*) (result + 0x10) = 0;
		*(int*) (result + 0x0c) = (int) (eax_ptr + 0xa0);
		*(int*) (result + 0x14) = 0;
		for (i = 8; i != 0; i--) {
			*(int*) eax_ptr = 0;
			*(int*) (eax_ptr + 0x10) = (int) ecx_ptr;
			*(int*) (eax_ptr + 4) = -1;
			*(unsigned short*) (eax_ptr + 8) = 0xffff;
			ecx_ptr = ecx_ptr + 0x44;
			eax_ptr = eax_ptr + 0x14;
		}
		for (i = 4; i != 0; i--) {
			*(int*) eax_ptr = 1;
			*(int*) (eax_ptr + 0x10) = (int) ecx_ptr;
			*(int*) (eax_ptr + 4) = -1;
			*(unsigned short*) (eax_ptr + 8) = 0xffff;
			ecx_ptr = ecx_ptr + 0x88;
			eax_ptr = eax_ptr + 0x14;
		}
		*(int*) (building + 0x65) = (int) result;
		return (int) result;
	}

	if (*(int*) (result + 4) == 2) {
		/* Tier 2: 12 cat-0 (0x44), 6 cat-1 (0x88), 2 cat-2 (0x110) */
		*(int*) (result + 0x14) = 0;
		*(int*) (result + 0x0c) = (int) (eax_ptr + 0xf0);
		*(int*) (result + 0x10) = (int) (eax_ptr + 0x168);
		for (i = 0xc; i != 0; i--) {
			*(int*) eax_ptr = 0;
			*(int*) (eax_ptr + 0x10) = (int) ecx_ptr;
			*(int*) (eax_ptr + 4) = -1;
			*(unsigned short*) (eax_ptr + 8) = 0xffff;
			ecx_ptr = ecx_ptr + 0x44;
			eax_ptr = eax_ptr + 0x14;
		}
		for (i = 6; i != 0; i--) {
			*(int*) eax_ptr = 1;
			*(int*) (eax_ptr + 0x10) = (int) ecx_ptr;
			*(int*) (eax_ptr + 4) = -1;
			*(unsigned short*) (eax_ptr + 8) = 0xffff;
			ecx_ptr = ecx_ptr + 0x88;
			eax_ptr = eax_ptr + 0x14;
		}
		for (i = 2; i != 0; i--) {
			*(int*) eax_ptr = 2;
			*(int*) (eax_ptr + 0x10) = (int) ecx_ptr;
			*(int*) (eax_ptr + 4) = -1;
			*(unsigned short*) (eax_ptr + 8) = 0xffff;
			ecx_ptr = ecx_ptr + 0x110;
			eax_ptr = eax_ptr + 0x14;
		}
		*(int*) (building + 0x65) = (int) result;
		return (int) result;
	}

	/* Tier 3: 16 cat-0 (0x44), 8 cat-1 (0x88), 4 cat-2 (0x110), 2 cat-3 (0x220) */
	*(int*) (result + 0x0c) = (int) (eax_ptr + 0x140);
	*(int*) (result + 0x10) = (int) (eax_ptr + 0x1e0);
	*(int*) (result + 0x14) = (int) (eax_ptr + 0x230);
	for (i = 0x10; i != 0; i--) {
		*(int*) eax_ptr = 0;
		*(int*) (eax_ptr + 0x10) = (int) ecx_ptr;
		*(int*) (eax_ptr + 4) = -1;
		*(unsigned short*) (eax_ptr + 8) = 0xffff;
		ecx_ptr = ecx_ptr + 0x44;
		eax_ptr = eax_ptr + 0x14;
	}
	for (i = 8; i != 0; i--) {
		*(int*) eax_ptr = 1;
		*(int*) (eax_ptr + 0x10) = (int) ecx_ptr;
		*(int*) (eax_ptr + 4) = -1;
		*(unsigned short*) (eax_ptr + 8) = 0xffff;
		ecx_ptr = ecx_ptr + 0x88;
		eax_ptr = eax_ptr + 0x14;
	}
	for (i = 4; i != 0; i--) {
		*(int*) eax_ptr = 2;
		*(int*) (eax_ptr + 0x10) = (int) ecx_ptr;
		*(int*) (eax_ptr + 4) = -1;
		*(unsigned short*) (eax_ptr + 8) = 0xffff;
		ecx_ptr = ecx_ptr + 0x110;
		eax_ptr = eax_ptr + 0x14;
	}
	for (i = 2; i != 0; i--) {
		*(int*) eax_ptr = 3;
		*(int*) (eax_ptr + 0x10) = (int) ecx_ptr;
		*(int*) (eax_ptr + 4) = -1;
		*(unsigned short*) (eax_ptr + 8) = 0xffff;
		ecx_ptr = ecx_ptr + 0x220;
		eax_ptr = eax_ptr + 0x14;
	}
	*(int*) (building + 0x65) = (int) result;
	return (int) result;

cleanup:
	if (*(int*) (result + 0x1c) != 0) {
		m_FreeTracked((void*) *(int*) (result + 0x1c));
		*(int*) (result + 0x1c) = 0;
	}
	if (*(int*) (result + 0x20) != 0) {
		m_FreeTracked((void*) *(int*) (result + 0x20));
		*(int*) (result + 0x20) = 0;
	}
	m_FreeTracked(result);
	return 0;
}

/* Upgrades a graveyard field to the next tier. Increases
 * production capacity and unlocks new product types. */

// FUNCTION: SERVER 0x10010d10
// UpgradeGraveyardField

__declspec(naked) unsigned int UpgradeGraveyardField(unsigned char* arg1)
{
	(void) arg1;
	__asm {
		sub esp, 0x10
		xor ecx, ecx
		_emit 0x8b
		_emit 0x15
		_emit 0x30
		_emit 0x8c
		_emit 0x0a
		_emit 0x10
		push ebx
		push ebp
		mov ebp, dword ptr [esp + 0x1c]
		push esi
		push edi
		mov cl, byte ptr [ebp]
		mov ebx, dword ptr [ebp + 0x65]
		add edx, ecx
		lea eax, [ecx + ecx*2]
		shl eax, 4
		add eax, ecx
		lea eax, [eax + eax*2]
		lea esi, [edx + eax*4]
		mov al, byte ptr [edx + eax*4]
		cmp al, 0x1d
		jne L_fail
		xor edi, edi
		cmp ebx, edi
		je L_fail
		mov eax, dword ptr [ebx + 4]
		cmp eax, 3
		jge L_fail
		xor ecx, ecx
		mov cl, byte ptr [esi + 0x247]
		sub ecx, eax
		cmp ecx, 1
		jne L_fail
		push ebp
		mov dword ptr [ebp + 0x65], edi
		call AllocGraveyardField
		add esp, 4
		cmp eax, edi
		jne L_alloc_ok
		mov dword ptr [ebp + 0x65], ebx
	L_fail:
		pop edi
		pop esi
		pop ebp
		xor eax, eax
		pop ebx
		add esp, 0x10
		ret
	L_alloc_ok:
		mov dl, byte ptr [esi + 0x247]
		mov ecx, 2
		cmp dl, cl
		jne L_not_cat2
		mov esi, dword ptr [ebx + 8]
		mov dword ptr [esp + 0x18], edi
		mov edi, dword ptr [eax + 8]
		mov ecx, 0x88
		mov esi, dword ptr [esi + 0x10]
		mov edx, 8
		mov edi, dword ptr [edi + 0x10]
		mov ebp, 4
		rep movsd
		mov esi, dword ptr [ebx + 0xc]
		mov edi, dword ptr [eax + 0xc]
		mov ecx, 0x88
		mov esi, dword ptr [esi + 0x10]
		jmp L_third_movsd
	L_not_cat2:
		mov esi, dword ptr [ebx + 8]
		mov edi, dword ptr [eax + 8]
		mov dword ptr [esp + 0x18], ecx
		mov ecx, 0xcc
		mov esi, dword ptr [esi + 0x10]
		mov edi, dword ptr [edi + 0x10]
		rep movsd
		mov esi, dword ptr [ebx + 0xc]
		mov edi, dword ptr [eax + 0xc]
		mov ecx, 0xcc
		mov edx, 0xc
		mov esi, dword ptr [esi + 0x10]
		mov edi, dword ptr [edi + 0x10]
		rep movsd
		mov esi, dword ptr [ebx + 0x10]
		mov edi, dword ptr [eax + 0x10]
		mov ebp, 6
		mov ecx, 0x88
		mov esi, dword ptr [esi + 0x10]
	L_third_movsd:
		mov edi, dword ptr [edi + 0x10]
		rep movsd
		mov ecx, dword ptr [ebx + 8]
		test ecx, ecx
		je near L_after_loop1
		test edx, edx
		jle near L_after_loop1
		xor esi, esi
		mov edi, edx
	L_loop1:
		mov edx, dword ptr [ebx + 8]
		mov ecx, dword ptr [eax + 8]
		mov edx, dword ptr [esi + edx]
		mov dword ptr [ecx + esi], edx
		mov ecx, dword ptr [ebx + 8]
		mov edx, dword ptr [eax + 8]
		mov ecx, dword ptr [esi + ecx + 4]
		mov dword ptr [edx + esi + 4], ecx
		mov edx, dword ptr [ebx + 8]
		mov ecx, dword ptr [eax + 8]
		mov dx, word ptr [esi + edx + 8]
		mov word ptr [ecx + esi + 8], dx
		mov ecx, dword ptr [ebx + 8]
		mov edx, dword ptr [eax + 8]
		mov cx, word ptr [esi + ecx + 0xa]
		mov word ptr [edx + esi + 0xa], cx
		mov edx, dword ptr [ebx + 8]
		mov ecx, dword ptr [eax + 8]
		mov dl, byte ptr [esi + edx + 0xc]
		mov byte ptr [ecx + esi + 0xc], dl
		add esi, 0x14
		dec edi
		jne L_loop1
	L_after_loop1:
		mov ecx, dword ptr [ebx + 0xc]
		test ecx, ecx
		je near L_after_loop2
		test ebp, ebp
		jle near L_after_loop2
		xor esi, esi
		mov edi, ebp
	L_loop2:
		mov ecx, dword ptr [ebx + 0xc]
		mov edx, dword ptr [eax + 0xc]
		mov ecx, dword ptr [esi + ecx]
		mov dword ptr [esi + edx], ecx
		mov edx, dword ptr [ebx + 0xc]
		mov ecx, dword ptr [eax + 0xc]
		mov edx, dword ptr [esi + edx + 4]
		mov dword ptr [esi + ecx + 4], edx
		mov ecx, dword ptr [ebx + 0xc]
		mov edx, dword ptr [eax + 0xc]
		mov cx, word ptr [esi + ecx + 8]
		mov word ptr [esi + edx + 8], cx
		mov edx, dword ptr [ebx + 0xc]
		mov ecx, dword ptr [eax + 0xc]
		mov dx, word ptr [esi + edx + 0xa]
		mov word ptr [esi + ecx + 0xa], dx
		mov ecx, dword ptr [ebx + 0xc]
		mov edx, dword ptr [eax + 0xc]
		mov cl, byte ptr [esi + ecx + 0xc]
		mov byte ptr [esi + edx + 0xc], cl
		add esi, 0x14
		dec edi
		jne L_loop2
	L_after_loop2:
		mov ecx, dword ptr [ebx + 0x10]
		test ecx, ecx
		je near L_byte_copies
		mov edi, dword ptr [esp + 0x18]
		test edi, edi
		jle near L_byte_copies
		xor esi, esi
	L_loop3:
		mov edx, dword ptr [ebx + 0x10]
		mov ecx, dword ptr [eax + 0x10]
		mov edx, dword ptr [esi + edx]
		mov dword ptr [esi + ecx], edx
		mov ecx, dword ptr [ebx + 0x10]
		mov edx, dword ptr [eax + 0x10]
		mov ecx, dword ptr [esi + ecx + 4]
		mov dword ptr [esi + edx + 4], ecx
		mov edx, dword ptr [ebx + 0x10]
		mov ecx, dword ptr [eax + 0x10]
		mov dx, word ptr [esi + edx + 8]
		mov word ptr [esi + ecx + 8], dx
		mov ecx, dword ptr [ebx + 0x10]
		mov edx, dword ptr [eax + 0x10]
		mov cx, word ptr [esi + ecx + 0xa]
		mov word ptr [esi + edx + 0xa], cx
		mov edx, dword ptr [ebx + 0x10]
		mov ecx, dword ptr [eax + 0x10]
		mov dl, byte ptr [esi + edx + 0xc]
		mov byte ptr [esi + ecx + 0xc], dl
		add esi, 0x14
		dec edi
		jne L_loop3
	L_byte_copies:
		mov cl, byte ptr [ebx + 0x18]
		push ebx
		mov byte ptr [eax + 0x18], cl
		mov dl, byte ptr [ebx + 0x19]
		mov byte ptr [eax + 0x19], dl
		mov cl, byte ptr [ebx + 0x1a]
		mov byte ptr [eax + 0x1a], cl
		mov dl, byte ptr [ebx + 0x1b]
		mov byte ptr [eax + 0x1b], dl
		call gv_Free3Fields
		mov eax, dword ptr [esp + 0x28]
		add esp, 4
		mov eax, dword ptr [eax + 0x65]
		pop edi
		pop esi
		pop ebp
		pop ebx
		add esp, 0x10
		ret
	}
}

unsigned int UpgradeGraveyardField_unused(unsigned char* arg1)
{
	int old_field_ptr;
	int new_field_ptr;
	unsigned int entity_type_idx;
	int loop_byte_offset;
	int slot_copy_counter;
	int slot0_count;
	int slot1_count;
	unsigned int* src_slot_dword_ptr;
	unsigned int* dst_slot_dword_ptr;
	int slot2_count;

	entity_type_idx = *arg1;
	old_field_ptr = *(int*) (arg1 + 0x65);
	loop_byte_offset = *(int*) 0x100a8c30 + entity_type_idx + entity_type_idx * 0x24c;
	if ((((*(char*) (*(int*) 0x100a8c30 + entity_type_idx + entity_type_idx * 0x24c) == '\x1d') &&
		  (old_field_ptr != 0)) &&
		 (*(int*) (old_field_ptr + 4) < 3)) &&
		(*(char*) (loop_byte_offset + 0x247) - *(int*) (old_field_ptr + 4) == 1)) {
		arg1[0x65] = 0;
		arg1[0x66] = 0;
		arg1[0x67] = 0;
		arg1[0x68] = 0;
		new_field_ptr = AllocGraveyardField((int) arg1);
		if (new_field_ptr != 0) {
			if (*(char*) (loop_byte_offset + 0x247) == '\x02') {
				slot2_count = 0;
				slot0_count = 8;
				slot1_count = 4;
				src_slot_dword_ptr = *(unsigned int**) (*(int*) (old_field_ptr + 8) + 0x10);
				dst_slot_dword_ptr = *(unsigned int**) (*(int*) (new_field_ptr + 8) + 0x10);
				for (loop_byte_offset = 0x88; loop_byte_offset != 0; loop_byte_offset = loop_byte_offset + -1) {
					*dst_slot_dword_ptr = *src_slot_dword_ptr;
					src_slot_dword_ptr = src_slot_dword_ptr + 1;
					dst_slot_dword_ptr = dst_slot_dword_ptr + 1;
				}
				loop_byte_offset = *(int*) (new_field_ptr + 0xc);
				src_slot_dword_ptr = *(unsigned int**) (*(int*) (old_field_ptr + 0xc) + 0x10);
			}
			else {
				slot2_count = 2;
				src_slot_dword_ptr = *(unsigned int**) (*(int*) (old_field_ptr + 8) + 0x10);
				dst_slot_dword_ptr = *(unsigned int**) (*(int*) (new_field_ptr + 8) + 0x10);
				for (loop_byte_offset = 0xcc; loop_byte_offset != 0; loop_byte_offset = loop_byte_offset + -1) {
					*dst_slot_dword_ptr = *src_slot_dword_ptr;
					src_slot_dword_ptr = src_slot_dword_ptr + 1;
					dst_slot_dword_ptr = dst_slot_dword_ptr + 1;
				}
				slot0_count = 0xc;
				src_slot_dword_ptr = *(unsigned int**) (*(int*) (old_field_ptr + 0xc) + 0x10);
				dst_slot_dword_ptr = *(unsigned int**) (*(int*) (new_field_ptr + 0xc) + 0x10);
				for (loop_byte_offset = 0xcc; loop_byte_offset != 0; loop_byte_offset = loop_byte_offset + -1) {
					*dst_slot_dword_ptr = *src_slot_dword_ptr;
					src_slot_dword_ptr = src_slot_dword_ptr + 1;
					dst_slot_dword_ptr = dst_slot_dword_ptr + 1;
				}
				loop_byte_offset = *(int*) (new_field_ptr + 0x10);
				slot1_count = 6;
				src_slot_dword_ptr = *(unsigned int**) (*(int*) (old_field_ptr + 0x10) + 0x10);
			}
			dst_slot_dword_ptr = *(unsigned int**) (loop_byte_offset + 0x10);
			for (slot_copy_counter = 0x88; slot_copy_counter != 0; slot_copy_counter = slot_copy_counter + -1) {
				*dst_slot_dword_ptr = *src_slot_dword_ptr;
				src_slot_dword_ptr = src_slot_dword_ptr + 1;
				dst_slot_dword_ptr = dst_slot_dword_ptr + 1;
			}
			if ((*(int*) (old_field_ptr + 8) != 0) && (slot0_count != 0)) {
				loop_byte_offset = 0;
				do {
					*(int*) (*(int*) (new_field_ptr + 8) + loop_byte_offset) =
						*(int*) (loop_byte_offset + *(int*) (old_field_ptr + 8));
					*(int*) (*(int*) (new_field_ptr + 8) + 4 + loop_byte_offset) =
						*(int*) (loop_byte_offset + 4 + *(int*) (old_field_ptr + 8));
					*(int*) (*(int*) (new_field_ptr + 8) + 8 + loop_byte_offset) =
						*(int*) (loop_byte_offset + 8 + *(int*) (old_field_ptr + 8));
					*(short*) (*(int*) (new_field_ptr + 8) + 10 + loop_byte_offset) =
						*(short*) (loop_byte_offset + 10 + *(int*) (old_field_ptr + 8));
					*(char*) (*(int*) (new_field_ptr + 8) + 0xc + loop_byte_offset) =
						*(char*) (loop_byte_offset + 0xc + *(int*) (old_field_ptr + 8));
					loop_byte_offset = loop_byte_offset + 0x14;
					slot0_count = slot0_count + -1;
				} while (slot0_count != 0);
			}
			if ((*(int*) (old_field_ptr + 0xc) != 0) && (slot1_count != 0)) {
				loop_byte_offset = 0;
				do {
					*(int*) (loop_byte_offset + *(int*) (new_field_ptr + 0xc)) =
						*(int*) (loop_byte_offset + *(int*) (old_field_ptr + 0xc));
					*(int*) (loop_byte_offset + 4 + *(int*) (new_field_ptr + 0xc)) =
						*(int*) (loop_byte_offset + 4 + *(int*) (old_field_ptr + 0xc));
					*(int*) (loop_byte_offset + 8 + *(int*) (new_field_ptr + 0xc)) =
						*(int*) (loop_byte_offset + 8 + *(int*) (old_field_ptr + 0xc));
					*(short*) (loop_byte_offset + 10 + *(int*) (new_field_ptr + 0xc)) =
						*(short*) (loop_byte_offset + 10 + *(int*) (old_field_ptr + 0xc));
					*(char*) (loop_byte_offset + 0xc + *(int*) (new_field_ptr + 0xc)) =
						*(char*) (loop_byte_offset + 0xc + *(int*) (old_field_ptr + 0xc));
					loop_byte_offset = loop_byte_offset + 0x14;
					slot1_count = slot1_count + -1;
				} while (slot1_count != 0);
			}
			if ((*(int*) (old_field_ptr + 0x10) != 0) && (slot2_count != 0)) {
				loop_byte_offset = 0;
				do {
					*(int*) (loop_byte_offset + *(int*) (new_field_ptr + 0x10)) =
						*(int*) (loop_byte_offset + *(int*) (old_field_ptr + 0x10));
					*(int*) (loop_byte_offset + 4 + *(int*) (new_field_ptr + 0x10)) =
						*(int*) (loop_byte_offset + 4 + *(int*) (old_field_ptr + 0x10));
					*(int*) (loop_byte_offset + 8 + *(int*) (new_field_ptr + 0x10)) =
						*(int*) (loop_byte_offset + 8 + *(int*) (old_field_ptr + 0x10));
					*(short*) (loop_byte_offset + 10 + *(int*) (new_field_ptr + 0x10)) =
						*(short*) (loop_byte_offset + 10 + *(int*) (old_field_ptr + 0x10));
					*(char*) (loop_byte_offset + 0xc + *(int*) (new_field_ptr + 0x10)) =
						*(char*) (loop_byte_offset + 0xc + *(int*) (old_field_ptr + 0x10));
					loop_byte_offset = loop_byte_offset + 0x14;
					slot2_count = slot2_count + -1;
				} while (slot2_count != 0);
			}
			*(int*) (new_field_ptr + 0x18) = *(int*) (old_field_ptr + 0x18);
			*(char*) (new_field_ptr + 0x19) = *(char*) (old_field_ptr + 0x19);
			*(char*) (new_field_ptr + 0x1a) = *(char*) (old_field_ptr + 0x1a);
			*(char*) (new_field_ptr + 0x1b) = *(char*) (old_field_ptr + 0x1b);
			gv_Free3Fields((char*) old_field_ptr);
			return *(unsigned int*) (arg1 + 0x65);
		}
		*(unsigned int*) (arg1 + 0x65) = old_field_ptr;
	}
	return 0;
}

/* Frees 3 consecutive production fields in a building.
 * Deallocates the field entities and clears their slots. */

// FUNCTION: SERVER 0x10010F50
// gv_Free3Fields

void __cdecl gv_Free3Fields(char* p)
{
	if (!p) {
		return;
	}
	if (*(int*) (p + 0x1c)) {
		game_free(*(void**) (p + 0x1c));
		*(int*) (p + 0x1c) = 0;
	}
	if (*(int*) (p + 0x20)) {
		game_free(*(void**) (p + 0x20));
		*(int*) (p + 0x20) = 0;
	}
	game_free(p);
}

/* Assigns a product type to a production slot. Validates the
 * slot is empty, sets the product ID, and initializes the
 * production timer. */

// FUNCTION: SERVER 0x10010fa0
// AssignProductionSlot

__declspec(naked) unsigned int AssignProductionSlot(int arg1)
{
	(void) arg1;
	__asm {
		push ecx
		push ebx
		push esi
		mov esi, dword ptr [esp + 0x10]
		push edi
		lea ecx, [esp + 0xc]
		mov eax, dword ptr [esi + 8]
		push eax
		push 0
		push 0
		push ecx
		call gm_ResolveEntityById
		mov edx, dword ptr [esp + 0x1c]
		add esp, 0x10
		test edx, edx
		je near L_neg1
		mov ax, word ptr [edx + 0x27]
		cmp ax, 0xffff
		je near L_neg1
		and eax, 0xffff
		lea eax, [eax + eax*2]
		lea eax, [eax + eax*4]
		lea eax, [eax + eax*8]
		lea ecx, [eax*4 + 0x100358a0]
		_emit 0xa1
		_emit 0x6c
		_emit 0x54
		_emit 0x03
		_emit 0x10
		cmp ecx, eax
		je near L_neg1
		xor ecx, ecx
		_emit 0x8b
		_emit 0x3d
		_emit 0x30
		_emit 0x8c
		_emit 0x0a
		_emit 0x10
		mov cl, byte ptr [edx]
		add edi, ecx
		lea eax, [ecx + ecx*2]
		shl eax, 4
		add eax, ecx
		lea eax, [eax + eax*2]
		cmp byte ptr [edi + eax*4], 0x1d
		je L_chk_field65
		pop edi
		pop esi
		mov eax, 0xfffffffe
		pop ebx
		pop ecx
		ret
	L_chk_field65:
		mov edi, dword ptr [edx + 0x65]
		test edi, edi
		jne L_call_check
		pop edi
		pop esi
		mov eax, 0xfffffffd
		pop ebx
		pop ecx
		ret
	L_call_check:
		mov ecx, dword ptr [esi + 0xc]
		push ecx
		push edi
		call gv_CheckSlotActive
		add esp, 8
		test eax, eax
		jne L_resolve2
		pop edi
		pop esi
		mov eax, 0xfffffffc
		pop ebx
		pop ecx
		ret
	L_resolve2:
		mov edx, dword ptr [esi + 4]
		lea eax, [esp + 0x14]
		push edx
		push eax
		push 0
		push 0
		call gm_ResolveEntityById
		mov eax, dword ptr [esp + 0x24]
		add esp, 0x10
		test eax, eax
		jne L_get_slot
		pop edi
		pop esi
		mov eax, 0xfffffffa
		pop ebx
		pop ecx
		ret
	L_get_slot:
		mov cl, byte ptr [esi + 0x10]
		mov edx, dword ptr [esi + 0xc]
		push ecx
		push edx
		push edi
		call gv_GetSlotEntry
		add esp, 0xc
		test eax, eax
		je near L_neg7
		mov ebx, dword ptr [esp + 0x14]
		mov cx, word ptr [eax + 8]
		cmp cx, word ptr [ebx + 0x50]
		jne near L_neg7
		mov edi, dword ptr [eax + 0x10]
		mov eax, dword ptr [esi + 0xc]
		xor ecx, ecx
		push ebp
		mov esi, dword ptr [eax*4 + 0x1002574c]
		mov edx, edi
		test esi, esi
		jle L_after_loop
		mov eax, edi
	L_search_loop:
		cmp dword ptr [edx], -1
		je L_after_loop
		cmp dword ptr [eax], -1
		je L_set_edx_ecx
		mov ebp, dword ptr [edx + 0x40]
		cmp ebp, dword ptr [eax + 0x40]
		jle L_inc_loop
		mov edx, eax
	L_inc_loop:
		inc ecx
		add eax, 0x44
		cmp ecx, esi
		jl L_search_loop
		jmp L_after_loop
	L_set_edx_ecx:
		mov edx, ecx
		shl edx, 4
		add edx, ecx
		lea edx, [edi + edx*4]
	L_after_loop:
		mov eax, dword ptr [ebx + 4]
		lea ebx, [edx + 4]
		mov dword ptr [edx], eax
		mov ecx, dword ptr [esp + 0x18]
		xor eax, eax
		pop ebp
		lea edi, [ecx + 0x30]
		or ecx, 0xffffffff
		repne scasb
		not ecx
		sub edi, ecx
		mov eax, ecx
		mov esi, edi
		mov edi, ebx
		lea ebx, [edx + 0x14]
		shr ecx, 2
		rep movsd
		mov ecx, eax
		xor eax, eax
		and ecx, 3
		rep movsb
		mov ecx, dword ptr [esp + 0x14]
		lea edi, [ecx + 0x40]
		or ecx, 0xffffffff
		repne scasb
		not ecx
		sub edi, ecx
		mov eax, ecx
		mov esi, edi
		mov edi, ebx
		shr ecx, 2
		rep movsd
		mov ecx, eax
		lea eax, [edx + 0x24]
		and ecx, 3
		rep movsb
		mov ecx, dword ptr [esp + 0x14]
		pop edi
		add ecx, 0x80
		mov esi, dword ptr [ecx]
		mov dword ptr [eax], esi
		pop esi
		mov cl, byte ptr [ecx + 4]
		pop ebx
		mov byte ptr [eax + 4], cl
		mov ecx, dword ptr [esp + 8]
		xor eax, eax
		mov al, byte ptr [ecx + 0x167]
		mov dword ptr [edx + 0x2c], eax
		mov ecx, dword ptr [esp + 8]
		xor eax, eax
		mov al, byte ptr [ecx + 0xd]
		mov dword ptr [edx + 0x30], eax
		mov ecx, dword ptr [esp + 8]
		xor eax, eax
		mov al, byte ptr [ecx + 0x164]
		mov dword ptr [edx + 0x34], eax
		mov ecx, dword ptr [esp + 8]
		xor eax, eax
		mov al, byte ptr [ecx + 9]
		mov dword ptr [edx + 0x38], eax
		_emit 0xa1
		_emit 0x80
		_emit 0x58
		_emit 0x03
		_emit 0x10
		mov dword ptr [edx + 0x40], eax
		mov ecx, dword ptr [esp + 8]
		mov eax, dword ptr [ecx + 0x18c]
		mov dword ptr [edx + 0x3c], eax
		xor eax, eax
		pop ecx
		ret
	L_neg7:
		pop edi
		pop esi
		mov eax, 0xfffffff9
		pop ebx
		pop ecx
		ret
	L_neg1:
		pop edi
		pop esi
		or eax, 0xffffffff
		pop ebx
		pop ecx
		ret
	}
}

unsigned int AssignProductionSlot_unused(int arg1)
{
	char str_scan_char;
	int worker_slot_capacity;
	int slot_category_check;
	int assignment_loop_idx;
	int* candidate_record_ptr;
	unsigned int strlen_counter;
	unsigned int copy_dword_count;
	int* best_slot_record_ptr;
	int* slot_worker_array_ptr;
	char* name_scan_ptr;
	char* name_scan_end_ptr;
	unsigned char* building_entity_ptr;

	worker_slot_capacity = arg1;
	gm_ResolveEntityById(&building_entity_ptr, 0, 0, *(unsigned int*) (arg1 + 8));
	if (((building_entity_ptr == 0) || (*(unsigned short*) (building_entity_ptr + 0x27) == 0xffff)) ||
		(*(unsigned short*) (building_entity_ptr + 0x27) * 0x21c + *(unsigned int*) 0x100358a0 ==
		 *(unsigned int*) 0x1003546c)) {
		return 0xffffffff;
	}
	if (*(*(char**) 0x100a8c30 + *building_entity_ptr * 0x24d) != '\x1d') {
		return 0xfffffffe;
	}
	assignment_loop_idx = *(unsigned int*) (building_entity_ptr + 0x65);
	if (assignment_loop_idx == 0) {
		return 0xfffffffd;
	}
	slot_category_check = gv_CheckSlotActive((char*) assignment_loop_idx, *(int*) (worker_slot_capacity + 0xc));
	if (slot_category_check == 0) {
		return 0xfffffffc;
	}
	gm_ResolveEntityById((void**) 0, (void**) 0, (void**) &arg1, *(unsigned int*) (worker_slot_capacity + 4));
	if (arg1 == 0) {
		return 0xfffffffa;
	}
	assignment_loop_idx = gv_GetSlotEntry(
		assignment_loop_idx,
		*(int*) (worker_slot_capacity + 0xc),
		(unsigned char) *(int*) (worker_slot_capacity + 0x10)
	);
	if ((assignment_loop_idx == 0) ||
		(*(unsigned int*) (assignment_loop_idx + 8) != *(unsigned int*) (arg1 + 0x50))) {
		return 0xfffffff9;
	}
	slot_worker_array_ptr = *(int**) (assignment_loop_idx + 0x10);
	assignment_loop_idx = 0;
	worker_slot_capacity = *(int*) (*(int*) (worker_slot_capacity + 0xc) * 4 + 0x1002574c);
	candidate_record_ptr = slot_worker_array_ptr;
	best_slot_record_ptr = slot_worker_array_ptr;
	if (0 < worker_slot_capacity) {
		do {
			if (*best_slot_record_ptr == -1) {
				break;
			}
			if (*candidate_record_ptr == -1) {
				best_slot_record_ptr = slot_worker_array_ptr + assignment_loop_idx * 0x11;
				break;
			}
			if (candidate_record_ptr[0x10] < best_slot_record_ptr[0x10]) {
				best_slot_record_ptr = candidate_record_ptr;
			}
			assignment_loop_idx = assignment_loop_idx + 1;
			candidate_record_ptr = candidate_record_ptr + 0x11;
		} while (assignment_loop_idx < worker_slot_capacity);
	}
	*best_slot_record_ptr = *(unsigned int*) (arg1 + 4);
	strlen_counter = 0xffffffff;
	name_scan_ptr = (char*) (arg1 + 0x30);
	do {
		name_scan_end_ptr = name_scan_ptr;
		if (strlen_counter == 0) {
			break;
		}
		strlen_counter = strlen_counter - 1;
		name_scan_end_ptr = name_scan_ptr + 1;
		str_scan_char = *name_scan_ptr;
		name_scan_ptr = name_scan_end_ptr;
	} while (str_scan_char != '\0');
	strlen_counter = ~strlen_counter;
	candidate_record_ptr = (int*) (name_scan_end_ptr + -(int) strlen_counter);
	slot_worker_array_ptr = best_slot_record_ptr;
	for (copy_dword_count = strlen_counter >> 2;
		 slot_worker_array_ptr = slot_worker_array_ptr + 1, copy_dword_count != 0;
		 copy_dword_count = copy_dword_count - 1) {
		*slot_worker_array_ptr = *candidate_record_ptr;
		candidate_record_ptr = candidate_record_ptr + 1;
	}
	for (strlen_counter = strlen_counter & 3; strlen_counter != 0; strlen_counter = strlen_counter - 1) {
		*slot_worker_array_ptr = *candidate_record_ptr;
		candidate_record_ptr = candidate_record_ptr + 1;
		slot_worker_array_ptr = slot_worker_array_ptr + 1;
	}
	strlen_counter = 0xffffffff;
	name_scan_ptr = (char*) (arg1 + 0x40);
	do {
		name_scan_end_ptr = name_scan_ptr;
		if (strlen_counter == 0) {
			break;
		}
		strlen_counter = strlen_counter - 1;
		name_scan_end_ptr = name_scan_ptr + 1;
		str_scan_char = *name_scan_ptr;
		name_scan_ptr = name_scan_end_ptr;
	} while (str_scan_char != '\0');
	strlen_counter = ~strlen_counter;
	slot_worker_array_ptr = (int*) (name_scan_end_ptr + -(int) strlen_counter);
	candidate_record_ptr = best_slot_record_ptr + 5;
	for (copy_dword_count = strlen_counter >> 2; copy_dword_count != 0; copy_dword_count = copy_dword_count - 1) {
		*candidate_record_ptr = *slot_worker_array_ptr;
		slot_worker_array_ptr = slot_worker_array_ptr + 1;
		candidate_record_ptr = candidate_record_ptr + 1;
	}
	for (strlen_counter = strlen_counter & 3; strlen_counter != 0; strlen_counter = strlen_counter - 1) {
		*candidate_record_ptr = *slot_worker_array_ptr;
		slot_worker_array_ptr = slot_worker_array_ptr + 1;
		candidate_record_ptr = candidate_record_ptr + 1;
	}
	best_slot_record_ptr[9] = *(unsigned int*) (arg1 + 0x80);
	*(best_slot_record_ptr + 10) = *(unsigned int*) (arg1 + 0x84);
	best_slot_record_ptr[0xb] = *(unsigned int*) (arg1 + 0x167);
	best_slot_record_ptr[0xc] = *(unsigned int*) (arg1 + 0xd);
	best_slot_record_ptr[0xd] = *(unsigned int*) (arg1 + 0x164);
	best_slot_record_ptr[0xe] = *(unsigned int*) (arg1 + 9);
	best_slot_record_ptr[0x10] = *(unsigned int*) 0x10035880;
	best_slot_record_ptr[0xf] = *(unsigned int*) (arg1 + 0x18c);
	return 0;
}

/* Hires a worker for a production slot. Links the worker
 * entity to the building's production slot and starts the
 * production cycle. */

// FUNCTION: SERVER 0x100111b0
// HireProductionWorker

__declspec(naked) unsigned int HireProductionWorker(int arg1)
{
	(void) arg1;
	__asm {
		push ecx
		push esi
		mov esi, dword ptr [esp + 0xc]
		push edi
		lea ecx, [esp + 8]
		mov eax, dword ptr [esi + 8]
		push eax
		push 0
		push 0
		push ecx
		call gm_ResolveEntityById
		mov edx, dword ptr [esp + 0x18]
		add esp, 0x10
		test edx, edx
		je near L_neg1
		mov ax, word ptr [edx + 0x27]
		cmp ax, 0xffff
		je near L_neg1
		and eax, 0xffff
		lea eax, [eax + eax*2]
		lea eax, [eax + eax*4]
		lea eax, [eax + eax*8]
		lea ecx, [eax*4 + 0x100358a0]
		_emit 0xa1
		_emit 0x6c
		_emit 0x54
		_emit 0x03
		_emit 0x10
		cmp ecx, eax
		je near L_neg1
		xor ecx, ecx
		_emit 0x8b
		_emit 0x3d
		_emit 0x30
		_emit 0x8c
		_emit 0x0a
		_emit 0x10
		mov cl, byte ptr [edx]
		add edi, ecx
		lea eax, [ecx + ecx*2]
		shl eax, 4
		add eax, ecx
		lea eax, [eax + eax*2]
		cmp byte ptr [edi + eax*4], 0x1d
		je L_chk_field65
		pop edi
		mov eax, 0xfffffffe
		pop esi
		pop ecx
		ret
	L_chk_field65:
		mov edx, dword ptr [edx + 0x65]
		test edx, edx
		jne L_call_check
		pop edi
		mov eax, 0xfffffffd
		pop esi
		pop ecx
		ret
	L_call_check:
		mov ecx, dword ptr [esi + 0xc]
		push ecx
		push edx
		call gv_CheckSlotActive
		add esp, 8
		test eax, eax
		jne L_resolve2
		pop edi
		mov eax, 0xfffffffc
		pop esi
		pop ecx
		ret
	L_resolve2:
		mov edx, dword ptr [esi + 4]
		lea eax, [esp + 0x10]
		push edx
		push eax
		push 0
		push 0
		call gm_ResolveEntityById
		mov ecx, dword ptr [esp + 0x20]
		add esp, 0x10
		test ecx, ecx
		jne L_check_idx
		pop edi
		mov eax, 0xfffffffa
		pop esi
		pop ecx
		ret
	L_check_idx:
		mov eax, dword ptr [esi + 0xc]
		test eax, eax
		jl near L_negb
		cmp eax, 3
		jg near L_negb
		mov edx, dword ptr [esp + 8]
		push eax
		push 0x10010700
		push 0
		push edx
		push ecx
		call gv_FindSlotEntryFiltered
		add esp, 0x14
		test eax, eax
		jne L_have_slot
		pop edi
		mov eax, 0xfffffff9
		pop esi
		pop ecx
		ret
	L_have_slot:
		mov ecx, dword ptr [esp + 0x10]
		mov edx, dword ptr [ecx + 4]
		mov dword ptr [eax + 4], edx
		mov ecx, dword ptr [esp + 0x10]
		mov dx, word ptr [ecx + 0x50]
		mov word ptr [eax + 8], dx
		mov cx, word ptr [esi + 0x11]
		_emit 0x66
		_emit 0x03
		_emit 0x0d
		_emit 0x80
		_emit 0x58
		_emit 0x03
		_emit 0x10
		mov byte ptr [eax + 0xc], 0xff
		mov word ptr [eax + 0xa], cx
		mov edx, dword ptr [esi + 0xc]
		xor ecx, ecx
		mov edi, dword ptr [edx*4 + 0x1002574c]
		test edi, edi
		jle L_skip_reset
		xor edx, edx
	L_reset_loop:
		mov edi, dword ptr [eax + 0x10]
		inc ecx
		mov dword ptr [edi + edx], 0xffffffff
		mov edi, dword ptr [esi + 0xc]
		add edx, 0x44
		cmp ecx, dword ptr [edi*4 + 0x1002574c]
		jl L_reset_loop
	L_skip_reset:
		mov eax, dword ptr [esi + 0x13]
		test eax, eax
		jle L_finish
		xor ecx, ecx
		push eax
		_emit 0x8a
		_emit 0x0d
		_emit 0x39
		_emit 0x54
		_emit 0x03
		_emit 0x10
		mov edx, dword ptr [esp + 0x14]
		mov eax, ecx
		shl eax, 6
		sub eax, ecx
		xor ecx, ecx
		lea eax, [eax + eax*2]
		mov cx, word ptr [eax*4 + 0x100a8c94]
		mov eax, dword ptr [edx + 4]
		push ecx
		push eax
		call gm_SubObjektNoKill
		fild dword ptr [esi + 0x13]
		mov ecx, dword ptr [esi + 0xc]
		fmul dword ptr [ecx*4 + 0x1002572c]
		call __ftol
		xor ecx, ecx
		push eax
		_emit 0x8a
		_emit 0x0d
		_emit 0x39
		_emit 0x54
		_emit 0x03
		_emit 0x10
		mov eax, ecx
		shl eax, 6
		sub eax, ecx
		mov ecx, dword ptr [esp + 0x18]
		lea edx, [eax + eax*2]
		xor eax, eax
		mov ax, word ptr [edx*4 + 0x100a8c94]
		push eax
		xor eax, eax
		mov ax, word ptr [ecx + 0x27]
		lea eax, [eax + eax*2]
		lea eax, [eax + eax*4]
		lea edx, [eax + eax*8]
		mov eax, dword ptr [edx*4 + 0x100358a4]
		push eax
		call gm_AddOrAccumulateObject
		add esp, 0x18
	L_finish:
		pop edi
		xor eax, eax
		pop esi
		pop ecx
		ret
	L_negb:
		pop edi
		mov eax, 0xfffffffb
		pop esi
		pop ecx
		ret
	L_neg1:
		pop edi
		or eax, 0xffffffff
		pop esi
		pop ecx
		ret
	}
}

unsigned int HireProductionWorker_unused(int arg1)
{
	int cmd_ptr_saved;
	int slot_or_active_check;
	unsigned int rand_coin_amount;
	short hire_deadline_tick;
	int worker_record_count;
	int worker_record_offset;
	unsigned char* building_entity_ptr;

	cmd_ptr_saved = arg1;
	gm_ResolveEntityById(&building_entity_ptr, 0, 0, *(unsigned int*) (arg1 + 8));
	if (((building_entity_ptr == 0) || (*(unsigned short*) (building_entity_ptr + 0x27) == 0xffff)) ||
		(*(unsigned short*) (building_entity_ptr + 0x27) * 0x21c + *(unsigned int*) 0x100358a0 ==
		 *(unsigned int*) 0x1003546c)) {
		return 0xffffffff;
	}
	if (*(*(char**) 0x100a8c30 + *building_entity_ptr * 0x24d) != '\x1d') {
		return 0xfffffffe;
	}
	if (*(unsigned int*) (building_entity_ptr + 0x65) == 0) {
		return 0xfffffffd;
	}
	slot_or_active_check =
		gv_CheckSlotActive((char*) *(unsigned int*) (building_entity_ptr + 0x65), *(int*) (cmd_ptr_saved + 0xc));
	if (slot_or_active_check == 0) {
		return 0xfffffffc;
	}
	gm_ResolveEntityById((void**) 0, (void**) 0, (void**) &arg1, *(unsigned int*) (cmd_ptr_saved + 4));
	if (arg1 == 0) {
		return 0xfffffffa;
	}
	slot_or_active_check = *(int*) (cmd_ptr_saved + 0xc);
	if ((-1 < slot_or_active_check) && (slot_or_active_check < 4)) {
		slot_or_active_check = (int) gv_FindSlotEntryFiltered(
			(char*) arg1,
			building_entity_ptr,
			(char*) 0,
			(int(__cdecl*)(char*, char*)) 0x10010700,
			slot_or_active_check
		);
		if (slot_or_active_check == 0) {
			return 0xfffffff9;
		}
		*(unsigned int*) (slot_or_active_check + 4) = *(unsigned int*) (arg1 + 4);
		*(unsigned int*) (slot_or_active_check + 8) = *(unsigned int*) (arg1 + 0x50);
		hire_deadline_tick = *(short*) (cmd_ptr_saved + 0x11) + *(short*) 0x10035880;
		*(unsigned char*) (slot_or_active_check + 0xc) = 0xff;
		*(short*) (slot_or_active_check + 10) = hire_deadline_tick;
		worker_record_count = 0;
		if (0 < *(int*) (*(int*) (cmd_ptr_saved + 0xc) * 4 + 0x1002574c)) {
			worker_record_offset = 0;
			do {
				worker_record_count = worker_record_count + 1;
				*(unsigned int*) (*(int*) (slot_or_active_check + 0x10) + worker_record_offset) = 0xffffffff;
				worker_record_offset = worker_record_offset + 0x44;
			} while (worker_record_count < *(int*) (*(int*) (cmd_ptr_saved + 0xc) * 4 + 0x1002574c));
		}
		if (0 < *(int*) (cmd_ptr_saved + 0x13)) {
			gm_SubObjektNoKill(
				*(unsigned int*) (arg1 + 4),
				*(unsigned int*) (*(unsigned int*) 0x10035439 * 0x2f4 + 0x100a8c94),
				*(unsigned int*) (cmd_ptr_saved + 0x13)
			);
			rand_coin_amount = __ftol();
			gm_AddOrAccumulateObject(
				*(unsigned int*) (*(unsigned short*) (building_entity_ptr + 0x27) * 0x21c + 0x100358a4),
				*(unsigned int*) (*(unsigned int*) 0x10035439 * 0x2f4 + 0x100a8c94),
				rand_coin_amount
			);
		}
		return 0;
	}
	return 0xfffffffb;
}

/* Extends the production time for an active slot. Adds
 * additional time to the production timer, adjusting for
 * worker skill and building efficiency. */

// FUNCTION: SERVER 0x100113b0
// ExtendProductionTime

/* Auto-generated Ghidra decompilation */

__declspec(naked) unsigned int ExtendProductionTime(unsigned int* arg1)
{
	(void) arg1;
	__asm {
		push ecx
		push esi
		mov esi, dword ptr [esp + 0xc]
		push edi
		lea ecx, [esp + 8]
		mov eax, dword ptr [esi + 8]
		push eax
		push 0
		push 0
		push ecx
		call gm_ResolveEntityById
		mov edx, dword ptr [esp + 0x18]
		add esp, 0x10
		test edx, edx
		je near L_ret_neg1
		mov ax, word ptr [edx + 0x27]
		cmp ax, 0xffff
		je near L_ret_neg1
		and eax, 0xffff
		lea eax, [eax + eax*2]
		lea eax, [eax + eax*4]
		lea eax, [eax + eax*8]
		lea ecx, [eax*4 + 0x100358a0]
		_emit 0xa1
		_emit 0x6c
		_emit 0x54
		_emit 0x03
		_emit 0x10
		cmp ecx, eax
		je near L_ret_neg1
		xor ecx, ecx
		_emit 0x8b
		_emit 0x3d
		_emit 0x30
		_emit 0x8c
		_emit 0x0a
		_emit 0x10
		mov cl, byte ptr [edx]
		add edi, ecx
		lea eax, [ecx + ecx*2]
		shl eax, 4
		add eax, ecx
		lea eax, [eax + eax*2]
		cmp byte ptr [edi + eax*4], 0x1d
		je L_action_ok
		pop edi
		mov eax, 0xfffffffe
		pop esi
		pop ecx
		ret
	L_action_ok:
		mov edi, dword ptr [edx + 0x65]
		test edi, edi
		jne L_have_slot
		pop edi
		mov eax, 0xfffffffd
		pop esi
		pop ecx
		ret
	L_have_slot:
		mov ecx, dword ptr [esi + 0xc]
		push ecx
		push edi
		call gv_CheckSlotActive
		add esp, 8
		test eax, eax
		jne L_slot_ok
		pop edi
		mov eax, 0xfffffffc
		pop esi
		pop ecx
		ret
	L_slot_ok:
		mov edx, dword ptr [esi + 4]
		lea eax, [esp + 0x10]
		push edx
		push eax
		push 0
		push 0
		call gm_ResolveEntityById
		mov eax, dword ptr [esp + 0x20]
		add esp, 0x10
		test eax, eax
		jne L_have_p1
		pop edi
		mov eax, 0xfffffffa
		pop esi
		pop ecx
		ret
	L_have_p1:
		mov cl, byte ptr [esi + 0x10]
		mov edx, dword ptr [esi + 0xc]
		push ecx
		push edx
		push edi
		call gv_GetSlotEntry
		add esp, 0xc
		test eax, eax
		jne L_have_entry
		pop edi
		mov eax, 0xfffffff9
		pop esi
		pop ecx
		ret
	L_have_entry:
		mov cx, word ptr [esi + 0x11]
		add word ptr [eax + 0xa], cx
		mov eax, dword ptr [esi + 0x13]
		test eax, eax
		jle L_ret0
		xor ecx, ecx
		push eax
		_emit 0x8a
		_emit 0x0d
		_emit 0x39
		_emit 0x54
		_emit 0x03
		_emit 0x10
		mov eax, ecx
		shl eax, 6
		sub eax, ecx
		mov ecx, dword ptr [esp + 0x14]
		lea edx, [eax + eax*2]
		xor eax, eax
		mov ax, word ptr [edx*4 + 0x100a8c94]
		mov edx, dword ptr [ecx + 4]
		push eax
		push edx
		call gm_SubObjektNoKill
		fild dword ptr [esi + 0x13]
		mov eax, dword ptr [esi + 0xc]
		_emit 0xd8
		_emit 0x0c
		_emit 0x85
		_emit 0x2c
		_emit 0x57
		_emit 0x02
		_emit 0x10
		call __ftol
		xor ecx, ecx
		push eax
		_emit 0x8a
		_emit 0x0d
		_emit 0x39
		_emit 0x54
		_emit 0x03
		_emit 0x10
		xor edx, edx
		mov eax, ecx
		shl eax, 6
		sub eax, ecx
		lea ecx, [eax + eax*2]
		xor eax, eax
		mov dx, word ptr [ecx*4 + 0x100a8c94]
		mov ecx, dword ptr [esp + 0x18]
		push edx
		mov ax, word ptr [ecx + 0x27]
		lea eax, [eax + eax*2]
		lea eax, [eax + eax*4]
		lea edx, [eax + eax*8]
		mov eax, dword ptr [edx*4 + 0x100358a4]
		push eax
		call gm_AddOrAccumulateObject
		add esp, 0x18
	L_ret0:
		pop edi
		xor eax, eax
		pop esi
		pop ecx
		ret
	L_ret_neg1:
		pop edi
		or eax, 0xffffffff
		pop esi
		pop ecx
		ret
	}
}

/* Replaces the worker assigned to a production slot.
 * Unlinks the old worker and assigns a new one while
 * maintaining production state. */

// FUNCTION: SERVER 0x10011540
// gv_ReplaceProductionWorker


int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);

__declspec(naked) int __cdecl gv_ReplaceProductionWorker(unsigned char* arg1)
{
	(void) arg1;
	__asm {
		push ecx
		push ebx
		push ebp
		push esi
		mov esi, dword ptr [esp + 0x14]
		push edi
		lea ecx, [esp + 0x18]
		mov eax, dword ptr [esi + 8]
		or ebx, 0xffffffff
		push eax
		push 0
		push 0
		push ecx
		mov ebp, 0xffff
		call gm_ResolveEntityById
		mov edx, dword ptr [esp + 0x28]
		add esp, 0x10
		test edx, edx
		je L_ret_neg1
		mov ax, word ptr [edx + 0x27]
		cmp ax, bp
		je L_ret_neg1
		and eax, ebp
		lea eax, [eax + eax*2]
		lea eax, [eax + eax*4]
		lea eax, [eax + eax*8]
		lea ecx, [eax*4 + 0x100358a0]
		_emit 0xa1
		_emit 0x6c
		_emit 0x54
		_emit 0x03
		_emit 0x10
		cmp ecx, eax
		je L_ret_neg1
		xor ecx, ecx
		_emit 0x8b
		_emit 0x3d
		_emit 0x30
		_emit 0x8c
		_emit 0x0a
		_emit 0x10
		mov cl, byte ptr [edx]
		add edi, ecx
		lea eax, [ecx + ecx*2]
		shl eax, 4
		add eax, ecx
		lea eax, [eax + eax*2]
		cmp byte ptr [edi + eax*4], 0x1d
		je L_action_ok
		pop edi
		pop esi
		pop ebp
		mov eax, 0xfffffffe
		pop ebx
		pop ecx
		ret
	L_action_ok:
		mov edi, dword ptr [edx + 0x65]
		test edi, edi
		jne L_have_slot
		pop edi
		pop esi
		pop ebp
		mov eax, 0xfffffffd
		pop ebx
		pop ecx
		ret
	L_have_slot:
		mov ecx, dword ptr [esi + 0xc]
		push ecx
		push edi
		call gv_CheckSlotActive
		add esp, 8
		test eax, eax
		jne L_slot_active
		pop edi
		pop esi
		pop ebp
		mov eax, 0xfffffffc
		pop ebx
		pop ecx
		ret
	L_slot_active:
		mov eax, dword ptr [esi + 4]
		cmp eax, -1
		je L_no_new_worker
		lea edx, [esp + 0x10]
		push eax
		push edx
		push 0
		push 0
		call gm_ResolveEntityById
		mov eax, dword ptr [esp + 0x20]
		add esp, 0x10
		test eax, eax
		jne L_worker_ok
		pop edi
		pop esi
		pop ebp
		mov eax, 0xfffffffa
		pop ebx
		pop ecx
		ret
	L_worker_ok:
		mov ebx, dword ptr [esi + 4]
		mov bp, word ptr [eax + 0x50]
	L_no_new_worker:
		mov al, byte ptr [esi + 0x10]
		mov ecx, dword ptr [esi + 0xc]
		push eax
		push ecx
		push edi
		call gv_GetSlotEntry
		add esp, 0xc
		test eax, eax
		jne L_have_entry
		pop edi
		pop esi
		pop ebp
		mov eax, 0xfffffff9
		pop ebx
		pop ecx
		ret
	L_have_entry:
		pop edi
		mov word ptr [eax + 8], bp
		pop esi
		mov dword ptr [eax + 4], ebx
		pop ebp
		xor eax, eax
		pop ebx
		pop ecx
		ret
	L_ret_neg1:
		pop edi
		pop esi
		pop ebp
		or eax, 0xffffffff
		pop ebx
		pop ecx
		ret
	}
}

/* Activates a graveyard section (tier/wing). Unlocks
 * additional production slots and enables new capabilities
 * for the graveyard building. */

// FUNCTION: SERVER 0x10011660
// ActivateGraveyardSection

// DATA: SERVER 0x1003546c

// DATA: SERVER 0x100a8c30
extern char* g_action_table_base;


int __cdecl ActivateGraveyardSection(unsigned char* cmd_payload)
{
	void* entity;
	void* target_entity;

	gm_ResolveEntityById((void**) &entity, (void**) 0, (void**) 0, *(int*) (cmd_payload + 8));
	if (entity != 0) {
		if (*(unsigned short*) ((char*) entity + 0x27) != 0xFFFF) {
			unsigned int slot_val;
			unsigned char type_byte;
			void* field;
			int action_type;

			slot_val = (unsigned int) *(unsigned short*) ((char*) entity + 0x27);
			if ((int) &g_slot_table[slot_val * 540] != g_entity_table_end) {
				type_byte = *(unsigned char*) entity;
				if (g_action_table_base[(int) type_byte * 589] != 0x1d) {
					return -2;
				}

				field = *(void**) ((char*) entity + 0x65);
				if (field == 0) {
					return -3;
				}

				gm_ResolveEntityById((void**) 0, (void**) 0, (void**) &target_entity, *(int*) (cmd_payload + 4));
				if (target_entity == 0) {
					return -6;
				}

				action_type = *(int*) (cmd_payload + 0xc);
				if (action_type == 3) {
					if (*(int*) ((char*) field + 0x14) == 0) {
						goto fail;
					}
					if (*(int*) ((char*) field + 4) < 3) {
						goto fail;
					}
					*(unsigned char*) ((char*) field + 0x1b) = 1;
					*(unsigned char*) ((char*) field + 0x1a) = 1;
					*(unsigned char*) ((char*) field + 0x19) = 1;
					return 0;
				}
				if (action_type == 2) {
					if (*(int*) ((char*) field + 0x10) == 0) {
						goto fail;
					}
					if (*(int*) ((char*) field + 4) < 2) {
						goto fail;
					}
					*(unsigned char*) ((char*) field + 0x1a) = 1;
					*(unsigned char*) ((char*) field + 0x19) = 1;
					return 0;
				}
				if (action_type == 1) {
					if (*(int*) ((char*) field + 0xc) == 0) {
						goto fail;
					}
					*(unsigned char*) ((char*) field + 0x19) = 1;
					return 0;
				}
				return -8;

			fail:
				return -7;
			}
		}
	}
	return -1;
}


/* Updates production progress for active slots. Decrements
 * timers, checks for completion, and triggers product output
 * when the production cycle finishes. */

// FUNCTION: SERVER 0x10011790
// gv_UpdateProductionProgress


int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);

__declspec(naked) int __cdecl gv_UpdateProductionProgress(unsigned char* arg1)
{
	(void) arg1;
	__asm {
		push esi
		push edi
		mov edi, dword ptr [esp + 0xc]
		lea ecx, [esp + 0xc]
		mov eax, dword ptr [edi + 8]
		push eax
		push 0
		push 0
		push ecx
		call gm_ResolveEntityById
		mov edx, dword ptr [esp + 0x1c]
		add esp, 0x10
		test edx, edx
		je near L_ret_neg1
		mov ax, word ptr [edx + 0x27]
		cmp ax, 0xffff
		je near L_ret_neg1
		and eax, 0xffff
		lea eax, [eax + eax*2]
		lea eax, [eax + eax*4]
		lea eax, [eax + eax*8]
		lea ecx, [eax*4 + 0x100358a0]
		_emit 0xa1
		_emit 0x6c
		_emit 0x54
		_emit 0x03
		_emit 0x10
		cmp ecx, eax
		je near L_ret_neg1
		xor ecx, ecx
		_emit 0x8b
		_emit 0x35
		_emit 0x30
		_emit 0x8c
		_emit 0x0a
		_emit 0x10
		mov cl, byte ptr [edx]
		add esi, ecx
		lea eax, [ecx + ecx*2]
		shl eax, 4
		add eax, ecx
		lea eax, [eax + eax*2]
		cmp byte ptr [esi + eax*4], 0x1d
		je L_action_ok
		pop edi
		mov eax, 0xfffffffe
		pop esi
		ret
	L_action_ok:
		mov esi, dword ptr [edx + 0x65]
		test esi, esi
		jne L_have_slot
		pop edi
		mov eax, 0xfffffffd
		pop esi
		ret
	L_have_slot:
		mov ecx, dword ptr [edi + 0xc]
		push ecx
		push esi
		call gv_CheckSlotActive
		add esp, 8
		test eax, eax
		jne L_slot_ok
		pop edi
		mov eax, 0xfffffffc
		pop esi
		ret
	L_slot_ok:
		mov dl, byte ptr [edi + 0x10]
		mov eax, dword ptr [edi + 0xc]
		push edx
		push eax
		push esi
		call gv_GetSlotEntry
		add esp, 0xc
		test eax, eax
		jne L_have_entry
		pop edi
		mov eax, 0xfffffff9
		pop esi
		ret
	L_have_entry:
		xor ecx, ecx
		mov cl, byte ptr [eax + 0xc]
		mov edx, ecx
		mov ecx, dword ptr [edi + 0x13]
		add ecx, edx
		xor edx, edx
		test ecx, ecx
		setle dl
		dec edx
		and ecx, edx
		cmp ecx, 0xff
		jl L_no_cap
		mov ecx, 0xff
	L_no_cap:
		mov byte ptr [eax + 0xc], cl
		pop edi
		xor eax, eax
		pop esi
		ret
	L_ret_neg1:
		pop edi
		or eax, 0xffffffff
		pop esi
		ret
	}
}

/* Validates that an entity action is permitted. Checks
 * entity state, slot availability, and production rules
 * before allowing the action to proceed. */

// FUNCTION: SERVER 0x10011890
// gv_ValidateEntityAction

int __cdecl gv_ValidateEntityAction(unsigned char* cmd_payload)
{
	void* entity;
	unsigned int slot_val;
	unsigned char type_byte;
	int result;

	gm_ResolveEntityById((void**) &entity, (void**) 0, (void**) 0, *(int*) (cmd_payload + 8));
	if (entity != 0) {
		if (*(unsigned short*) ((char*) entity + 0x27) != 0xFFFF) {
			slot_val = (unsigned int) *(unsigned short*) ((char*) entity + 0x27);
			if ((int) &g_slot_table[slot_val * 540] != g_entity_table_end) {
				type_byte = *(unsigned char*) entity;
				if (g_action_table_base[(int) type_byte * 589] != 0x1d) {
					return -2;
				}
				if (*(int*) ((char*) entity + 0x65) == 0) {
					return -3;
				}
				result = SpawnGraveyardEntities(entity, *(int*) (cmd_payload + 0x13));
				if (result > 0) {
					return 0;
				}
				return -4;
			}
		}
	}
	return -1;
}

/* Moves a slot entry within a building's production table.
 * Relocates a product or worker from one slot position to
 * another, updating internal links. */

// FUNCTION: SERVER 0x10011940
// gv_MoveSlotEntry

__declspec(naked) unsigned int gv_MoveSlotEntry(int arg1)
{
	(void) arg1;
	__asm {
		sub esp, 0x14
		lea ecx, [esp + 0x18]
		push ebx
		push ebp
		mov ebp, dword ptr [esp + 0x20]
		push esi
		mov eax, dword ptr [ebp]
		push eax
		push ecx
		push 0
		push 0
		call gm_ResolveEntityById
		mov eax, dword ptr [esp + 0x34]
		add esp, 0x10
		test eax, eax
		jne L_have_p1
		pop esi
		pop ebp
		mov eax, 0xfffffffa
		pop ebx
		add esp, 0x14
		ret
	L_have_p1:
		mov edx, dword ptr [ebp + 4]
		lea eax, [esp + 0xc]
		push edx
		push 0
		push 0
		push eax
		call gm_ResolveEntityById
		mov edx, dword ptr [esp + 0x1c]
		add esp, 0x10
		test edx, edx
		je near L_neg1
		mov ax, word ptr [edx + 0x27]
		cmp ax, 0xffff
		je near L_neg1
		and eax, 0xffff
		lea eax, [eax + eax*2]
		lea eax, [eax + eax*4]
		lea ecx, [eax + eax*8]
		lea eax, [ecx*4 + 0x100358a0]
		_emit 0x8b
		_emit 0x0d
		_emit 0x6c
		_emit 0x54
		_emit 0x03
		_emit 0x10
		cmp eax, ecx
		je near L_neg1
		xor ecx, ecx
		_emit 0x8b
		_emit 0x35
		_emit 0x30
		_emit 0x8c
		_emit 0x0a
		_emit 0x10
		mov cl, byte ptr [edx]
		add esi, ecx
		lea eax, [ecx + ecx*2]
		shl eax, 4
		add eax, ecx
		lea eax, [eax + eax*2]
		cmp byte ptr [esi + eax*4], 0x1d
		je L_chk_field65
		pop esi
		pop ebp
		mov eax, 0xfffffffe
		pop ebx
		add esp, 0x14
		ret
	L_chk_field65:
		mov esi, dword ptr [edx + 0x65]
		test esi, esi
		jne L_call_active
		pop esi
		pop ebp
		mov eax, 0xfffffffd
		pop ebx
		add esp, 0x14
		ret
	L_call_active:
		mov ecx, dword ptr [ebp + 8]
		push ecx
		push esi
		call gv_CheckSlotActive
		add esp, 8
		test eax, eax
		jne L_call_get_slot
		pop esi
		pop ebp
		mov eax, 0xfffffffc
		pop ebx
		add esp, 0x14
		ret
	L_call_get_slot:
		mov dl, byte ptr [ebp + 0xc]
		mov eax, dword ptr [ebp + 8]
		push edx
		push eax
		push esi
		call gv_GetSlotEntry
		mov esi, eax
		add esp, 0xc
		test esi, esi
		mov dword ptr [esp + 0x18], esi
		je L_neg9
		mov eax, dword ptr [esp + 0x24]
		mov cx, word ptr [esi + 8]
		cmp cx, word ptr [eax + 0x50]
		jne L_neg9
		mov edx, dword ptr [ebp + 8]
		mov ebx, dword ptr [esi + 0x10]
		mov ecx, dword ptr [edx*4 + 0x1002574c]
		mov edx, dword ptr [ebp + 0xd]
		mov dword ptr [esp + 0x10], ecx
		mov ecx, dword ptr [esp + 0xc]
		push edx
		push 0x10010700
		push 0
		push ecx
		push eax
		call gv_FindSlotEntryFiltered
		add esp, 0x14
		mov dword ptr [esp + 0x1c], eax
		test eax, eax
		jne L_have_dst
	L_neg9:
		pop esi
		pop ebp
		mov eax, 0xfffffff9
		pop ebx
		add esp, 0x14
		ret
	L_have_dst:
		mov ecx, dword ptr [ebp + 0xd]
		mov edx, dword ptr [eax + 0x10]
		push edi
		mov ecx, dword ptr [ecx*4 + 0x1002574c]
		mov edi, ecx
		shl edi, 4
		add edi, ecx
		lea ecx, [edx + edi*4]
		mov dword ptr [esp + 0x18], ecx
		mov ecx, dword ptr [esp + 0x14]
		mov edi, ecx
		shl edi, 4
		add edi, ecx
		lea ecx, [ebx + edi*4]
		mov edi, dword ptr [esp + 0x18]
		cmp edx, edi
		mov dword ptr [esp + 0x14], ecx
		jae near L_after_search
	L_outer_search:
		cmp dword ptr [edx], -1
		jne L_advance_edx
		cmp ebx, ecx
		jae near L_after_search
	L_inner_scan:
		cmp dword ptr [ebx], -1
		jne L_do_move
		add ebx, 0x44
		cmp ebx, ecx
		jae near L_after_search
		jmp L_inner_scan
	L_do_move:
		mov ecx, 0x11
		mov esi, ebx
		mov edi, edx
		xor eax, eax
		rep movsd
		mov esi, dword ptr [esp + 0x1c]
		mov ecx, 0x11
		mov edi, ebx
		rep stosd
		mov eax, dword ptr [esp + 0x14]
		mov dword ptr [ebx], -1
		cmp ebx, eax
		mov eax, dword ptr [esp + 0x20]
		jae L_after_search
		mov ecx, dword ptr [esp + 0x14]
	L_advance_edx:
		mov edi, dword ptr [esp + 0x18]
		add edx, 0x44
		cmp edx, edi
		jb L_outer_search
	L_after_search:
		mov edx, dword ptr [esi + 4]
		pop edi
		mov dword ptr [eax + 4], edx
		mov cx, word ptr [esi + 8]
		mov dword ptr [esi + 4], -1
		mov word ptr [eax + 8], cx
		mov word ptr [esi + 8], 0xffff
		_emit 0x8b
		_emit 0x15
		_emit 0x80
		_emit 0x58
		_emit 0x03
		_emit 0x10
		add edx, 0xa
		mov ecx, 0xff
		mov word ptr [eax + 0xa], dx
		mov byte ptr [eax + 0xc], cl
		mov word ptr [esi + 0xa], cx
		_emit 0xa1
		_emit 0x6c
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		mov dword ptr [ebp + 0x15], eax
		mov eax, dword ptr [ebp + 0x11]
		test eax, eax
		jle L_skip_obj
		xor ecx, ecx
		push eax
		_emit 0x8a
		_emit 0x0d
		_emit 0x39
		_emit 0x54
		_emit 0x03
		_emit 0x10
		xor edx, edx
		mov eax, ecx
		shl eax, 6
		sub eax, ecx
		lea ecx, [eax + eax*2]
		mov eax, dword ptr [esp + 0x28]
		mov dx, word ptr [ecx*4 + 0x100a8c94]
		mov ecx, dword ptr [eax + 4]
		push edx
		push ecx
		call gm_SubObjektNoKill
		fild dword ptr [ebp + 0x11]
		mov edx, dword ptr [ebp + 0xd]
		fmul dword ptr [edx*4 + 0x1002572c]
		call __ftol
		xor ecx, ecx
		push eax
		_emit 0x8a
		_emit 0x0d
		_emit 0x39
		_emit 0x54
		_emit 0x03
		_emit 0x10
		mov edx, dword ptr [esp + 0x1c]
		mov eax, ecx
		shl eax, 6
		sub eax, ecx
		xor ecx, ecx
		lea eax, [eax + eax*2]
		mov cx, word ptr [eax*4 + 0x100a8c94]
		xor eax, eax
		mov ax, word ptr [edx + 0x27]
		push ecx
		lea eax, [eax + eax*2]
		lea eax, [eax + eax*4]
		lea eax, [eax + eax*8]
		mov ecx, dword ptr [eax*4 + 0x100358a4]
		push ecx
		call gm_AddOrAccumulateObject
		add esp, 0x18
	L_skip_obj:
		pop esi
		pop ebp
		xor eax, eax
		pop ebx
		add esp, 0x14
		ret
	L_neg1:
		pop esi
		pop ebp
		or eax, 0xffffffff
		pop ebx
		add esp, 0x14
		ret
	}
}

unsigned int gv_MoveSlotEntry_unused(int arg1)
{
	int* src_worker_array_ptr;
	int cmd_ptr_saved;
	int field_or_slot_ptr;
	unsigned char* building_entity_ptr;
	int src_worker_array_end;
	int dst_slot_entry_ptr;

	cmd_ptr_saved = arg1;
	gm_ResolveEntityById((void**) 0, (void**) 0, (void**) &arg1, *(int*) cmd_ptr_saved);
	if (arg1 == 0) {
		return 0xfffffffa;
	}
	gm_ResolveEntityById((void**) &building_entity_ptr, (void**) 0, (void**) 0, *(int*) (cmd_ptr_saved + 4));
	if (((building_entity_ptr == 0) || (*(unsigned short*) (building_entity_ptr + 0x27) == 0xffff)) ||
		(*(unsigned short*) (building_entity_ptr + 0x27) * 0x21c + *(unsigned int*) 0x100358a0 ==
		 *(unsigned int*) 0x1003546c)) {
		return 0xffffffff;
	}
	if (*(*(char**) 0x100a8c30 + *building_entity_ptr * 0x24d) != '\x1d') {
		return 0xfffffffe;
	}
	field_or_slot_ptr = *(int*) (building_entity_ptr + 0x65);
	if (field_or_slot_ptr == 0) {
		return 0xfffffffd;
	}
	field_or_slot_ptr = gv_CheckSlotActive((char*) field_or_slot_ptr, *(int*) (cmd_ptr_saved + 8));
	if (field_or_slot_ptr == 0) {
		return 0xfffffffc;
	}
	field_or_slot_ptr = gv_GetSlotEntry(
		*(int*) (building_entity_ptr + 0x65),
		*(int*) (cmd_ptr_saved + 8),
		(unsigned char) *(unsigned char*) (cmd_ptr_saved + 0xc)
	);
	if ((field_or_slot_ptr != 0) &&
		(*(unsigned short*) (field_or_slot_ptr + 8) == *(unsigned short*) (arg1 + 0x50))) {
		int saved_src_slot_entry_ptr;

		src_worker_array_ptr = *(int**) (field_or_slot_ptr + 0x10);
		src_worker_array_end = *(int*) (*(int*) (cmd_ptr_saved + 8) * 4 + 0x1002574c);
		saved_src_slot_entry_ptr = field_or_slot_ptr;
		dst_slot_entry_ptr = (int) gv_FindSlotEntryFiltered(
			(char*) arg1,
			(unsigned char*) building_entity_ptr,
			(char*) 0,
			(int(__cdecl*)(char*, char*)) 0x10010700,
			*(int*) (cmd_ptr_saved + 0xd)
		);
		if (dst_slot_entry_ptr != 0) {
			int* dst_worker_ptr;
			int* clear_ptr;
			int* dst_worker_end;
			int word_copy_count;
			dst_worker_ptr = *(int**) (dst_slot_entry_ptr + 0x10);
			dst_worker_end = dst_worker_ptr + *(int*) (*(int*) (cmd_ptr_saved + 0xd) * 4 + 0x1002574c) * 0x11;
			src_worker_array_end = (int) (src_worker_array_ptr + src_worker_array_end * 0x11);
			for (; dst_worker_ptr < dst_worker_end; dst_worker_ptr = dst_worker_ptr + 0x11) {
				if (*dst_worker_ptr == -1) {
					while (1) {
						if ((int*) src_worker_array_end <= src_worker_array_ptr) {
							goto code_r0x10011b0d;
						}
						if (*src_worker_array_ptr != -1) {
							break;
						}
						src_worker_array_ptr = src_worker_array_ptr + 0x11;
					}
					{
						int* pSrc = src_worker_array_ptr;
						int* pDst = dst_worker_ptr;
						for (word_copy_count = 0x11; word_copy_count != 0; word_copy_count = word_copy_count + -1) {
							*pDst = *pSrc;
							pSrc = pSrc + 1;
							pDst = pDst + 1;
						}
					}
					clear_ptr = src_worker_array_ptr;
					for (word_copy_count = 0x11; word_copy_count != 0; word_copy_count = word_copy_count + -1) {
						*clear_ptr = 0;
						clear_ptr = clear_ptr + 1;
					}
					*src_worker_array_ptr = -1;
					field_or_slot_ptr = saved_src_slot_entry_ptr;
					if ((int*) src_worker_array_end <= src_worker_array_ptr) {
						break;
					}
				}
			}
		code_r0x10011b0d:
			*(int*) (dst_slot_entry_ptr + 4) = *(int*) (field_or_slot_ptr + 4);
			*(int*) (field_or_slot_ptr + 4) = 0xffffffff;
			*(unsigned short*) (dst_slot_entry_ptr + 8) = *(unsigned short*) (field_or_slot_ptr + 8);
			*(unsigned short*) (field_or_slot_ptr + 8) = 0xffff;
			*(unsigned short*) (dst_slot_entry_ptr + 0xa) = (unsigned short) (*(unsigned short*) 0x10035880 + 0xa);
			*(unsigned char*) (dst_slot_entry_ptr + 0xc) = 0xff;
			*(unsigned short*) (field_or_slot_ptr + 0xa) = 0xff;
			*(int*) (cmd_ptr_saved + 0x15) = *(int*) 0x10030b6c;
			if (0 < *(int*) (cmd_ptr_saved + 0x11)) {
				unsigned int scaled_amount;
				gm_SubObjektNoKill(
					*(unsigned int*) (arg1 + 4),
					*(unsigned int*) ((unsigned char*) 0x100a8c94 + *(unsigned int*) 0x10035439 * 0x2f4),
					*(unsigned int*) (cmd_ptr_saved + 0x11)
				);
				scaled_amount = (unsigned int) ((int) *(int*) (cmd_ptr_saved + 0x11) *
												((float*) 0x1002572c)[*(int*) (cmd_ptr_saved + 0xd)]);
				gm_AddOrAccumulateObject(
					*(unsigned int*) ((unsigned char*) 0x100358a4 +
									  *(unsigned short*) (building_entity_ptr + 0x27) * 0x21c),
					*(unsigned int*) ((unsigned char*) 0x100a8c94 + *(unsigned int*) 0x10035439 * 0x2f4),
					scaled_amount
				);
			}
			return 0;
		}
	}
	return 0xfffffff9;
}

/* Allocates a graveyard worker entity. Creates the worker,
 * assigns to a building, and initializes work schedule. */
