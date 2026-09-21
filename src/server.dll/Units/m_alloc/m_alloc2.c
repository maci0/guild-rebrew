#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

#pragma intrinsic(memset, strcmp, strcpy)

void __cdecl ReportFatalError(char*, unsigned int, char*); /* 0x10003520 */
void __cdecl ReportMessage(char* msg); /* Single arg log? */
// DATA: SERVER 0x10034628
int g_stat1 = 0;
// DATA: SERVER 0x1003462c
int g_stat2 = 0;
// DATA: SERVER 0x10034630
int g_stat3 = 0;
// DATA: SERVER 0x10034634
int g_stat4 = 0;
void __cdecl free(void* ptr);
void __cdecl m_ReportGroupInfo(const char* toggle);
void* __cdecl m_AllocTracked(unsigned int size, const char* file_and_line);
void __cdecl m_FreeTracked(void*);
extern void __cdecl LogMessageInternal(const char*, int, const char*, int);

/* Allocates tracked memory. Wraps HeapAlloc with allocation
 * tracking: records source location string, updates group
 * counters, and maintains the allocation list. */

// FUNCTION: SERVER 0x10006c00
// m_ShutdownAllocator

void __cdecl m_ShutdownAllocator(void)
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
			m_ReportGroupInfo(0);
		}
	} else {
		if (g_flag_3c == 0) {
			goto cleanup;
		}
		m_ReportGroupInfo(0);
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

// DATA: SERVER 0x10028b78
// DATA: SERVER 0x10028b60
// FUNCTION: SERVER 0x10006d20
// m_PoolAlloc



// SIZE 0x10
struct BlockNode {
	int count;
	int max;
	int size;
	struct BlockNode* next;
};

/* The target keeps a frame pointer here (push ebp / mov ebp,esp) and homes the
 * memset operands back into the incoming parameter slots at [ebp+8]/[ebp+0xc].
 * The pragma gives this one function the frame without a per-file /Oy-, which
 * would break its file-mates (see docs/msvc6-count-shapes.md sections 12 and 13).
 * Residual at 245/270 (obj 258) is the block-fill prelude and nothing else.
 * The mismatched bytes are offsets 0xe9 and 0xeb-0x101, one contiguous run
 * covering the prelude and the epilogue it displaces; the first 0xe8 bytes are
 * byte-identical.  Sequence-aligning the two instruction streams gives 96 of
 * 102 candidate instructions identical at zero shift, with the 6 differing
 * pairs all inside the prelude window.  See docs/msvc6-allocator.md,
 * "m_PoolAlloc (0x10006d20) / srv_InitBuildingTypeTable (0x1000b040)".
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
				int count;
				char* fdest;
				int flen;
				/* The target's fill operands live in the incoming parameter
				 * slots: dest at [ebp+0xc] and len at [ebp+8].  That is not a
				 * hand-placed home, it is /O2 reusing the dead parameter slots
				 * for the two block-scoped locals, and the register allocator
				 * picks them when the locals are ordinary (non-volatile)
				 * variables named directly by the asm block.  Forcing the same
				 * slots through `*(volatile int*)&head` aliases instead scores
				 * 266/270: the volatile edge pins the two stores in source
				 * order, so the target's descending [ebp+0xc] / [ebp+8] order
				 * cannot be expressed, and any source swap sinks the
				 * `alen -= 4` (ADD esi,-4) below the stores (260).  With named
				 * locals msvc6 emits dest then len, in the target's order, with
				 * `alen -= 4` still ahead of both: 270/270.
				 *
				 * The prelude itself is the original's hand-written 24-byte
				 * block-fill (docs/msvc6-allocator.md Finding 19); no msvc6 C
				 * memset/memcpy spelling emits it. */
				alen = (char *)(unsigned)asize;
				count = block->count;
				slot += 4;
				count++;
				alen -= 4;
				asize = (int)(unsigned)alen;
				block->count = count;
				*(int*)(slot - 4) = (int) block;
				fdest = (char*) slot;
				flen = (int) alen;
				__asm {
					mov edi, fdest
					mov ebx, flen
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
// m_pool_free

void __cdecl m_pool_free(int* pool, int* block)
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

/* Five truncated stub arrays used to live here -- g_str_10028888,
 * s_Pointer_not_freed_10028aec, s_Memory_Shutdown_Anomaly_10028b04, s_m_pool_alloc_tp_m_pool_10028b60 and
 * s_m_pool_get_free_tp_m_pool_10028b78 -- each holding only the FIRST BYTE of
 * a string the reference has in full at that VA.  Every one of those strings
 * is already emitted by this TU as a real `??_C@` COMDAT literal, from the
 * call sites above:
 *
 *   0x10028888  "D:\Develop\Units\m_alloc\m_alloc.c"    (LogMessageInternal)
 *   0x10028aec  "-> Pointer not freed:%s"               (sprintf)
 *   0x10028b04  "[*] Memory-Shutdown-Anomaly: [*]..."   (sprintf)
 *   0x10028b60  "m:pool_alloc(tp_m_pool)"               (m_AllocTracked)
 *   0x10028b78  "m:pool_get_free(tp_m_pool)"            (m_AllocTracked)
 *
 * So the object emitted the text TWICE: 64 bytes of stubs in its regular
 * `.data`, and the COMDATs after them -- where the reference has only the
 * strings.  Nothing referenced the stub names.  Dropping them lets the COMDAT
 * run slide down into the reference's addresses (section 100: an object's
 * regular `.data` precedes its COMDATs, so the stubs were displacing the very
 * text they stood in for). */
