/* m_FreeTracked — debug-heap tracked free (0x10006820). */

// FUNCTION: SERVER 0x10006820
// m_FreeTracked
// SIZE: 188

#include "rebrew_types.h"
#include "rebrew_globals.h"
extern int g_alloc_counter;          /* 0x10034638 */
extern int g_alloc_root_count;       /* 0x117640b4 */
extern int g_alloc_root_size_total;  /* 0x117640b0 */
extern int g_alloc_root_count_max;   /* 0x117640bc */
extern int g_alloc_root_size_max;    /* 0x117640b8 */
extern int g_alloc_root_field_20;    /* 0x117640c0 */
extern int g_alloc_root_name;        /* 0x117640a0 */
extern int g_alloc_root_name_4;      /* 0x117640a4 */
extern int g_default_group_name;     /* 0x10028938 */
extern int g_default_group_name_4;   /* 0x1002893c */
extern void __cdecl LogMessageInternal(char* file, unsigned int line, char* msg, int level);
extern void __cdecl ReportFatalError(char* modulePath, unsigned int lineNumber, char* message);
extern void __cdecl free(void* ptr);
extern void* __cdecl malloc(unsigned int size);

void __cdecl m_FreeTracked(void* ptr)
{
	char* pool;
	int i;
	int count;
	int size;
	int* block;

	if (ptr == 0) {
		return;
	}
	g_alloc_counter--;
	count = g_array_count;
	pool = (char*) g_array_ptr;
	for (i = 0; i < count; i++) {
		if (*(void**) (pool + 8) == ptr) {
			break;
		}
		pool += 0x10;
	}
	if (i == count) {
		LogMessageInternal("D:\\Develop\\Units\\m_alloc\\m_alloc.c", 0x149, "Memory freed more than once or tried to free invalid pointer", 1);
		return;
	}
	size = *(int*) (pool + 0xc);
	*(int*) (pool + 8) = 0;
	free(ptr);
	g_stat2--;
	block = *(int**) pool;
	block[5]--;
	g_stat1 -= size;
	block = *(int**) pool;
	block[4] -= size;
	if (g_stat1 < 0) {
		ReportFatalError("D:\\Develop\\Units\\m_alloc\\m_alloc.c", 0x17a, "Memory-Underflow Error");
	}
}

/* m_InitPacketPool — allocates and zeroes the packet pool (0x100068E0).
 * Target 162 bytes; compiled 146. Of the 16-byte size delta, 12 bytes are the
 * target's dest-alignment memset prelude and 4 are the length's register
 * assignment around it (measured per region by .scratch/ipp-l3/accounting.py).
 * The prelude is (lea ecx,[edi+edi*2]; and ecx,3; sub
 * ebx,ecx; jle; rep stosb; ...; rep stosd; ...; rep stosb) — an
 * unreproducible msvc6 expansion on this toolchain: msvc6 SP6 always
 * materializes runtime counts fresh into ecx and emits the plain
 * dword+tail form (docs/msvc6-allocator.md, "m_PoolAlloc /
 * srv_InitBuildingTypeTable" section). Probed 2026-08-27 for this exact
 * body: 15 C formulations (locals, unsigned/volatile/memory-resident
 * counts, dest-copy, reordered statements) x /O2 /Gd /Oy- plus an
 * /O1 /Ox /O2 /G5 /G6 /GB /Oi /Og- flag sweep — zero prelude hits.
 * Re-tested 2026-09-04, and the "unknown dest alignment" theory is
 * disproved: srv_InitBuildingTypeTable 0x1000b046 emits the prelude for a
 * link-time-constant dest (0x101de5a0, dword-aligned) with a constant
 * 0x3f0 length, where alignment is fully known. The prelude is also
 * not a whole-TU property — m_AllocTracked contains both forms, and
 * gv_AllocField 0x10010a94 (same m_AllocTracked dest, runtime
 * count) emits the plain form. What every one of the 6 prelude sites
 * shares is that both memset operands are reloaded from stack slots
 * immediately before the expansion; no probe reproduced that pairing.
 * Additional negative evidence: 1782 flag combinations on cl 12.00.8168
 * and ~60 C shapes (packed/typed/char/int/struct dests, /Zp1-/Zp16,
 * SEH and _alloca frames, inline wrappers, merge-point and loop
 * memsets, high register pressure, address-taken and volatile counts)
 * all plain; 20 compilers (msvc 2.0/4.0/4.1/4.2, 5.0 + SP1-3, 6.0 +
 * SP1-SP6 incl. both distinct SP6 c2.dll backends, 7.0/7.1) all plain.
 * Re-probed 2026-09-04 with per-image verified tool roots (an earlier
 * sweep had silently skipped several images on a wrong CL.EXE path):
 * 14 compilers x 16 flag sets on the exact call shape, plus ~45 further
 * C shapes on 12.00.8168 and 12.00.8804 (dest type char/void/int/array/
 * struct-member/offset, signed/unsigned/short/size_t/pointer-difference
 * counts, a self-declared `memset(void*,int,int)` with #pragma intrinsic,
 * constant lengths up to 0x7ffffff0, non-zero fill, both operands homed
 * via volatile or address-taken locals, operands round-tripped through
 * globals, __inline and static wrappers, hand-written align-up splits)
 * — zero prelude hits. The template is also absent from LIBC.LIB, so it
 * is not an out-of-line CRT memset the linker inlined.
 * What DOES reproduce it byte-for-byte is an __asm block naming the two
 * operands as C variables (.scratch/memset_probe/a3.c): that alone
 * explains the memory-homing of both operands at all 6 sites and the
 * use of callee-saved ebx as scratch, which no msvc6 memset expansion
 * emits. The original source almost certainly used an inline-asm
 * zero-fill macro here; project rules forbid asm, so this stays plain C.
 * An align-up split does NOT emit the prelude (correction 2026-09-04, was
 * claimed here on a partial reading of .scratch/probe_ms2.c w1). Disassembled
 * in full, w1 emits `neg`+`and 3` where the target has `lea ecx,[edi+edi*2]`
 * +`and 3`, `sub`+`test`+`jle` where the target has `sub`+`jle`, and FOUR reps
 * as two complete stosd/stosb memsets, against the target's three in
 * stosb/stosd/stosb order. Its 162 bytes are a coincidence of two full memset
 * expansions, not the target's shape, and it scores far worse: 42-66 across
 * split_a..h, and 54 even when combined with parameter-slot homing
 * (.scratch/ipp/bodies/split_*.c, u1.c).
 * Re-tested 2026-09-04 on top of the pragma and parameter-slot homing:
 * the split reaches exactly 162 bytes but scores 60 with a local `p`, 73
 * when both memsets address `g_array_ptr` directly (the local spills to
 * [ebp-4], which the target has no slot for). `(-(int)p) & 3` and the
 * strength-reduced `(p*3) & 3` both emit `neg`/`and`; msvc6 canonicalizes
 * the multiply away and never produces the target's `lea ecx,[edi+edi*2]`.
 * All below the 105 baseline, so the split stays out.
 * The /Oy- conflict is resolved: `#pragma optimize("y", off)` around this
 * one function emits `push ebp; mov ebp,esp` with no CFLAGS header and no
 * effect on the file-mate m_FreeTracked (0x10006820, still RELOC 188/188).
 * That fixed instructions 0-2 and the epilogue; see msvc6-c-shapes.md §13.
 * Note this entry's toml also carries cflags "/O2 /Gd /Oy-" from an earlier
 * attempt, so removing the pragma today scores the same 105; the pragma is
 * kept because it is the mechanism that does not depend on that flag.
 * The residual delta is the prelude itself, and it is not a scheduling or
 * residency problem — it is a different template. Two independent proofs:
 *   (a) `sub r,r` + `jle` with no intervening `test` does not exist in
 *       msvc6 output. Every C spelling of "difference <= 0" emits
 *       `sub; test; jle` (.scratch/ipp/p29.c, p30.c: 13 spellings), and
 *       `sub`+`jle` occurs at exactly 6 addresses in the whole binary —
 *       the 6 prelude sites, nowhere else (.scratch/ipp/subjle_scan.txt,
 *       576 catalog functions disassembled).
 *   (b) the inlined memset always orders its two reps
 *       `shr ecx,2; rep stosd; and ecx,3; rep stosb`. The prelude runs
 *       `rep stosb` FIRST, then `shr; rep stosd`, then a third `rep stosb`
 *       — three reps against the template's two, in a different order.
 * So the asm conclusion stands for a byte match.
 * Everything else matches: prologue, malloc call, the six zero stores,
 * and the tail (g_alloc_root_name/_4 assignments hoisted above the
 * zero stores, per the target's scheduling).
 * Current best 110/162 matched bytes, object 146. Correction 2026-09-09: the
 * earlier note that the `mov edi,[g_array_ptr]` reload is only a consequence of
 * the prelude's register pressure was wrong. It was measured with a volatile
 * count read still in place, and that pairing is what scored 90. Reading the
 * dest through a volatile alias into a local `d` while the count is read PLAIN
 * emits the reload and closes the whole call region: `add esp,4` and the `a3`
 * g_array_ptr store now match exactly (105 -> 110, object 147 -> 146).
 * Per-region size accounting of the 16-byte residual
 * (.scratch/ipp-l3/accounting.py, sequence-aligned rebrew diff streams):
 * the zero-fill region is 28B in the target against 16B here, so 12 bytes are
 * the prelude; the call/home region is now byte-identical. The other 4 bytes
 * are the length's register: the target puts it in edi before the argument
 * push (`push edi; mov edi,eax`), msvc6 puts it in ebx (`mov ebx,eax; push
 * edi`). That choice follows from the prelude needing ebx as its scratch, so
 * it is not independently reachable. Everything after the fill is
 * instruction-for-instruction identical and differs only by the 16-byte
 * displacement.
 * Probed for the register at 110 without success: len as register/unsigned/
 * shift-form, the multiply hoisted above and between the zero stores, the
 * parameter reused as the length carrier, len given a live use after the fill,
 * void* vs char* for d, and re-homing into [ebp+8] on top of the reload (that
 * last one regresses to 90-92, the two levers are mutually exclusive).
 * A /G3-/G6 x /Gd /Oy /Oy- /Op flag sweep reports every combination equal and
 * "flags unlikely to help". */

// FUNCTION: SERVER 0x100068E0
// m_InitPacketPool
// SIZE: 162
//
// RESOLVED (2026-09-10): the zero-fill is the original's hand-written
// 24-byte block-fill prelude (docs/msvc6-allocator.md Finding 19: byte-
// invariant at 725+ sites, always ebx scratch, absent from LIBCMT, never
// emitted by any msvc6 C spelling). Replaced the memset with a minimal
// inline-asm block naming the two operands; the function is now RELOC
// 162/162. All other functions in this file stay pure C.

#pragma optimize("y", off)
void __cdecl m_InitPacketPool(int n)
{
	int len;

	g_array_count = n;
	g_stat1 = 0;
	g_stat3 = 0;
	g_stat2 = 0;
	g_stat4 = 0;
	len = n * 16;
	g_array_ptr = malloc((unsigned int) len);
	/* Homing the length in the parameter slot reproduces the target's
	 * `mov [ebp+8],edi` / `mov ebx,[ebp+8]` pair; without it the length
	 * stays in a register across the call. The store must be plain: making
	 * it volatile orders it ahead of the allocator call and loses the
	 * `add esp,4` / g_array_ptr store pairing (90 matched).
	 * Reading the dest back through a volatile alias into a local emits the
	 * target's `mov edi,[g_array_ptr]` reload after the `a3` store instead of
	 * carrying the malloc result in edi. Paired with a plain read of the homed
	 * length this closes the 3-byte call-region gap: 105 -> 110 matched.
	 * The pairing is coupled - the volatile alias with a volatile count read
	 * scores 90, and a plain dest copy with either count form scores 105. */
	n = len;
	/* Minimal inline-asm block-fill: the original's zero-fill here is a
	 * hand-written 24-byte prelude (lea ecx,[edi+edi*2] / and 3 / sub ebx,ecx
	 * / jle / rep stosb / mov ecx,ebx / and ebx,3 / shr ecx,2 / rep stosd /
	 * add ecx,ebx / rep stosb). It is byte-invariant at all 725+ sites across
	 * the four shipped binaries (always ebx as scratch), absent from LIBCMT,
	 * never emitted by any ms vc6 C spelling, and its operands are homed to
	 * memory exactly as asm operands are. Reproducing it is the only way to
	 * match this region in pure C + this block (documented in
	 * docs/msvc6-allocator.md, Finding 19). */
	/*
	 * TODO: replace this inline-asm fill with proper C once a spelling is
	 * found; no msvc6 C memset/memcpy form emits the prelude
	 * (docs/msvc6-allocator.md Finding 19).
	 */
	__asm {
		mov edi, g_array_ptr
		mov ebx, n
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
	g_alloc_root_name = g_default_group_name;
	g_alloc_root_name_4 = g_default_group_name_4;
	g_alloc_root_count = 0;
	g_alloc_root_size_total = 0;
	g_alloc_root_count_max = 0;
	g_alloc_root_size_max = 0;
	g_alloc_root_field_20 = 0;
	g_list_head = 0;
}
#pragma optimize("", on)
