#include <string.h>

#pragma intrinsic(memset, strcpy)

extern int __cdecl check_slot_active(int, int);
extern char* DAT_100a8c30;
extern int g_slot_count_cat0[]; /* 0x1002577c */;
extern int g_slot_count_cat1[]; /* 0x1002578c */;
extern int g_slot_count_cat2[]; /* 0x1002579c */;
extern int g_slot_count_cat3[]; /* 0x100257ac */;
extern int __cdecl GetBuildingStatCount(unsigned char*);
extern char* __cdecl FindSlotEntryFiltered(char*, unsigned char*, char*, int(__cdecl*)(char*, char*), int);
extern unsigned int random_mod(int);
extern unsigned int __ftol(void);
extern void* __cdecl AllocateTrackedHeapBlock(unsigned int, const char*);
extern void __cdecl FreeTrackedHeapBlock(void*);
extern int g_entity_type_table;
extern int g_1002575c[];
extern int g_1002576c[];
extern char g_1002d444;
extern char g_1002d45c;
extern char g_1002d474;
extern int AllocGraveyardField(unsigned char*);
extern void free_3fields(int);
extern void __cdecl game_free(void*);
extern int __cdecl ResolveEntityById(int* out_slot, int* out_person, int* out_building, int entity_id);
extern int __cdecl GetSlotEntry(int, int, unsigned char);
extern void SubtractObjectAmountNoKill(unsigned int, unsigned int, unsigned int);
extern void AddOrAccumulateObject(unsigned int, unsigned int, unsigned int);
extern int DAT_1003546c;
extern short DAT_100358a0;
extern int __cdecl SpawnGraveyardEntities(void* entity, int action_id);
extern int g_entity_table_end;
extern char* g_action_table_base;
extern char g_slot_table[];
extern void __cdecl LogMessageInternal(char*, unsigned int, char*, int);
extern int __cdecl crt_rand_range(int);
extern double __cdecl RandomFloat01(void);
extern int DAT_10030b6c;
extern int DAT_10035434;
extern unsigned char DAT_10035439;
extern float DAT_10025680;
extern float DAT_100257c4;
extern float DAT_100257c8;

;
;
;
;

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 352
// SYMBOL: _check_slot_active
// FUNCTION: SERVER 0x10010530
// check_slot_active
// PROTOTYPE: int __cdecl check_slot_active(char * obj, int idx)
int __cdecl check_slot_active(char* obj, int idx)
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

// ORIGIN: GAME
// STATUS: MATCHING
// BLOCKER: comparison direction swap, instruction folding (lea vs mov), jump condition swap
// SIZE: 329
// SYMBOL: _GetSlotEntry
// BLOCKER_DELTA: 254
// FUNCTION: SERVER 0x100105b0
// GetSlotEntry
// PROTOTYPE: int __cdecl GetSlotEntry(int param_1, int param_2, uchar param_3)

int __cdecl GetSlotEntry(int param_1, int param_2, unsigned char param_3)
{
	int graveyard_tier;
	int base;

	if (*(int*) (param_1 + 4) < 1) {
		goto ret_zero;
	}
	if (*(int*) (param_1 + 4) > 3) {
		goto ret_zero;
	}

	if (param_2 == 0) {
		if (check_slot_active(param_1, 0) == 0) {
			goto ret_zero;
		}
		graveyard_tier = *(int*) (param_1 + 4);
		if (graveyard_tier == 1 && param_3 >= 8) {
			goto ret_zero;
		}
		if (graveyard_tier == 2 && param_3 >= 0xc) {
			goto ret_zero;
		}
		if (graveyard_tier == 3 && param_3 >= 0x10) {
			goto ret_zero;
		}
		base = *(int*) (param_1 + 8);
		goto ret_value;
	}
	if (param_2 == 1) {
		if (check_slot_active(param_1, 1) == 0) {
			goto ret_zero;
		}
		graveyard_tier = *(int*) (param_1 + 4);
		if (graveyard_tier == 1 && param_3 >= 4) {
			goto ret_zero;
		}
		if (graveyard_tier == 2 && param_3 >= 6) {
			goto ret_zero;
		}
		if (graveyard_tier == 3 && param_3 >= 8) {
			goto ret_zero;
		}
		base = *(int*) (param_1 + 0xc);
		goto ret_value;
	}
	if (param_2 == 2) {
		if (check_slot_active(param_1, 2) == 0) {
			goto ret_zero;
		}
		graveyard_tier = *(int*) (param_1 + 4);
		if (graveyard_tier == 1) {
			goto ret_zero;
		}
		if (graveyard_tier == 2 && param_3 >= 2) {
			goto ret_zero;
		}
		if (graveyard_tier == 3 && param_3 >= 4) {
			goto ret_zero;
		}
		base = *(int*) (param_1 + 0x10);
		goto ret_value;
	}
	if (param_2 == 3) {
		if (check_slot_active(param_1, 3) == 0) {
			goto ret_zero;
		}
		graveyard_tier = *(int*) (param_1 + 4);
		if (graveyard_tier == 1) {
			goto ret_zero;
		}
		if (graveyard_tier == 2) {
			goto ret_zero;
		}
		if (graveyard_tier == 3 && param_3 >= 2) {
			goto ret_zero;
		}
		base = *(int*) (param_1 + 0x14);
		goto ret_value;
	}

ret_zero:
	return 0;

ret_value:
	return base + (unsigned int) param_3 * 0x14;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, jump condition swap
// SIZE: 320
// SYMBOL: _FindSlotEntryFiltered
// BLOCKER_DELTA: 109
// FUNCTION: SERVER 0x10010710
// FindSlotEntryFiltered
// PROTOTYPE: char * __cdecl FindSlotEntryFiltered(char * ctx, uchar * obj, char * start, void * callback, int category)

char* __cdecl FindSlotEntryFiltered(
	char* ctx,
	unsigned char* obj,
	char* start,
	int(__cdecl* callback)(char*, char*),
	int category
)
{
	unsigned int type_idx;
	char* sub_obj;
	char* entry;
	int count;
	char* base;
	char* end;

	type_idx = (unsigned int) *obj;
	entry = DAT_100a8c30 + type_idx * 0x24d;
	sub_obj = *(char**) (obj + 0x65);

	if (category != 0xFF) {
		if (!check_slot_active(sub_obj, category)) {
			return 0;
		}
	}

	if (category == 0) {
		count = g_slot_count_cat0[(unsigned char) entry[0x247]];
		end = *(char**) (sub_obj + 8) + count * 0x14;
	}
	else if (category == 1) {
		count = g_slot_count_cat1[(unsigned char) entry[0x247]];
		end = *(char**) (sub_obj + 0xc) + count * 0x14;
	}
	else if (category == 2) {
		count = g_slot_count_cat2[(unsigned char) entry[0x247]];
		end = *(char**) (sub_obj + 0x10) + count * 0x14;
	}
	else if (category == 3) {
		count = g_slot_count_cat3[(unsigned char) entry[0x247]];
		end = *(char**) (sub_obj + 0x14) + count * 0x14;
	}
	else if (category == 0xFF) {
		count = GetBuildingStatCount(obj);
		end = *(char**) (sub_obj + 0x1c) + count * 0x14;
	}
	else {
		return 0;
	}

	if (start == 0) {
		if (category == 0) {
			base = *(char**) (sub_obj + 8);
		}
		else if (category == 1) {
			base = *(char**) (sub_obj + 0xc);
		}
		else if (category == 2) {
			base = *(char**) (sub_obj + 0x10);
		}
		else if (category == 3) {
			base = *(char**) (sub_obj + 0x14);
		}
		else {
			base = *(char**) (sub_obj + 0x1c);
		}
	}
	else {
		base = start + 0x14;
	}

	if ((unsigned int) base >= (unsigned int) end) {
		return 0;
	}

	do {
		if (callback == 0) {
			return base;
		}
		if (callback(ctx, base)) {
			return base;
		}
		base += 0x14;
	} while ((unsigned int) base < (unsigned int) end);

	return 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 370
// SYMBOL: _SpawnGraveyardEntities
// FUNCTION: SERVER 0x10010850
// SpawnGraveyardEntities

/* Auto-generated Ghidra decompilation */
// BLOCKER_DELTA: 339
// PROTOTYPE: int __cdecl SpawnGraveyardEntities(uchar * param_1, int param_2)

int SpawnGraveyardEntities(unsigned char* param_1, int param_2)
{
	unsigned char building_tier;
	unsigned int new_entity_id;
	short current_game_tick;
	unsigned char rand_skill_byte;
	int slot_entry_ptr;
	unsigned int rand_stat_val;
	int spawn_count;
	int skill_index;
	char* entity_type_entry;
	char entity_class_byte;

	rand_stat_val = *param_1;
	entity_type_entry = *(char**) 0x100a8c30 + rand_stat_val + rand_stat_val * 0x24c;
	entity_class_byte = *entity_type_entry;

	if (entity_class_byte == '\x1d') {
		building_tier = *(unsigned char*) (entity_type_entry + 0x247);
		if (building_tier != 0 && building_tier < 4) {
			spawn_count = 0;
			if (0 < param_2) {
				do {
					slot_entry_ptr = FindSlotEntryFiltered(0, param_1, 0, 0x10010700, 0);
					if (slot_entry_ptr == 0) {
						return spawn_count;
					}
					*(*(unsigned int**) (slot_entry_ptr + 0x10)) = *(unsigned int*) 0x10030b6c;
					*(unsigned int*) 0x10030b6c = *(unsigned int*) 0x10030b6c + 1;
					new_entity_id = *(*(unsigned int**) (slot_entry_ptr + 0x10));
					*(unsigned int*) (slot_entry_ptr + 8) = 0x7fff;
					*(unsigned int*) (slot_entry_ptr + 4) = new_entity_id;
					current_game_tick = *(short*) 0x10035880;
					*(unsigned int*) (slot_entry_ptr + 0xc) = 0xff;
					*(unsigned int*) (slot_entry_ptr + 10) = current_game_tick + 5;
					skill_index = 0;
					do {
						random_mod(8);
						rand_skill_byte = __ftol();
						skill_index = skill_index + 1;
						*(*(char**) (slot_entry_ptr + 0x10) + 0x23 + skill_index) = rand_skill_byte;
					} while (skill_index < 5);
					rand_stat_val = random_mod(9);
					*(*(char**) (slot_entry_ptr + 0x10) + 0x2c) = (rand_stat_val & 0xffff) + 1;
					rand_stat_val = random_mod(2);
					*(*(char**) (slot_entry_ptr + 0x10) + 0x30) = (rand_stat_val & 0xffff) + 1;
					rand_stat_val = random_mod(0x5e);
					*(*(char**) (slot_entry_ptr + 0x10) + 0x34) = (rand_stat_val & 0xffff) + 1;
					rand_stat_val = random_mod(4);
					*(*(char**) (slot_entry_ptr + 0x10) + 0x40) = (*(short*) 0x10035880 - (rand_stat_val & 0xffff)) + -1;
					rand_stat_val = random_mod(2);
					*(*(char**) (slot_entry_ptr + 0x10) + 0x38) = rand_stat_val & 0xffff;
					random_mod(0x10);
					random_mod(0x10);
					random_mod(0x10);
					spawn_count = spawn_count + 1;
				} while (spawn_count < param_2);
			}
			return spawn_count;
		}
	}
	return 0;
}

// ORIGIN: GAME
// STATUS: RELOC
// SIZE: 832
// SYMBOL: _AllocGraveyardField
// FUNCTION: SERVER 0x100109d0
// AllocGraveyardField
// PROTOTYPE: int __cdecl AllocGraveyardField(int building_ptr)

#ifdef __clang__
#define REBREW_NAKED
#else
#define REBREW_NAKED __declspec(naked)
#endif

int REBREW_NAKED __cdecl AllocGraveyardField(int param_1)
{
	__asm {
        mov     eax, dword ptr [esp+4]
        xor     ecx, ecx
        push    ebx
        push    ebp
        mov     cl, byte ptr [eax]
        push    esi
        push    edi
        lea     eax, [ecx+ecx*2]
        shl     eax, 4
        add     eax, ecx
        lea     edx, [eax+eax*2]
        mov     eax, dword ptr [g_entity_type_table]
        add     eax, ecx
        lea     ebp, [eax+edx*4]
        mov     al, byte ptr [eax+edx*4]
        cmp     al, 1Dh
        jne     L_ret_zero
        mov     al, byte ptr [ebp+247h]
        cmp     al, 1
        jb      L_ret_zero
        cmp     al, 3
        ja      L_ret_zero

        push    offset g_1002d474
        push    24h
        call    AllocateTrackedHeapBlock
        mov     esi, eax
        xor     ebx, ebx
        add     esp, 8
        cmp     esi, ebx
        je      L_ret_zero

        mov     ecx, 9
        xor     eax, eax
        mov     edi, esi
        push    offset g_1002d45c
        rep stosd
        mov     ecx, dword ptr [esp+18h]
        mov     edx, dword ptr [ecx+1]
        xor     ecx, ecx
        mov     dword ptr [esi], edx
        mov     al, byte ptr [ebp+247h]
        mov     dword ptr [esi+4], eax
        mov     cl, byte ptr [ebp+247h]
        mov     eax, dword ptr [g_1002575c + ecx*4]
        lea     edx, [eax+eax*4]
        shl     edx, 2
        push    edx
        call    AllocateTrackedHeapBlock
        mov     edi, eax
        add     esp, 8
        cmp     edi, ebx
        mov     dword ptr [esi+1Ch], edi
        je      short L_cleanup

        xor     eax, eax
        push    offset g_1002d444
        mov     al, byte ptr [ebp+247h]
        mov     eax, dword ptr [g_1002575c + eax*4]
        lea     ecx, [eax+eax*4]
        xor     eax, eax
        shl     ecx, 2
        mov     edx, ecx
        shr     ecx, 2
        rep stosd
        mov     ecx, edx
        and     ecx, 3
        rep stosb
        xor     eax, eax
        mov     al, byte ptr [ebp+247h]
        mov     eax, dword ptr [g_1002576c + eax*4]
        mov     ecx, eax
        shl     ecx, 4
        add     ecx, eax
        shl     ecx, 2
        push    ecx
        call    AllocateTrackedHeapBlock
        mov     edi, eax
        add     esp, 8
        cmp     edi, ebx
        mov     dword ptr [esi+20h], edi
        jne     short L_init_slots

    L_cleanup:
        mov     eax, dword ptr [esi+1Ch]
        cmp     eax, ebx
        je      short L_check_20
        push    eax
        call    FreeTrackedHeapBlock
        add     esp, 4
        mov     dword ptr [esi+1Ch], ebx

    L_check_20:
        mov     eax, dword ptr [esi+20h]
        cmp     eax, ebx
        je      short L_free_result
        push    eax
        call    FreeTrackedHeapBlock
        add     esp, 4
        mov     dword ptr [esi+20h], ebx

    L_free_result:
        push    esi
        call    FreeTrackedHeapBlock
        add     esp, 4

    L_ret_zero:
        pop     edi
        pop     esi
        pop     ebp
        xor     eax, eax
        pop     ebx
        ret

    L_init_slots:
        xor     edx, edx
        mov     dl, byte ptr [ebp+247h]
        mov     eax, dword ptr [g_1002576c + edx*4]
        mov     ecx, eax
        shl     ecx, 4
        add     ecx, eax
        xor     eax, eax
        shl     ecx, 2
        mov     edx, ecx
        shr     ecx, 2
        rep stosd
        mov     ecx, edx
        and     ecx, 3
        rep stosb

        xor     ecx, ecx
        xor     eax, eax
        mov     cl, byte ptr [ebp+247h]
        or      edi, 0FFFFFFFFh
        cmp     dword ptr [g_1002576c + ecx*4], ebx
        jle     short L_after_init

        xor     ecx, ecx
    L_init_loop:
        mov     edx, dword ptr [esi+20h]
        inc     eax
        mov     dword ptr [ecx+edx], edi
        xor     edx, edx
        mov     dl, byte ptr [ebp+247h]
        add     ecx, 44h
        cmp     eax, dword ptr [g_1002576c + edx*4]
        jl      short L_init_loop

    L_after_init:
        mov     edx, dword ptr [esi+4]
        mov     eax, dword ptr [esi+1Ch]
        mov     ecx, dword ptr [esi+20h]
        cmp     edx, 1
        mov     dword ptr [esi+8], eax
        mov     byte ptr [esi+18h], 1
        mov     byte ptr [esi+19h], bl
        mov     byte ptr [esi+1Ah], bl
        mov     byte ptr [esi+1Bh], bl
        jne     short L_not_type1

        lea     edx, [eax+0A0h]
        mov     dword ptr [esi+10h], ebx
        mov     dword ptr [esi+0Ch], edx
        mov     dword ptr [esi+14h], ebx
        mov     ebp, 8
        mov     edx, 0FFFFh

    L_t1_loop1:
        mov     dword ptr [eax], ebx
        mov     dword ptr [eax+10h], ecx
        mov     dword ptr [eax+4], edi
        mov     word ptr [eax+8], dx
        add     ecx, 44h
        add     eax, 14h
        dec     ebp
        jne     short L_t1_loop1

        mov     ebp, 4

    L_t1_loop2:
        mov     dword ptr [eax], 1
        mov     dword ptr [eax+10h], ecx
        mov     dword ptr [eax+4], edi
        mov     word ptr [eax+8], dx
        add     ecx, 88h
        add     eax, 14h
        dec     ebp
        jne     short L_t1_loop2

        mov     eax, dword ptr [esp+14h]
        pop     edi
        mov     dword ptr [eax+65h], esi
        mov     eax, esi
        pop     esi
        pop     ebp
        pop     ebx
        ret

    L_not_type1:
        cmp     edx, 2
        jne     L_type3

        lea     edx, [eax+0F0h]
        mov     dword ptr [esi+14h], ebx
        mov     dword ptr [esi+0Ch], edx
        lea     edx, [eax+168h]
        mov     dword ptr [esi+10h], edx
        mov     ebp, 0Ch
        mov     edx, 0FFFFh

    L_t2_loop1:
        mov     dword ptr [eax], ebx
        mov     dword ptr [eax+10h], ecx
        mov     dword ptr [eax+4], edi
        mov     word ptr [eax+8], dx
        add     ecx, 44h
        add     eax, 14h
        dec     ebp
        jne     short L_t2_loop1

        mov     ebp, 6

    L_t2_loop2:
        mov     dword ptr [eax], 1
        mov     dword ptr [eax+10h], ecx
        mov     dword ptr [eax+4], edi
        mov     word ptr [eax+8], dx
        add     ecx, 88h
        add     eax, 14h
        dec     ebp
        jne     short L_t2_loop2

        mov     ebp, 2

    L_t2_loop3:
        mov     dword ptr [eax], 2
        mov     dword ptr [eax+10h], ecx
        mov     dword ptr [eax+4], edi
        mov     word ptr [eax+8], dx
        add     ecx, 110h
        add     eax, 14h
        dec     ebp
        jne     short L_t2_loop3

        mov     eax, dword ptr [esp+14h]
        pop     edi
        mov     dword ptr [eax+65h], esi
        mov     eax, esi
        pop     esi
        pop     ebp
        pop     ebx
        ret

    L_type3:
        lea     edx, [eax+140h]
        mov     ebp, 10h
        mov     dword ptr [esi+0Ch], edx
        lea     edx, [eax+1E0h]
        mov     dword ptr [esi+10h], edx
        lea     edx, [eax+230h]
        mov     dword ptr [esi+14h], edx
        mov     edx, 0FFFFh

    L_t3_loop1:
        mov     dword ptr [eax], ebx
        mov     dword ptr [eax+10h], ecx
        mov     dword ptr [eax+4], edi
        mov     word ptr [eax+8], dx
        add     ecx, 44h
        add     eax, 14h
        dec     ebp
        jne     short L_t3_loop1

        mov     ebp, 8

    L_t3_loop2:
        mov     dword ptr [eax], 1
        mov     dword ptr [eax+10h], ecx
        mov     dword ptr [eax+4], edi
        mov     word ptr [eax+8], dx
        add     ecx, 88h
        add     eax, 14h
        dec     ebp
        jne     short L_t3_loop2

        mov     ebp, 4

    L_t3_loop3:
        mov     dword ptr [eax], 2
        mov     dword ptr [eax+10h], ecx
        mov     dword ptr [eax+4], edi
        mov     word ptr [eax+8], dx
        add     ecx, 110h
        add     eax, 14h
        dec     ebp
        jne     short L_t3_loop3

        mov     ebp, 2

    L_t3_loop4:
        mov     dword ptr [eax], 3
        mov     dword ptr [eax+10h], ecx
        mov     dword ptr [eax+4], edi
        mov     word ptr [eax+8], dx
        add     ecx, 220h
        add     eax, 14h
        dec     ebp
        jne     short L_t3_loop4

        mov     eax, dword ptr [esp+14h]
        pop     edi
        mov     dword ptr [eax+65h], esi
        mov     eax, esi
        pop     esi
        pop     ebp
        pop     ebx
        ret
	}
}

#undef REBREW_NAKED

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, instruction folding (lea vs mov), zero-extend pattern (xor vs mov)
// SIZE: 570
// SYMBOL: _UpgradeGraveyardField
// FUNCTION: SERVER 0x10010d10
// UpgradeGraveyardField

/* Auto-generated Ghidra decompilation */
// BLOCKER_DELTA: 539
// PROTOTYPE: uint __cdecl UpgradeGraveyardField(uint8_t * param_1)

unsigned int UpgradeGraveyardField(unsigned char* param_1)
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

	entity_type_idx = *param_1;
	old_field_ptr = *(int*) (param_1 + 0x65);
	loop_byte_offset = *(int*) 0x100a8c30 + entity_type_idx + entity_type_idx * 0x24c;
	if ((((*(char*) (*(int*) 0x100a8c30 + entity_type_idx + entity_type_idx * 0x24c) == '\x1d') && (old_field_ptr != 0)) &&
		 (*(int*) (old_field_ptr + 4) < 3)) &&
		(*(char*) (loop_byte_offset + 0x247) - *(int*) (old_field_ptr + 4) == 1)) {
		param_1[0x65] = 0;
		param_1[0x66] = 0;
		param_1[0x67] = 0;
		param_1[0x68] = 0;
		new_field_ptr = AllocGraveyardField(param_1);
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
					*(int*) (*(int*) (new_field_ptr + 8) + loop_byte_offset) = *(int*) (loop_byte_offset + *(int*) (old_field_ptr + 8));
					*(int*) (*(int*) (new_field_ptr + 8) + 4 + loop_byte_offset) = *(int*) (loop_byte_offset + 4 + *(int*) (old_field_ptr + 8));
					*(int*) (*(int*) (new_field_ptr + 8) + 8 + loop_byte_offset) = *(int*) (loop_byte_offset + 8 + *(int*) (old_field_ptr + 8));
					*(short*) (*(int*) (new_field_ptr + 8) + 10 + loop_byte_offset) = *(short*) (loop_byte_offset + 10 + *(int*) (old_field_ptr + 8));
					*(char*) (*(int*) (new_field_ptr + 8) + 0xc + loop_byte_offset) = *(char*) (loop_byte_offset + 0xc + *(int*) (old_field_ptr + 8));
					loop_byte_offset = loop_byte_offset + 0x14;
					slot0_count = slot0_count + -1;
				} while (slot0_count != 0);
			}
			if ((*(int*) (old_field_ptr + 0xc) != 0) && (slot1_count != 0)) {
				loop_byte_offset = 0;
				do {
					*(int*) (loop_byte_offset + *(int*) (new_field_ptr + 0xc)) = *(int*) (loop_byte_offset + *(int*) (old_field_ptr + 0xc));
					*(int*) (loop_byte_offset + 4 + *(int*) (new_field_ptr + 0xc)) = *(int*) (loop_byte_offset + 4 + *(int*) (old_field_ptr + 0xc));
					*(int*) (loop_byte_offset + 8 + *(int*) (new_field_ptr + 0xc)) = *(int*) (loop_byte_offset + 8 + *(int*) (old_field_ptr + 0xc));
					*(short*) (loop_byte_offset + 10 + *(int*) (new_field_ptr + 0xc)) = *(short*) (loop_byte_offset + 10 + *(int*) (old_field_ptr + 0xc));
					*(char*) (loop_byte_offset + 0xc + *(int*) (new_field_ptr + 0xc)) = *(char*) (loop_byte_offset + 0xc + *(int*) (old_field_ptr + 0xc));
					loop_byte_offset = loop_byte_offset + 0x14;
					slot1_count = slot1_count + -1;
				} while (slot1_count != 0);
			}
			if ((*(int*) (old_field_ptr + 0x10) != 0) && (slot2_count != 0)) {
				loop_byte_offset = 0;
				do {
					*(int*) (loop_byte_offset + *(int*) (new_field_ptr + 0x10)) = *(int*) (loop_byte_offset + *(int*) (old_field_ptr + 0x10));
					*(int*) (loop_byte_offset + 4 + *(int*) (new_field_ptr + 0x10)) = *(int*) (loop_byte_offset + 4 + *(int*) (old_field_ptr + 0x10));
					*(int*) (loop_byte_offset + 8 + *(int*) (new_field_ptr + 0x10)) = *(int*) (loop_byte_offset + 8 + *(int*) (old_field_ptr + 0x10));
					*(short*) (loop_byte_offset + 10 + *(int*) (new_field_ptr + 0x10)) = *(short*) (loop_byte_offset + 10 + *(int*) (old_field_ptr + 0x10));
					*(char*) (loop_byte_offset + 0xc + *(int*) (new_field_ptr + 0x10)) = *(char*) (loop_byte_offset + 0xc + *(int*) (old_field_ptr + 0x10));
					loop_byte_offset = loop_byte_offset + 0x14;
					slot2_count = slot2_count + -1;
				} while (slot2_count != 0);
			}
			*(int*) (new_field_ptr + 0x18) = *(int*) (old_field_ptr + 0x18);
			*(char*) (new_field_ptr + 0x19) = *(char*) (old_field_ptr + 0x19);
			*(char*) (new_field_ptr + 0x1a) = *(char*) (old_field_ptr + 0x1a);
			*(char*) (new_field_ptr + 0x1b) = *(char*) (old_field_ptr + 0x1b);
			free_3fields(old_field_ptr);
			return *(unsigned int*) (param_1 + 0x65);
		}
		*(unsigned int*) (param_1 + 0x65) = old_field_ptr;
	}
	return 0;
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 66
// SYMBOL: _free_3fields
// FUNCTION: SERVER 0x10010F50
// free_3fields
// PROTOTYPE: void __cdecl free_3fields(char * p)

void __cdecl free_3fields(char* p)
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

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: instruction folding (lea vs mov), loop rotation / branch layout, zero-extend pattern (xor vs mov)
// SIZE: 525
// SYMBOL: _AssignProductionSlot
// FUNCTION: SERVER 0x10010fa0
// AssignProductionSlot

/* Auto-generated Ghidra decompilation */
// BLOCKER_DELTA: 462
// PROTOTYPE: uint __cdecl AssignProductionSlot(int param_1)

unsigned int AssignProductionSlot(int param_1)
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

	worker_slot_capacity = param_1;
	ResolveEntityById(&building_entity_ptr, 0, 0, *(unsigned int*) (param_1 + 8));
	if (((building_entity_ptr == 0) || (*(unsigned short*) (building_entity_ptr + 0x27) == 0xffff)) ||
		(*(unsigned short*) (building_entity_ptr + 0x27) * 0x21c + *(unsigned int*) 0x100358a0 == *(unsigned int*) 0x1003546c)) {
		return 0xffffffff;
	}
	if (*(*(char**) 0x100a8c30 + *building_entity_ptr * 0x24d) != '\x1d') {
		return 0xfffffffe;
	}
	assignment_loop_idx = *(unsigned int*) (building_entity_ptr + 0x65);
	if (assignment_loop_idx == 0) {
		return 0xfffffffd;
	}
	slot_category_check = check_slot_active(assignment_loop_idx, *(int*) (worker_slot_capacity + 0xc));
	if (slot_category_check == 0) {
		return 0xfffffffc;
	}
	ResolveEntityById(0, 0, (int*) &param_1, *(unsigned int*) (worker_slot_capacity + 4));
	if (param_1 == 0) {
		return 0xfffffffa;
	}
	assignment_loop_idx = GetSlotEntry(assignment_loop_idx, *(int*) (worker_slot_capacity + 0xc), *(int*) (worker_slot_capacity + 0x10));
	if ((assignment_loop_idx == 0) || (*(unsigned int*) (assignment_loop_idx + 8) != *(unsigned int*) (param_1 + 0x50))) {
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
	*best_slot_record_ptr = *(unsigned int*) (param_1 + 4);
	strlen_counter = 0xffffffff;
	name_scan_ptr = (char*) (param_1 + 0x30);
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
	candidate_record_ptr = (int*) (name_scan_end_ptr + -strlen_counter);
	slot_worker_array_ptr = best_slot_record_ptr;
	for (copy_dword_count = strlen_counter >> 2; slot_worker_array_ptr = slot_worker_array_ptr + 1, copy_dword_count != 0; copy_dword_count = copy_dword_count - 1) {
		*slot_worker_array_ptr = *candidate_record_ptr;
		candidate_record_ptr = candidate_record_ptr + 1;
	}
	for (strlen_counter = strlen_counter & 3; strlen_counter != 0; strlen_counter = strlen_counter - 1) {
		*slot_worker_array_ptr = *candidate_record_ptr;
		candidate_record_ptr = candidate_record_ptr + 1;
		slot_worker_array_ptr = slot_worker_array_ptr + 1;
	}
	strlen_counter = 0xffffffff;
	name_scan_ptr = (char*) (param_1 + 0x40);
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
	slot_worker_array_ptr = (int*) (name_scan_end_ptr + -strlen_counter);
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
	best_slot_record_ptr[9] = *(unsigned int*) (param_1 + 0x80);
	*(best_slot_record_ptr + 10) = *(unsigned int*) (param_1 + 0x84);
	best_slot_record_ptr[0xb] = *(unsigned int*) (param_1 + 0x167);
	best_slot_record_ptr[0xc] = *(unsigned int*) (param_1 + 0xd);
	best_slot_record_ptr[0xd] = *(unsigned int*) (param_1 + 0x164);
	best_slot_record_ptr[0xe] = *(unsigned int*) (param_1 + 9);
	best_slot_record_ptr[0x10] = *(unsigned int*) 0x10035880;
	best_slot_record_ptr[0xf] = *(unsigned int*) (param_1 + 0x18c);
	return 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, instruction folding (lea vs mov), jump condition swap, zero-extend pattern (xor vs mov)
// SIZE: 501
// SYMBOL: _HireProductionWorker
// FUNCTION: SERVER 0x100111b0
// HireProductionWorker

/* Auto-generated Ghidra decompilation */
// BLOCKER_DELTA: 456
// PROTOTYPE: uint __cdecl HireProductionWorker(int param_1)

unsigned int HireProductionWorker(int param_1)
{
	int cmd_ptr_saved;
	int slot_or_active_check;
	unsigned int rand_coin_amount;
	short hire_deadline_tick;
	int worker_record_count;
	int worker_record_offset;
	unsigned char* building_entity_ptr;

	cmd_ptr_saved = param_1;
	ResolveEntityById(&building_entity_ptr, 0, 0, *(unsigned int*) (param_1 + 8));
	if (((building_entity_ptr == 0) || (*(unsigned short*) (building_entity_ptr + 0x27) == 0xffff)) ||
		(*(unsigned short*) (building_entity_ptr + 0x27) * 0x21c + *(unsigned int*) 0x100358a0 == *(unsigned int*) 0x1003546c)) {
		return 0xffffffff;
	}
	if (*(*(char**) 0x100a8c30 + *building_entity_ptr * 0x24d) != '\x1d') {
		return 0xfffffffe;
	}
	if (*(unsigned int*) (building_entity_ptr + 0x65) == 0) {
		return 0xfffffffd;
	}
	slot_or_active_check = check_slot_active(*(unsigned int*) (building_entity_ptr + 0x65), *(int*) (cmd_ptr_saved + 0xc));
	if (slot_or_active_check == 0) {
		return 0xfffffffc;
	}
	ResolveEntityById(0, 0, (int*) &param_1, *(unsigned int*) (cmd_ptr_saved + 4));
	if (param_1 == 0) {
		return 0xfffffffa;
	}
	slot_or_active_check = *(int*) (cmd_ptr_saved + 0xc);
	if ((-1 < slot_or_active_check) && (slot_or_active_check < 4)) {
		slot_or_active_check = FindSlotEntryFiltered(param_1, building_entity_ptr, 0, 0x10010700, slot_or_active_check);
		if (slot_or_active_check == 0) {
			return 0xfffffff9;
		}
		*(unsigned int*) (slot_or_active_check + 4) = *(unsigned int*) (param_1 + 4);
		*(unsigned int*) (slot_or_active_check + 8) = *(unsigned int*) (param_1 + 0x50);
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
			SubtractObjectAmountNoKill(
				*(unsigned int*) (param_1 + 4),
				*(unsigned int*) (*(unsigned int*) 0x10035439 * 0x2f4 + 0x100a8c94),
				*(unsigned int*) (cmd_ptr_saved + 0x13)
			);
			rand_coin_amount = __ftol();
			AddOrAccumulateObject(
				*(unsigned int*) (*(unsigned short*) (building_entity_ptr + 0x27) * 0x21c + 0x100358a4),
				*(unsigned int*) (*(unsigned int*) 0x10035439 * 0x2f4 + 0x100a8c94),
				rand_coin_amount
			);
		}
		return 0;
	}
	return 0xfffffffb;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: instruction folding (lea vs mov), zero-extend pattern (xor vs mov)
// SIZE: 390
// SYMBOL: _ExtendProductionTime
// FUNCTION: SERVER 0x100113b0
// ExtendProductionTime

/* Auto-generated Ghidra decompilation */
// BLOCKER_DELTA: 306
// PROTOTYPE: uint __cdecl ExtendProductionTime(uint32_t * param_1)

unsigned int ExtendProductionTime(unsigned int* param_1)
{
	unsigned int* cmd_ptr_saved;
	int slot_active_result;
	int slot_entry_ptr;
	unsigned int rand_coin_amount;
	unsigned char* building_entity_ptr;

	cmd_ptr_saved = param_1;
	ResolveEntityById(&building_entity_ptr, 0, 0, *(param_1 + 8));
	if (((building_entity_ptr == 0) || (*(unsigned short*) (building_entity_ptr + 0x27) == 0xffff)) ||
		((*(unsigned short*) (building_entity_ptr + 0x27) * 0x21c + *(unsigned int*) 0x100358a0) ==
		 *(unsigned int*) 0x1003546c)) {
		return 0xffffffff;
	}
	if (*(*(char**) 0x100a8c30 + *building_entity_ptr * 0x24d) != '\x1d') {
		return 0xfffffffe;
	}
	slot_entry_ptr = *(unsigned int*) (building_entity_ptr + 0x65);
	if (slot_entry_ptr == 0) {
		return 0xfffffffd;
	}
	slot_active_result = check_slot_active(slot_entry_ptr, *(cmd_ptr_saved + 0xc));
	if (slot_active_result == 0) {
		return 0xfffffffc;
	}
	ResolveEntityById(0, 0, (int*) &param_1, *(cmd_ptr_saved + 4));
	if (param_1 == 0) {
		return 0xfffffffa;
	}
	slot_entry_ptr = GetSlotEntry(slot_entry_ptr, *(cmd_ptr_saved + 0xc), *(cmd_ptr_saved + 0x10));
	if (slot_entry_ptr == 0) {
		return 0xfffffff9;
	}
	*(unsigned int*) (slot_entry_ptr + 10) = *(unsigned int*) (slot_entry_ptr + 10) + *(cmd_ptr_saved + 0x11);
	if (0 < (int) *(cmd_ptr_saved + 0x13)) {
		SubtractObjectAmountNoKill(
			*(param_1 + 4),
			*(*(unsigned int**) 0x100a8c94 + *(unsigned int*) 0x10035439 * 0x2f4),
			*(cmd_ptr_saved + 0x13)
		);
		rand_coin_amount = __ftol();
		AddOrAccumulateObject(
			*(*(unsigned int**) 0x100358a4 + *(unsigned short*) (building_entity_ptr + 0x27) * 0x21c),
			*(*(unsigned int**) 0x100a8c94 + *(unsigned int*) 0x10035439 * 0x2f4),
			rand_coin_amount
		);
	}
	return 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 288
// SYMBOL: _ReplaceProductionWorker
// FUNCTION: SERVER 0x10011540
// ReplaceProductionWorker

// GLOBALS: SERVER 0x1003546c
// PROTOTYPE: int __cdecl ReplaceProductionWorker(uchar * param_1)

int __cdecl ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
int __cdecl check_slot_active(int param_1, int param_2);
int __cdecl GetSlotEntry(int param_1, int param_2, int param_3);

int __cdecl ReplaceProductionWorker(unsigned char* param_1)
{
	unsigned char* cmd_ptr_saved;
	int slot_active_result;
	int slot_entry_ptr;
	int new_worker_entity_id;
	unsigned short new_worker_job_type;
	void* new_worker_entity_ptr;

	new_worker_entity_id = -1;
	new_worker_job_type = 0xffff;
	cmd_ptr_saved = param_1;
	ResolveEntityById((void**) &param_1, (void**) 0, (void**) 0, *(int*) (param_1 + 8));
	if (((param_1 == (unsigned char*) 0) || (*(unsigned short*) (param_1 + 0x27) == 0xffff)) ||
		((char*) &DAT_100358a0 + (unsigned int) *(unsigned short*) (param_1 + 0x27) * 0x10e == (char*) DAT_1003546c)) {
		return -1;
	}
	if (*(char*) (DAT_100a8c30 + (unsigned int) *param_1 * 0x24d) != 0x1d) {
		return -2;
	}
	slot_entry_ptr = *(int*) (param_1 + 0x65);
	if (slot_entry_ptr == 0) {
		return -3;
	}
	slot_active_result = check_slot_active(slot_entry_ptr, *(int*) (cmd_ptr_saved + 0xc));
	if (slot_active_result == 0) {
		return -4;
	}
	if (*(int*) (cmd_ptr_saved + 4) != -1) {
		ResolveEntityById((void**) 0, (void**) 0, &new_worker_entity_ptr, *(int*) (cmd_ptr_saved + 4));
		if (new_worker_entity_ptr == (void*) 0) {
			return -6;
		}
		new_worker_entity_id = *(int*) (cmd_ptr_saved + 4);
		new_worker_job_type = *(unsigned short*) ((int) new_worker_entity_ptr + 0x50);
	}
	slot_entry_ptr = GetSlotEntry(slot_entry_ptr, *(int*) (cmd_ptr_saved + 0xc), (int) *(char*) (cmd_ptr_saved + 0x10));
	if (slot_entry_ptr == 0) {
		return -7;
	}
	*(unsigned short*) (slot_entry_ptr + 8) = new_worker_job_type;
	*(int*) (slot_entry_ptr + 4) = new_worker_entity_id;
	return 0;
}

// STATUS: RELOC
// ORIGIN: GAME
// GLOBALS: SERVER 0x100a8c30
// BLOCKER_DELTA: 273
// SIZE: 297
// SYMBOL: _ActivateGraveyardSection
// BLOCKER_DELTA: 39
// FUNCTION: SERVER 0x10011660
// ActivateGraveyardSection

/* GLOBAL: SERVER 0x1003546c */
extern int g_entity_table_end;

/* GLOBAL: SERVER 0x100a8c30 */
extern char* g_action_table_base;

/* GLOBAL: SERVER 0x100358a0 */
extern char g_slot_table[];

int __cdecl ActivateGraveyardSection(unsigned char* param_1)
{
	void* entity;
	void* target_entity;

	ResolveEntityById((int*) &entity, 0, 0, *(int*) (param_1 + 8));
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

				ResolveEntityById(0, 0, (int*) &target_entity, *(int*) (param_1 + 4));
				if (target_entity == 0) {
					return -6;
				}

				action_type = *(int*) (param_1 + 0xc);
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

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: zero-extend pattern (xor vs mov)
// SIZE: 242
// SYMBOL: _UpdateProductionProgress

// BLOCKER_DELTA: 96
// FUNCTION: SERVER 0x10011790
// UpdateProductionProgress

// GLOBALS: SERVER 0x1003546c
// PROTOTYPE: int __cdecl UpdateProductionProgress(uchar * param_1)

int __cdecl ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
int __cdecl check_slot_active(int param_1, int param_2);
int __cdecl GetSlotEntry(int param_1, int param_2, int param_3);

int __cdecl UpdateProductionProgress(unsigned char* param_1)
{
	unsigned char* cmd_ptr_saved;
	int slot_active_result;
	int slot_entry_ptr;
	unsigned int new_progress_value;

	cmd_ptr_saved = param_1;
	ResolveEntityById((void**) &param_1, (void**) 0, (void**) 0, *(int*) (param_1 + 8));
	if (((param_1 == (unsigned char*) 0) || (*(unsigned short*) (param_1 + 0x27) == 0xffff)) ||
		((char*) &DAT_100358a0 + (unsigned int) *(unsigned short*) (param_1 + 0x27) * 0x10e == (char*) DAT_1003546c)) {
		return -1;
	}
	if (*(char*) (DAT_100a8c30 + (unsigned int) *param_1 * 0x24d) != 0x1d) {
		return -2;
	}
	slot_entry_ptr = *(int*) (param_1 + 0x65);
	if (slot_entry_ptr == 0) {
		return -3;
	}
	slot_active_result = check_slot_active(slot_entry_ptr, *(int*) (cmd_ptr_saved + 0xc));
	if (slot_active_result == 0) {
		return -4;
	}
	slot_entry_ptr = GetSlotEntry(slot_entry_ptr, *(int*) (cmd_ptr_saved + 0xc), cmd_ptr_saved[0x10]);
	if (slot_entry_ptr == 0) {
		return -7;
	}
	new_progress_value = *(int*) (cmd_ptr_saved + 0x13) + (unsigned int) *(unsigned char*) (slot_entry_ptr + 0xc);
	new_progress_value = new_progress_value & ((int) new_progress_value <= 0) - 1;
	if ((int) new_progress_value >= 0xff) {
		new_progress_value = 0xff;
	}
	*(char*) (slot_entry_ptr + 0xc) = (char) new_progress_value;
	return 0;
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 164
// SYMBOL: _ValidateEntityAction
// ANALYSIS: Validates a standard entity action command. Resolves the target entity ID (from cmd->payload + 0). Validates the entity exists, is a valid type, and its action mask/state is valid using FUN_10010850. Returns 0 on success, negative error codes (-1 to -4) on failure.
// FUNCTION: SERVER 0x10011890
// ValidateEntityAction
// PROTOTYPE: int __cdecl ValidateEntityAction(uchar * param_1)

int __cdecl ValidateEntityAction(unsigned char* param_1)
{
	void* entity;
	unsigned int slot_val;
	unsigned char type_byte;
	int result;

	ResolveEntityById((int*) &entity, 0, 0, *(int*) (param_1 + 8));
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
				result = SpawnGraveyardEntities(entity, *(int*) (param_1 + 0x13));
				if (result > 0) {
					return 0;
				}
				return -4;
			}
		}
	}
	return -1;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 674
// SYMBOL: _MoveSlotEntry
// BLOCKER_DELTA: 639
// FUNCTION: SERVER 0x10011940
// MoveSlotEntry
// PROTOTYPE: uint __cdecl MoveSlotEntry(int param_1)

unsigned int MoveSlotEntry(int param_1)
{
	int* src_worker_array_ptr;
	int cmd_ptr_saved;
	int field_or_slot_ptr;
	unsigned char* building_entity_ptr;
	int src_worker_array_end;
	int dst_slot_entry_ptr;

	cmd_ptr_saved = param_1;
	ResolveEntityById(0, 0, &param_1, *(int*) cmd_ptr_saved);
	if (param_1 == 0) {
		return 0xfffffffa;
	}
	ResolveEntityById((int) &building_entity_ptr, 0, 0, *(int*) (cmd_ptr_saved + 4));
	if (((building_entity_ptr == 0) || (*(unsigned short*) (building_entity_ptr + 0x27) == 0xffff)) ||
		(*(unsigned short*) (building_entity_ptr + 0x27) * 0x21c + *(unsigned int*) 0x100358a0 == *(unsigned int*) 0x1003546c)) {
		return 0xffffffff;
	}
	if (*(*(char**) 0x100a8c30 + *building_entity_ptr * 0x24d) != '\x1d') {
		return 0xfffffffe;
	}
	field_or_slot_ptr = *(int*) (building_entity_ptr + 0x65);
	if (field_or_slot_ptr == 0) {
		return 0xfffffffd;
	}
	field_or_slot_ptr = check_slot_active(field_or_slot_ptr, *(int*) (cmd_ptr_saved + 8));
	if (field_or_slot_ptr == 0) {
		return 0xfffffffc;
	}
	field_or_slot_ptr = GetSlotEntry(*(int*) (building_entity_ptr + 0x65), *(int*) (cmd_ptr_saved + 8), (int) *(unsigned char*) (cmd_ptr_saved + 0xc));
	if ((field_or_slot_ptr != 0) && (*(unsigned short*) (field_or_slot_ptr + 8) == *(unsigned short*) (param_1 + 0x50))) {
		int saved_src_slot_entry_ptr;

		src_worker_array_ptr = *(int**) (field_or_slot_ptr + 0x10);
		src_worker_array_end = *(int*) (*(int*) (cmd_ptr_saved + 8) * 4 + 0x1002574c);
		saved_src_slot_entry_ptr = field_or_slot_ptr;
		dst_slot_entry_ptr = FindSlotEntryFiltered(param_1, (int) building_entity_ptr, 0, 0x10010700, *(int*) (cmd_ptr_saved + 0xd));
		if (dst_slot_entry_ptr != 0) {
			int* piVar5;
			int* piVar7;
			int* piVar8;
			int word_copy_count;
			piVar5 = *(int**) (dst_slot_entry_ptr + 0x10);
			piVar8 = piVar5 + *(int*) (*(int*) (cmd_ptr_saved + 0xd) * 4 + 0x1002574c) * 0x11;
			src_worker_array_end = (int) (src_worker_array_ptr + src_worker_array_end * 0x11);
			for (; piVar5 < piVar8; piVar5 = piVar5 + 0x11) {
				if (*piVar5 == -1) {
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
						int* pDst = piVar5;
						for (word_copy_count = 0x11; word_copy_count != 0; word_copy_count = word_copy_count + -1) {
							*pDst = *pSrc;
							pSrc = pSrc + 1;
							pDst = pDst + 1;
						}
					}
					piVar7 = src_worker_array_ptr;
					for (word_copy_count = 0x11; word_copy_count != 0; word_copy_count = word_copy_count + -1) {
						*piVar7 = 0;
						piVar7 = piVar7 + 1;
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
				SubtractObjectAmountNoKill(
					*(unsigned int*) (param_1 + 4),
					*(unsigned int*) ((unsigned char*) 0x100a8c94 + *(unsigned int*) 0x10035439 * 0x2f4),
					*(unsigned int*) (cmd_ptr_saved + 0x11)
				);
				scaled_amount = (unsigned int) ((int) *(int*) (cmd_ptr_saved + 0x11) * ((float*) 0x1002572c)[*(int*) (cmd_ptr_saved + 0xd)]);
				AddOrAccumulateObject(
					*(unsigned int*) ((unsigned char*) 0x100358a4 + *(unsigned short*) (building_entity_ptr + 0x27) * 0x21c),
					*(unsigned int*) ((unsigned char*) 0x100a8c94 + *(unsigned int*) 0x10035439 * 0x2f4),
					scaled_amount
				);
			}
			return 0;
		}
	}
	return 0xfffffff9;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 1040
// SYMBOL: _gv_ExAllocGraveyardWorker
// BLOCKER_DELTA: 1021
// GHIDRA: AllocGraveyardWorker
// ANALYSIS: Allocates a graveyard worker (type 0x1b or 0x1c). Validates parent building is graveyard type (0x1d), finds production entry matching requested job, allocates a free static entity slot, initializes all fields including skills (halved from template), name, relationships (random +/-32), and coordinates.
// FUNCTION: SERVER 0x10011bf0
// gv_ExAllocGraveyardWorker
// PROTOTYPE: uint __stdcall gv_ExAllocGraveyardWorker(int param_1)

unsigned int __cdecl gv_ExAllocGraveyardWorker(int param_1)
{
	unsigned short* new_entity_slot_ptr;
	unsigned short entity_slot_index;
	char rand_relationship_val;
	int entity_slot_byte_offset;
	int* matched_production_record;
	short* slot_scan_ptr;
	char* entity_type_scan_ptr;
	int* production_record_walker;
	int clear_loop_counter;
	int search_loop_idx;
	int slot_scan_idx_or_capacity;
	unsigned int* relationship_array_ptr;
	unsigned short* slot_clear_ptr;
	double random_float;
	int relationship_loop_idx;
	unsigned char* building_entity_ptr;
	int production_slot_entry_ptr;

	if (*(int*) (param_1 + 0x15) != 0x1b && *(int*) (param_1 + 0x15) != 0x1c) {
		return 0xfffffffa;
	}
	search_loop_idx = 0;
	ResolveEntityById(&building_entity_ptr, 0, 0, *(unsigned int*) (param_1 + 8));
	if (building_entity_ptr == 0 || *(unsigned short*) (building_entity_ptr + 0x27) == 0xffff ||
		*(unsigned short*) (building_entity_ptr + 0x27) * 0x21c + (int) &DAT_100358a0 == DAT_1003546c) {
		return 0xffffffff;
	}
	if (*(char*) (DAT_100a8c30 + (unsigned int) *building_entity_ptr * 0x24d) != '\x1d') {
		return 0xfffffffe;
	}
	slot_scan_idx_or_capacity = *(int*) (building_entity_ptr + 0x65);
	if (slot_scan_idx_or_capacity == 0) {
		return 0xfffffffd;
	}
	entity_slot_byte_offset = check_slot_active(slot_scan_idx_or_capacity, *(int*) (param_1 + 0xc));
	if (entity_slot_byte_offset == 0) {
		return 0xfffffffc;
	}
	production_slot_entry_ptr = GetSlotEntry(slot_scan_idx_or_capacity, *(int*) (param_1 + 0xc), *(unsigned char*) (param_1 + 0x10));
	if (production_slot_entry_ptr == 0) {
		return 0xffff;
	}
	entity_slot_byte_offset = 0;
	slot_scan_idx_or_capacity = *(int*) (*(int*) (param_1 + 0xc) * 4 + 0x1002574c);
	if (0 < slot_scan_idx_or_capacity) {
		production_record_walker = *(int**) (production_slot_entry_ptr + 0x10);
		do {
			matched_production_record = production_record_walker;
			if (*matched_production_record == *(int*) (param_1 + 0x11)) {
				break;
			}
			entity_slot_byte_offset = entity_slot_byte_offset + 1;
			production_record_walker = matched_production_record + 0x11;
		} while (entity_slot_byte_offset < slot_scan_idx_or_capacity);
		if (matched_production_record != 0 && *matched_production_record == *(int*) (param_1 + 0x11)) {
			slot_scan_idx_or_capacity = 0;
			slot_scan_ptr = (short*) &DAT_100358a0;
			do {
				if (*slot_scan_ptr == -1) {
					break;
				}
				slot_scan_ptr = slot_scan_ptr + 0x10e;
				slot_scan_idx_or_capacity = slot_scan_idx_or_capacity + 1;
			} while (slot_scan_ptr < (short*) 0x1009aca0);
			if (slot_scan_idx_or_capacity == 0x300) {
				slot_scan_idx_or_capacity = 0;
				entity_type_scan_ptr = (char*) 0x100358a2;
				do {
					if (*entity_type_scan_ptr == '\x0f') {
						break;
					}
					entity_type_scan_ptr = entity_type_scan_ptr + 0x21c;
					slot_scan_idx_or_capacity = slot_scan_idx_or_capacity + 1;
				} while (entity_type_scan_ptr < (char*) 0x1009aca2);
				if (slot_scan_idx_or_capacity == 0x300) {
					LogMessageInternal(
						"D:\\Develop\\DieGildeAddOn\\game\\friedhof_logic.c",
						0x6ef,
						"gv_ExAllocGraveyardWorker: array overflow...",
						1
					);
					return 0xffff;
				}
			}
			entity_slot_byte_offset = slot_scan_idx_or_capacity * 0x21c;
			if (*(char*) (entity_slot_byte_offset + 0x100358a2) == '\x0f') {
				DAT_10035434 = DAT_10035434 - 1;
			}
			new_entity_slot_ptr = (unsigned short*) (entity_slot_byte_offset + (int) &DAT_100358a0);
			slot_clear_ptr = new_entity_slot_ptr;
			for (clear_loop_counter = 0x87; clear_loop_counter != 0; clear_loop_counter = clear_loop_counter - 1) {
				slot_clear_ptr[0] = 0;
				slot_clear_ptr[1] = 0;
				slot_clear_ptr = slot_clear_ptr + 2;
			}
			*new_entity_slot_ptr = 0xffff;
			*(int*) (entity_slot_byte_offset + 0x100358a4) = (int) 0xffffffff;
			relationship_array_ptr = (unsigned int*) (entity_slot_byte_offset + 0x100358fc);
			for (clear_loop_counter = 8; clear_loop_counter != 0; clear_loop_counter = clear_loop_counter - 1) {
				*relationship_array_ptr = 0xffffffff;
				relationship_array_ptr = relationship_array_ptr + 1;
			}
			*(unsigned char**) (entity_slot_byte_offset + 0x10035a10) = building_entity_ptr;
			*(unsigned char**) (entity_slot_byte_offset + 0x10035a0c) = building_entity_ptr;
			DAT_10035434 = DAT_10035434 + 1;
			*(int*) (entity_slot_byte_offset + 0x100358a4) = DAT_10030b6c;
			DAT_10030b6c = DAT_10030b6c + 1;
			*new_entity_slot_ptr = (unsigned short) slot_scan_idx_or_capacity;
			*(char*) (entity_slot_byte_offset + 0x100358a2) = 0x14;
			*(int*) (entity_slot_byte_offset + 0x10035a90) = 0;
			*(int*) (entity_slot_byte_offset + 0x10035ab0) = (int) 0xffffffff;
			*(char*) (entity_slot_byte_offset + 0x10035ab5) = 0;
			*(char*) (entity_slot_byte_offset + 0x10035ab6) = 0;
			*(char*) (entity_slot_byte_offset + 0x10035ab7) = 0;
			*(char*) (entity_slot_byte_offset + 0x10035ab8) = 1;
			*(int*) (entity_slot_byte_offset + 0x10035a84) = 0x3f800000;
			*(short*) (entity_slot_byte_offset + 0x100358a8) = 100;
			*(short*) (entity_slot_byte_offset + 0x100358aa) = 0x10;
			*(char*) (entity_slot_byte_offset + 0x10035a04) = 0;
			*(char*) (entity_slot_byte_offset + 0x10035a06) = 0;
			*(char*) (entity_slot_byte_offset + 0x10035a05) = *(char*) (param_1 + 0x15);
			*(int*) (entity_slot_byte_offset + 0x10035a94) = 0;
			*(int*) (entity_slot_byte_offset + 0x10035a30) = 4;
			*(int*) (entity_slot_byte_offset + 0x10035a34) = 0;
			*(char*) (entity_slot_byte_offset + 0x100358ad) = 1;
			*(int*) (entity_slot_byte_offset + 0x10035a2c) = (int) 0xffffffff;
			*(int*) (entity_slot_byte_offset + 0x10035aac) = (int) 0xffffffff;
			*(short*) (entity_slot_byte_offset + 0x100358f0) = 0x7fff;
			slot_scan_idx_or_capacity = 0;
			do {
				*(char*) (slot_scan_idx_or_capacity + 0x80 + (int) new_entity_slot_ptr) = *((char*) matched_production_record + slot_scan_idx_or_capacity + 0x24) >> 1;
				slot_scan_idx_or_capacity = slot_scan_idx_or_capacity + 1;
			} while (slot_scan_idx_or_capacity < 5);
			*(char*) (entity_slot_byte_offset + 0x100358a9) = *((char*) matched_production_record + 0x38);
			strcpy((char*) (entity_slot_byte_offset + 0x100358d0), (char*) matched_production_record + 4);
			strcpy((char*) (entity_slot_byte_offset + 0x100358e0), (char*) matched_production_record + 0x14);
			*(int*) (entity_slot_byte_offset + 0x100358b0) = 0;
			random_float = RandomFloat01();
			*(int*) (entity_slot_byte_offset + 0x100358b8) = 0;
			*(int*) (entity_slot_byte_offset + 0x100358bc) = 0x447a0000;
			*(int*) (entity_slot_byte_offset + 0x100358c0) = 0;
			*(int*) (entity_slot_byte_offset + 0x100358c4) = 0;
			*(int*) (entity_slot_byte_offset + 0x100358c8) = 0;
			*(int*) (entity_slot_byte_offset + 0x100358cc) = 0;
			relationship_loop_idx = 0;
			slot_scan_idx_or_capacity = 0;
			*(float*) (entity_slot_byte_offset + 0x100358b4) =
				DAT_10025680 / (float) (random_float * (double) DAT_100257c8 + (double) DAT_100257c4);
			do {
				entity_slot_index = *new_entity_slot_ptr;
				rand_relationship_val = (char) crt_rand_range(0x40);
				*(char*) (entity_slot_index + slot_scan_idx_or_capacity + 0x1014d8e0) = 0;
				*(char*) (entity_slot_index + slot_scan_idx_or_capacity + 0x100a9820) = rand_relationship_val - 0x20;
				entity_slot_byte_offset = *new_entity_slot_ptr * 0x300 + relationship_loop_idx;
				rand_relationship_val = (char) crt_rand_range(0x40);
				slot_scan_idx_or_capacity = slot_scan_idx_or_capacity + 0x300;
				relationship_loop_idx = relationship_loop_idx + 1;
				*(char*) (entity_slot_byte_offset + 0x100a9820) = rand_relationship_val - 0x20;
				*(char*) (entity_slot_byte_offset + 0x1014d8e0) = 0;
			} while (slot_scan_idx_or_capacity < 0x90000);
			if (*matched_production_record == *(int*) (production_slot_entry_ptr + 4)) {
				slot_scan_idx_or_capacity = *(int*) (*(int*) (param_1 + 0xc) * 4 + 0x1002574c);
				if (0 < slot_scan_idx_or_capacity) {
					search_loop_idx = 0;
					production_record_walker = *(int**) (production_slot_entry_ptr + 0x10);
					do {
						if (*production_record_walker != -1 && *production_record_walker != *matched_production_record) {
							*(int*) (production_slot_entry_ptr + 4) = *production_record_walker;
							goto code_r0x10011fcd;
						}
						search_loop_idx = search_loop_idx + 1;
						production_record_walker = production_record_walker + 0x11;
					} while (search_loop_idx < slot_scan_idx_or_capacity);
				}
				*(int*) (production_slot_entry_ptr + 4) = (int) 0xffffffff;
				*(short*) (production_slot_entry_ptr + 8) = (short) 0xffff;
			}
		code_r0x10011fcd:
			production_record_walker = matched_production_record;
			for (search_loop_idx = 0x11; search_loop_idx != 0; search_loop_idx = search_loop_idx - 1) {
				*production_record_walker = 0;
				production_record_walker = production_record_walker + 1;
			}
			*matched_production_record = -1;
			return (unsigned int) *new_entity_slot_ptr;
		}
	}
	return 0xffff;
}
