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

// STUB: SERVER 0x10006580
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
