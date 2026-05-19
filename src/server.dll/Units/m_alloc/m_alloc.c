#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma intrinsic(memset, strcmp, strcpy)

void __cdecl ReportFatalError(char*, unsigned int, char*); /* 0x10003520 */
;
void __cdecl ReportMessage(char* msg); /* Single arg log? */
;
void* __cdecl _callnewh(int); /* 0x1001a7f7 */
;
extern int DAT_10034624;
extern int DAT_10034628;
extern int DAT_1003462c;
extern int DAT_10034630;
extern int DAT_10034634;
extern int DAT_10034638;
extern void* DAT_10034640;
void __cdecl m_FreeHeapLocked(void* ptr);
extern int DAT_117640b4;
extern int DAT_117640b0;
extern int DAT_117640bc;
extern int DAT_117640b8;
extern int DAT_117640c0;
extern int DAT_117640c4;
extern int DAT_117640a0;
extern int DAT_117640a4;
extern int DAT_10028938;
extern int DAT_1002893c;
void __cdecl ReportMemoryGroupInfo(const char* toggle);
void* __cdecl m_AllocTracked(unsigned int size, const char* file_and_line);
void __cdecl m_FreeTracked(void*);
extern void __cdecl LogMessageInternal(const char*, int, const char*, int);

;
;
;

/* Allocates tracked memory. Wraps HeapAlloc with allocation
 * tracking: records source location string, updates group
 * counters, and maintains the allocation list. */

// FUNCTION: SERVER 0x10006580
// m_AllocTracked

void* __cdecl m_AllocTracked(unsigned int size, const char* source)
{
	char msgBuf[256];
	char nameBuf[16];
	int prev;
	char* group;

	if (DAT_10034640 == 0) {
		ReportFatalError(
			"D:\\Develop\\Units\\m_alloc\\m_alloc.c",
			0x93,
			"m_alloc() called without prior call to m_init()!"
		);
		return 0;
	}
	if (size == 0) {
		return 0;
	}
	DAT_10034638 = DAT_10034638 + 1;
	group = (char*) 0x117640a0;
	if (source != 0) {
		int nameLen;
		char* colon;
		colon = strchr(source, 0x3a);
		if (colon != 0) {
			nameLen = (int) (colon - source) + 1;
			if (nameLen >= 0x10) {
				sprintf(msgBuf, "m_alloc_debug: GroupInformation too long: %s", source);
				ReportMessage(msgBuf);
			}
			strncpy(nameBuf, source, nameLen);
			nameBuf[nameLen] = '\0';
			group = (char*) 0x117640a0;
			if (group != 0) {
				do {
					if (strcmp(nameBuf, group) == 0) {
						if (group != 0) {
							goto found;
						}
						break;
					}
					prev = (int) group;
					group = *(char**) (group + 0x24);
				} while (group != 0);
			}
			group = (char*) _callnewh(0x28);
			strcpy(group, nameBuf);
			*(int*) (group + 0x14) = 0;
			*(int*) (group + 0x10) = 0;
			*(int*) (group + 0x1c) = 0;
			*(int*) (group + 0x18) = 0;
			*(int*) (group + 0x20) = 0;
			*(int*) (group + 0x24) = 0;
			*(int*) (prev + 0x24) = (int) group;
		}
	}
found: {
	void* block;
	int tmp;
	*(int*) (group + 0x20) = *(int*) (group + 0x20) + 1;
	prev = size;
	block = _callnewh(size);
	if (block == 0) {
		sprintf(nameBuf, "Out of Memory Error: Malloc - Failed %s for %u bytes", source, size);
		ReportFatalError("D:\\Develop\\Units\\m_alloc\\m_alloc.c", 0xcd, nameBuf);
		return 0;
	}
	memset(block, 0, prev);
	if (DAT_1003462c < DAT_10034624) {
		int i;
		int* slot;
		i = 0;
		slot = DAT_10034640;
		if (DAT_10034624 > 0) {
			do {
				if (slot[2] == 0) {
					break;
				}
				slot = slot + 4;
				i = i + 1;
			} while (i < DAT_10034624);
		}
		slot[2] = (int) block;
		slot[1] = (int) source;
		slot[3] = size;
		*slot = (int) group;
		DAT_10034628 = DAT_10034628 + size;
		if (DAT_10034628 > DAT_10034630) {
			DAT_10034630 = DAT_10034628;
		}
		tmp = *(int*) (group + 0x10) + size;
		*(int*) (group + 0x10) = tmp;
		if (tmp > *(int*) (group + 0x18)) {
			*(int*) (group + 0x18) = tmp;
		}
		DAT_1003462c = DAT_1003462c + 1;
		if (DAT_1003462c > DAT_10034634) {
			DAT_10034634 = DAT_1003462c;
		}
		tmp = *(int*) (group + 0x14) + 1;
		*(int*) (group + 0x14) = tmp;
		if (tmp > *(int*) (group + 0x1c)) {
			*(int*) (group + 0x1c) = tmp;
		}
	}
	else {
		ReportFatalError(
			"D:\\Develop\\Units\\m_alloc\\m_alloc.c",
			0xf0,
			"No more free memory slots...\nCall m_init() with more slots!"
		);
	}
	return block;
}
}

/* Frees tracked memory. Removes the allocation from the
 * tracking list, updates group counters, and calls HeapFree. */

// FUNCTION: SERVER 0x10006820
// m_FreeTracked

__declspec(naked) void __cdecl m_FreeTracked(void* heapBlock)
{
	(void) heapBlock;
	__asm {
		mov edx, dword ptr [esp + 4]
		push esi
		test edx, edx
		push edi
		je L_ret
		mov eax, dword ptr [DAT_10034638]
		mov ecx, dword ptr [DAT_10034624]
		mov esi, dword ptr [DAT_10034640]
		dec eax
		mov dword ptr [DAT_10034638], eax
		xor eax, eax
		test ecx, ecx
		jle L_aftercheck
	L_loop:
		cmp dword ptr [esi + 8], edx
		je L_aftercheck
		add esi, 0x10
		inc eax
		cmp eax, ecx
		jl L_loop
	L_aftercheck:
		cmp eax, ecx
		jne L_dofree
		push 1
		push 0x100288f8
		push 0x149
		push 0x10028888
		call LogMessageInternal
		add esp, 0x10
		pop edi
		pop esi
		ret
	L_dofree:
		mov edi, dword ptr [esi + 0xc]
		push edx
		mov dword ptr [esi + 8], 0
		call m_FreeHeapLocked
		mov edx, dword ptr [DAT_1003462c]
		add esp, 4
		dec edx
		mov dword ptr [DAT_1003462c], edx
		mov eax, dword ptr [esi]
		mov ecx, dword ptr [eax + 0x14]
		dec ecx
		mov dword ptr [eax + 0x14], ecx
		mov edx, dword ptr [DAT_10034628]
		sub edx, edi
		mov dword ptr [DAT_10034628], edx
		mov esi, dword ptr [esi]
		mov ecx, dword ptr [esi + 0x10]
		sub ecx, edi
		mov dword ptr [esi + 0x10], ecx
		mov eax, dword ptr [DAT_10034628]
		test eax, eax
		jge L_ret
		push 0x100288e0
		push 0x17a
		push 0x10028888
		call ReportFatalError
		add esp, 0xc
	L_ret:
		pop edi
		pop esi
		ret
	}
}

/* Initializes the packet memory pool with a fixed number of
 * pre-allocated blocks for network packet buffering. */

// FUNCTION: SERVER 0x100068e0
// InitPacketPool

__declspec(naked) void __cdecl InitPacketPool(int param_1)
{
	(void) param_1;
	__asm {
		push ebp
		mov ebp, esp
		mov eax, dword ptr [ebp + 8]
		push ebx
		mov dword ptr [DAT_10034624], eax
		push esi
		shl eax, 4
		push edi
		mov edi, eax
		xor esi, esi
		push edi
		mov dword ptr [DAT_10034628], esi
		mov dword ptr [DAT_10034630], esi
		mov dword ptr [DAT_1003462c], esi
		mov dword ptr [DAT_10034634], esi
		call malloc
		add esp, 4
		mov dword ptr [DAT_10034640], eax
		mov dword ptr [ebp + 8], edi
		mov edi, dword ptr [DAT_10034640]
		mov ebx, dword ptr [ebp + 8]
		xor eax, eax
		lea ecx, [edi + edi*2]
		and ecx, 3
		sub ebx, ecx
		jle L_tail_only
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L_tail_only:
		add ecx, ebx
		rep stosb
		mov eax, dword ptr [DAT_10028938]
		mov ecx, dword ptr [DAT_1002893c]
		mov dword ptr [DAT_117640b4], esi
		mov dword ptr [DAT_117640b0], esi
		mov dword ptr [DAT_117640bc], esi
		mov dword ptr [DAT_117640b8], esi
		mov dword ptr [DAT_117640c0], esi
		mov dword ptr [DAT_117640c4], esi
		pop edi
		pop esi
		mov dword ptr [DAT_117640a0], eax
		mov dword ptr [DAT_117640a4], ecx
		pop ebx
		pop ebp
		ret
	}
}

/* Reports memory usage statistics for a named allocation group.
 * Logs count, total bytes, and peak usage to the log system. */

// FUNCTION: SERVER 0x10006990
// ReportMemoryGroupInfo

void __cdecl ReportMemoryGroupInfo(const char* param_1)
{
	char name[16];
	char buf[1024];
	char* group;
	int* slot;
	int i;
	char matched;

	if (*(int*) 0x10034628 == 0 && *(int*) 0x1003462c == 0) {
		sprintf(buf, (char*) 0x10028aa0, *(int*) 0x10034634, *(int*) 0x10034630, *(int*) 0x10034630 >> 10);
	}
	else {
		sprintf(
			buf,
			(char*) 0x10028a2c,
			*(int*) 0x10034634,
			*(int*) 0x10034630,
			*(int*) 0x10034630 >> 10,
			*(int*) 0x1003462c,
			*(int*) 0x10034628,
			*(int*) 0x10034628 >> 10
		);
	}

	LogMessageInternal((char*) 0x10028888, 0x1b5, buf, 1);
	LogMessageInternal((char*) 0x10028888, 0x1b6, (char*) 0x10028a10, 1);

	group = (char*) 0x117640a0;

	if (group == 0) {
		goto done;
	}

	do {
		if (param_1 == 0 || strstr(group, param_1) == 0) {
			matched = 0;
		}
		else {
			matched = 1;
		}

		if (*(int*) (group + 0x1c) <= 0) {
			goto next_group;
		}

		if (*group == '!' && *(int*) (group + 0x14) == 0 && !matched) {
			goto next_group;
		}

		if (param_1 != 0 && !matched) {
			goto next_group;
		}

		strcpy(name, group);

		{
			char* p = strrchr(name, ':');
			if (p != 0) {
				*p = 0;
			}
		}

		if (*(int*) (group + 0x10) == 0 && *(int*) (group + 0x14) == 0) {
			sprintf(
				buf,
				(char*) 0x100289d4,
				name,
				*(int*) (group + 0x18),
				*(int*) (group + 0x18) >> 10,
				*(int*) (group + 0x1c),
				*(int*) (group + 0x20)
			);
		}
		else {
			sprintf(
				buf,
				(char*) 0x1002898c,
				name,
				*(int*) (group + 0x10),
				*(int*) (group + 0x18),
				*(int*) (group + 0x10) >> 10,
				*(int*) (group + 0x18) >> 10,
				*(int*) (group + 0x14),
				*(int*) (group + 0x1c),
				*(int*) (group + 0x20)
			);
		}

		LogMessageInternal((char*) 0x10028888, 0x1cc, buf, 1);

		if (matched) {
			slot = *(int**) 0x10034640;
			for (i = 0; i < *(int*) 0x10034624; i++) {
				if (slot[2] != 0 && slot[0] == (int) group) {
					sprintf(buf, (char*) 0x10028974, (char*) slot[1], slot[3], slot[3] >> 10);
					LogMessageInternal((char*) 0x10028888, 0x1d5, buf, 1);
				}
				slot += 4;
			}
			LogMessageInternal((char*) 0x10028888, 0x1d8, (char*) 0x10028958, 1);
		}

	next_group:
		group = *(char**) (group + 0x24);
	} while (group != 0);

done:
	LogMessageInternal((char*) 0x10028888, 0x1dc, (char*) 0x10028940, 1);
}

/* Shuts down the memory allocator. Frees all remaining tracked
 * allocations, destroys the packet pool, and reports any
 * memory leaks. */

// FUNCTION: SERVER 0x10006c00
// ShutdownMemoryAllocator

// DATA: SERVER 0x10034624
extern int g_array_count;
// DATA: SERVER 0x10034628
extern int g_stat1;
// DATA: SERVER 0x1003462c
extern int g_stat2;
// DATA: SERVER 0x10034630
extern int g_stat3;
// DATA: SERVER 0x10034634
extern int g_stat4;
// DATA: SERVER 0x1003463c
extern int g_flag_3c;

struct ArrayItem {
	int field0;
	int field4;
	void* ptr8;
	int fieldC;
};

// DATA: SERVER 0x10034640
extern struct ArrayItem* g_array_ptr;

struct LinkedListNode {
	char data[0x24];
	struct LinkedListNode* next;
};

// DATA: SERVER 0x117640c4
extern struct LinkedListNode* g_list_head;

// DATA: SERVER 0x10028b04
extern char g_str_10028b04[];
// DATA: SERVER 0x10028aec
extern char g_str_10028aec[];
// DATA: SERVER 0x10028888
extern char g_str_10028888[];

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
extern char g_str_10028b78[];

// DATA: SERVER 0x10028b60
extern char g_str_10028b60[];

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

__declspec(naked) void __cdecl m_PoolFree(int* param_1, int* param_2)
{
	(void) param_1;
	(void) param_2;
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
