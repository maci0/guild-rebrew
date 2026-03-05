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
extern unsigned int func_1001a0d0(int);
extern unsigned int func_1001b564(void);
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
	int iVar1;
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
		iVar1 = *(int*) (param_1 + 4);
		if (iVar1 == 1 && param_3 >= 8) {
			goto ret_zero;
		}
		if (iVar1 == 2 && param_3 >= 0xc) {
			goto ret_zero;
		}
		if (iVar1 == 3 && param_3 >= 0x10) {
			goto ret_zero;
		}
		base = *(int*) (param_1 + 8);
		goto ret_value;
	}
	if (param_2 == 1) {
		if (check_slot_active(param_1, 1) == 0) {
			goto ret_zero;
		}
		iVar1 = *(int*) (param_1 + 4);
		if (iVar1 == 1 && param_3 >= 4) {
			goto ret_zero;
		}
		if (iVar1 == 2 && param_3 >= 6) {
			goto ret_zero;
		}
		if (iVar1 == 3 && param_3 >= 8) {
			goto ret_zero;
		}
		base = *(int*) (param_1 + 0xc);
		goto ret_value;
	}
	if (param_2 == 2) {
		if (check_slot_active(param_1, 2) == 0) {
			goto ret_zero;
		}
		iVar1 = *(int*) (param_1 + 4);
		if (iVar1 == 1) {
			goto ret_zero;
		}
		if (iVar1 == 2 && param_3 >= 2) {
			goto ret_zero;
		}
		if (iVar1 == 3 && param_3 >= 4) {
			goto ret_zero;
		}
		base = *(int*) (param_1 + 0x10);
		goto ret_value;
	}
	if (param_2 == 3) {
		if (check_slot_active(param_1, 3) == 0) {
			goto ret_zero;
		}
		iVar1 = *(int*) (param_1 + 4);
		if (iVar1 == 1) {
			goto ret_zero;
		}
		if (iVar1 == 2) {
			goto ret_zero;
		}
		if (iVar1 == 3 && param_3 >= 2) {
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
	unsigned char uVar1;
	unsigned int uVar2;
	short iVar3;
	unsigned char uVar4;
	int iVar5;
	unsigned int uVar6;
	int iVar7;
	int iVar8;
	char* pcVar;
	char cVar;

	uVar6 = *param_1;
	pcVar = *(char**) 0x100a8c30 + uVar6 + uVar6 * 0x24c;
	cVar = *pcVar;

	if (cVar == '\x1d') {
		uVar1 = *(unsigned char*) (pcVar + 0x247);
		if (uVar1 != 0 && uVar1 < 4) {
			iVar7 = 0;
			if (0 < param_2) {
				do {
					iVar5 = FindSlotEntryFiltered(0, param_1, 0, 0x10010700, 0);
					if (iVar5 == 0) {
						return iVar7;
					}
					*(*(unsigned int**) (iVar5 + 0x10)) = *(unsigned int*) 0x10030b6c;
					*(unsigned int*) 0x10030b6c = *(unsigned int*) 0x10030b6c + 1;
					uVar2 = *(*(unsigned int**) (iVar5 + 0x10));
					*(unsigned int*) (iVar5 + 8) = 0x7fff;
					*(unsigned int*) (iVar5 + 4) = uVar2;
					iVar3 = *(short*) 0x10035880;
					*(unsigned int*) (iVar5 + 0xc) = 0xff;
					*(unsigned int*) (iVar5 + 10) = iVar3 + 5;
					iVar8 = 0;
					do {
						func_1001a0d0(8);
						uVar4 = func_1001b564();
						iVar8 = iVar8 + 1;
						*(*(char**) (iVar5 + 0x10) + 0x23 + iVar8) = uVar4;
					} while (iVar8 < 5);
					uVar6 = func_1001a0d0(9);
					*(*(char**) (iVar5 + 0x10) + 0x2c) = (uVar6 & 0xffff) + 1;
					uVar6 = func_1001a0d0(2);
					*(*(char**) (iVar5 + 0x10) + 0x30) = (uVar6 & 0xffff) + 1;
					uVar6 = func_1001a0d0(0x5e);
					*(*(char**) (iVar5 + 0x10) + 0x34) = (uVar6 & 0xffff) + 1;
					uVar6 = func_1001a0d0(4);
					*(*(char**) (iVar5 + 0x10) + 0x40) = (*(short*) 0x10035880 - (uVar6 & 0xffff)) + -1;
					uVar6 = func_1001a0d0(2);
					*(*(char**) (iVar5 + 0x10) + 0x38) = uVar6 & 0xffff;
					func_1001a0d0(0x10);
					func_1001a0d0(0x10);
					func_1001a0d0(0x10);
					iVar7 = iVar7 + 1;
				} while (iVar7 < param_2);
			}
			return iVar7;
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
	int iVar1;
	int iVar2;
	unsigned int uVar3;
	int iVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	unsigned int* puVar8;
	unsigned int* puVar9;
	int iStack_8;

	uVar3 = *param_1;
	iVar1 = *(int*) (param_1 + 0x65);
	iVar4 = *(int*) 0x100a8c30 + uVar3 + uVar3 * 0x24c;
	if ((((*(char*) (*(int*) 0x100a8c30 + uVar3 + uVar3 * 0x24c) == '\x1d') && (iVar1 != 0)) &&
		 (*(int*) (iVar1 + 4) < 3)) &&
		(*(char*) (iVar4 + 0x247) - *(int*) (iVar1 + 4) == 1)) {
		param_1[0x65] = 0;
		param_1[0x66] = 0;
		param_1[0x67] = 0;
		param_1[0x68] = 0;
		iVar2 = AllocGraveyardField(param_1);
		if (iVar2 != 0) {
			if (*(char*) (iVar4 + 0x247) == '\x02') {
				iStack_8 = 0;
				iVar6 = 8;
				iVar7 = 4;
				puVar8 = *(unsigned int**) (*(int*) (iVar1 + 8) + 0x10);
				puVar9 = *(unsigned int**) (*(int*) (iVar2 + 8) + 0x10);
				for (iVar4 = 0x88; iVar4 != 0; iVar4 = iVar4 + -1) {
					*puVar9 = *puVar8;
					puVar8 = puVar8 + 1;
					puVar9 = puVar9 + 1;
				}
				iVar4 = *(int*) (iVar2 + 0xc);
				puVar8 = *(unsigned int**) (*(int*) (iVar1 + 0xc) + 0x10);
			}
			else {
				iStack_8 = 2;
				puVar8 = *(unsigned int**) (*(int*) (iVar1 + 8) + 0x10);
				puVar9 = *(unsigned int**) (*(int*) (iVar2 + 8) + 0x10);
				for (iVar4 = 0xcc; iVar4 != 0; iVar4 = iVar4 + -1) {
					*puVar9 = *puVar8;
					puVar8 = puVar8 + 1;
					puVar9 = puVar9 + 1;
				}
				iVar6 = 0xc;
				puVar8 = *(unsigned int**) (*(int*) (iVar1 + 0xc) + 0x10);
				puVar9 = *(unsigned int**) (*(int*) (iVar2 + 0xc) + 0x10);
				for (iVar4 = 0xcc; iVar4 != 0; iVar4 = iVar4 + -1) {
					*puVar9 = *puVar8;
					puVar8 = puVar8 + 1;
					puVar9 = puVar9 + 1;
				}
				iVar4 = *(int*) (iVar2 + 0x10);
				iVar7 = 6;
				puVar8 = *(unsigned int**) (*(int*) (iVar1 + 0x10) + 0x10);
			}
			puVar9 = *(unsigned int**) (iVar4 + 0x10);
			for (iVar5 = 0x88; iVar5 != 0; iVar5 = iVar5 + -1) {
				*puVar9 = *puVar8;
				puVar8 = puVar8 + 1;
				puVar9 = puVar9 + 1;
			}
			if ((*(int*) (iVar1 + 8) != 0) && (iVar6 != 0)) {
				iVar4 = 0;
				do {
					*(int*) (*(int*) (iVar2 + 8) + iVar4) = *(int*) (iVar4 + *(int*) (iVar1 + 8));
					*(int*) (*(int*) (iVar2 + 8) + 4 + iVar4) = *(int*) (iVar4 + 4 + *(int*) (iVar1 + 8));
					*(int*) (*(int*) (iVar2 + 8) + 8 + iVar4) = *(int*) (iVar4 + 8 + *(int*) (iVar1 + 8));
					*(short*) (*(int*) (iVar2 + 8) + 10 + iVar4) = *(short*) (iVar4 + 10 + *(int*) (iVar1 + 8));
					*(char*) (*(int*) (iVar2 + 8) + 0xc + iVar4) = *(char*) (iVar4 + 0xc + *(int*) (iVar1 + 8));
					iVar4 = iVar4 + 0x14;
					iVar6 = iVar6 + -1;
				} while (iVar6 != 0);
			}
			if ((*(int*) (iVar1 + 0xc) != 0) && (iVar7 != 0)) {
				iVar4 = 0;
				do {
					*(int*) (iVar4 + *(int*) (iVar2 + 0xc)) = *(int*) (iVar4 + *(int*) (iVar1 + 0xc));
					*(int*) (iVar4 + 4 + *(int*) (iVar2 + 0xc)) = *(int*) (iVar4 + 4 + *(int*) (iVar1 + 0xc));
					*(int*) (iVar4 + 8 + *(int*) (iVar2 + 0xc)) = *(int*) (iVar4 + 8 + *(int*) (iVar1 + 0xc));
					*(short*) (iVar4 + 10 + *(int*) (iVar2 + 0xc)) = *(short*) (iVar4 + 10 + *(int*) (iVar1 + 0xc));
					*(char*) (iVar4 + 0xc + *(int*) (iVar2 + 0xc)) = *(char*) (iVar4 + 0xc + *(int*) (iVar1 + 0xc));
					iVar4 = iVar4 + 0x14;
					iVar7 = iVar7 + -1;
				} while (iVar7 != 0);
			}
			if ((*(int*) (iVar1 + 0x10) != 0) && (iStack_8 != 0)) {
				iVar4 = 0;
				do {
					*(int*) (iVar4 + *(int*) (iVar2 + 0x10)) = *(int*) (iVar4 + *(int*) (iVar1 + 0x10));
					*(int*) (iVar4 + 4 + *(int*) (iVar2 + 0x10)) = *(int*) (iVar4 + 4 + *(int*) (iVar1 + 0x10));
					*(int*) (iVar4 + 8 + *(int*) (iVar2 + 0x10)) = *(int*) (iVar4 + 8 + *(int*) (iVar1 + 0x10));
					*(short*) (iVar4 + 10 + *(int*) (iVar2 + 0x10)) = *(short*) (iVar4 + 10 + *(int*) (iVar1 + 0x10));
					*(char*) (iVar4 + 0xc + *(int*) (iVar2 + 0x10)) = *(char*) (iVar4 + 0xc + *(int*) (iVar1 + 0x10));
					iVar4 = iVar4 + 0x14;
					iStack_8 = iStack_8 + -1;
				} while (iStack_8 != 0);
			}
			*(int*) (iVar2 + 0x18) = *(int*) (iVar1 + 0x18);
			*(char*) (iVar2 + 0x19) = *(char*) (iVar1 + 0x19);
			*(char*) (iVar2 + 0x1a) = *(char*) (iVar1 + 0x1a);
			*(char*) (iVar2 + 0x1b) = *(char*) (iVar1 + 0x1b);
			free_3fields(iVar1);
			return *(unsigned int*) (param_1 + 0x65);
		}
		*(unsigned int*) (param_1 + 0x65) = iVar1;
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
	char cVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	int* piVar5;
	unsigned int uVar6;
	unsigned int uVar7;
	int* piVar8;
	int* piVar9;
	char* pcVar10;
	char* pcVar11;
	unsigned char* puStack_4;

	iVar2 = param_1;
	ResolveEntityById(&puStack_4, 0, 0, *(unsigned int*) (param_1 + 8));
	if (((puStack_4 == 0) || (*(unsigned short*) (puStack_4 + 0x27) == 0xffff)) ||
		(*(unsigned short*) (puStack_4 + 0x27) * 0x21c + *(unsigned int*) 0x100358a0 == *(unsigned int*) 0x1003546c)) {
		return 0xffffffff;
	}
	if (*(*(char**) 0x100a8c30 + *puStack_4 * 0x24d) != '\x1d') {
		return 0xfffffffe;
	}
	iVar4 = *(unsigned int*) (puStack_4 + 0x65);
	if (iVar4 == 0) {
		return 0xfffffffd;
	}
	iVar3 = check_slot_active(iVar4, *(int*) (iVar2 + 0xc));
	if (iVar3 == 0) {
		return 0xfffffffc;
	}
	ResolveEntityById(0, 0, (int*) &param_1, *(unsigned int*) (iVar2 + 4));
	if (param_1 == 0) {
		return 0xfffffffa;
	}
	iVar4 = GetSlotEntry(iVar4, *(int*) (iVar2 + 0xc), *(int*) (iVar2 + 0x10));
	if ((iVar4 == 0) || (*(unsigned int*) (iVar4 + 8) != *(unsigned int*) (param_1 + 0x50))) {
		return 0xfffffff9;
	}
	piVar9 = *(int**) (iVar4 + 0x10);
	iVar4 = 0;
	iVar2 = *(int*) (*(int*) (iVar2 + 0xc) * 4 + 0x1002574c);
	piVar5 = piVar9;
	piVar8 = piVar9;
	if (0 < iVar2) {
		do {
			if (*piVar8 == -1) {
				break;
			}
			if (*piVar5 == -1) {
				piVar8 = piVar9 + iVar4 * 0x11;
				break;
			}
			if (piVar5[0x10] < piVar8[0x10]) {
				piVar8 = piVar5;
			}
			iVar4 = iVar4 + 1;
			piVar5 = piVar5 + 0x11;
		} while (iVar4 < iVar2);
	}
	*piVar8 = *(unsigned int*) (param_1 + 4);
	uVar6 = 0xffffffff;
	pcVar10 = (char*) (param_1 + 0x30);
	do {
		pcVar11 = pcVar10;
		if (uVar6 == 0) {
			break;
		}
		uVar6 = uVar6 - 1;
		pcVar11 = pcVar10 + 1;
		cVar1 = *pcVar10;
		pcVar10 = pcVar11;
	} while (cVar1 != '\0');
	uVar6 = ~uVar6;
	piVar5 = (int*) (pcVar11 + -uVar6);
	piVar9 = piVar8;
	for (uVar7 = uVar6 >> 2; piVar9 = piVar9 + 1, uVar7 != 0; uVar7 = uVar7 - 1) {
		*piVar9 = *piVar5;
		piVar5 = piVar5 + 1;
	}
	for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
		*piVar9 = *piVar5;
		piVar5 = piVar5 + 1;
		piVar9 = piVar9 + 1;
	}
	uVar6 = 0xffffffff;
	pcVar10 = (char*) (param_1 + 0x40);
	do {
		pcVar11 = pcVar10;
		if (uVar6 == 0) {
			break;
		}
		uVar6 = uVar6 - 1;
		pcVar11 = pcVar10 + 1;
		cVar1 = *pcVar10;
		pcVar10 = pcVar11;
	} while (cVar1 != '\0');
	uVar6 = ~uVar6;
	piVar9 = (int*) (pcVar11 + -uVar6);
	piVar5 = piVar8 + 5;
	for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
		*piVar5 = *piVar9;
		piVar9 = piVar9 + 1;
		piVar5 = piVar5 + 1;
	}
	for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
		*piVar5 = *piVar9;
		piVar9 = piVar9 + 1;
		piVar5 = piVar5 + 1;
	}
	piVar8[9] = *(unsigned int*) (param_1 + 0x80);
	*(piVar8 + 10) = *(unsigned int*) (param_1 + 0x84);
	piVar8[0xb] = *(unsigned int*) (param_1 + 0x167);
	piVar8[0xc] = *(unsigned int*) (param_1 + 0xd);
	piVar8[0xd] = *(unsigned int*) (param_1 + 0x164);
	piVar8[0xe] = *(unsigned int*) (param_1 + 9);
	piVar8[0x10] = *(unsigned int*) 0x10035880;
	piVar8[0xf] = *(unsigned int*) (param_1 + 0x18c);
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
	int iVar1;
	int iVar2;
	unsigned int uVar3;
	short iVar4;
	int iVar5;
	int iVar6;
	unsigned char* puStack_4;

	iVar1 = param_1;
	ResolveEntityById(&puStack_4, 0, 0, *(unsigned int*) (param_1 + 8));
	if (((puStack_4 == 0) || (*(unsigned short*) (puStack_4 + 0x27) == 0xffff)) ||
		(*(unsigned short*) (puStack_4 + 0x27) * 0x21c + *(unsigned int*) 0x100358a0 == *(unsigned int*) 0x1003546c)) {
		return 0xffffffff;
	}
	if (*(*(char**) 0x100a8c30 + *puStack_4 * 0x24d) != '\x1d') {
		return 0xfffffffe;
	}
	if (*(unsigned int*) (puStack_4 + 0x65) == 0) {
		return 0xfffffffd;
	}
	iVar2 = check_slot_active(*(unsigned int*) (puStack_4 + 0x65), *(int*) (iVar1 + 0xc));
	if (iVar2 == 0) {
		return 0xfffffffc;
	}
	ResolveEntityById(0, 0, (int*) &param_1, *(unsigned int*) (iVar1 + 4));
	if (param_1 == 0) {
		return 0xfffffffa;
	}
	iVar2 = *(int*) (iVar1 + 0xc);
	if ((-1 < iVar2) && (iVar2 < 4)) {
		iVar2 = FindSlotEntryFiltered(param_1, puStack_4, 0, 0x10010700, iVar2);
		if (iVar2 == 0) {
			return 0xfffffff9;
		}
		*(unsigned int*) (iVar2 + 4) = *(unsigned int*) (param_1 + 4);
		*(unsigned int*) (iVar2 + 8) = *(unsigned int*) (param_1 + 0x50);
		iVar4 = *(short*) (iVar1 + 0x11) + *(short*) 0x10035880;
		*(unsigned char*) (iVar2 + 0xc) = 0xff;
		*(short*) (iVar2 + 10) = iVar4;
		iVar5 = 0;
		if (0 < *(int*) (*(int*) (iVar1 + 0xc) * 4 + 0x1002574c)) {
			iVar6 = 0;
			do {
				iVar5 = iVar5 + 1;
				*(unsigned int*) (*(int*) (iVar2 + 0x10) + iVar6) = 0xffffffff;
				iVar6 = iVar6 + 0x44;
			} while (iVar5 < *(int*) (*(int*) (iVar1 + 0xc) * 4 + 0x1002574c));
		}
		if (0 < *(int*) (iVar1 + 0x13)) {
			SubtractObjectAmountNoKill(
				*(unsigned int*) (param_1 + 4),
				*(unsigned int*) (*(unsigned int*) 0x10035439 * 0x2f4 + 0x100a8c94),
				*(unsigned int*) (iVar1 + 0x13)
			);
			uVar3 = func_1001b564();
			AddOrAccumulateObject(
				*(unsigned int*) (*(unsigned short*) (puStack_4 + 0x27) * 0x21c + 0x100358a4),
				*(unsigned int*) (*(unsigned int*) 0x10035439 * 0x2f4 + 0x100a8c94),
				uVar3
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
	unsigned int* iVar1;
	int iVar2;
	int iVar3;
	unsigned int uVar4;
	unsigned char* puStack_4;

	iVar1 = param_1;
	ResolveEntityById(&puStack_4, 0, 0, *(param_1 + 8));
	if (((puStack_4 == 0) || (*(unsigned short*) (puStack_4 + 0x27) == 0xffff)) ||
		((*(unsigned short*) (puStack_4 + 0x27) * 0x21c + *(unsigned int*) 0x100358a0) ==
		 *(unsigned int*) 0x1003546c)) {
		return 0xffffffff;
	}
	if (*(*(char**) 0x100a8c30 + *puStack_4 * 0x24d) != '\x1d') {
		return 0xfffffffe;
	}
	iVar3 = *(unsigned int*) (puStack_4 + 0x65);
	if (iVar3 == 0) {
		return 0xfffffffd;
	}
	iVar2 = check_slot_active(iVar3, *(iVar1 + 0xc));
	if (iVar2 == 0) {
		return 0xfffffffc;
	}
	ResolveEntityById(0, 0, (int*) &param_1, *(iVar1 + 4));
	if (param_1 == 0) {
		return 0xfffffffa;
	}
	iVar3 = GetSlotEntry(iVar3, *(iVar1 + 0xc), *(iVar1 + 0x10));
	if (iVar3 == 0) {
		return 0xfffffff9;
	}
	*(unsigned int*) (iVar3 + 10) = *(unsigned int*) (iVar3 + 10) + *(iVar1 + 0x11);
	if (0 < (int) *(iVar1 + 0x13)) {
		SubtractObjectAmountNoKill(
			*(param_1 + 4),
			*(*(unsigned int**) 0x100a8c94 + *(unsigned int*) 0x10035439 * 0x2f4),
			*(iVar1 + 0x13)
		);
		uVar4 = func_1001b564();
		AddOrAccumulateObject(
			*(*(unsigned int**) 0x100358a4 + *(unsigned short*) (puStack_4 + 0x27) * 0x21c),
			*(*(unsigned int**) 0x100a8c94 + *(unsigned int*) 0x10035439 * 0x2f4),
			uVar4
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
	unsigned char* pbVar1;
	int iVar2;
	int iVar3;
	int uVar4;
	unsigned short uVar5;
	void* local_4;

	uVar4 = -1;
	uVar5 = 0xffff;
	pbVar1 = param_1;
	ResolveEntityById((void**) &param_1, (void**) 0, (void**) 0, *(int*) (param_1 + 8));
	if (((param_1 == (unsigned char*) 0) || (*(unsigned short*) (param_1 + 0x27) == 0xffff)) ||
		((char*) &DAT_100358a0 + (unsigned int) *(unsigned short*) (param_1 + 0x27) * 0x10e == (char*) DAT_1003546c)) {
		return -1;
	}
	if (*(char*) (DAT_100a8c30 + (unsigned int) *param_1 * 0x24d) != 0x1d) {
		return -2;
	}
	iVar3 = *(int*) (param_1 + 0x65);
	if (iVar3 == 0) {
		return -3;
	}
	iVar2 = check_slot_active(iVar3, *(int*) (pbVar1 + 0xc));
	if (iVar2 == 0) {
		return -4;
	}
	if (*(int*) (pbVar1 + 4) != -1) {
		ResolveEntityById((void**) 0, (void**) 0, &local_4, *(int*) (pbVar1 + 4));
		if (local_4 == (void*) 0) {
			return -6;
		}
		uVar4 = *(int*) (pbVar1 + 4);
		uVar5 = *(unsigned short*) ((int) local_4 + 0x50);
	}
	iVar3 = GetSlotEntry(iVar3, *(int*) (pbVar1 + 0xc), (int) *(char*) (pbVar1 + 0x10));
	if (iVar3 == 0) {
		return -7;
	}
	*(unsigned short*) (iVar3 + 8) = uVar5;
	*(int*) (iVar3 + 4) = uVar4;
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
	unsigned char* pbVar1;
	int iVar2;
	int iVar3;
	unsigned int uVar4;

	pbVar1 = param_1;
	ResolveEntityById((void**) &param_1, (void**) 0, (void**) 0, *(int*) (param_1 + 8));
	if (((param_1 == (unsigned char*) 0) || (*(unsigned short*) (param_1 + 0x27) == 0xffff)) ||
		((char*) &DAT_100358a0 + (unsigned int) *(unsigned short*) (param_1 + 0x27) * 0x10e == (char*) DAT_1003546c)) {
		return -1;
	}
	if (*(char*) (DAT_100a8c30 + (unsigned int) *param_1 * 0x24d) != 0x1d) {
		return -2;
	}
	iVar3 = *(int*) (param_1 + 0x65);
	if (iVar3 == 0) {
		return -3;
	}
	iVar2 = check_slot_active(iVar3, *(int*) (pbVar1 + 0xc));
	if (iVar2 == 0) {
		return -4;
	}
	iVar3 = GetSlotEntry(iVar3, *(int*) (pbVar1 + 0xc), pbVar1[0x10]);
	if (iVar3 == 0) {
		return -7;
	}
	uVar4 = *(int*) (pbVar1 + 0x13) + (unsigned int) *(unsigned char*) (iVar3 + 0xc);
	uVar4 = uVar4 & ((int) uVar4 <= 0) - 1;
	if ((int) uVar4 >= 0xff) {
		uVar4 = 0xff;
	}
	*(char*) (iVar3 + 0xc) = (char) uVar4;
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
	int* piVar6;
	int iVar3;
	int iVar2;
	unsigned char* puStack_4;
	int piStack_10;
	int iStack_4;

	iVar3 = param_1;
	ResolveEntityById(0, 0, &param_1, *(int*) iVar3);
	if (param_1 == 0) {
		return 0xfffffffa;
	}
	ResolveEntityById((int) &puStack_4, 0, 0, *(int*) (iVar3 + 4));
	if (((puStack_4 == 0) || (*(unsigned short*) (puStack_4 + 0x27) == 0xffff)) ||
		(*(unsigned short*) (puStack_4 + 0x27) * 0x21c + *(unsigned int*) 0x100358a0 == *(unsigned int*) 0x1003546c)) {
		return 0xffffffff;
	}
	if (*(*(char**) 0x100a8c30 + *puStack_4 * 0x24d) != '\x1d') {
		return 0xfffffffe;
	}
	iVar2 = *(int*) (puStack_4 + 0x65);
	if (iVar2 == 0) {
		return 0xfffffffd;
	}
	iVar2 = check_slot_active(iVar2, *(int*) (iVar3 + 8));
	if (iVar2 == 0) {
		return 0xfffffffc;
	}
	iVar2 = GetSlotEntry(*(int*) (puStack_4 + 0x65), *(int*) (iVar3 + 8), (int) *(unsigned char*) (iVar3 + 0xc));
	if ((iVar2 != 0) && (*(unsigned short*) (iVar2 + 8) == *(unsigned short*) (param_1 + 0x50))) {
		int iStack_8;

		piVar6 = *(int**) (iVar2 + 0x10);
		piStack_10 = *(int*) (*(int*) (iVar3 + 8) * 4 + 0x1002574c);
		iStack_8 = iVar2;
		iStack_4 = FindSlotEntryFiltered(param_1, (int) puStack_4, 0, 0x10010700, *(int*) (iVar3 + 0xd));
		if (iStack_4 != 0) {
			int* piVar5;
			int* piVar7;
			int* piVar8;
			int iVar9;
			piVar5 = *(int**) (iStack_4 + 0x10);
			piVar8 = piVar5 + *(int*) (*(int*) (iVar3 + 0xd) * 4 + 0x1002574c) * 0x11;
			piStack_10 = (int) (piVar6 + piStack_10 * 0x11);
			for (; piVar5 < piVar8; piVar5 = piVar5 + 0x11) {
				if (*piVar5 == -1) {
					while (1) {
						if ((int*) piStack_10 <= piVar6) {
							goto code_r0x10011b0d;
						}
						if (*piVar6 != -1) {
							break;
						}
						piVar6 = piVar6 + 0x11;
					}
					{
						int* pSrc = piVar6;
						int* pDst = piVar5;
						for (iVar9 = 0x11; iVar9 != 0; iVar9 = iVar9 + -1) {
							*pDst = *pSrc;
							pSrc = pSrc + 1;
							pDst = pDst + 1;
						}
					}
					piVar7 = piVar6;
					for (iVar9 = 0x11; iVar9 != 0; iVar9 = iVar9 + -1) {
						*piVar7 = 0;
						piVar7 = piVar7 + 1;
					}
					*piVar6 = -1;
					iVar2 = iStack_8;
					if ((int*) piStack_10 <= piVar6) {
						break;
					}
				}
			}
		code_r0x10011b0d:
			*(int*) (iStack_4 + 4) = *(int*) (iVar2 + 4);
			*(int*) (iVar2 + 4) = 0xffffffff;
			*(unsigned short*) (iStack_4 + 8) = *(unsigned short*) (iVar2 + 8);
			*(unsigned short*) (iVar2 + 8) = 0xffff;
			*(unsigned short*) (iStack_4 + 0xa) = (unsigned short) (*(unsigned short*) 0x10035880 + 0xa);
			*(unsigned char*) (iStack_4 + 0xc) = 0xff;
			*(unsigned short*) (iVar2 + 0xa) = 0xff;
			*(int*) (iVar3 + 0x15) = *(int*) 0x10030b6c;
			if (0 < *(int*) (iVar3 + 0x11)) {
				unsigned int uVar4;
				SubtractObjectAmountNoKill(
					*(unsigned int*) (param_1 + 4),
					*(unsigned int*) ((unsigned char*) 0x100a8c94 + *(unsigned int*) 0x10035439 * 0x2f4),
					*(unsigned int*) (iVar3 + 0x11)
				);
				uVar4 = (unsigned int) ((int) *(int*) (iVar3 + 0x11) * ((float*) 0x1002572c)[*(int*) (iVar3 + 0xd)]);
				AddOrAccumulateObject(
					*(unsigned int*) ((unsigned char*) 0x100358a4 + *(unsigned short*) (puStack_4 + 0x27) * 0x21c),
					*(unsigned int*) ((unsigned char*) 0x100a8c94 + *(unsigned int*) 0x10035439 * 0x2f4),
					uVar4
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
	unsigned short* puVar1;
	unsigned short uVar2;
	char cVar5;
	int iVar6;
	int* piVar7;
	short* piVar8;
	char* pcVar9;
	int* piVar10;
	int iVar11;
	int iVar14;
	int iVar15;
	unsigned int* puVar16;
	unsigned short* puVar17;
	double fVar20;
	int iStack_c;
	unsigned char* puStack_8;
	int iStack_4;

	if (*(int*) (param_1 + 0x15) != 0x1b && *(int*) (param_1 + 0x15) != 0x1c) {
		return 0xfffffffa;
	}
	iVar14 = 0;
	ResolveEntityById(&puStack_8, 0, 0, *(unsigned int*) (param_1 + 8));
	if (puStack_8 == 0 || *(unsigned short*) (puStack_8 + 0x27) == 0xffff ||
		*(unsigned short*) (puStack_8 + 0x27) * 0x21c + (int) &DAT_100358a0 == DAT_1003546c) {
		return 0xffffffff;
	}
	if (*(char*) (DAT_100a8c30 + (unsigned int) *puStack_8 * 0x24d) != '\x1d') {
		return 0xfffffffe;
	}
	iVar15 = *(int*) (puStack_8 + 0x65);
	if (iVar15 == 0) {
		return 0xfffffffd;
	}
	iVar6 = check_slot_active(iVar15, *(int*) (param_1 + 0xc));
	if (iVar6 == 0) {
		return 0xfffffffc;
	}
	iStack_4 = GetSlotEntry(iVar15, *(int*) (param_1 + 0xc), *(unsigned char*) (param_1 + 0x10));
	if (iStack_4 == 0) {
		return 0xffff;
	}
	iVar6 = 0;
	iVar15 = *(int*) (*(int*) (param_1 + 0xc) * 4 + 0x1002574c);
	if (0 < iVar15) {
		piVar10 = *(int**) (iStack_4 + 0x10);
		do {
			piVar7 = piVar10;
			if (*piVar7 == *(int*) (param_1 + 0x11)) {
				break;
			}
			iVar6 = iVar6 + 1;
			piVar10 = piVar7 + 0x11;
		} while (iVar6 < iVar15);
		if (piVar7 != 0 && *piVar7 == *(int*) (param_1 + 0x11)) {
			iVar15 = 0;
			piVar8 = (short*) &DAT_100358a0;
			do {
				if (*piVar8 == -1) {
					break;
				}
				piVar8 = piVar8 + 0x10e;
				iVar15 = iVar15 + 1;
			} while (piVar8 < (short*) 0x1009aca0);
			if (iVar15 == 0x300) {
				iVar15 = 0;
				pcVar9 = (char*) 0x100358a2;
				do {
					if (*pcVar9 == '\x0f') {
						break;
					}
					pcVar9 = pcVar9 + 0x21c;
					iVar15 = iVar15 + 1;
				} while (pcVar9 < (char*) 0x1009aca2);
				if (iVar15 == 0x300) {
					LogMessageInternal(
						"D:\\Develop\\DieGildeAddOn\\game\\friedhof_logic.c",
						0x6ef,
						"gv_ExAllocGraveyardWorker: array overflow...",
						1
					);
					return 0xffff;
				}
			}
			iVar6 = iVar15 * 0x21c;
			if (*(char*) (iVar6 + 0x100358a2) == '\x0f') {
				DAT_10035434 = DAT_10035434 - 1;
			}
			puVar1 = (unsigned short*) (iVar6 + (int) &DAT_100358a0);
			puVar17 = puVar1;
			for (iVar11 = 0x87; iVar11 != 0; iVar11 = iVar11 - 1) {
				puVar17[0] = 0;
				puVar17[1] = 0;
				puVar17 = puVar17 + 2;
			}
			*puVar1 = 0xffff;
			*(int*) (iVar6 + 0x100358a4) = (int) 0xffffffff;
			puVar16 = (unsigned int*) (iVar6 + 0x100358fc);
			for (iVar11 = 8; iVar11 != 0; iVar11 = iVar11 - 1) {
				*puVar16 = 0xffffffff;
				puVar16 = puVar16 + 1;
			}
			*(unsigned char**) (iVar6 + 0x10035a10) = puStack_8;
			*(unsigned char**) (iVar6 + 0x10035a0c) = puStack_8;
			DAT_10035434 = DAT_10035434 + 1;
			*(int*) (iVar6 + 0x100358a4) = DAT_10030b6c;
			DAT_10030b6c = DAT_10030b6c + 1;
			*puVar1 = (unsigned short) iVar15;
			*(char*) (iVar6 + 0x100358a2) = 0x14;
			*(int*) (iVar6 + 0x10035a90) = 0;
			*(int*) (iVar6 + 0x10035ab0) = (int) 0xffffffff;
			*(char*) (iVar6 + 0x10035ab5) = 0;
			*(char*) (iVar6 + 0x10035ab6) = 0;
			*(char*) (iVar6 + 0x10035ab7) = 0;
			*(char*) (iVar6 + 0x10035ab8) = 1;
			*(int*) (iVar6 + 0x10035a84) = 0x3f800000;
			*(short*) (iVar6 + 0x100358a8) = 100;
			*(short*) (iVar6 + 0x100358aa) = 0x10;
			*(char*) (iVar6 + 0x10035a04) = 0;
			*(char*) (iVar6 + 0x10035a06) = 0;
			*(char*) (iVar6 + 0x10035a05) = *(char*) (param_1 + 0x15);
			*(int*) (iVar6 + 0x10035a94) = 0;
			*(int*) (iVar6 + 0x10035a30) = 4;
			*(int*) (iVar6 + 0x10035a34) = 0;
			*(char*) (iVar6 + 0x100358ad) = 1;
			*(int*) (iVar6 + 0x10035a2c) = (int) 0xffffffff;
			*(int*) (iVar6 + 0x10035aac) = (int) 0xffffffff;
			*(short*) (iVar6 + 0x100358f0) = 0x7fff;
			iVar15 = 0;
			do {
				*(char*) (iVar15 + 0x80 + (int) puVar1) = *((char*) piVar7 + iVar15 + 0x24) >> 1;
				iVar15 = iVar15 + 1;
			} while (iVar15 < 5);
			*(char*) (iVar6 + 0x100358a9) = *((char*) piVar7 + 0x38);
			strcpy((char*) (iVar6 + 0x100358d0), (char*) piVar7 + 4);
			strcpy((char*) (iVar6 + 0x100358e0), (char*) piVar7 + 0x14);
			*(int*) (iVar6 + 0x100358b0) = 0;
			fVar20 = RandomFloat01();
			*(int*) (iVar6 + 0x100358b8) = 0;
			*(int*) (iVar6 + 0x100358bc) = 0x447a0000;
			*(int*) (iVar6 + 0x100358c0) = 0;
			*(int*) (iVar6 + 0x100358c4) = 0;
			*(int*) (iVar6 + 0x100358c8) = 0;
			*(int*) (iVar6 + 0x100358cc) = 0;
			iStack_c = 0;
			iVar15 = 0;
			*(float*) (iVar6 + 0x100358b4) =
				DAT_10025680 / (float) (fVar20 * (double) DAT_100257c8 + (double) DAT_100257c4);
			do {
				uVar2 = *puVar1;
				cVar5 = (char) crt_rand_range(0x40);
				*(char*) (uVar2 + iVar15 + 0x1014d8e0) = 0;
				*(char*) (uVar2 + iVar15 + 0x100a9820) = cVar5 - 0x20;
				iVar6 = *puVar1 * 0x300 + iStack_c;
				cVar5 = (char) crt_rand_range(0x40);
				iVar15 = iVar15 + 0x300;
				iStack_c = iStack_c + 1;
				*(char*) (iVar6 + 0x100a9820) = cVar5 - 0x20;
				*(char*) (iVar6 + 0x1014d8e0) = 0;
			} while (iVar15 < 0x90000);
			if (*piVar7 == *(int*) (iStack_4 + 4)) {
				iVar15 = *(int*) (*(int*) (param_1 + 0xc) * 4 + 0x1002574c);
				if (0 < iVar15) {
					iVar14 = 0;
					piVar10 = *(int**) (iStack_4 + 0x10);
					do {
						if (*piVar10 != -1 && *piVar10 != *piVar7) {
							*(int*) (iStack_4 + 4) = *piVar10;
							goto code_r0x10011fcd;
						}
						iVar14 = iVar14 + 1;
						piVar10 = piVar10 + 0x11;
					} while (iVar14 < iVar15);
				}
				*(int*) (iStack_4 + 4) = (int) 0xffffffff;
				*(short*) (iStack_4 + 8) = (short) 0xffff;
			}
		code_r0x10011fcd:
			piVar10 = piVar7;
			for (iVar14 = 0x11; iVar14 != 0; iVar14 = iVar14 - 1) {
				*piVar10 = 0;
				piVar10 = piVar10 + 1;
			}
			*piVar7 = -1;
			return (unsigned int) *puVar1;
		}
	}
	return 0xffff;
}
