#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <string.h>
int __cdecl __ftol(void);

typedef int(__cdecl* dispatch_fn)(unsigned char*);

extern char* g_table;
int __cdecl gm_ResolveEntityById(void** dynamic, int zero1, int zero2, int id);
int __cdecl gm_RandomMod(int range);
float __cdecl gm_RandomFloat01(void);
void __cdecl gm_AddOrAccumulateObject(int p1, int p2, int p3);
int __cdecl gm_RefreshMarketAvailability(int season);
int __cdecl gm_LookupEntityRecordById(int);
void __cdecl gm_DeallocEntity(unsigned int index, int param);
void* __cdecl gm_NextEntityQueryMatch(void);
extern float fColorScale;
extern int g_next_object_id;
extern unsigned char g_current_season;
extern float g_float_const_cc;
extern float g_float_const_a0;
extern double dScaleFactor;
extern int g_alchemy_entity_table[];
int* __cdecl ahm_LookupEntityInTable(int);
extern dispatch_fn PTR_LAB_1002c5a0[];

// SIZE 0x8
typedef struct {
	int key;
	int val;
} PAIR;

// SIZE 0x14
typedef struct {
	char hdr[8];
	int key;
	char pad[4];
	int val;
} SRC;

// SIZE 0x3c
typedef struct {
	char hdr[0xc];
	PAIR entries[6];
} TGT;

/* Resets an alchemy entity to its initial state by zeroing
 * out its operational fields via memset. */

// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);

// FUNCTION: SERVER 0x1000ca00
// ahm_ProcessEntityChain

__declspec(naked) int __cdecl ahm_ProcessEntityChain(char* cmd_payload)
{
	(void) cmd_payload;
	__asm {
		push ebx
		push esi
		push edi
		mov edi, dword ptr [esp + 0x10]
		mov ebx, 1
		mov esi, dword ptr [edi + 0x95]
	L_loop:
		mov al, byte ptr [esi]
		cmp al, 6
		je L_check_result
		and eax, 0xff
		push esi
		call dword ptr [eax*4 + 0x1002c5a0]
		add esp, 4
		test eax, eax
		je L_no_err
		xor ebx, ebx
	L_no_err:
		mov esi, dword ptr [esi + 0x95]
		test ebx, ebx
		jne L_loop
	L_error_path:
		mov cl, byte ptr [edi]
		mov eax, edi
		cmp cl, 6
		je L_err_end
	L_err_loop:
		mov byte ptr [eax], 2
		mov eax, dword ptr [eax + 0x95]
		cmp byte ptr [eax], 6
		jne L_err_loop
	L_err_end:
		pop edi
		mov byte ptr [eax], 2
		pop esi
		mov eax, 1
		pop ebx
		ret
	L_check_result:
		test ebx, ebx
		je L_error_path
		mov byte ptr [edi], 1
		mov cl, byte ptr [edi]
		cmp cl, 6
		mov eax, edi
		je L_ok_end
	L_ok_loop:
		mov eax, dword ptr [eax + 0x95]
		cmp byte ptr [eax], 6
		jne L_ok_loop
	L_ok_end:
		pop edi
		mov byte ptr [eax], 1
		pop esi
		mov eax, 1
		pop ebx
		ret
	}
}

/* Resolves a field value by type from a command packet.
 * Performs entity ID resolution through the global entity
 * tables. Returns the resolved value or 0 on failure. */

// FUNCTION: SERVER 0x1000CA90
// gm_GetFieldByType
__declspec(naked) int __cdecl gm_GetFieldByType(char* p, int type)
{
	(void) p;
	(void) type;
	__asm {
		mov eax, dword ptr [esp + 8]
		cmp eax, -2
		jne L_t3
		mov eax, dword ptr [esp + 4]
		xor ecx, ecx
		mov cl, byte ptr [eax + 3]
		mov eax, ecx
		shl eax, 4
		add eax, ecx
		shl eax, 8
		add eax, ecx
		shl eax, 4
		add eax, ecx
		lea ecx, [eax + eax*8]
		mov eax, dword ptr [ecx*4 + 0x10442d00]
		ret
	L_t3:
		cmp eax, -3
		jne L_t4
		mov edx, dword ptr [esp + 4]
		xor ecx, ecx
		mov cl, byte ptr [edx + 3]
		mov eax, ecx
		shl eax, 4
		add eax, ecx
		shl eax, 8
		add eax, ecx
		shl eax, 4
		add eax, ecx
		lea eax, [eax + eax*8]
		mov eax, dword ptr [eax*4 + 0x10442d04]
		ret
	L_t4:
		cmp eax, -4
		jne L_ret0
		mov edx, dword ptr [esp + 4]
		xor ecx, ecx
		mov cl, byte ptr [edx + 3]
		mov eax, ecx
		shl eax, 4
		add eax, ecx
		shl eax, 8
		add eax, ecx
		shl eax, 4
		add eax, ecx
		lea eax, [eax + eax*8]
		mov eax, dword ptr [eax*4 + 0x10442d08]
	L_ret0:
		ret
	}
}
