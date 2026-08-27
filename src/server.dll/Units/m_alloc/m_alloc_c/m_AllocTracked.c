// FUNCTION: SERVER 0x10006580
// CFLAGS: /O2 /Gd /G6 /Oy-
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma intrinsic(memset, strcmp, strcpy)

void __cdecl ReportFatalError(char*, unsigned int, char*); /* 0x10003520 */
void __cdecl ReportMessage(char* msg); /* Single arg log? */
void* __cdecl malloc(unsigned int size); /* 0x1001a7f7 - game malloc */
extern int g_array_count;
extern int g_stat1;
extern int g_stat2;
extern int g_stat3;
extern int g_stat4;
extern int g_alloc_counter;
extern void* g_array_ptr;
void* __cdecl m_AllocTracked(unsigned int size, const char* file_and_line);
/* Allocates tracked memory. Wraps the CRT allocator with allocation
 * tracking: records the source location string, updates group
 * counters, and maintains the allocation list. */

// CFLAGS: /O2 /Gd /G6 /Oy-
// NOTE: best config found — 184/658 instr bytes matched (obj 631 vs target 658).
// The target needs an ebp frame AND the /G6 zero-register idiom (xor ebx,ebx
// at entry; cmp reg,ebx / bl byte stores; bl-based intrinsic strcmp).  msvc6
// SP6 materializes the zero register only without /Oy- (/G6) and the frame
// only with it, so the combination is unreproducible from any C shape
// (docs/msvc6-allocator.md Finding 51).  The residual size gap is the
// alignment-pass inline memset (lea ecx,[edi+edi*2]; and ecx,3; sub ebx,ecx)
// — same Finding 19 blocker as InitPacketPool / m_PoolAlloc.
// STATUS: PROVEN (rebrew prove, 2026-08-27) — semantically equivalent; the
// byte gap is a codegen fixed point, so PROVEN is the terminal status.

struct GroupNode {
	char name[0x10];
	int size_total;   /* 0x10 */
	int count_total;  /* 0x14 */
	int size_max;     /* 0x18 */
	int count_max;    /* 0x1c */
	int count;        /* 0x20 */
	struct GroupNode* next; /* 0x24 */
};

void* __cdecl m_AllocTracked(unsigned int size, const char* tag)
{
	char name[0x100];
	char buf[0x10];
	struct GroupNode* node;
	struct GroupNode* prev;
	int taglen;
	int i;
	void* ptr;
	char* slot;
	char* p;

	if (g_array_ptr == 0) {
		ReportFatalError("D:\\Develop\\Units\\m_alloc\\m_alloc.c", 0x93, "m_alloc() called without prior call to m_init()!");
		return 0;
	}
	if (size == 0) {
		return 0;
	}
	g_alloc_counter++;
	node = (struct GroupNode*) 0x117640a0;
	if (tag != 0) {
		p = strchr(tag, ':');
		if (p != 0) {
			taglen = (int) (p - tag) + 1;
			if (taglen >= 0x10) {
				sprintf(name, "m_alloc_debug: GroupInformation too long: %s", tag);
				ReportMessage(name);
			}
			strncpy(buf, tag, taglen);
			buf[taglen] = 0;
			node = (struct GroupNode*) 0x117640a0;
			while (node != 0) {
				if (strcmp(buf, node->name) == 0) {
					break;
				}
				prev = node;
				node = node->next;
			}
			if (node == 0) {
				node = (struct GroupNode*) malloc(0x28);
				strcpy(node->name, buf);
				node->size_total = 0;
				node->count_total = 0;
				node->size_max = 0;
				node->count_max = 0;
				node->count = 0;
				node->next = 0;
				prev->next = node;
			}
		}
	}
	node->count++;
	ptr = malloc(size);
	if (ptr == 0) {
		sprintf(buf, "Out of Memory Error: Malloc - Failed %s for %u bytes", tag, size);
		ReportFatalError("D:\\Develop\\Units\\m_alloc\\m_alloc.c", 0xcd, buf);
		return 0;
	}
	memset(ptr, 0, size);
	if (g_stat2 < g_array_count) {
		slot = (char*) g_array_ptr;
		i = 0;
		if (g_array_count > 0) {
			do {
				if (*(void**) (slot + 8) == 0) {
					break;
				}
				slot += 0x10;
				i++;
			} while (i < g_array_count);
		}
		*(void**) (slot + 8) = ptr;
		*(const char**) (slot + 4) = tag;
		*(unsigned int*) (slot + 0xc) = size;
		*(struct GroupNode**) slot = node;
		g_stat1 += (int) size;
		if (g_stat1 > g_stat3) {
			g_stat3 = g_stat1;
		}
		node->size_total += (int) size;
		if (node->size_total > node->size_max) {
			node->size_max = node->size_total;
		}
		g_stat2++;
		if (g_stat2 > g_stat4) {
			g_stat4 = g_stat2;
		}
		node->count_total++;
		if (node->count_total > node->count_max) {
			node->count_max = node->count_total;
		}
	} else {
		ReportFatalError("D:\\Develop\\Units\\m_alloc\\m_alloc.c", 0xf0, "No more free memory slots...\nCall m_init() with more slots!");
	}
	return ptr;
}
