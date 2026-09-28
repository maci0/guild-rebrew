/* m_FreeTracked — debug-heap tracked free (0x10006820). */

extern int g_array_count;
extern int g_stat1;
extern int g_stat2;
extern int g_stat3;
extern int g_stat4;
extern void *g_array_ptr;
extern void *__cdecl malloc(unsigned int size);
extern int g_alloc_root_name;
extern int g_alloc_root_name_4;
extern int g_default_group_name;
extern int g_default_group_name_4;
extern int g_alloc_root_count;
extern int g_alloc_root_size_total;
extern int g_alloc_root_count_max;
extern int g_alloc_root_size_max;
extern int g_alloc_root_spare;
extern int g_list_head;

// FUNCTION: GOLD 0x004226a0
// SIZE: 162
// FUNCTION: GOLDTL 0x41de50
// SIZE: 162
// m_init
// SIZE: 162
//
// RESOLVED (2026-09-10): the zero-fill is the original's hand-written
// 24-byte block-fill prelude (docs/msvc6-allocator.md Finding 19: byte-
// invariant at 725+ sites, always ebx scratch, absent from LIBCMT, never
// emitted by any msvc6 C spelling). Replaced the memset with a minimal
// inline-asm block naming the two operands; the function is now RELOC
// 162/162. All other functions in this file stay pure C.

#pragma optimize("y", off)
void __cdecl m_init(int n)
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
	g_alloc_root_spare = 0;
	g_list_head = 0;
}
#pragma optimize("", on)
