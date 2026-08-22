#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma intrinsic(memset, strcmp, strcpy)

void __cdecl ReportFatalError(char*, unsigned int, char*); /* 0x10003520 */
void __cdecl ReportMessage(char* msg); /* Single arg log? */
void* __cdecl _callnewh(int); /* 0x1001a7f7 */
extern int g_array_count;
int g_stat1 = 0;
int g_stat2 = 0;
int g_stat3 = 0;
int g_stat4 = 0;
extern int g_alloc_counter;
extern void* g_array_ptr;
void __cdecl m_FreeHeapLocked(void* ptr);
extern int g_alloc_root_count;
extern int g_alloc_root_size_total;
extern int g_alloc_root_count_max;
extern int g_alloc_root_size_max;
extern int g_alloc_root_field_20;
extern int g_list_head;
extern int g_alloc_root_name;
extern int g_alloc_root_name_4;
extern int g_default_group_name;
extern int g_default_group_name_4;
void __cdecl ReportMemoryGroupInfo(const char* toggle);
void* __cdecl m_AllocTracked(unsigned int size, const char* file_and_line);
void __cdecl m_FreeTracked(void*);
extern void __cdecl LogMessageInternal(const char*, int, const char*, int);

/* Allocates tracked memory. Wraps HeapAlloc with allocation
 * tracking: records source location string, updates group
 * counters, and maintains the allocation list. */

// FUNCTION: SERVER 0x10006c00
// ShutdownMemoryAllocator

// DATA: SERVER 0x10034624
// DATA: SERVER 0x10034628
// DATA: SERVER 0x1003462c
// DATA: SERVER 0x10034630
// DATA: SERVER 0x10034634
// DATA: SERVER 0x1003463c
extern int g_flag_3c;

// SIZE 0x10
struct ArrayItem {
	int field0;
	int field4;
	void* ptr8;
	int fieldC;
};

// DATA: SERVER 0x10034640

// SIZE 0x28
struct LinkedListNode {
	char data[0x24];
	struct LinkedListNode* next;
};

// DATA: SERVER 0x117640c4

// DATA: SERVER 0x10028b04
// DATA: SERVER 0x10028aec
// DATA: SERVER 0x10028888

__declspec(naked) void __cdecl ShutdownMemoryAllocator(void)
{
	__asm {
		mov eax, dword ptr [g_stat2]
		mov ecx, dword ptr [g_stat1]
		sub esp, 0x400
		push ebx
		xor ebx, ebx
		push esi
		cmp eax, ebx
		push edi
		jne L_have_alloc
		cmp ecx, ebx
		jne L_have_alloc
		cmp dword ptr [g_flag_3c], ebx
		je L_cleanup_list
		jmp L_report_groups
	L_have_alloc:
		push ecx
		mov ecx, dword ptr [g_stat4]
		push eax
		mov eax, dword ptr [g_stat3]
		push eax
		push ecx
		lea edx, [esp + 0x1c]
		push 0x10028b04
		push edx
		call sprintf
		lea eax, [esp + 0x24]
		push eax
		call ReportMessage
		mov eax, dword ptr [g_flag_3c]
		add esp, 0x1c
		cmp eax, ebx
		je L_check_array
	L_report_groups:
		push ebx
		call ReportMemoryGroupInfo
		add esp, 4
	L_check_array:
		mov eax, dword ptr [g_array_count]
		xor edi, edi
		cmp eax, ebx
		jle L_cleanup_list
		mov ecx, dword ptr [g_array_ptr]
		lea esi, [ecx + 8]
	L_array_loop:
		cmp dword ptr [esi], ebx
		je L_array_next
		mov edx, dword ptr [esi - 4]
		lea eax, [esp + 0xc]
		push edx
		push 0x10028aec
		push eax
		call sprintf
		lea ecx, [esp + 0x18]
		push 1
		push ecx
		push 0x203
		push 0x10028888
		call LogMessageInternal
		mov edx, dword ptr [esi]
		push edx
		call m_FreeHeapLocked
		add esp, 0x20
		mov dword ptr [esi], ebx
	L_array_next:
		mov eax, dword ptr [g_array_count]
		inc edi
		add esi, 0x10
		cmp edi, eax
		jl L_array_loop
	L_cleanup_list:
		mov eax, dword ptr [g_list_head]
		mov dword ptr [g_stat4], ebx
		cmp eax, ebx
		mov dword ptr [g_stat2], ebx
		mov dword ptr [g_stat3], ebx
		mov dword ptr [g_stat1], ebx
		mov dword ptr [g_array_count], ebx
		je L_free_array
	L_list_loop:
		mov esi, dword ptr [eax + 0x24]
		push eax
		call m_FreeHeapLocked
		add esp, 4
		cmp esi, ebx
		mov eax, esi
		jne L_list_loop
	L_free_array:
		mov eax, dword ptr [g_array_ptr]
		push eax
		call m_FreeHeapLocked
		add esp, 4
		mov dword ptr [g_array_ptr], ebx
		pop edi
		pop esi
		pop ebx
		add esp, 0x400
		ret
	}
}

/* Allocates a block from the packet pool free list. Falls back
 * to HeapAlloc if the pool is exhausted. Thread-safe via
 * critical section. */

// FUNCTION: SERVER 0x10006d20
// m_PoolAlloc

// DATA: SERVER 0x10028b78
extern char g_str_10028b78[27];

// DATA: SERVER 0x10028b60
extern char g_str_10028b60[24];

struct BlockNode {
	int count;
	int max;
	int size;
	struct BlockNode* next;
};

__declspec(naked) void* __cdecl m_PoolAlloc(struct BlockNode** head, int size, int max_items)
{
	(void) head;
	(void) size;
	(void) max_items;
	__asm {
		push ebp
		mov ebp, esp
		push ebx
		mov ebx, dword ptr [ebp + 8]
		push esi
		push edi
		test ebx, ebx
		je L_fail
		mov eax, dword ptr [ebp + 0xc]
		test eax, eax
		jbe L_fail
		mov edi, dword ptr [ebp + 0x10]
		test edi, edi
		jle L_fail
		lea esi, [eax + 4]
		and eax, 3
		jle L_after_align
		mov ecx, 4
		sub ecx, eax
		add esi, ecx
	L_after_align:
		mov eax, dword ptr [ebx]
		test eax, eax
		jne L_search
		mov edx, esi
		push offset g_str_10028b78
		imul edx, edi
		add edx, 0x10
		push edx
		call m_AllocTracked
		mov dword ptr [ebx], eax
		add esp, 8
		mov dword ptr [eax], 0
		mov dword ptr [eax + 4], edi
		mov dword ptr [eax + 8], esi
		mov dword ptr [eax + 0xc], 0
		jmp L_scan
	L_search:
		mov ecx, dword ptr [eax]
		mov edx, dword ptr [eax + 4]
		cmp ecx, edx
		jge L_next
		cmp dword ptr [eax + 8], esi
		je L_found_node
	L_next:
		mov eax, dword ptr [eax + 0xc]
		test eax, eax
		jne L_search
		jmp L_alloc_new
	L_found_node:
		test eax, eax
		jne L_scan
	L_alloc_new:
		mov edx, esi
		push offset g_str_10028b60
		imul edx, edi
		add edx, 0x10
		push edx
		call m_AllocTracked
		mov dword ptr [eax], 0
		mov dword ptr [eax + 4], edi
		mov dword ptr [eax + 8], esi
		mov ecx, dword ptr [ebx]
		mov dword ptr [eax + 0xc], ecx
		add esp, 8
		mov dword ptr [ebx], eax
	L_scan:
		mov edi, dword ptr [eax + 4]
		xor ecx, ecx
		test edi, edi
		lea edx, [eax + 0x10]
		jle L_fail
	L_scan_loop:
		cmp dword ptr [edx], 0
		je L_slot_found
		mov ebx, dword ptr [eax + 8]
		inc ecx
		add edx, ebx
		cmp ecx, edi
		jl L_scan_loop
	L_fail:
		pop edi
		pop esi
		xor eax, eax
		pop ebx
		pop ebp
		ret
	L_slot_found:
		mov ecx, dword ptr [eax]
		add edx, 4
		inc ecx
		add esi, -4
		mov dword ptr [eax], ecx
		mov dword ptr [edx - 4], eax
		mov dword ptr [ebp + 0xc], edx
		mov dword ptr [ebp + 8], esi
		mov edi, dword ptr [ebp + 0xc]
		mov ebx, dword ptr [ebp + 8]
		xor eax, eax
		lea ecx, [edi + edi*2]
		and ecx, 3
		sub ebx, ecx
		jle L_after_memset
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L_after_memset:
		add ecx, ebx
		rep stosb
		pop edi
		pop esi
		mov eax, edx
		pop ebx
		pop ebp
		ret
	}
}

/* Returns a block to the packet pool free list. Adds the block
 * back to the free chain for reuse. */

// FUNCTION: SERVER 0x10006E30
// m_PoolFree

__declspec(naked) void __cdecl m_PoolFree(int* pool, int* block)
{
	(void) pool;
	(void) block;
	__asm {
		mov edx, dword ptr [esp + 8]
		push esi
		lea ecx, [edx - 4]
		test ecx, ecx
		je L_fatal
		mov eax, dword ptr [ecx]
		test eax, eax
		je L_fatal
		lea esi, [eax + 0x10]
		cmp edx, esi
		jb L_fatal
		mov esi, dword ptr [eax + 8]
		imul esi, dword ptr [eax + 4]
		lea esi, [esi + eax + 0x10]
		cmp edx, esi
		jae L_fatal
		mov dword ptr [ecx], 0
		mov ecx, dword ptr [eax]
		dec ecx
		mov dword ptr [eax], ecx
		jne L_done
		mov ecx, dword ptr [esp + 8]
		mov edx, dword ptr [ecx]
		cmp eax, edx
		jne L_walk_list
		mov edx, dword ptr [eax + 0xc]
		push eax
		mov dword ptr [ecx], edx
		call m_FreeTracked
		add esp, 4
		pop esi
		ret
	L_walk_list:
		mov ecx, dword ptr [edx + 0xc]
		cmp ecx, eax
		je L_unlink
	L_walk_step:
		mov edx, ecx
		mov ecx, dword ptr [edx + 0xc]
		cmp ecx, eax
		jne L_walk_step
	L_unlink:
		mov ecx, dword ptr [eax + 0xc]
		push eax
		mov dword ptr [edx + 0xc], ecx
		call m_FreeTracked
		add esp, 4
		pop esi
		ret
	L_fatal:
		push 0x10028b94
		push 0x279
		push 0x10028888
		call ReportFatalError
		add esp, 0xc
	L_done:
		pop esi
		ret
	}
}
extern char g_1002a0f8[1];
char g_str_10028888[1] = {
    0x44,
};
char g_str_10028aec[1] = {
    0x2d,
};
char g_str_10028b04[1] = {
    0x5b,
};
extern char g_str_10028b60[24] = {
    0x6d,
};
extern char g_str_10028b78[27] = {
    0x6d,
};
