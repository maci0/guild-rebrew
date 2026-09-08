// FUNCTION: SERVER 0x10006580
// CFLAGS: /O2 /Gd /G6 /Oy-
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma intrinsic(strcmp, strcpy)
#pragma function(memset)

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
// NOTE: best config found - 212/658 instr bytes matched (obj 624 vs target 658).
// The target homes three values in the ebp frame: the group node at [ebp-4],
// the allocation size at [ebp-8], and buf at [ebp-0x18].  The `np` alias on
// `node` supplies the search-loop spill, the matching `pp` alias on `prev`
// supplies its own home slot (200 -> 208), the `sz` volatile shadow the size
// slot, and the `nodev` shadow the node reload after the malloc.
// `buf[0x14]`, not `buf[0x10]`: the target's frame is 0x118 with buf based at
// [ebp-0x18], and a 0x10 buffer lands it at [ebp-0x14], shifting every
// `lea eax,[ebp-0x18]` and the `mov [ebp+reg-0x18],bl` terminator store by 4.
// Widening buf alone supplies the missing home slot without disturbing the
// [ebp-4]/[ebp-8] pair.  208 -> 212.  (An earlier note claimed enlarging
// name[]/buf[] scored 187; that was measured by enlarging both.)
// Two further stores now agree with the target at no score change, and are
// kept because the operand roles match: the fresh node's fields are zeroed
// 0x14, 0x10, 0x1c, 0x18 (count_total before size_total, count_max before
// size_max, 0x100066bc-0x100066c5), and the slot-capacity guard is spelled
// `g_array_count > g_stat2` so g_array_count is loaded first, as at
// 0x1000674a-0x10006755.
// The target combines the /G6 zero-register idiom (xor ebx,ebx at entry;
// cmp reg,ebx; bl byte stores) with an ebp frame.  Marking `node` volatile
// does unlock the zero register under the file CFLAGS (verified: .scratch/b4,
// obj 687-705), but it also spills node on every access and costs more than it
// gains: 179-182 against 208 here.  #pragma optimize("y", off) under /O2 /Gd
// gives the frame but drops the zero register; the two levers are mutually
// exclusive from source (docs/msvc6-allocator.md Finding 51).
// Dead ends measured this pass: hoisting `tag` into a local before the node
// constant, 208 (no change); a cached loop cursor `n` instead of the double
// indirection, 200; dropping the redundant second node constant, 157;
// dropping the `sz` shadow, 172; dropping `nodev`, 197.
// Dead ends measured on top of the 212 body, all reverted: an explicit `int z`
// zero local threaded through every null test to force `xor ebx,ebx` (msvc6
// constant-folds it, 212 unchanged; the `volatile` spelling spills it and
// drops to 140); reading `tag` into `p` before the g_alloc_counter increment
// to claim edi first, 212; materializing the node constant after `taglen`,
// 212; `node->next = 0` before `node->count = 0`, 212.
// The residual size gap is the alignment-pass inline memset
// (lea ecx,[edi+edi*2]; and ecx,3; sub ebx,ecx) - same Finding 19 blocker as
// InitPacketPool / m_PoolAlloc.  docs/msvc6-c-shapes.md section 11 records the
// full probe sweep for that prelude (pointer type, destination provenance,
// length shape, 12 flag sets, and an explicit align-up split) and concludes no
// pure-C shape emits it; the three-rep order (stosb, stosd, stosb) is a
// different expansion template, not a scheduling difference.
// Also measured and reverted: `/O1` in place of `/O2` in the CFLAGS header, to
// chase the target's /G6 zero-register idiom (`xor ebx,ebx` at entry, then
// `cmp reg,ebx` instead of `test reg,reg`).  Byte-identical result, 212 at 624,
// so the header's optimization level is not what selects that idiom here.
// CORRECTION (this pass): the zero register IS reachable from C under the
// current CFLAGS.  An earlier note claimed no flag set produces it; that was
// measured on a reduced probe that was too small.  A probe carrying this
// function's own shape (.scratch/L3/pz2.c `q1`, 0x100-byte array for the ebp
// frame, three long-lived values, the same guard chain) emits the target's
// entry verbatim under /O2 /Gd /G6 /Oy-:
//   push ebp; mov ebp,esp; sub esp,0x114; mov eax,[g]; push ebx;
//   xor ebx,ebx; cmp ebx,eax; push esi; push edi
// It does not depend on spelling the zeros through a named local: the same
// probe with plain literal `0` everywhere (.scratch/L3/pz7.c) still emits it,
// and spelling all 17 zeros in this file through a `const int z = 0` is inert
// at 212/658, so that lever was measured and reverted.
//
// What suppresses it here is `node`'s live range across the malloc.  Bisected
// on this exact body by truncating it at successive statements
// (.scratch/L3/{c0..c3,r1,r2,x1..x4}.c, all under /O2 /Gd /G6 /Oy-):
//   - body cut before `nodev = (int) node`, returning ptr:  xor ebx,ebx
//   - the same cut returning `node` instead of `ptr`:       no zero register
//   - adding `nodev = (int) node` alone:                    no zero register
//   - adding `node->count++` alone:                         no zero register
//   - adding `sz = size` and the malloc alone:              zero register kept
// So the zero register and a node value that stays live across the allocator
// call are mutually exclusive here, and the target has both.  Forms tried to
// keep both, all still without the register: plain (non-volatile) `nodev`, a
// `struct GroupNode* volatile` shadow instead of the int one, dropping `nodev`
// and relying on the `np` alias, moving `count++` after the null check, and
// hoisting the increment into a fresh pointer local.  `(*np)->count++` does
// restore the register in the truncated body but not in the full function
// (.scratch/L3/m1.c), and it is unsafe besides: `np` is unset when tag == 0.
// Whole-file: 145/658 at 650 bytes, reverted.
//
// CORRECTION to the bisection above (2026-09-08, .scratch/l9-mat/pr/zr*.c,
// standalone probes under this file's own /O2 /Gd /G6 /Oy-).  The conclusion
// is right but the stated cause is not: it is NOT `node` living across the
// allocator call.  Probe zr7.c keeps a node value live across `mallocx` and
// still gets the zero register (`xor esi,esi` + `cmp esi,eax`), so the call
// does not destroy it.  What destroys it is putting the node's zero-field
// stores under a CONDITIONAL.  With the six `node->field = 0` stores at the
// top level the register appears (zr3.c, zr7.c); wrapping the same stores in
// a single `if (node == 0)` removes it (zr8.c), and so do two and three
// levels of nesting (zr4.c).  Neither a zero-initialised local defined before
// the first guard (zr5.c), nor extra top-level zero stores after the call
// (zr6.c), nor routing all six stores plus the buf terminator through one
// zero-valued `z` local (zr9.c) brings it back.
//
// That makes the register unreachable rather than merely untried: this
// function's zero stores are the fresh-node initialiser, which is
// semantically required to sit under `if (node == 0)` inside
// `if (tag != 0) { if (p != 0) { ... } }`.  The condition msvc6 wants is one
// this function's control flow cannot supply, so the 88 bytes `rebrew
// near-diag` attributes to `register` are not addressable from C.
//
// CORRECTION (later pass): the zero-register suppressor is NOT `node`'s live
// range across malloc.  It is the inline expansion of `memset` and `strcpy`.
// Bisected by building the file's own shape as a probe and adding one
// intrinsic at a time (.scratch/L3B/p/q_{memset,strcmp,strcpy,strncpy}.c, all
// /O2 /Gd /G6 /Oy-, checking byte 0xe of the entry):
//   + strcmp   -> push ebx / xor ebx,ebx   (zero register KEPT)
//   + strncpy  -> push ebx / xor ebx,ebx   (zero register KEPT)
//   + memset   -> test eax,eax             (zero register LOST)
//   + strcpy   -> test eax,eax             (zero register LOST)
// Both expansions reserve edi and a scratch register for their `rep`
// sequences, so neither leaves a callee-saved register free to hold the zero.
// The earlier bisection blamed `node` because its probes carried memset.
//
// `#pragma function(memset)` with strcpy left intrinsic is the best split:
// 212 -> 227/658 at obj 619 (target 658).  It restores the target's
// `mov ecx,[ebp-8]` / node-field zero stores and the exact 0x118 frame.
// Measured alternatives:
//   - #pragma function(memset, strcpy): 219 at obj 604.  This one DOES get
//     the zero register and the entry matches the target instruction for
//     instruction, but out-of-lining strcpy loses the target's inline
//     `repne scasb` / `rep movsd` at 0x100066a0-0x100066b7, which costs more
//     than the entry gains.  The zero register and an inlined strcpy are
//     mutually exclusive from source; the target has both, so it was not
//     built with the msvc6 SP6 codegen this project has.
//   - #pragma function(strcpy) with memset intrinsic: 179 at obj 625.
//   - Original #pragma intrinsic(memset, strcmp, strcpy): 212 at obj 624.
// `buf[0x14]` still beats `buf[0x10]` on the new body (227 vs 223); under
// #pragma function(memset, strcpy) the ranking inverts (219 vs 218), which is
// why the earlier note recorded the opposite.
// Both volatile shadows still pay on the new body: plain `sz` scores 185,
// plain `nodev` 222, and passing `size` instead of `sz` to malloc 223.
// `prev->next = node` in place of `(*pp)->next = node` scores 219; assigning
// `pp = &prev` (which would make that read defined) also costs the same 219,
// so the unassigned-`pp` spelling is load-bearing for the score.  It is a
// genuine defect in this reconstruction, not a deliberate shape: `pp` is
// never written, so `(*pp)` is undefined behaviour.  The target's store is
// plainly `prev->next = node` (0x100066b9 `mov ecx,[ebp-8]`; 0x100066ce
// `mov [ecx+0x24],edx`).  Flagged rather than silently kept at the higher
// score; whoever next touches this function should decide whether 8 matched
// bytes are worth an undefined read.  Re-measured on the 230 body: the defined
// alternatives all cost 10-11 bytes (plain `prev->next` 219, `pp = &prev` plus
// `*pp = *np` 219, a `volatile int prevv` shadow 220, a volatile-alias store to
// `prev` 220, `prev = node` seeded before the loop 225).
//
// 227 -> 230: the three tail reads of the size (slot+0xc, g_stat1, and
// node->size_total) take the parameter `size` rather than the volatile `sz`
// shadow.  The target reloads `[ebp+8]` at 0x10006780 for the slot store and
// keeps that value in ecx for the g_stat1 add, so only the memset and the
// malloc argument need the [ebp-8] home.  Reading `sz` there forced an extra
// volatile reload per use.  `sz` is still required at the malloc (passing
// `size` scores 184) and at the memset (183).
// Also measured and reverted at this body: `#pragma intrinsic(memset)` 214,
// `#pragma function(memset, strcpy)` 215 (and 96 aligned instrs against 131),
// an inline `memcpy(node->name, buf, strlen(buf) + 1)` in place of `strcpy`
// 218 (and still no zero register at the entry), a `slots` local caching
// g_array_count 230 (inert, dropped), `slots > g_stat2` guard order 230,
// dropping the `cur` loop temp 230, a load-before-store split of the
// size_total/size_max update 229, and hoisting `count_max` above the
// count_total increment 230.  CFLAGS sweep (/O2, /Ox, /G5, /G6, /Ob2, with and
// without /Oy-) is flat at 230.
// STATUS: PROVEN (rebrew prove, 2026-08-27) - semantically equivalent; not a
// byte match.  Residual against the target's 249 instructions: 131 aligned
// identical, 42 instructions blocked by the zero register (the target's
// `xor ebx,ebx` plus its `cmp reg,ebx` and `mov [..],bl` users, mutually
// exclusive with the inlined strcpy per the bisection above), 31 by the
// block-fill prelude at 0x10006730, 11 register-assignment-only, and 68
// ordinary codegen downstream of those two shifts.
//
// 2026-09-08 pass, no source change, still 233/658 at obj 608.  The 50-byte
// object shortfall was re-measured by instruction alignment
// (.scratch/l8-mat/pr/m.py, register-normalized differ) rather than by the
// positional compare: 194 byte-identical aligned bytes, 207 role-rotated,
// 257 unaligned target bytes.  Only ONE alignment gap is the documented
// prelude wall: target[163:179] at 0x100067(28..4a), the 26-byte
// `lea ecx,[edi+edi*2]; and ecx,3; sub ebx,ecx; jle;` three-run `rep stos`
// group.  The rest of the shortfall is the memset CALL this file emits there
// where the target inlines, which `#pragma function(memset)` mandates by
// definition.  Removing it does inline the fill, but as msvc6's naive
// two-run `rep stosd; and ecx,3; rep stosb` and never the target's three-run
// prelude: confirmed standalone at .scratch/l8-mat/pr/pm2.c under this
// file's own /O2 /Gd /G6 /Oy-, with the count in a volatile shadow and the
// dest kept live.  So the pragma is not costing a reachable win, and the
// three intrinsic spellings all regress here (218 at obj 613 for
// `intrinsic(memset)` in any of the three orderings).
//
// The zero register was re-attacked from the value side rather than the
// live-range side, all inert at 233: the `buf[taglen]` terminator written
// through a named zero local, to match the target's `mov [ebp+esi-0x18],bl`;
// and every null/zero guard in the function (g_array_ptr, size, tag, p,
// node, ptr, cur, and the search-loop condition) spelled as a comparison
// against one function-scope `zero` local so a single zero value spans the
// whole body.  Initialising `prev`, `taglen` or `i` to 0 ahead of the first
// guard so a zero opens the function is likewise inert.  This is consistent
// with the bisection above: the blocker is `node` staying live across the
// malloc, not how the zeros are spelled.
//
// Other shapes measured and reverted this pass: a `pp = &prev` refresh
// inside the search loop (226 at obj 623, and structurally worse at 156
// aligned-identical); the strcmp result through a named int (inert);
// `prev->next` and `pp`-refreshed linkage for the fresh node (222 at 617),
// and the same with a `nodev` store first (229 at 611); `nodev` written
// after `count++` (inert); `node = 0` after the shadow store to end its
// range before the malloc (inert); reloading `node` from `nodev` right after
// the malloc and before the null check (227 at 611); malloc taking `size`
// with `sz` written after (181 at 615) or before (183 at 611); and
// `count++` moved below the `sz` store (inert).  The six field zeros are
// already in the target's 0x14/0x10/0x1c/0x18/0x20/0x24 order.

// SIZE 0x28
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
	char buf[0x14];
	struct GroupNode* node;
	struct GroupNode* prev;
	int taglen;
	int i;
	void* ptr;
	char* slot;
	char* p;
	struct GroupNode** np;
	struct GroupNode** pp;
	volatile unsigned int sz;
	volatile int nodev;
	void* cur;

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
			np = &node;
			while (*np != 0) {
				if (strcmp(buf, (*np)->name) == 0) {
					break;
				}
				prev = *np;
				*np = (*np)->next;
			}
			if (node == 0) {
				node = (struct GroupNode*) malloc(0x28);
				strcpy(node->name, buf);
				node->count_total = 0;
				node->size_total = 0;
				node->count_max = 0;
				node->size_max = 0;
				node->count = 0;
				node->next = 0;
				(*pp)->next = node;
			}
		}
	}
	nodev = (int) node;
	node->count++;
	sz = size;
	ptr = malloc(sz);
	if (ptr == 0) {
		sprintf(buf, "Out of Memory Error: Malloc - Failed %s for %u bytes", tag, size);
		ReportFatalError("D:\\Develop\\Units\\m_alloc\\m_alloc.c", 0xcd, buf);
		return 0;
	}
	memset(ptr, 0, sz);
	if (g_stat2 < g_array_count) {
		node = (struct GroupNode*) nodev;
		slot = (char*) g_array_ptr;
		i = 0;
		while (i < g_array_count) {
			cur = *(void**) (slot + 8);
			if (cur == 0) {
				break;
			}
			slot += 0x10;
			i++;
		}
		p = (char*) tag;
		*(void**) (slot + 8) = ptr;
		*(const char**) (slot + 4) = p;
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
