#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma intrinsic(memset, strcmp, strcpy)

void __cdecl ReportFatalError(char*, unsigned int, char*); /* 0x10003520 */
void __cdecl ReportMessage(char* msg); /* Single arg log? */
void* __cdecl malloc(unsigned int size); /* 0x1001a7f7 - game malloc */
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

void __cdecl ShutdownMemoryAllocator(void)
{
	char buf[0x3f0];
	char buf2[0xc];
	int i;
	char* item;
	char* node;
	char* next;

	if (g_stat2 != 0 || g_stat1 != 0) {
		sprintf(buf, "[*] Memory-Shutdown-Anomaly: [*]\nUsed %i blocks in %i bytes.\n\n%i block(s) left in %i bytes.", g_stat4, g_stat3, g_stat2, g_stat1);
		ReportMessage(buf);
		if (g_flag_3c != 0) {
			ReportMemoryGroupInfo(0);
		}
	} else {
		if (g_flag_3c == 0) {
			goto cleanup;
		}
		ReportMemoryGroupInfo(0);
	}
	for (i = 0; i < g_array_count; i++) {
		item = (char*) g_array_ptr + 8 + i * 0x10;
		if (*(char**) item != 0) {
			sprintf(buf2, "-> Pointer not freed:%s", *(char**) (item - 4));
			LogMessageInternal("D:\\Develop\\Units\\m_alloc\\m_alloc.c", 0x203, buf2, 1);
			m_FreeHeapLocked(*(void**) item);
			*(char**) item = 0;
		}
	}
cleanup:
	g_stat4 = 0;
	g_stat2 = 0;
	g_stat3 = 0;
	g_stat1 = 0;
	g_array_count = 0;
	node = (char*) g_list_head;
	while (node != 0) {
		next = *(char**) (node + 0x24);
		m_FreeHeapLocked(node);
		node = next;
	}
	m_FreeHeapLocked((void*) g_array_ptr);
	g_array_ptr = 0;
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

void* __cdecl m_PoolAlloc(struct BlockNode** head, int size, int max_items)
{
	int asize;
	struct BlockNode* block;
	int i;
	char* slot;

	if (head == 0 || (unsigned int) size == 0 || max_items <= 0) {
		return 0;
	}
	asize = size + 4;
	if ((size & 3) > 0) {
		asize += 4 - (size & 3);
	}
	block = *head;
	if (block != 0) {
		while (block->count >= block->max || block->size != asize) {
			block = block->next;
			if (block == 0) {
				break;
			}
		}
	}
	if (block == 0) {
		block = (struct BlockNode*) m_AllocTracked(asize * max_items + 0x10, "m:pool_get_free(tp_m_pool)");
		block->count = 0;
		block->max = max_items;
		block->size = asize;
		block->next = *head;
		*head = block;
	}
	if (block->max <= 0) {
		return 0;
	}
	slot = (char*) block + 0x10;
	for (i = 0; i < block->max; i++) {
		if (*(int*) slot == 0) {
			break;
		}
		slot += asize;
	}
	if (i >= block->max) {
		return 0;
	}
	block->count++;
	slot += 4;
	memset(slot, 0, asize - 4);
	return slot;
}

/* Returns a block to the packet pool free list. Adds the block
 * back to the free chain for reuse. */

// FUNCTION: SERVER 0x10006E30
// m_PoolFree

void __cdecl m_PoolFree(int* pool, int* block)
{
	int* slot;
	int* blk;
	int* prev;

	slot = (int*) ((char*) block - 4);
	if (slot == 0 || *slot == 0) {
		ReportFatalError("D:\\Develop\\Units\\m_alloc\\m_alloc.c", 0x279, "m_pool_free: tried to free invalid pool-entry (or overwritten void*)!");
		return;
	}
	blk = (int*) *slot;
	if ((unsigned int) (char*) block < (unsigned int) ((char*) blk + 0x10) ||
	    (unsigned int) (char*) block >= (unsigned int) ((char*) blk + 0x10 + blk[2] * blk[1])) {
		ReportFatalError("D:\\Develop\\Units\\m_alloc\\m_alloc.c", 0x279, "m_pool_free: tried to free invalid pool-entry (or overwritten void*)!");
		return;
	}
	*slot = 0;
	blk[0]--;
	if (blk[0] == 0) {
		if (blk == (int*) *pool) {
			*pool = blk[3];
			m_FreeTracked(blk);
			return;
		}
		prev = (int*) *pool;
		while (prev[3] != (int) blk) {
			prev = (int*) prev[3];
		}
		prev[3] = blk[3];
		m_FreeTracked(blk);
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
