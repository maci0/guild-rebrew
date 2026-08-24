#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"
#include "../../Units/vfs/vfs.h"
#include "../game/entity.h"

#include <stdlib.h>

int __cdecl AllocGraveyardField(int);
extern void amt_FindEntity26(int);
extern void amt_FindEntity27(int);
extern char gm_RandomMod(int);
extern unsigned char __ftol();
extern void gm_AddOrAccumulateObject(int, int, int);
int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
extern int g_save_version;
int __cdecl ls_LoadGraveyardData(int stream_ctx, int dest_buf);
extern int g_file_version; /* 0x1002d4ec */
extern unsigned char* g_entity_ptr; /* 0x1014d8c0 */
extern int g_101de454; /* 0x101de454 */
extern int g_101de55c; /* 0x101de55c */
extern unsigned int gm_LookupEntityRecordById(unsigned int);
extern int gm_ResolveEntityById(void**, void**, void**, int);
extern void gm_EntitySetField(void);
extern int g_save_info[2];
extern int OpenVfsStream(char*, char*, int);
char s_ls_ID2Ptr____Stadtspieler_Id_not_1002d580[] = "ls_ID2Ptr(): Stadtspieler Id not found";
char s_D__Develop_DieGildeAddOn_loadsav_1002d550[] = "D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c";
char s_ls_ID2Ptr____Houston__wir_haben_e_1002d520[] = "ls_ID2Ptr(): Houston, wir haben ein Problem...";
int ls_LoadSavegameHeader(int, char*);
int ls_LoadExistingEntities(int);
unsigned int ls_LoadBuildingEntityState(unsigned int);
int ls_LoadDynamicEntities(void*);
int ls_LoadEntities(int);
int ls_LoadTownData(int);
extern int amt_fio_LoadAemter(int, int);
extern unsigned int ls_ID2Ptr(void);

/* Loads graveyard-specific data from a save file. Reads
 * production slots, worker assignments, and field states
 * for graveyard buildings. */

// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, int, int, ...);

// FUNCTION: SERVER 0x10014070
// ls_ID2Ptr
// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED

#ifdef REBREW_ALLOW_NAKED
// NAKED verification build: byte-identical to original 0x10014070.
// Id-resolution with fatal path — no C conversion attempted; fenced-naked.
__declspec(naked) unsigned int ls_ID2Ptr(void)
{
	__asm {
		_emit 0xa1
		_emit 0x6c
		_emit 0x54
		_emit 0x03
		_emit 0x10
		sub esp, 0xc
		push eax
		call gm_LookupEntityRecordById
		add esp, 4
		_emit 0xa3
		_emit 0x6c
		_emit 0x54
		_emit 0x03
		_emit 0x10
		test eax, eax
		jne L_have_player
		push 1
		push offset s_ls_ID2Ptr____Stadtspieler_Id_not_1002d580
		push 0x1016
		push offset s_D__Develop_DieGildeAddOn_loadsav_1002d550
		call LogMessageInternal
		add esp, 0x10
		xor eax, eax
		add esp, 0xc
		ret
	L_have_player:
		push ebp
		push esi
		push edi
		push 0xa
		push 5
		push 1
		call gm_StartFilteredEntitySearch
		_emit 0xa3
		_emit 0x3c
		_emit 0x54
		_emit 0x03
		_emit 0x10
		_emit 0xa1
		_emit 0xec
		_emit 0xd4
		_emit 0x02
		_emit 0x10
		add esp, 0xc
		cmp eax, 0x10017
		jl L_skip_lookup_array
		mov esi, 0x10035478
	L_lookup_loop:
		mov ecx, dword ptr [esi]
		push ecx
		call gm_LookupEntityRecordById
		mov dword ptr [esi], eax
		add esi, 4
		add esp, 4
		cmp esi, 0x10035498
		jl L_lookup_loop
	L_skip_lookup_array:
		mov esi, 0x10035a10
		mov edi, 0xffff
	L_entity_loop:
		cmp word ptr [esi - 0x170], di
		je L_entity_skip
		mov ecx, dword ptr [esi - 4]
		lea eax, [esi - 4]
		cmp ecx, -1
		jne L_resolve_a
		mov dword ptr [eax], 0
		jmp L_check_b
	L_resolve_a:
		push ecx
		push 0
		push 0
		push eax
		call gm_ResolveEntityById
		add esp, 0x10
	L_check_b:
		mov eax, dword ptr [esi]
		cmp eax, -1
		jne L_resolve_b
		mov dword ptr [esi], 0
		jmp L_entity_skip
	L_resolve_b:
		push eax
		push 0
		push 0
		push esi
		call gm_ResolveEntityById
		add esp, 0x10
	L_entity_skip:
		add esi, 0x21c
		cmp esi, 0x1009ae10
		jl L_entity_loop
		_emit 0xa1
		_emit 0x50
		_emit 0x54
		_emit 0x03
		_emit 0x10
		xor ebp, ebp
		test eax, eax
		jle L_finish
		xor edi, edi
	L_outer:
		_emit 0x8b
		_emit 0x15
		_emit 0x34
		_emit 0x8c
		_emit 0x0a
		_emit 0x10
		xor eax, eax
		mov ax, word ptr [edi + edx]
		lea esi, [edi + edx]
		_emit 0x8b
		_emit 0x15
		_emit 0x50
		_emit 0xe4
		_emit 0x1d
		_emit 0x10
		mov ecx, eax
		shl ecx, 6
		add edx, ecx
		cmp byte ptr [eax + edx], 0x1d
		jne L_after_clear
		mov dword ptr [esi + 0x24], 0
	L_after_clear:
		mov eax, dword ptr [esi + 6]
		cmp eax, -1
		je near L_inc
		push eax
		lea eax, [esp + 0x18]
		lea ecx, [esp + 0x14]
		push eax
		lea edx, [esp + 0x14]
		push ecx
		push edx
		call gm_ResolveEntityById
		add esp, 0x10
		test eax, eax
		jne L_resolved
		push 1
		push offset s_ls_ID2Ptr____Houston__wir_haben_e_1002d520
		push 0x1050
		push offset s_D__Develop_DieGildeAddOn_loadsav_1002d550
		call LogMessageInternal
		add esp, 0x10
		jmp L_inc
	L_resolved:
		mov eax, dword ptr [esp + 0xc]
		test eax, eax
		je L_chk_b
		mov ecx, dword ptr [eax + 0x5d]
		test ecx, ecx
		jne L_walk_5d
		mov dword ptr [eax + 0x5d], esi
		jmp L_inc
	L_walk_5d:
		mov eax, dword ptr [ecx + 0x3f]
		test eax, eax
		je L_attach_3f
	L_walk_5d_loop:
		mov ecx, eax
		mov eax, dword ptr [ecx + 0x3f]
		test eax, eax
		jne L_walk_5d_loop
		jmp L_attach_3f
	L_chk_b:
		mov eax, dword ptr [esp + 0x10]
		test eax, eax
		je L_chk_c
		mov ecx, dword ptr [eax + 0x14]
		test ecx, ecx
		jne L_walk_14
		mov dword ptr [eax + 0x14], esi
		jmp L_inc
	L_walk_14:
		mov eax, dword ptr [ecx + 0x3f]
		test eax, eax
		je L_attach_3f
	L_walk_14_loop:
		mov ecx, eax
		mov eax, dword ptr [ecx + 0x3f]
		test eax, eax
		jne L_walk_14_loop
		jmp L_attach_3f
	L_chk_c:
		mov eax, dword ptr [esp + 0x14]
		mov ecx, dword ptr [eax + 0x178]
		test ecx, ecx
		jne L_walk_178
		mov dword ptr [eax + 0x178], esi
		jmp L_inc
	L_walk_178:
		mov eax, dword ptr [ecx + 0x3f]
		test eax, eax
		je L_attach_3f
	L_walk_178_loop:
		mov ecx, eax
		mov eax, dword ptr [ecx + 0x3f]
		test eax, eax
		jne L_walk_178_loop
	L_attach_3f:
		mov dword ptr [ecx + 0x3f], esi
	L_inc:
		_emit 0xa1
		_emit 0x50
		_emit 0x54
		_emit 0x03
		_emit 0x10
		inc ebp
		add edi, 0x43
		cmp ebp, eax
		jl near L_outer
	L_finish:
		call gm_EntitySetField
		pop edi
		pop esi
		mov eax, 1
		pop ebp
		add esp, 0xc
		ret
	}
}
#else
unsigned int ls_ID2Ptr(void)
{
	/* C fallback (no byte-matching conversion; id resolution). */
	return 0;
}
#endif

/* Receives and loads a complete game state from a client.
 * Called during lobby-to-game transition to receive the
 * savegame data stream and initialize the game world. */
extern unsigned char g_file_append_mode[1];
extern char s__s__s_100270fc[1];
extern char s_LogFile_has_been_deleted__1002733c[1];
extern char s__________________________________1002735c[1];
extern char g_str_10028888[1];
extern char g_str_10028aec[1];
extern char g_str_10028b04[1];
extern char g_1002a0f8[1];
extern int g_1002dde0[4];
extern int g_array_count[4];
int g_stat1[4] = {
    0x00, 0x00, 0x00, 0x00,
};
int g_stat2[4] = {
    0x00, 0x00, 0x00, 0x00,
};
int g_stat3[4] = {
    0x00, 0x00, 0x00, 0x00,
};
int g_stat4[4] = {
    0x00, 0x00, 0x00, 0x00,
};
extern int g_flag_3c[4];
extern void* g_array_ptr[4];
extern char g_stream_pool[1];
extern int g_stream_count[4];
extern int g_connection_counter[4];
int g_next_object_id[4] = {
    0x01, 0x00, 0x00, 0x00,
};
char g_filter_extra5[1] = {
    0xff,
};
int g_query_filter_extra1[4] = {
    0xff, 0xff, 0xff, 0xff,
};
int g_query_filter_extra2[4] = {
    0xff, 0x7f, 0xff, 0x7f,
};
short g_query_filter_extra3[2] = {
    0xff, 0x7f,
};
int g_query_filter_extra4[4] = {
    0xff, 0x00, 0x00, 0x00,
};
int g_query_filter_owner[4] = {
    0xff, 0xff, 0xff, 0xff,
};
char g_query_filter_state[1] = {
    0xff,
};
char g_str_10031500[1] = {
    0x67,
};
char g_str_10031538[1] = {
    0x67,
};
