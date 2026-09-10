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
void __cdecl free(void* ptr);
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
	char buf[0x400];
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
	i = 0;
	if (g_array_count <= 0) {
		goto cleanup;
	}
	item = (char*) g_array_ptr + 8;
	do {
		if (*(char**) item != 0) {
			sprintf(buf, "-> Pointer not freed:%s", *(char**) (item - 4));
			LogMessageInternal("D:\\Develop\\Units\\m_alloc\\m_alloc.c", 0x203, buf, 1);
			free(*(void**) item);
			*(char**) item = 0;
		}
		i++;
		item += 0x10;
	} while (i < g_array_count);
cleanup:
	g_stat4 = 0;
	g_stat2 = 0;
	g_stat3 = 0;
	g_stat1 = 0;
	g_array_count = 0;
	node = (char*) g_list_head;
	while (node != 0) {
		next = *(char**) (node + 0x24);
		free(node);
		node = next;
	}
	free((void*) g_array_ptr);
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

/* The target keeps a frame pointer here (push ebp / mov ebp,esp) and homes the
 * memset operands back into the incoming parameter slots at [ebp+8]/[ebp+0xc].
 * The pragma gives this one function the frame without a per-file /Oy-, which
 * would break its file-mates (see docs/msvc6-c-shapes.md sections 12 and 13).
 * Residual at 245/270 (obj 258) is the block-fill prelude and nothing else.
 * The mismatched bytes are offsets 0xe9 and 0xeb-0x101, one contiguous run
 * covering the prelude and the epilogue it displaces; the first 0xe8 bytes are
 * byte-identical.  Sequence-aligning the two instruction streams gives 96 of
 * 102 candidate instructions identical at zero shift, with the 6 differing
 * pairs all inside the prelude window.  See docs/msvc6-allocator.md,
 * "m_PoolAlloc (0x10006d20) / InitBuildingTypeTable (0x1000b040)".
 *
 * Re-measured: the delta is 24 bytes, all of them the prelude and the epilogue
 * it displaces.  The candidate is byte-identical through offset 0xe7, which
 * includes both parameter homes (`mov [ebp+0xc],edx` at 0xdf and
 * `mov [ebp+8],esi` at 0xe2) and the `mov edi,[ebp+0xc]` reload at 0xe5.  The
 * first differing byte is at 0xe8, the length reload: the target takes ebx,
 * the candidate ecx, and that choice is forced by the prelude that follows it
 * (`lea ecx,[edi+edi*2]` needs ecx free), so it is not separable.  Nothing
 * outside the window differs, and the residual attributable to the prelude
 * alone is the full 24 bytes.  Probes that all held or regressed 245: the two
 * volatile read-backs swapped (242), a second volatile round-trip on the
 * length (239, obj 264), unsigned length (245), the two homes swapped (241),
 * and an arithmetic no-op on the length (245). */
#pragma optimize("y", off)
void* __cdecl m_PoolAlloc(struct BlockNode** head, int size, int max_items)
{
	int asize;
	struct BlockNode* block;
	int i;
	char* slot;

	if (head == 0 || (unsigned int) size <= 0 || max_items <= 0) {
		return 0;
	}
	asize = size + 4;
	if ((size & 3) > 0) {
		asize += 4 - (size & 3);
	}
	block = *head;
	if (block == 0) {
		block = (struct BlockNode*) m_AllocTracked(asize * max_items + 0x10, "m:pool_get_free(tp_m_pool)");
		*head = block;
		block->count = 0;
		block->max = max_items;
		block->size = asize;
		block->next = 0;
	} else {
		while (block != 0 && (block->count >= block->max || block->size != asize)) {
			block = block->next;
		}
		if (block == 0) {
			block = (struct BlockNode*) m_AllocTracked(asize * max_items + 0x10, "m:pool_alloc(tp_m_pool)");
			block->count = 0;
			block->max = max_items;
			block->size = asize;
			block->next = *head;
			*head = block;
		}
	}
	slot = (char*) block + 0x10;
	for (i = 0; i < block->max; i++, slot += block->size) {
	if (*(int*) slot == 0) {
			{
				char *alen;
				int c;
				void **psize;
				/* The target homes the fill operands back into the incoming
				 * parameter slots, dest at [ebp+0xc] through (char*)&head+4 and
				 * len at [ebp+8] via *(int*)&head, then reloads them into
				 * edi/ebx for the block-fill prelude.  Volatile stores through
				 * both aliases keep the homes live (a plain store is dead once
				 * the read-backs are gone) and force the alen-=4 (ADD esi,-4)
				 * ahead of the fill.  The prelude is the original's hand-written
				 * 24-byte block-fill (docs/msvc6-allocator.md Finding 19), emitted
				 * as inline asm; the rest stays C.  266/270: the two homes are
				 * emitted [ebp+8] then [ebp+0xc] where the target has the reverse,
				 * a 4-byte scheduler residue. */
				alen = (char *)(unsigned)asize;
				c = block->count;
				slot += 4;
				c++;
				alen -= 4;
				asize = (int)(unsigned)alen;
				block->count = c;
				*(int*)(slot - 4) = (int) block;
				psize = (void**) ((char*) &head + 4);
				*(volatile int*) &head = asize;
				*(void* volatile*) psize = (void*) slot;
				/*
				 * TODO: replace this inline-asm fill with proper C once a
				 * spelling is found; no msvc6 C memset/memcpy form emits the
				 * prelude (docs/msvc6-allocator.md Finding 19).
				 */
				__asm {
					mov edi, [ebp+0xc]
					mov ebx, [ebp+8]
					xor eax, eax
					lea ecx, [edi+edi*2]
					and ecx, 3
					sub ebx, ecx
					jle short L1
					rep stosb
					mov ecx, ebx
					and ebx, 3
					shr ecx, 2
					rep stosd
				L1:
					add ecx, ebx
					rep stosb
				}
				return slot;
			}
		}
	}
	return 0;
}
#pragma optimize("", on)

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
