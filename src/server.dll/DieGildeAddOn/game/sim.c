#include "../../Units/Error/error.h"
extern unsigned short gm_RandomMod(unsigned int);
unsigned int __cdecl gm_CreateEntityFromParents(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8);
void __cdecl table_lookup(unsigned int a, unsigned short* b);
extern int g_entity_type_table;
unsigned int __cdecl FindAndMatchParents(unsigned int param);
extern unsigned char g_entity_type_bytes;
extern unsigned char g_stat_b_array;
extern unsigned char g_slot_table;
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);

/* Searches for matching parent entities by type and creates
 * family tree linkages. Used in citizen creation to find
 * compatible parents for stat inheritance. */

// FUNCTION: SERVER 0x100151e0
// FindAndMatchParents

__declspec(naked) unsigned int FindAndMatchParents(unsigned int arg1)
{
	(void) arg1;
	__asm {
		sub esp, 0x20
		push ebx
		push ebp
		push esi
		push edi
		xor edi, edi
		mov dword ptr [esp + 0x18], 0x60
		mov dword ptr [esp + 0x1c], 0x4b
		mov dword ptr [esp + 0x20], 0x28
		mov dword ptr [esp + 0x24], 0x17
		mov dword ptr [esp + 0x28], 9
		mov dword ptr [esp + 0x2c], edi
		mov ebx, 0x300
	L_loop1:
		push ebx
		call gm_RandomMod
		mov ebp, eax
		and eax, 0xffff
		add esp, 4
		lea eax, [eax + eax*2]
		lea eax, [eax + eax*4]
		lea ecx, [eax + eax*8]
		shl ecx, 2
		_emit 0x66
		_emit 0x81
		_emit 0xb9
		_emit 0xa0
		_emit 0x58
		_emit 0x03
		_emit 0x10
		_emit 0xff
		_emit 0xff
		jne L_l1_check_state
		lea eax, [ebx + ebx*2]
		cdq
		and edx, 3
		add eax, edx
		sar eax, 2
		mov ebx, eax
		jmp L_l1_continue
	L_l1_check_state:
		cmp byte ptr [ecx + 0x100358a2], 6
		jae L_l1_fail
		xor eax, eax
		mov ax, word ptr [ecx + 0x100358aa]
		mov dword ptr [esp + 0x10], eax
		fild dword ptr [esp + 0x10]
		fcomp dword ptr [ecx + 0x100358c0]
		fnstsw ax
		test ah, 1
		jne L_l1_fail
		mov al, byte ptr [ecx + 0x100358a8]
		test al, al
		je L_l1_fail
		lea eax, [ecx + 0x10035908]
		xor esi, esi
		mov ecx, 5
	L_l1_count:
		cmp dword ptr [eax], -1
		je L_l1_count_skip
		inc esi
	L_l1_count_skip:
		add eax, 4
		dec ecx
		jne L_l1_count
		push 0x100
		call gm_RandomMod
		mov ecx, dword ptr [esp + esi*4 + 0x1c]
		and eax, 0xffff
		add esp, 4
		inc eax
		cmp eax, ecx
		jl L_l1_done
		jmp L_l1_continue
	L_l1_fail:
		mov ebp, 0xffff
	L_l1_continue:
		inc edi
		cmp edi, 0x10
		jl L_loop1
	L_l1_done:
		_emit 0x66
		_emit 0x81
		_emit 0xfd
		_emit 0xff
		_emit 0xff
		jne L_loop2_init
		pop edi
		pop esi
		pop ebp
		xor ax, ax
		pop ebx
		add esp, 0x20
		ret
	L_loop2_init:
		mov dword ptr [esp + 0x10], 0
	L_loop2:
		push ebx
		call gm_RandomMod
		mov esi, eax
		and eax, 0xffff
		add esp, 4
		lea eax, [eax + eax*2]
		lea eax, [eax + eax*4]
		lea ecx, [eax + eax*8]
		shl ecx, 2
		_emit 0x66
		_emit 0x81
		_emit 0xb9
		_emit 0xa0
		_emit 0x58
		_emit 0x03
		_emit 0x10
		_emit 0xff
		_emit 0xff
		jne L_l2_check_state
		lea eax, [ebx + ebx*2]
		cdq
		and edx, 3
		add eax, edx
		sar eax, 2
		mov ebx, eax
		jmp L_l2_continue
	L_l2_check_state:
		cmp byte ptr [ecx + 0x100358a2], 6
		jae L_l2_fail
		xor edx, edx
		mov dx, word ptr [ecx + 0x100358aa]
		mov dword ptr [esp + 0x14], edx
		fild dword ptr [esp + 0x14]
		fcomp dword ptr [ecx + 0x100358c0]
		fnstsw ax
		test ah, 1
		jne L_l2_fail
		mov al, byte ptr [ecx + 0x100358a8]
		test al, al
		je L_l2_fail
		lea eax, [ecx + 0x10035908]
		xor edi, edi
		mov ecx, 5
	L_l2_count:
		cmp dword ptr [eax], -1
		je L_l2_count_skip
		inc edi
	L_l2_count_skip:
		add eax, 4
		dec ecx
		jne L_l2_count
		push 0x100
		call gm_RandomMod
		mov ecx, dword ptr [esp + edi*4 + 0x1c]
		and eax, 0xffff
		add esp, 4
		inc eax
		cmp eax, ecx
		jl L_l2_done
		jmp L_l2_continue
	L_l2_fail:
		mov esi, 0xffff
	L_l2_continue:
		mov eax, dword ptr [esp + 0x10]
		inc eax
		cmp eax, 0x10
		mov dword ptr [esp + 0x10], eax
		jl L_loop2
	L_l2_done:
		_emit 0x66
		_emit 0x81
		_emit 0xfe
		_emit 0xff
		_emit 0xff
		jne L_have_parents
		pop edi
		pop esi
		pop ebp
		xor ax, ax
		pop ebx
		add esp, 0x20
		ret
	L_have_parents:
		mov eax, dword ptr [esp + 0x34]
		push 2
		push 0
		push 0
		and esi, 0xffff
		push 0
		push eax
		and ebp, 0xffff
		lea eax, [esi + esi*2]
		lea eax, [eax + eax*4]
		lea ecx, [eax + eax*8]
		mov eax, ebp
		mov edx, dword ptr [ecx*4 + 0x100358a4]
		lea eax, [eax + eax*2]
		push edx
		lea eax, [eax + eax*4]
		lea eax, [eax + eax*8]
		mov ecx, dword ptr [eax*4 + 0x100358a4]
		push ecx
		push 0
		call gm_CreateEntityFromParents
		add esp, 0x20
		pop edi
		pop esi
		pop ebp
		pop ebx
		add esp, 0x20
		ret
	}
}


/* Updates entity priority/scheduling. Called during simulation
 * tick to adjust entity processing order based on game state. */

// FUNCTION: SERVER 0x10015400
// sim_PriorityUpdate

__declspec(naked) void __cdecl sim_PriorityUpdate(char* ctx, char* entity)
{
	(void) ctx;
	(void) entity;
	__asm {
		sub esp, 8
		xor ecx, ecx
		_emit 0x8d
		_emit 0x44
		_emit 0x24
		_emit 0x00
		push esi
		mov esi, dword ptr [esp + 0x14]
		push eax
		mov cl, byte ptr [esi]
		push ecx
		call table_lookup
		movzx dx, byte ptr [esi + 0x65]
		add esp, 8
		cmp dx, word ptr [esp + 4]
		jae L_done
		mov edx, dword ptr [esp + 0x10]
		mov ecx, dword ptr [edx + 0x170]
		test ecx, ecx
		je L_setnew
		mov al, byte ptr [ecx + 0x65]
		test al, al
		jbe L_setnew
		dec al
		mov byte ptr [ecx + 0x65], al
	L_setnew:
		mov dword ptr [edx + 0x170], esi
		mov al, byte ptr [esi + 0x65]
		inc al
		mov byte ptr [esi + 0x65], al
	L_done:
		pop esi
		add esp, 8
		ret
	}
}

/* Starts an entity query filtered by type byte from arg1.
 * Dispatches entity iteration across buildings, citizens, or
 * other entity categories based on the type selector. */

// FUNCTION: SERVER 0x10015460
// sim_StartEntityQueryByType

__declspec(naked) void __cdecl sim_StartEntityQueryByType(unsigned char* arg1)
{
	(void) arg1;
	__asm {
		push esi
		mov esi, dword ptr [esp + 8]
		xor edx, edx
		push edi
		mov dl, byte ptr [esi]
		mov edi, dword ptr [g_entity_type_table]
		add edi, edx
		xor eax, eax
		lea ecx, [edx + edx*2]
		shl ecx, 4
		add ecx, edx
		lea ecx, [ecx + ecx*2]
		lea ecx, [edi + ecx*4]
		mov cl, byte ptr [ecx]
		cmp cl, 1
		jne L_chk2
		mov edx, dword ptr [esi + 0x5d]
		push 0x12
		push eax
		push 1
		push edx
		call gm_StartEntityQuery
		add esp, 0x10
		pop edi
		pop esi
		ret
	L_chk2:
		cmp cl, 2
		jne L_chk1d
		mov eax, dword ptr [esi + 0x5d]
		push 0x13
		push 0
		push 1
		push eax
		call gm_StartEntityQuery
		add esp, 0x10
		pop edi
		pop esi
		ret
	L_chk1d:
		cmp cl, 0x1d
		jne L_chk16
		mov ecx, dword ptr [esi + 0x5d]
		push 0xfd
		push 0
		push 1
		push ecx
		call gm_StartEntityQuery
		add esp, 0x10
		pop edi
		pop esi
		ret
	L_chk16:
		cmp cl, 0x16
		jne L_ret
		mov edx, dword ptr [esi + 0x5d]
		push 0x120
		push 0
		push 1
		push edx
		call gm_StartEntityQuery
		add esp, 0x10
	L_ret:
		pop edi
		pop esi
		ret
	}
}

/* Creates a new citizen entity with initial stats generated
 * from parent entities. Allocates entity memory, assigns random
 * stats via gm_CreateEntityFromParents, and links to home. */

// FUNCTION: SERVER 0x10015500
// sim_CreateCitizen

void* __cdecl sim_CreateCitizen(unsigned char flags, int citizen_type, int parent_id, unsigned char stat_a, unsigned char stat_b)
{
	unsigned int new_entity_slot;

	if ((flags & 1) != 0) {
		new_entity_slot = FindAndMatchParents(parent_id) & 0xffff;
		if (new_entity_slot == 0xffff) {
			goto error;
		}
		if ((flags & 2) != 0) {
			(&g_stat_b_array)[new_entity_slot * 0x21c] = stat_b;
			(&g_entity_type_bytes)[new_entity_slot * 0x21c] = stat_a;
		}
	}
	else {
		new_entity_slot =
			gm_CreateEntityFromParents(citizen_type, -1, -1, parent_id, 0, (unsigned int) stat_a, (unsigned int) stat_b, 2) &
			0xffff;
	}
	if (new_entity_slot == 0xffff) {
		goto error;
	}
	return &g_slot_table + new_entity_slot * 0x21c;
error:
	LogMessageInternal(
		"D:\\Develop\\DieGildeAddOn\\game\\sim.c",
		0x127d,
		"sim_CreateCitizen(): could not alloc spieler",
		1
	);
	return (void*) 0;
}

/* Advances the game clock by one tick. Updates day/hour/minute
 * counters, triggers periodic events (taxes, production cycles),
 * and notifies connected clients of time changes. */

// FUNCTION: SERVER 0x100155c0
// AdvanceGameClock

#pragma pack(push, 1)
// SIZE 0xe
typedef struct {
	int days;    /* 0x00 */
	short hours; /* 0x04 */
	int minutes; /* 0x06 */
	int seconds; /* 0x0a */
} TimeStruct;
#pragma pack(pop)

__declspec(naked) int __cdecl AdvanceGameClock(int* arg1, int arg2, int arg3, int arg4)
{
	(void) arg1;
	(void) arg2;
	(void) arg3;
	(void) arg4;
	__asm {
		mov ecx, dword ptr [esp + 4]
		mov edx, dword ptr [esp + 0x10]
		push esi
		mov eax, dword ptr [ecx + 0xa]
		lea esi, [edx + eax]
		mov eax, 0x88888889
		imul esi
		add edx, esi
		sar edx, 5
		mov eax, edx
		shr eax, 0x1f
		add edx, eax
		mov eax, dword ptr [ecx + 6]
		add eax, edx
		mov dword ptr [ecx + 6], eax
		mov eax, esi
		cdq
		mov esi, 0x3c
		idiv esi
		mov eax, dword ptr [esp + 0x10]
		mov dword ptr [ecx + 0xa], edx
		mov edx, dword ptr [ecx + 6]
		lea esi, [edx + eax]
		mov eax, 0x88888889
		imul esi
		add edx, esi
		sar edx, 5
		mov eax, edx
		shr eax, 0x1f
		add edx, eax
		mov eax, esi
		add word ptr [ecx + 4], dx
		mov esi, 0x3c
		cdq
		idiv esi
		xor esi, esi
		mov si, word ptr [ecx + 4]
		mov dword ptr [ecx + 6], edx
		mov edx, dword ptr [esp + 0xc]
		add esi, edx
		cmp esi, 0x18
		jl L_check_neg
		mov eax, 0xaaaaaaab
		mul esi
		shr edx, 4
		lea eax, [edx*4]
		sub eax, edx
		neg eax
		lea esi, [esi + eax*8]
	L_inc_loop:
		mov eax, dword ptr [ecx]
		inc eax
		dec edx
		mov dword ptr [ecx], eax
		jne L_inc_loop
	L_check_neg:
		test esi, esi
		jge L_store_pos
		mov edx, 0x17
		mov eax, 0xaaaaaaab
		sub edx, esi
		mul edx
		shr edx, 4
		lea eax, [edx + edx*2]
		lea eax, [esi + eax*8]
	L_dec_loop:
		mov esi, dword ptr [ecx]
		dec esi
		dec edx
		mov dword ptr [ecx], esi
		jne L_dec_loop
		mov word ptr [ecx + 4], ax
		pop esi
		ret
	L_store_pos:
		mov word ptr [ecx + 4], si
		pop esi
		ret
	}
}

/* Sets synchronization parameters for the simulation.
 * Configures tick rate, player count, and timing values
 * used for network-synchronized game state. */

// FUNCTION: SERVER 0x10015690
// sim_SetSyncParams

void __cdecl sim_SetSyncParams(int arg1, unsigned char arg2, unsigned int arg3, unsigned int arg4)
{
	*(unsigned int*) (arg1 + 10) = arg4 & 0xff;
	*(unsigned short*) (arg1 + 4) = (unsigned short) arg2;
	*(unsigned int*) (arg1 + 6) = arg3 & 0xff;
}
