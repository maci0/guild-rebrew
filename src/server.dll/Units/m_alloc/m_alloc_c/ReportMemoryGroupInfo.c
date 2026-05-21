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
extern int g_array_count;
extern int g_stat1;
extern int g_stat2;
extern int g_stat3;
extern int g_stat4;
extern int g_alloc_counter;
extern void* g_array_ptr;
void __cdecl m_FreeHeapLocked(void* ptr);
extern int DAT_117640b4;
extern int DAT_117640b0;
extern int DAT_117640bc;
extern int DAT_117640b8;
extern int DAT_117640c0;
extern int g_list_head;
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

// STUB: SERVER 0x10006990
// ReportMemoryGroupInfo

void __cdecl ReportMemoryGroupInfo(const char* filter)
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
		if (filter == 0 || strstr(group, filter) == 0) {
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

		if (filter != 0 && !matched) {
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
