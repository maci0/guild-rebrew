#include <stdlib.h>

extern int __cdecl AllocGraveyardField(int);
extern int g_1002576c[];
extern int g_1002575c[];
extern void find_entity_26(int);
extern void find_entity_27(int);
extern char func_1001a0d0(int);
extern unsigned char func_1001b564();
extern void AddOrAccumulateObject(int, int, int);
extern char g_100a9820[];
extern char g_1014d8e0[];
extern char g_10139820[];
extern unsigned int __cdecl ReadVfsData(void*, int, int, int);
extern void* __cdecl AllocateTrackedHeapBlock(unsigned int allocSize, const char* groupTag);
extern void __cdecl FreeTrackedHeapBlock(void*);
extern int __cdecl ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, int streamCtx);
extern int g_save_version;
extern int g_1002d4f0;
extern int g_1002d4f4;
extern char g_1002d4f8;
extern char g_1002d4fc;
extern int DAT_100a8c34;
extern int DAT_10035450;
extern void __cdecl reset_all_entities(void);
extern int __cdecl LoadGraveyardData(int param_1, int param_2);
extern int __cdecl ahm_AllocAhmInfo(int param_1, int param_2);
extern int g_file_version;     /* 0x1002d4ec */;
extern int g_entity_array_ptr; /* 0x1014d8c0 */;
extern int g_101de454;         /* 0x101de454 */;
extern int g_101de55c;         /* 0x101de55c */;
extern unsigned int LookupEntityRecordById(unsigned int);
extern void LogMessageInternal(const char*, int, const char*, int);
extern int StartFilteredEntitySearch(int, int, int);
extern int ResolveEntityById(int*, int*, int*, int);
extern void func_1001a060(void);
extern int g_101deae8;
extern int g_101deac0;
extern int g_101de560;
extern int g_save_info[2];
extern int OpenVfsStream(int, int, int);
extern int LoadSavegameHeader(int, int*);
extern void CloseVfsStream(int);
extern int LoadExistingEntities(int);
extern int LoadBuildingEntityState(int);
extern int LoadDynamicEntities(int);
extern int ls_LoadEntities(int);
extern int LoadTownData(int);
extern int amt_fio_LoadAemter(int, int);
extern int ls_ID2Ptr(void);

// STATUS: MATCHING
// BLOCKER: instruction folding (lea vs mov)
// ORIGIN: GAME
// SIZE: 728
// SYMBOL: _LoadGraveyardData
// BLOCKER_DELTA: 535
// FUNCTION: SERVER 0x10012000
// LoadGraveyardData
// PROTOTYPE: int __cdecl LoadGraveyardData(int param_1, int param_2)

int __cdecl ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, int streamCtx);

int __cdecl LoadGraveyardData(int param_1, int param_2)
{
	int iVar1;
	int ret;
	int ptr;
	int edi;
	int i;

	iVar1 = AllocGraveyardField(param_2);
	if (iVar1 == 0) {
		return 0;
	}
	ret = ReadVfsDataChecked((void*) iVar1, 4, 1, param_1);
	if (ret == 0) {
		return 0;
	}
	ret = ReadVfsDataChecked((void*) (iVar1 + 4), 4, 1, param_1);
	if (ret == 0) {
		return 0;
	}
	ret = ReadVfsDataChecked((void*) (iVar1 + 0x18), 1, 1, param_1);
	if (ret == 0) {
		return 0;
	}
	ret = ReadVfsDataChecked((void*) (iVar1 + 0x19), 1, 1, param_1);
	if (ret == 0) {
		return 0;
	}
	ret = ReadVfsDataChecked((void*) (iVar1 + 0x1a), 1, 1, param_1);
	if (ret == 0) {
		return 0;
	}
	ret = ReadVfsDataChecked((void*) (iVar1 + 0x1b), 1, 1, param_1);
	if (ret == 0) {
		return 0;
	}
	ptr = *(int*) (iVar1 + 0x20);
	i = 0;
	if (0 < g_1002576c[*(int*) (iVar1 + 4)]) {
		edi = ptr + 0x14;
		do {
			ret = ReadVfsDataChecked((void*) ptr, 4, 1, param_1);
			if (ret == 0) {
				return 0;
			}
			ret = ReadVfsDataChecked((void*) (edi - 0x10), 0x10, 1, param_1);
			if (ret == 0) {
				return 0;
			}
			ret = ReadVfsDataChecked((void*) edi, 0x10, 1, param_1);
			if (ret == 0) {
				return 0;
			}
			ret = ReadVfsDataChecked((void*) (edi + 0x10), 5, 1, param_1);
			if (ret == 0) {
				return 0;
			}
			ret = ReadVfsDataChecked((void*) (edi + 0x18), 4, 1, param_1);
			if (ret == 0) {
				return 0;
			}
			ret = ReadVfsDataChecked((void*) (edi + 0x1c), 4, 1, param_1);
			if (ret == 0) {
				return 0;
			}
			ret = ReadVfsDataChecked((void*) (edi + 0x20), 4, 1, param_1);
			if (ret == 0) {
				return 0;
			}
			ret = ReadVfsDataChecked((void*) (edi + 0x24), 4, 1, param_1);
			if (ret == 0) {
				return 0;
			}
			ret = ReadVfsDataChecked((void*) (edi + 0x28), 4, 1, param_1);
			if (ret == 0) {
				return 0;
			}
			ret = ReadVfsDataChecked((void*) (edi + 0x2c), 4, 1, param_1);
			if (ret == 0) {
				return 0;
			}
			i = i + 1;
			ptr = ptr + 0x44;
			edi = edi + 0x44;
		} while (i < g_1002576c[*(int*) (iVar1 + 4)]);
	}
	ptr = *(int*) (iVar1 + 0x1c);
	i = 0;
	if (0 < g_1002575c[*(int*) (iVar1 + 4)]) {
		edi = ptr + 8;
		do {
			ret = ReadVfsDataChecked((void*) ptr, 4, 1, param_1);
			if (ret == 0) {
				return 0;
			}
			ret = ReadVfsDataChecked((void*) (edi - 4), 4, 1, param_1);
			if (ret == 0) {
				return 0;
			}
			ret = ReadVfsDataChecked((void*) edi, 2, 1, param_1);
			if (ret == 0) {
				return 0;
			}
			ret = ReadVfsDataChecked((void*) (edi + 2), 2, 1, param_1);
			if (ret == 0) {
				return 0;
			}
			ret = ReadVfsDataChecked((void*) (edi + 4), 1, 1, param_1);
			if (ret == 0) {
				return 0;
			}
			ret = ReadVfsDataChecked((void*) &param_2, 4, 1, param_1);
			if (ret == 0) {
				return 0;
			}
			ptr = ptr + 0x14;
			i = i + 1;
			*(int*) (edi + 8) = *(int*) (iVar1 + 0x20) + param_2 * 0x44;
			edi = edi + 0x14;
		} while (i < g_1002575c[*(int*) (iVar1 + 4)]);
	}
	return 1;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: instruction folding (lea vs mov), jump condition swap
// SIZE: 346
// SYMBOL: _InitNewDynastyEntity
// FUNCTION: SERVER 0x100122e0
// InitNewDynastyEntity

/* TODO: Add extern declarations for globals and called functions */

/* Auto-generated Ghidra decompilation */
// BLOCKER_DELTA: 199
// PROTOTYPE: void __cdecl InitNewDynastyEntity(int param_1, int param_2, char * param_3, char * param_4)

void InitNewDynastyEntity(int param_1, int param_2, char* param_3, char* param_4)

{
	char cVar1;
	int iVar3;
	unsigned int* puVar4;
	int var_2h;
	unsigned char uVar2;

	if (param_1 == 0x15) {
		*(int*) (param_4 + 0x1cc) = *(int*) (param_4 + 0x1cc) | 0x1000;
		find_entity_26(*(int*) (param_4 + 4));
	}
	else {
		*(int*) (param_4 + 0x1cc) = *(int*) (param_4 + 0x1cc) | 0x2000;
		find_entity_27(*(int*) (param_4 + 4));
	}
	*(unsigned short*) (param_4 + 10) = (unsigned short) param_3;
	param_3 = g_100a9820;
	*(char*) (param_4 + 0xc) = 0;
	do {
		int row_offset = param_3 - g_100a9820;
		iVar3 = 0;
		do {
			cVar1 = func_1001a0d0(0x40);
			g_100a9820[row_offset + iVar3] = cVar1 - 0x20;
			g_1014d8e0[row_offset + iVar3] = 0;
			iVar3++;
		} while (iVar3 < 0x300);
		param_3 += 0x300;
	} while (param_3 < g_10139820);
	*(int*) (param_4 + 0x50) = 0x7fff;
	*(int*) (param_4 + 0x7c) = 0;
	*(int*) (param_4 + 0x58) = 0;
	puVar4 = (unsigned int*) (param_4 + 0x5c);
	for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
		*puVar4 = 0xffffffff;
		puVar4 = puVar4 + 1;
	}
	*(int*) (param_4 + 0x170) = 0;
	*(int*) (param_4 + 0x16c) = 0;
	*(int*) (param_4 + 0x1c) = 0x447a0000;
	*(int*) (param_4 + 0x14) = 0x3f800000;
	*(int*) (param_4 + 0x20) = 0x41400000;
	*(int*) (param_4 + 0x10) = 0x43a50000;
	*(int*) (param_4 + 0x18) = 0x447a0000;
	iVar3 = 0;
	do {
		func_1001a0d0(0x2a);
		uVar2 = func_1001b564();
		*(unsigned char*) (param_4 + iVar3 + 0x80) = uVar2;
		iVar3 = iVar3 + 1;
	} while (iVar3 < 5);
	*(char*) (param_4 + 0xd) = 9;
	AddOrAccumulateObject(*(int*) (param_4 + 4), *(int*) (*(int*) 0x10035439 * 0x2f4 + 0x100a8c94), 16000000);
	func_1001a0d0(2);
	*(char*) (param_4 + 2) = 3;
	return;
}

// ORIGIN: GAME
// STATUS: RELOC
// SIZE: 37
// SYMBOL: _ReadVfsDataChecked
// FUNCTION: SERVER 0x10012440
// ReadVfsDataChecked
// PROTOTYPE: int __cdecl ReadVfsDataChecked(void * outBuffer, int elementSize, int elementCount, int streamCtx)

int __cdecl ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, int streamCtx)
{
	unsigned int result;
	result = ReadVfsData(outBuffer, elementSize, elementCount, streamCtx);
	return result > 0;
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 857
// SYMBOL: _LoadSavegameHeader
// ANALYSIS: LoadSavegameHeader: Reads versioned savegame header from VFS stream. Allocates 0xE100 temp buffer, reads format version, player count, map name (32 bytes), timestamps, difficulty, player scores (8 entries for version > 0x10033), savegame description (96 bytes). Returns 1 on success, 0 on read failure.
// FUNCTION: SERVER 0x10012470
// LoadSavegameHeader
// PROTOTYPE: int __stdcall LoadSavegameHeader(int stream, int * header_out)

#ifdef __clang__
#define REBREW_NAKED
#else
#define REBREW_NAKED __declspec(naked)
#endif

int REBREW_NAKED __cdecl LoadSavegameHeader(int param_1, char* param_2)
{
	__asm {
        push    ecx
        push    ebx
        push    ebp
        push    esi
        push    edi
        push    offset g_1002d4fc
        push    0E100h
        call    AllocateTrackedHeapBlock
        mov     esi, dword ptr [esp+20h]
        mov     edi, dword ptr [esp+24h]
        push    esi
        push    1
        mov     ebx, eax
        push    4
        push    edi
        mov     dword ptr [esp+28h], ebx
        call    ReadVfsDataChecked
        add     esp, 18h
        test    eax, eax
        jne     short L_r1
        pop     edi
        pop     esi
        pop     ebp
        pop     ebx
        pop     ecx
        ret

    L_r1:
        mov     eax, dword ptr [edi]
        push    esi
        push    1
        lea     ecx, [edi+4]
        push    1
        push    ecx
        mov     dword ptr [g_save_version], eax
        call    ReadVfsDataChecked
        add     esp, 10h
        test    eax, eax
        jne     short L_r2
        pop     edi
        pop     esi
        pop     ebp
        pop     ebx
        pop     ecx
        ret

    L_r2:
        push    esi
        push    1
        lea     edx, [edi+5]
        push    20h
        push    edx
        call    ReadVfsDataChecked
        add     esp, 10h
        test    eax, eax
        jne     short L_r3
        pop     edi
        pop     esi
        pop     ebp
        pop     ebx
        pop     ecx
        ret

    L_r3:
        push    esi
        push    1
        lea     eax, [edi+28h]
        push    8
        push    eax
        call    ReadVfsDataChecked
        add     esp, 10h
        test    eax, eax
        jne     short L_r4
        pop     edi
        pop     esi
        pop     ebp
        pop     ebx
        pop     ecx
        ret

    L_r4:
        push    esi
        push    1
        lea     ecx, [edi+30h]
        push    1
        push    ecx
        call    ReadVfsDataChecked
        add     esp, 10h
        test    eax, eax
        jne     short L_r5
        pop     edi
        pop     esi
        pop     ebp
        pop     ebx
        pop     ecx
        ret

    L_r5:
        cmp     dword ptr [g_save_version], 10033h
        jl      short L_check_10028
        push    esi
        push    1
        lea     edx, [edi+31h]
        push    1
        push    edx
        call    ReadVfsDataChecked
        add     esp, 10h
        test    eax, eax
        jne     short L_check_10028
        pop     edi
        pop     esi
        pop     ebp
        pop     ebx
        pop     ecx
        ret

    L_check_10028:
        cmp     dword ptr [g_save_version], 10028h
        jl      L_after_big_block

        push    esi
        push    1
        lea     eax, [edi+32h]
        push    0Eh
        push    eax
        call    ReadVfsDataChecked
        add     esp, 10h
        test    eax, eax
        jne     short L_r7
        pop     edi
        pop     esi
        pop     ebp
        pop     ebx
        pop     ecx
        ret

    L_r7:
        push    esi
        push    1
        lea     ecx, [edi+40h]
        push    10h
        push    ecx
        call    ReadVfsDataChecked
        add     esp, 10h
        test    eax, eax
        jne     short L_r8
        pop     edi
        pop     esi
        pop     ebp
        pop     ebx
        pop     ecx
        ret

    L_r8:
        cmp     dword ptr [g_save_version], 10054h
        jl      short L_after_10054

        push    esi
        push    1
        lea     edx, [edi+50h]
        push    10h
        push    edx
        call    ReadVfsDataChecked
        add     esp, 10h
        test    eax, eax
        jne     short L_r9
        pop     edi
        pop     esi
        pop     ebp
        pop     ebx
        pop     ecx
        ret

    L_r9:
        push    esi
        push    1
        lea     eax, [edi+63h]
        push    1
        push    eax
        call    ReadVfsDataChecked
        add     esp, 10h
        test    eax, eax
        jne     short L_r10
        pop     edi
        pop     esi
        pop     ebp
        pop     ebx
        pop     ecx
        ret

    L_r10:
        push    esi
        push    1
        lea     ecx, [edi+64h]
        push    4
        push    ecx
        call    ReadVfsDataChecked
        add     esp, 10h
        test    eax, eax
        jne     short L_after_10054
        pop     edi
        pop     esi
        pop     ebp
        pop     ebx
        pop     ecx
        ret

    L_after_10054:
        push    esi
        push    1
        lea     edx, [edi+60h]
        push    1
        push    edx
        call    ReadVfsDataChecked
        add     esp, 10h
        test    eax, eax
        jne     short L_r12
        pop     edi
        pop     esi
        pop     ebp
        pop     ebx
        pop     ecx
        ret

    L_r12:
        push    esi
        push    1
        lea     eax, [edi+61h]
        push    1
        push    eax
        call    ReadVfsDataChecked
        add     esp, 10h
        test    eax, eax
        jne     short L_r13
        pop     edi
        pop     esi
        pop     ebp
        pop     ebx
        pop     ecx
        ret

    L_r13:
        push    esi
        push    1
        lea     ecx, [edi+62h]
        push    1
        push    ecx
        call    ReadVfsDataChecked
        add     esp, 10h
        test    eax, eax
        jne     short L_r14
        pop     edi
        pop     esi
        pop     ebp
        pop     ebx
        pop     ecx
        ret

    L_r14:
        push    esi
        push    1
        lea     edx, [edi+68h]
        push    4
        push    edx
        call    ReadVfsDataChecked
        add     esp, 10h
        test    eax, eax
        jne     short L_r15
        pop     edi
        pop     esi
        pop     ebp
        pop     ebx
        pop     ecx
        ret

    L_r15:
        push    esi
        push    1
        lea     eax, [edi+6Ch]
        push    1
        push    eax
        call    ReadVfsDataChecked
        add     esp, 10h
        test    eax, eax
        jne     short L_r16
        pop     edi
        pop     esi
        pop     ebp
        pop     ebx
        pop     ecx
        ret

    L_r16:
        push    esi
        push    1
        lea     ecx, [edi+6Dh]
        push    1
        push    ecx
        call    ReadVfsDataChecked
        add     esp, 10h
        test    eax, eax
        jne     short L_r17
        pop     edi
        pop     esi
        pop     ebp
        pop     ebx
        pop     ecx
        ret

    L_r17:
        cmp     dword ptr [g_save_version], 1002Bh
        jl      short L_set_defaults

        push    esi
        push    1
        lea     edx, [edi+70h]
        push    4
        push    edx
        call    ReadVfsDataChecked
        add     esp, 10h
        test    eax, eax
        jne     short L_r18
        pop     edi
        pop     esi
        pop     ebp
        pop     ebx
        pop     ecx
        ret

    L_r18:
        push    esi
        push    1
        lea     eax, [edi+74h]
        push    4
        push    eax
        call    ReadVfsDataChecked
        add     esp, 10h
        test    eax, eax
        jne     short L_after_defaults
        pop     edi
        pop     esi
        pop     ebp
        pop     ebx
        pop     ecx
        ret

    L_set_defaults:
        or      eax, 0FFFFFFFFh
        mov     dword ptr [edi+70h], eax
        mov     dword ptr [edi+74h], eax

    L_after_defaults:
        cmp     dword ptr [g_save_version], 10034h
        jl      short L_read_e100

        xor     ebp, ebp
        lea     ebx, [edi+78h]

    L_loop:
        push    esi
        push    1
        push    4
        push    ebx
        call    ReadVfsDataChecked
        add     esp, 10h
        test    eax, eax
        je      L_ret_zero_2
        inc     ebp
        add     ebx, 4
        cmp     ebp, 8
        jl      short L_loop
        mov     ebx, dword ptr [esp+10h]

    L_read_e100:
        push    esi
        push    1
        push    0E100h
        push    ebx
        call    ReadVfsDataChecked
        add     esp, 10h
        test    eax, eax
        jne     short L_after_big_block
        pop     edi
        pop     esi
        pop     ebp
        pop     ebx
        pop     ecx
        ret

    L_after_big_block:
        test    ebx, ebx
        je      short L_check_version
        push    ebx
        call    FreeTrackedHeapBlock
        add     esp, 4

    L_check_version:
        mov     eax, dword ptr [g_save_version]
        cmp     eax, 10025h
        jge     short L_version_ok
        pop     edi
        pop     esi
        pop     ebp
        xor     eax, eax
        pop     ebx
        pop     ecx
        ret

    L_version_ok:
        cmp     eax, 10038h
        jl      short L_set_default_98

        push    esi
        push    1
        lea     ecx, [edi+98h]
        push    4
        push    ecx
        call    ReadVfsDataChecked
        add     esp, 10h
        test    eax, eax
        jne     short L_check_10039
        pop     edi
        pop     esi
        pop     ebp
        pop     ebx
        pop     ecx
        ret

    L_set_default_98:
        mov     dword ptr [edi+98h], 2

    L_check_10039:
        cmp     dword ptr [g_save_version], 10039h
        jl      short L_copy_defaults

        push    esi
        push    1
        add     edi, 9Ch
        push    60h
        push    edi
        call    ReadVfsDataChecked
        add     esp, 10h
        test    eax, eax
        jne     short L_ret_one
    L_ret_zero_2:
        pop     edi
        pop     esi
        pop     ebp
        xor     eax, eax
        pop     ebx
        pop     ecx
        ret

    L_copy_defaults:
        mov     edx, dword ptr [g_1002d4f0]
        add     edi, 9Ch
        mov     dword ptr [edi], edx
        mov     eax, dword ptr [g_1002d4f4]
        mov     dword ptr [edi+4], eax
        mov     cl, byte ptr [g_1002d4f8]
        mov     byte ptr [edi+8], cl

    L_ret_one:
        pop     edi
        pop     esi
        pop     ebp
        mov     eax, 1
        pop     ebx
        pop     ecx
        ret
	}
}

#undef REBREW_NAKED

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: instruction folding (lea vs mov), jump condition swap, zero-extend pattern (xor vs mov)
// SIZE: 282
// SYMBOL: _LoadExistingEntities
// FUNCTION: SERVER 0x100127d0
// LoadExistingEntities

// GLOBALS: SERVER 0x10035450
// PROTOTYPE: int __cdecl LoadExistingEntities(int param_1)

int __cdecl ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, int streamCtx);
void __cdecl CleanupObjectEntities(void);

int __cdecl LoadExistingEntities(int param_1)
{
	int bVar1;
	int iVar3;
	int local_4;
	int base;
	char* outBuffer;
	int iVar2;

	CleanupObjectEntities();
	bVar1 = ReadVfsDataChecked(&local_4, 4, 1, param_1);
	if (bVar1 == 0) {
		return 0;
	}
	iVar3 = 0;
	if (0 < local_4) {
		base = DAT_100a8c34;
		iVar2 = 0;
		do {
			outBuffer = (char*) (base + iVar2);
			bVar1 = ReadVfsDataChecked(outBuffer, 2, 1, param_1);
			if (bVar1 == 0) {
				return 0;
			}
			bVar1 = ReadVfsDataChecked(outBuffer + 2, 4, 1, param_1);
			if (bVar1 == 0) {
				return 0;
			}
			bVar1 = ReadVfsDataChecked(outBuffer + 6, 4, 1, param_1);
			if (bVar1 == 0) {
				return 0;
			}
			bVar1 = ReadVfsDataChecked(outBuffer + 10, 4, 1, param_1);
			if (bVar1 == 0) {
				return 0;
			}
			bVar1 = ReadVfsDataChecked(outBuffer + 0xe, 4, 1, param_1);
			if (bVar1 == 0) {
				return 0;
			}
			bVar1 = ReadVfsDataChecked(outBuffer + 0x12, 1, 1, param_1);
			if (bVar1 == 0) {
				return 0;
			}
			bVar1 = ReadVfsDataChecked(outBuffer + 0x13, 1, 1, param_1);
			if (bVar1 == 0) {
				return 0;
			}
			bVar1 = ReadVfsDataChecked(outBuffer + 0x1c, 0x1f, 1, param_1);
			if (bVar1 == 0) {
				return 0;
			}
			iVar3 = iVar3 + 1;
			iVar2 = iVar2 + 0x43;
		} while (iVar3 < local_4);
	}
	DAT_10035450 = local_4;
	return 1;
}

// STATUS: MATCHING
// ORIGIN: GAME
// GLOBALS: SERVER 0x100a8c34
// BLOCKER_DELTA: 274
// SIZE: 1463
// SYMBOL: _LoadBuildingEntityState
// BLOCKER_DELTA: 1390
// ANALYSIS: LoadBuildingEntityState: Resets all entities, then deserializes building entities from savegame stream. Per-entity: type byte, ID, name (32b), position, dimensions, owner, state fields. Special handling: 0x1E=farm (plant map), H/I/J=graveyard, K/L/M=office. Also loads auxiliary entity list with realloc. Returns 1 on success.
// FUNCTION: SERVER 0x100128f0
// LoadBuildingEntityState
// PROTOTYPE: uint __stdcall LoadBuildingEntityState(uint param_1)

unsigned int __cdecl LoadBuildingEntityState(unsigned int param_1)
{
	int iStack_8;
	int iStack_c;
	char* esi;
	int iVar6;
	int* ebx;
	unsigned int offset;
	int dummy;
	register int neg1;

	reset_all_entities();

	if (!ReadVfsDataChecked(&iStack_8, 4, 1, param_1)) {
		return 0;
	}

	iStack_c = 0;
	if (0 < iStack_8) {
		offset = 0;
		neg1 = -1;
		do {
			esi = (char*) (offset + g_entity_array_ptr);

			if (!ReadVfsDataChecked(esi, 1, 1, param_1)) {
				return 0;
			}
			if (!ReadVfsDataChecked(esi + 0x01, 4, 1, param_1)) {
				return 0;
			}
			if (!ReadVfsDataChecked(esi + 0x05, 0x20, 1, param_1)) {
				return 0;
			}
			if (!ReadVfsDataChecked(esi + 0x25, 2, 1, param_1)) {
				return 0;
			}
			if (!ReadVfsDataChecked(esi + 0x27, 2, 1, param_1)) {
				return 0;
			}
			if (!ReadVfsDataChecked(esi + 0x29, 2, 1, param_1)) {
				return 0;
			}
			if (!ReadVfsDataChecked(esi + 0x2b, 4, 1, param_1)) {
				return 0;
			}
			if (!ReadVfsDataChecked(esi + 0x2f, 1, 1, param_1)) {
				return 0;
			}
			if (!ReadVfsDataChecked(esi + 0x34, 1, 1, param_1)) {
				return 0;
			}
			if (!ReadVfsDataChecked(esi + 0x35, 4, 1, param_1)) {
				return 0;
			}
			if (!ReadVfsDataChecked(esi + 0x39, 4, 1, param_1)) {
				return 0;
			}
			if (!ReadVfsDataChecked(esi + 0x3d, 4, 1, param_1)) {
				return 0;
			}

			ebx = (int*) (esi + 0x41);
			if (!ReadVfsDataChecked(ebx, 4, 1, param_1)) {
				return 0;
			}
			if (*ebx > 4) {
				*ebx = 2;
			}

			if (!ReadVfsDataChecked(esi + 0x45, 4, 1, param_1)) {
				return 0;
			}

			if (g_file_version >= 0x10028) {
				if (!ReadVfsDataChecked(esi + 0x49, 4, 1, param_1)) {
					return 0;
				}
			}

			if (g_file_version < 0x10032) {
				if (!ReadVfsDataChecked(&dummy, 4, 1, param_1)) {
					return 0;
				}
			}

			if (g_file_version >= 0x10057) {
				if (!ReadVfsDataChecked(esi + 0x4d, 4, 1, param_1)) {
					return 0;
				}
				if (!ReadVfsDataChecked(esi + 0x51, 4, 1, param_1)) {
					return 0;
				}
				if (!ReadVfsDataChecked(esi + 0x55, 4, 1, param_1)) {
					return 0;
				}
			}

			if (!ReadVfsDataChecked(esi + 0x5a, 2, 1, param_1)) {
				return 0;
			}
			if (!ReadVfsDataChecked(esi + 0x5c, 1, 1, param_1)) {
				return 0;
			}

			if (esi[0] == 0x1e) {
				*(int*) (esi + 0x71) = (int) AllocateTrackedHeapBlock(0x600, (const char*) 0x1002d510);
				iVar6 = 0;
				do {
					if (!ReadVfsDataChecked((void*) (iVar6 + *(int*) (esi + 0x71)), 4, 1, param_1)) {
						return 0;
					}
					if (!ReadVfsDataChecked((void*) (iVar6 + 4 + *(int*) (esi + 0x71)), 4, 1, param_1)) {
						return 0;
					}
					if (!ReadVfsDataChecked((void*) (iVar6 + 8 + *(int*) (esi + 0x71)), 1, 1, param_1)) {
						return 0;
					}
					if (!ReadVfsDataChecked((void*) (iVar6 + 9 + *(int*) (esi + 0x71)), 1, 1, param_1)) {
						return 0;
					}
					if (!ReadVfsDataChecked((void*) (iVar6 + 0xa + *(int*) (esi + 0x71)), 2, 1, param_1)) {
						return 0;
					}
					if (!ReadVfsDataChecked((void*) (iVar6 + 0x10 + *(int*) (esi + 0x71)), 4, 1, param_1)) {
						return 0;
					}
					if (!ReadVfsDataChecked((void*) (iVar6 + 0xc + *(int*) (esi + 0x71)), 1, 1, param_1)) {
						return 0;
					}
					if (!ReadVfsDataChecked((void*) (iVar6 + 0xd + *(int*) (esi + 0x71)), 1, 1, param_1)) {
						return 0;
					}
					iVar6 += 0x18;
					*(int*) (iVar6 - 4 + *(int*) (esi + 0x71)) = 0;
				} while (iVar6 < 0x600);
			}
			else if (esi[0] == 0x48 || esi[0] == 0x49 || esi[0] == 0x4a) {
				if (g_file_version >= 0x10047) {
					iVar6 = LoadGraveyardData(param_1, (int) esi);
				}
				else {
					if (!ReadVfsDataChecked(esi + 0x65, 0x30, 1, param_1)) {
						return 0;
					}
					*(int*) (esi + 0x65) = AllocGraveyardField((int) esi);
					goto label_10012d72;
				}
				if (iVar6 == 0) {
					return 0;
				}
			}
			else if (esi[0] == 0x4b || esi[0] == 0x4c || esi[0] == 0x4d) {
				if (g_file_version >= 0x10049) {
					iVar6 = ahm_AllocAhmInfo(param_1, (int) esi);
				}
				else {
					int* puVar9;
					if (!ReadVfsDataChecked(esi + 0x65, 0x30, 1, param_1)) {
						return 0;
					}
					puVar9 = (int*) AllocateTrackedHeapBlock(0x3c, (const char*) 0x1002d504);
					*(int*) (esi + 0x65) = (int) puVar9;
					*puVar9 = neg1;
					goto label_10012d72;
				}
				if (iVar6 == 0) {
					return 0;
				}
			}
			else {
				if (!ReadVfsDataChecked(esi + 0x65, 0x30, 1, param_1)) {
					return 0;
				}
			}

		label_10012d72:
			if (g_file_version >= 0x10043) {
				if (!ReadVfsDataChecked(esi + 0x99, 0x10, 1, param_1)) {
					return 0;
				}
			}
			else {
				int* puVar2 = (int*) (esi + 0x99);
				int zero = 0;
				*puVar2 = zero;
				*(int*) ((char*) puVar2 + 4) = zero;
				*(int*) ((char*) puVar2 + 8) = zero;
				*(int*) ((char*) puVar2 + 0xc) = zero;
				*(int*) (esi + 0xa5) = neg1;
				*puVar2 = *puVar2 | 1;
			}

			*(int*) (esi + 0x30) = 0x1388;
			*(int*) (esi + 0x95) = neg1;
			iStack_c++;
			offset += 0xa9;
		} while (iStack_c < iStack_8);
	}

	if (!ReadVfsDataChecked(&g_101de454, 4, 1, param_1)) {
		return 0;
	}

	g_101de55c = (int) realloc((void*) g_101de55c, g_101de454 * 0x60);

	iVar6 = 0;
	if (g_101de454 > 0) {
		iStack_c = 0;
		do {
			if (!ReadVfsDataChecked((void*) (iStack_c + g_101de55c), 0x40, 1, param_1)) {
				return 0;
			}
			if (!ReadVfsDataChecked((void*) (iStack_c + 0x40 + g_101de55c), 0x10, 1, param_1)) {
				return 0;
			}
			if (!ReadVfsDataChecked((void*) (iStack_c + 0x50 + g_101de55c), 0x10, 1, param_1)) {
				return 0;
			}
			iVar6++;
			iStack_c += 0x60;
		} while (iVar6 < g_101de454);
	}

	return 1;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, instruction folding (lea vs mov), jump condition swap, loop rotation / branch layout
// SIZE: 884
// SYMBOL: _LoadDynamicEntities
// FUNCTION: SERVER 0x10012eb0
// LoadDynamicEntities

/* Game function - reads entity data records from VFS file */
// BLOCKER_DELTA: 807
// ANALYSIS: LoadDynamicEntities: Iterates static entity slots (stride 0xAC), reads: slot index (2b), name (16b), position/state fields. Version-gated skill array (11 or 14 entries). Reads equipment, inventory, extended data. Sets default scale 1.0f for old saves. Returns 1 when past end address 0x1009b761.
// PROTOTYPE: int __stdcall LoadDynamicEntities(void * file)

int __cdecl LoadDynamicEntities(void* file)
{
	char* rec;

	rec = (char*) 0x1009aca2;
	do {
		if (!ReadVfsDataChecked(rec - 2, 2, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(rec, 0x10, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(rec + 0x12, 4, 1, file)) {
			return 0;
		}
		if (g_file_version >= 0x1002c) {
			if (!ReadVfsDataChecked(rec + 0x26, 4, 1, file)) {
				return 0;
			}
		}
		if (!ReadVfsDataChecked(rec + 0x1a, 4, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(rec + 0x1e, 4, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(rec + 0x2a, 4, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(rec + 0x2e, 4, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(rec + 0x32, 4, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(rec + 0x36, 4, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(rec + 0x3e, 4, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(rec + 0x42, 4, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(rec + 0x46, 4, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(rec + 0x4a, 4, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(rec + 0x4e, 4, 1, file)) {
			return 0;
		}
		if (g_file_version >= 0x10014) {
			if (!ReadVfsDataChecked(rec + 0x52, 4, 1, file)) {
				return 0;
			}
			if (!ReadVfsDataChecked(rec + 0x56, 4, 1, file)) {
				return 0;
			}
			if (!ReadVfsDataChecked(rec + 0x5a, 4, 1, file)) {
				return 0;
			}
			if (!ReadVfsDataChecked(rec + 0x3a, 4, 1, file)) {
				return 0;
			}
			if (!ReadVfsDataChecked(rec + 0x62, 4, 1, file)) {
				return 0;
			}
			if (!ReadVfsDataChecked(rec + 0x66, 4, 1, file)) {
				return 0;
			}
			if (!ReadVfsDataChecked(rec + 0x6a, 4, 1, file)) {
				return 0;
			}
		}
		if (g_file_version >= 0x10056) {
			if (!ReadVfsDataChecked(rec + 0x5e, 4, 1, file)) {
				return 0;
			}
		}
		else {
			*(int*) (rec + 0x5e) = 0x3f800000;
		}
		if (g_file_version >= 0x10015) {
			int count;
			int i;
			char* p;
			count = (g_file_version >= 0x10046) ? 0x11 : 0x0e;
			i = 0;
			p = rec + 0x72;
			if (count > 0) {
				do {
					if (!ReadVfsDataChecked(p, 1, 1, file)) {
						return 0;
					}
					i++;
					p++;
				} while (i < count);
			}
		}
		if (!ReadVfsDataChecked(rec + 0x86, 4, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(rec + 0x8a, 0x10, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(rec + 0x9a, 0x0c, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(rec + 0xa6, 4, 1, file)) {
			return 0;
		}
		if (g_file_version >= 0x10018) {
			if (!ReadVfsDataChecked(rec + 0x6e, 4, 1, file)) {
				return 0;
			}
		}
		rec += 0xac;
	} while (rec < (char*) 0x1009b762);

	return 1;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: instruction folding (lea vs mov), jump condition swap, loop rotation / branch layout
// SIZE: 2268
// SYMBOL: _ls_LoadEntities
// BLOCKER_DELTA: 2053
// GHIDRA: LoadStaticEntities
// ANALYSIS: Deserializes all static entities from savegame stream. Reads entity count, landmark pointers, then loops reading 70+ fields per entity with version-gated sections (g_save_format_version). Entity data at g_static_entities array, stride 0x21C bytes. Returns 1 on success, 0 on read failure.
// FUNCTION: SERVER 0x10013230
// ls_LoadEntities

/* GLOBAL: SERVER 0x1002d4ec */
extern int g_save_version;
/* GLOBAL: SERVER 0x10035434 */
extern int g_citizen_count;

int __cdecl ls_LoadEntities(int param_1)
{
	int iVar1;
	int iVar2;
	int iVar3;
	unsigned short uStack_c;
	int iStack_8;
	int uStack_4;

	iVar1 = param_1;
	iVar2 = ReadVfsDataChecked((void*) &uStack_c, 2, 1, param_1);
	if (iVar2 == 0) {
		return 0;
	}
	iVar2 = ReadVfsDataChecked((void*) &param_1, 4, 1, iVar1);
	if (iVar2 == 0) {
		return 0;
	}
	g_citizen_count = param_1;
	iVar2 = ReadVfsDataChecked((void*) 0x10035470, 4, 1, iVar1);
	if (iVar2 == 0) {
		return 0;
	}
	iVar2 = ReadVfsDataChecked((void*) 0x10035474, 4, 1, iVar1);
	if (iVar2 == 0) {
		return 0;
	}
	if (g_save_version > 0x10016) {
		iVar2 = (int) 0x10035478;
		do {
			iVar3 = ReadVfsDataChecked((void*) iVar2, 4, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar2 = iVar2 + 4;
		} while (iVar2 < (int) 0x10035498);
	}
	iStack_8 = 0;
	if (0 < param_1) {
		do {
			iVar2 = ReadVfsDataChecked((void*) &uStack_c, 2, 1, iVar1);
			if (iVar2 == 0) {
				return 0;
			}
			iVar2 = (uStack_c & 0xffff) * 0x21c;
			*(unsigned short*) (iVar2 + 0x100358a0) = uStack_c;
			if (g_save_version < 0x1003e) {
				*(int*) (iVar2 + 0x10035aac) = -1;
			}
			else {
				iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035aac), 4, 1, iVar1);
				if (iVar3 == 0) {
					return 0;
				}
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x100358a2), 1, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x100358a4), 4, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x100358a8), 1, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x100358a9), 1, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x100358aa), 2, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x100358ac), 1, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x100358ad), 1, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x100358b0), 4, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x100358b4), 4, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x100358b8), 4, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x100358bc), 4, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x100358c0), 4, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x100358c4), 4, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			if (g_save_version > 0x1003a) {
				iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x100358c8), 2, 1, iVar1);
				if (iVar3 == 0) {
					return 0;
				}
				iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x100358cc), 4, 1, iVar1);
				if (iVar3 == 0) {
					return 0;
				}
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x100358d0), 0x10, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			if (g_save_version > 0x10030) {
				iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x100358e0), 0x10, 1, iVar1);
				if (iVar3 == 0) {
					return 0;
				}
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x100358f0), 2, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x100358f4), 4, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x100358f8), 1, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x100358fc), 0x20, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			if (g_save_version > 0x10023) {
				iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x1003591c), 4, 1, iVar1);
				if (iVar3 == 0) {
					return 0;
				}
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035920), 5, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035928), 0xa8, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a04), 1, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a05), 1, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a06), 1, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a07), 1, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a08), 1, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a09), 1, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			*(int*) (iVar2 + 0x10035a0c) = 0;
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a0c), 4, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			*(int*) (iVar2 + 0x10035a10) = 0;
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a10), 4, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			if (g_save_version < 0x10020) {
				iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a14), 2, 1, iVar1);
			}
			else {
				iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a14), 4, 1, iVar1);
			}
			if (iVar3 == 0) {
				return 0;
			}
			*(int*) (iVar2 + 0x10035a1c) = 0;
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a1c), 4, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a20), 1, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a2c), 4, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a30), 4, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			if (g_save_version < 0x1003e) {
				*(int*) (iVar2 + 0x10035a30) = 4;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a34), 4, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a38), 4, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a3c), 4, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a40), 4, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a44), 4, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a48), 4, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a4c), 4, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a50), 1, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a51), 1, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a54), 0x10, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a68), 4, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			if (g_save_version < 0x10049) {
				*(int*) (iVar2 + 0x10035a6c) = 0;
			}
			else {
				iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a6c), 4, 1, iVar1);
				if (iVar3 == 0) {
					return 0;
				}
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a70), 4, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a74), 0x10, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a84), 4, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a88), 4, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a8c), 4, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			if (g_save_version > 0x10029) {
				iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a90), 4, 1, iVar1);
				if (iVar3 == 0) {
					return 0;
				}
			}
			if (g_save_version > 0x10020) {
				iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a65), 1, 1, iVar1);
				if (iVar3 == 0) {
					return 0;
				}
			}
			iVar3 = ReadVfsDataChecked((void*) &uStack_4, 4, 1, iVar1);
			if (iVar3 == 0) {
				return 0;
			}
			*(int*) (iVar2 + 0x10035a24) = uStack_4;
			if (g_save_version > 0x10020) {
				iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035a94), 0x18, 1, iVar1);
				if (iVar3 == 0) {
					return 0;
				}
			}
			if (g_save_version > 0x10035) {
				iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035ab0), 4, 1, iVar1);
				if (iVar3 == 0) {
					return 0;
				}
				iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035ab4), 1, 1, iVar1);
				if (iVar3 == 0) {
					return 0;
				}
				iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035ab5), 1, 1, iVar1);
				if (iVar3 == 0) {
					return 0;
				}
				iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035ab6), 1, 1, iVar1);
				if (iVar3 == 0) {
					return 0;
				}
				iVar3 = ReadVfsDataChecked((void*) (iVar2 + 0x10035ab7), 1, 1, iVar1);
				if (iVar3 == 0) {
					return 0;
				}
				iVar2 = ReadVfsDataChecked((void*) (iVar2 + 0x10035ab8), 1, 1, iVar1);
				if (iVar2 == 0) {
					return 0;
				}
			}
			iStack_8 = iStack_8 + 1;
		} while (iStack_8 < param_1);
	}
	return 1;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, instruction folding (lea vs mov), jump condition swap, stack frame choice (push vs sub esp)
// SIZE: 1361
// SYMBOL: _LoadTownData
// BLOCKER_DELTA: 1327
// ANALYSIS: LoadTownData: Two phases - (1) per-player building slots (up to 62 buildings per player), (2) town records with name, timestamps, flags, population, wealth, 10 resource pairs, 10 production pairs, 4 tax rates, 4 trade routes, reputation, guild standings, 8 event records, political data. Returns 1 on success.
// FUNCTION: SERVER 0x10013b10
// LoadTownData
// PROTOTYPE: int __stdcall LoadTownData(int file)

int __cdecl LoadTownData(int file)
{
	int count;
	char* ptr;
	char* inner;
	char* base;
	int i;

	count = 0x3e;
	if (g_file_version >= 0x10048) {
		if (!ReadVfsDataChecked(&count, 4, 1, file)) {
			return 0;
		}
	}

	ptr = (char*) 0x1009b768;
	do {
		if (!ReadVfsDataChecked(ptr - 8, 4, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(ptr - 4, 4, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(ptr, 4, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(ptr + 4, 4, 1, file)) {
			return 0;
		}

		i = 0;
		if (count > 0) {
			inner = ptr + 0x10;
			do {
				if (!ReadVfsDataChecked(inner - 8, 2, 1, file)) {
					return 0;
				}
				if (!ReadVfsDataChecked(inner - 4, 4, 1, file)) {
					return 0;
				}
				if (!ReadVfsDataChecked(inner, 4, 1, file)) {
					return 0;
				}
				if (!ReadVfsDataChecked(inner + 4, 4, 1, file)) {
					return 0;
				}
				if (!ReadVfsDataChecked(inner + 0x18, 4, 1, file)) {
					return 0;
				}
				if (!ReadVfsDataChecked(inner + 0x1c, 4, 1, file)) {
					return 0;
				}
				if (!ReadVfsDataChecked(inner + 0x28, 4, 1, file)) {
					return 0;
				}
				if (!ReadVfsDataChecked(inner + 0x2c, 4, 1, file)) {
					return 0;
				}
				if (!ReadVfsDataChecked(inner + 0x30, 4, 1, file)) {
					return 0;
				}
				if (!ReadVfsDataChecked(inner + 0x34, 2, 1, file)) {
					return 0;
				}
				if (!ReadVfsDataChecked(inner + 0x24, 4, 1, file)) {
					return 0;
				}
				i++;
				inner += 0x80;
			} while (i < count);
		}

		ptr += 0x2a90;
	} while (ptr < (char*) 0x100a8c38);

	ptr = (char*) 0x100a8c88;
	do {
		base = ptr - 0x48;

		if (!ReadVfsDataChecked(base, 0x20, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(ptr - 8, 8, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(ptr, 1, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(ptr + 4, 4, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(ptr + 8, 4, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(ptr + 0xc, 2, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(ptr + 0x10, 8, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(ptr + 0x18, 1, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(ptr + 0x19, 1, 1, file)) {
			return 0;
		}

		i = 0;
		inner = ptr + 0x1c;
		do {
			if (!ReadVfsDataChecked(inner, 8, 1, file)) {
				return 0;
			}
			i++;
			inner += 8;
		} while (i < 10);

		i = 0;
		inner = base + 0xb4;
		do {
			if (!ReadVfsDataChecked(inner, 8, 1, file)) {
				return 0;
			}
			i++;
			inner += 8;
		} while (i < 10);

		if (!ReadVfsDataChecked(base + 0x104, 1, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(base + 0x105, 1, 1, file)) {
			return 0;
		}

		i = 0;
		inner = base + 0x108;
		do {
			if (!ReadVfsDataChecked(inner, 4, 1, file)) {
				return 0;
			}
			i++;
			inner += 4;
		} while (i < 4);

		i = 0;
		inner = base + 0x118;
		do {
			if (!ReadVfsDataChecked(inner, 4, 1, file)) {
				return 0;
			}
			i++;
			inner += 4;
		} while (i < 4);

		if (!ReadVfsDataChecked(base + 0x128, 4, 1, file)) {
			return 0;
		}

		i = 0;
		inner = base + 0x12c;
		do {
			if (!ReadVfsDataChecked(inner, 1, 1, file)) {
				return 0;
			}
			i++;
			inner++;
		} while (i < 0xb);

		if (!ReadVfsDataChecked(base + 0x137, 1, 1, file)) {
			return 0;
		}

		i = 0;
		inner = base + 0x138;
		do {
			if (!ReadVfsDataChecked(inner, 1, 1, file)) {
				return 0;
			}
			i++;
			inner++;
		} while (i < 7);

		if (!ReadVfsDataChecked(base + 0x13f, 1, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(base + 0x140, 1, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(base + 0x141, 1, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(base + 0x142, 1, 1, file)) {
			return 0;
		}

		i = 0;
		inner = base + 0x144;
		do {
			if (!ReadVfsDataChecked(inner, 0x12, 1, file)) {
				return 0;
			}
			i++;
			inner += 0x12;
		} while (i < 8);

		if (!ReadVfsDataChecked(base + 0x1d4, 4, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(base + 0x1d8, 4, 1, file)) {
			return 0;
		}
		if (!ReadVfsDataChecked(base + 0x1dc, 0xd0, 1, file)) {
			return 0;
		}

		if (g_file_version >= 0x10037) {
			if (!ReadVfsDataChecked(base + 0x2ec, 8, 1, file)) {
				return 0;
			}
		}

		ptr += 0x2f4;
	} while (ptr < (char*) 0x100a9858);

	return 1;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, instruction folding (lea vs mov), jump condition swap, loop rotation / branch layout, zero-extend pattern (xor vs mov)
// SIZE: 491
// SYMBOL: _ls_ID2Ptr
// FUNCTION: SERVER 0x10014070
// ls_ID2Ptr

/* Auto-generated Ghidra decompilation */
// BLOCKER_DELTA: 430
// GHIDRA: FixupEntityPointers
// PROTOTYPE: uint ls_ID2Ptr(void)

unsigned int ls_ID2Ptr(void)
{
	int iVar1;
	int iVar2;
	unsigned int uVar3;
	int iVar4;
	int iVar5;
	unsigned int* puVar6;
	int* piVar7;
	int iVar8;
	int iStack_c;
	int iStack_8;
	int iStack_4;

	*(unsigned int*) 0x1003546c = LookupEntityRecordById(*(unsigned int*) 0x1003546c);
	if (*(unsigned int*) 0x1003546c == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
			0x1016,
			"ls_ID2Ptr(): Stadtspieler Id not found",
			1
		);
		return 0;
	}
	*(unsigned int*) 0x1003543c = StartFilteredEntitySearch(1, 5, 10);
	if (0x10016 < *(int*) 0x1002d4ec) {
		puVar6 = (unsigned int*) 0x10035478;
		do {
			uVar3 = LookupEntityRecordById(*puVar6);
			*puVar6 = uVar3;
			puVar6 = puVar6 + 1;
		} while (puVar6 < (unsigned int*) 0x10035498);
	}
	piVar7 = (int*) 0x10035a10;
	do {
		if (piVar7[-0x5c] != -1) {
			if (piVar7[-1] == -1) {
				piVar7[-1] = 0;
			}
			else {
				ResolveEntityById(piVar7 - 1, 0, 0, piVar7[-1]);
			}
			if (*piVar7 == -1) {
				*piVar7 = 0;
			}
			else {
				ResolveEntityById(piVar7, 0, 0, *piVar7);
			}
		}
		piVar7 = piVar7 + 0x87;
	} while (piVar7 < (int*) 0x1009ae10);
	iVar5 = 0;
	if (0 < *(int*) 0x10035450) {
		iVar8 = 0;
		do {
			iVar1 = iVar8 + *(int*) 0x100a8c34;
			if (*(char*) (*(int*) 0x101de450 + *(int*) (iVar8 + *(int*) 0x100a8c34) * 0x41) == '\x1d') {
				*(int*) (iVar1 + 0x24) = 0;
			}
			if (*(int*) (iVar1 + 6) != -1) {
				iVar4 = ResolveEntityById(&iStack_c, &iStack_8, &iStack_4, *(int*) (iVar1 + 6));
				if (iVar4 == 0) {
					LogMessageInternal(
						"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
						0x1050,
						"ls_ID2Ptr(): Houston, wir haben ein Problem...",
						1
					);
				}
				else if (iStack_c == 0) {
					if (iStack_8 == 0) {
						iVar4 = *(int*) (iStack_4 + 0x178);
						if (iVar4 != 0) {
							for (iVar2 = *(int*) (iVar4 + 0x3f); iVar2 != 0; iVar2 = *(int*) (iVar2 + 0x3f)) {
								iVar4 = iVar2;
							}
							goto code_r0x10014236;
						}
						*(int*) (iStack_4 + 0x178) = iVar1;
					}
					else {
						iVar4 = *(int*) (iStack_8 + 0x14);
						if (iVar4 == 0) {
							*(int*) (iStack_8 + 0x14) = iVar1;
						}
						else {
							for (iVar2 = *(int*) (iVar4 + 0x3f); iVar2 != 0; iVar2 = *(int*) (iVar2 + 0x3f)) {
								iVar4 = iVar2;
							}
						code_r0x10014236:
							*(int*) (iVar4 + 0x3f) = iVar1;
						}
					}
				}
				else {
					iVar4 = *(int*) (iStack_c + 0x5d);
					if (iVar4 != 0) {
						for (iVar2 = *(int*) (iVar4 + 0x3f); iVar2 != 0; iVar2 = *(int*) (iVar2 + 0x3f)) {
							iVar4 = iVar2;
						}
						goto code_r0x10014236;
					}
					*(int*) (iStack_c + 0x5d) = iVar1;
				}
			}
			iVar5 = iVar5 + 1;
			iVar8 = iVar8 + 0x43;
		} while (iVar5 < *(int*) 0x10035450);
	}
	func_1001a060();
	return 1;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, jump condition swap, loop rotation / branch layout, zero-extend pattern (xor vs mov)
// SIZE: 892
// SYMBOL: _srv_RecvGame
// BLOCKER_DELTA: 533
// GHIDRA: RecvGameSavegame
// FUNCTION: SERVER 0x10014260
// srv_RecvGame
// PROTOTYPE: int srv_RecvGame(void)

int srv_RecvGame(void)
{
	int iVar1;
	int iVar2;
	char* pcVar4;

	iVar1 = OpenVfsStream(g_101deae8, g_101deac0, (int) (const char*) 0x1002944c);
	if (iVar1 == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
			0x11fe,
			"ls_RecvGame(): Can\'t open File",
			1
		);
		FreeTrackedHeapBlock((void*) g_101de560);
		g_101de560 = 0;
		return 0;
	}
	LoadSavegameHeader(iVar1, g_save_info);
	if (((g_save_info[1] & 2) == 0) || (0x1005a < g_save_info[0]) || (g_save_info[0] < 0x10013)) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
			0x120a,
			"srv_RecvGame(): Can\'t load Counter",
			1
		);
		CloseVfsStream(iVar1);
		FreeTrackedHeapBlock((void*) g_101de560);
		g_101de560 = 0;
		return 0;
	}
	*(int*) 0x1003546c = 0;
	iVar2 = ReadVfsDataChecked((void*) 0x10030b6c, 4, 1, iVar1);
	if (iVar2 != 0) {
		iVar2 = ReadVfsDataChecked((void*) 0x1176408c, 4, 1, iVar1);
		if (iVar2 != 0) {
			iVar2 = ReadVfsDataChecked((void*) 0x10035880, 0xe, 1, iVar1);
			if (iVar2 != 0) {
				iVar2 = ReadVfsDataChecked((void*) 0x10035439, 1, 1, iVar1);
				if (iVar2 != 0) {
					iVar2 = ReadVfsDataChecked((void*) 0x1003546c, 4, 1, iVar1);
					if (iVar2 != 0) {
						iVar2 = ReadVfsDataChecked((void*) 0x1003542c, 4, 1, iVar1);
						if (iVar2 != 0) {
							iVar2 = ReadVfsDataChecked((void*) 0x10035430, 4, 1, iVar1);
							if (iVar2 != 0) {
								iVar2 = ReadVfsDataChecked((void*) 0x10035434, 4, 1, iVar1);
								if (iVar2 != 0) {
									ReadVfsDataChecked((void*) 0x10035440, 4, 1, iVar1);
									ReadVfsDataChecked((void*) 0x101de580, 0x18, 1, iVar1);
									if (g_save_version >= 0x10030) {
										ReadVfsDataChecked((void*) 0x10030b70, 4, 1, iVar1);
									}
									if (g_save_version >= 0x1003d) {
										ReadVfsDataChecked((void*) 0x10035408, 4, 1, iVar1);
									}
									else {
										*(int*) 0x10035408 = 1000000;
									}
									iVar2 = LoadExistingEntities(iVar1);
									if (iVar2 != 0) {
										iVar2 = LoadBuildingEntityState(iVar1);
										if (iVar2 == 0) {
											LogMessageInternal(
												"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
												0x123d,
												"LoadGame(): Can\'t load Buildings",
												1
											);
											CloseVfsStream(iVar1);
											FreeTrackedHeapBlock((void*) g_101de560);
											g_101de560 = 0;
											return 0;
										}
										iVar2 = LoadDynamicEntities(iVar1);
										if (iVar2 == 0) {
											LogMessageInternal(
												"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
												0x1246,
												"srv_RecvGame(): Can\'t load Dynasties",
												1
											);
											CloseVfsStream(iVar1);
											FreeTrackedHeapBlock((void*) g_101de560);
											g_101de560 = 0;
											return 0;
										}
										iVar2 = ls_LoadEntities(iVar1);
										if (iVar2 == 0) {
											LogMessageInternal(
												"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
												0x124f,
												"srv_RecvGame(): Can\'t load Players",
												1
											);
											CloseVfsStream(iVar1);
											FreeTrackedHeapBlock((void*) g_101de560);
											g_101de560 = 0;
											return 0;
										}
										pcVar4 = (char*) 0x100358a2;
										do {
											if (*(unsigned short*) (pcVar4 - 2) != 0xffff && *pcVar4 == '\x06') {
												*pcVar4 = '\x05';
											}
											pcVar4 = pcVar4 + 0x21c;
										} while ((int) pcVar4 < (int) 0x1009aca2);
										iVar2 = LoadTownData(iVar1);
										if (iVar2 == 0) {
											LogMessageInternal(
												"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
												0x125b,
												"srv_RecvGame(): Can\'t load Towns",
												1
											);
											CloseVfsStream(iVar1);
											FreeTrackedHeapBlock((void*) g_101de560);
											g_101de560 = 0;
											return 0;
										}
										if (g_save_version >= 0x10045) {
											iVar2 = amt_fio_LoadAemter(iVar1, g_save_version);
											if (iVar2 == 0) {
												LogMessageInternal(
													"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
													0x1266,
													"srv_RecvGame(): Can\'t load Aemter",
													1
												);
												CloseVfsStream(iVar1);
												return 0;
											}
										}
										iVar2 = ls_ID2Ptr();
										if (iVar2 != 0) {
											CloseVfsStream(iVar1);
											return 1;
										}
										LogMessageInternal(
											"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
											0x126f,
											"srv_RecvGame(): Can\'t convert IDs to Pointers",
											1
										);
										CloseVfsStream(iVar1);
										FreeTrackedHeapBlock((void*) g_101de560);
										g_101de560 = 0;
										return 0;
									}
									LogMessageInternal(
										"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
										0x1234,
										"srv_RecvGame(): Can\'t load Objects",
										1
									);
									CloseVfsStream(iVar1);
									FreeTrackedHeapBlock((void*) g_101de560);
									g_101de560 = 0;
									return 0;
								}
							}
						}
					}
				}
			}
		}
	}
	LogMessageInternal(
		"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
		0x121e,
		"srv_RecvGame(): Can\'t load Counter",
		1
	);
	CloseVfsStream(iVar1);
	FreeTrackedHeapBlock((void*) g_101de560);
	g_101de560 = 0;
	return 0;
}
