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
			return block;
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

void __cdecl m_FreeTracked(void* heapBlock)
{
	int trackedSize;
	int* trackingEntry;
	int blockSize;

	if (heapBlock != (void*) 0) {
		DAT_10034638 = DAT_10034638 - 1;
		trackedSize = 0;
		trackingEntry = DAT_10034640;
		if (DAT_10034624 > 0) {
			do {
				if ((void*) trackingEntry[2] == heapBlock) {
					break;
				}
				trackingEntry = trackingEntry + 4;
				trackedSize = trackedSize + 1;
			} while (trackedSize < DAT_10034624);
		}
		if (trackedSize == DAT_10034624) {
			LogMessageInternal(
				"D:\\Develop\\Units\\m_alloc\\m_alloc.c",
				0x149,
				"Memory freed more than once or tried to free non-allocated memory!",
				1
			);
			return;
		}
		blockSize = trackingEntry[3];
		trackingEntry[2] = 0;
		m_FreeHeapLocked(heapBlock);
		DAT_1003462c = DAT_1003462c - 1;
		*(int*) (*trackingEntry + 0x14) = *(int*) (*trackingEntry + 0x14) - 1;
		DAT_10034628 = DAT_10034628 - blockSize;
		*(int*) (*trackingEntry + 0x10) = *(int*) (*trackingEntry + 0x10) - blockSize;
		if (DAT_10034628 < 0) {
			ReportFatalError("D:\\Develop\\Units\\m_alloc\\m_alloc.c", 0x17a, "Memory Underflow Error");
		}
	}
}

/* Initializes the packet memory pool with a fixed number of
 * pre-allocated blocks for network packet buffering. */

// FUNCTION: SERVER 0x100068e0
// InitPacketPool

void __cdecl InitPacketPool(int param_1)
{
	int size;
	void* buf;

	DAT_10034624 = param_1;
	size = param_1 * 0x10;
	DAT_10034628 = 0;
	DAT_10034630 = 0;
	DAT_1003462c = 0;
	DAT_10034634 = 0;
	buf = malloc(size);
	DAT_10034640 = buf;
	memset(buf, 0, (unsigned int) size);
	DAT_117640b4 = 0;
	DAT_117640b0 = 0;
	DAT_117640bc = 0;
	DAT_117640b8 = 0;
	DAT_117640c0 = 0;
	DAT_117640c4 = 0;
	DAT_117640a0 = DAT_10028938;
	DAT_117640a4 = DAT_1002893c;
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
			i = 0;
			if (*(int*) 0x10034624 > 0) {
				do {
					if (slot[2] != 0 && slot[0] == (int) group) {
						sprintf(buf, (char*) 0x10028974, (char*) slot[1], slot[3], slot[3] >> 10);
						LogMessageInternal((char*) 0x10028888, 0x1d5, buf, 1);
					}
					i++;
					slot += 4;
				} while (i < *(int*) 0x10034624);
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

void __cdecl ShutdownMemoryAllocator(void)
{
	char buffer[1024]; /* 0x400 bytes */

	if (g_stat2 != 0 || g_stat1 != 0 || g_flag_3c != 0) {
		sprintf(buffer, g_str_10028b04, g_stat4, g_stat3, g_stat2, g_stat1);
		ReportMessage(buffer);

		if (g_flag_3c != 0) {
			ReportMemoryGroupInfo(0);
		}

		if (g_array_count > 0) {
			int i;
			for (i = 0; i < g_array_count; i++) {
				if (g_array_ptr[i].ptr8 != 0) {
					sprintf(buffer, g_str_10028aec, g_array_ptr[i].field4);
					LogMessageInternal(g_str_10028888, 0x203, buffer, 1);
					m_FreeHeapLocked(g_array_ptr[i].ptr8);
					g_array_ptr[i].ptr8 = 0;
				}
			}
		}
	}

	g_stat4 = 0;
	g_stat2 = 0;
	g_stat3 = 0;
	g_stat1 = 0;
	g_array_count = 0;

	{
		struct LinkedListNode* node = g_list_head;
		while (node != 0) {
			struct LinkedListNode* next = node->next;
			m_FreeHeapLocked(node);
			node = next;
		}
	}

	m_FreeHeapLocked(g_array_ptr);
	g_array_ptr = 0;
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

void* __cdecl m_PoolAlloc(struct BlockNode** head, int size, int max_items)
{
	int aligned_size;
	struct BlockNode* node;

	if (!head || size <= 0 || max_items <= 0) {
		return 0;
	}

	aligned_size = size + 4;
	if ((size & 3) > 0) {
		aligned_size += 4 - (size & 3);
	}

	node = *head;
	if (!node) {
		node = (struct BlockNode*) m_AllocTracked(aligned_size * max_items + 0x10, g_str_10028b78);
		*head = node;
		node->count = 0;
		node->max = max_items;
		node->size = aligned_size;
		node->next = 0;
	}
	else {
		while (node) {
			if (node->count < node->max && node->size == aligned_size) {
				break;
			}
			node = node->next;
		}
		if (!node) {
			node = (struct BlockNode*) m_AllocTracked(aligned_size * max_items + 0x10, g_str_10028b60);
			node->count = 0;
			node->max = max_items;
			node->size = aligned_size;
			node->next = *head;
			*head = node;
		}
	}

	node = *head;
	if (node->max > 0) {
		char* ptr = (char*) node + 0x10;
		int i;
		for (i = 0; i < node->max; i++) {
			if (*(int*) ptr == 0) {
				node->count++;
				*(struct BlockNode**) ptr = node;

				/* reuse arguments for smaller stack frame & exact match */
				head = (struct BlockNode**) (ptr + 4);
				size = aligned_size - 4;

				memset((void*) head, 0, size);
				return head;
			}
			ptr += node->size;
		}
	}
	return 0;
}

/* Returns a block to the packet pool free list. Adds the block
 * back to the free chain for reuse. */

// FUNCTION: SERVER 0x10006E30
// m_PoolFree

void __cdecl m_PoolFree(int* param_1, int* param_2)
{
	int* header;
	int* block;
	int count;
	int* cur;
	int* prev;

	header = param_2 - 1;
	if (header != 0 && (block = (int*) *header, block != 0) && param_2 >= block + 4 &&
		param_2 < (int*) ((int) block + block[2] * block[1] + 0x10)) {
		*header = 0;
		count = *block;
		count = count - 1;
		*block = count;
		if (count == 0) {
			prev = (int*) *param_1;
			if (block == prev) {
				*param_1 = block[3];
				m_FreeTracked(block);
				return;
			}
			while ((cur = (int*) prev[3]) != block) {
				prev = cur;
			}
			prev[3] = block[3];
			m_FreeTracked(block);
			return;
		}
	}
	else {
		ReportFatalError("D:\\Develop\\Units\\m_alloc\\m_alloc.c", 0x279, "m_pool_free: tried to free invalid address");
	}
}
