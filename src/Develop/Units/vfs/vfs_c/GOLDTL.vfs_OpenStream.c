// FUNCTION: GOLDTL 0x430cb0
// SIZE: 704
#include "../../Error/error.h"
#include "../../m_alloc/m_alloc.h"
#include "zlib.h"

#include <ctype.h>
#include <stdio.h>
extern unsigned int __cdecl crc32(unsigned int crc, unsigned char* buf, unsigned int len);
/* Opens a VFS stream over a caller buffer. Parses the mode flags
 * (N = none, R = read, W = write, Z = zlib) and initializes the
 * stream structure with the matching inflate/deflate setup.
 *
 * Byte match: 155/704 (obj 681 vs target 704), SIZE_MISMATCH, PROVEN retained.
 * Levers that moved it from the 94/704 baseline:
 *   - `sp`, a pointer alias on `idx`, homes the switch selector in memory
 *     (94 -> 97).
 *   - Flattening the mode14/mode13 nest into explicit labels, with the
 *     plain-buffer setup as a shared out-of-line block reached from both the
 *     size check and the two header-byte mismatches, matches the target's
 *     block layout (97 -> 114).
 *   - `mode14` declared volatile keeps it in the target's [esp+0x20] slot
 *     instead of a register, which reorders the whole flag prologue
 *     (114 -> 155).
 *   - The inflateInit2_ result tested as `== 0` with the fallthrough to
 *     finalize matches the target's `je` polarity (neutral on score, correct
 *     shape).
 *
 * Residual: the target's frame is 0xc and ours is 8, so every [esp+...]
 * displacement is off by 4 from index 0 and the positional compare cannot
 * recover. The extra dword is a slot msvc6 reserves for a fourth live value
 * that no source shape reproduced: unused padding locals are eliminated
 * (94), widening mode14/mode18 to int changes the slot count but not the
 * layout (92/94), int mode13 gives 97, and the `sp` alias gives 97 without
 * widening the frame.
 * Other dead ends, each re-tested: descending header-byte store order to
 * match the target's [edi+8]..[edi+3] (155, no change), a `zp` pointer local
 * folded before the inflate stores (155), a `flags` temp for the 0x13c
 * read-modify-write (155), an `m14` copy read before that store (155),
 * volatile mode13 (97), volatile mode18 (78), and routing the header-match
 * path through a shared mode18 test (102).
 *
 * Further dead ends: `int mode18`, to give it the dword slot the target
 * reloads at 0x1000926b, 104 at obj 669; an `unsigned char*` alias on
 * mode18 to force memory residency without volatile's ordering, inert
 * (155) whether only the initializing store or every access goes through
 * it; splitting the buf/size guard so the three flag stores interleave in
 * the target's mode14, mode18, mode13 order (0x1000902f), 118; dropping
 * the `sp` alias entirely, inert (155), so it is no longer load-bearing.
 *
 * This session, 155/701 -> 406/701: `int mode14` with all accesses at byte
 * width (`*(unsigned char*) &mode14`) gives the target's sub esp,0xc frame
 * with the same 0x13/0x14/0x18 slots, and reading mode14/13 through the
 * byte alias at the branch (not as dword) aligns the flag prologue through
 * the switch arms. The `idx = 0` init plus init order
 * (mode18, mode13, mode14-last) is the current best prefix. Case 4/9 arms
 * must stay PLAIN dword stores (`mode14 = 1/0`): byte-width arm stores
 * cost the frame (689, 151). Remaining prefix delta is 2 bytes: the
 * target's `xor eax,eax` between the buf load and `mov bl,1` (shared
 * early-return zero), plus case 0 joining case 12's `mov [esp+0x13],0`
 * tail instead of its own store. Post-prologue the next cluster is the
 * mode14 reload order (`mov cl,[esp+0x20]` before `mov esi,eax`, ours
 * reversed in al). STATUS: PROVEN retained; not a byte match.
 *
 * Follow-up session, held 406/693 (no score change; negative results only).
 * Measured via isolated probes (`.scratch/ovs_body*.c`, `ovs_sweep*.sh`):
 *   - init order is the prologue lever: only (18,13,14-last) with `idx = 0`
 *     first gives sub esp,0xc with slots 0x14/0x18/0x13; any permutation
 *     moves a slot. The `sp` alias is inert (kept, matches decomp).
 *   - the guard is fixed: `buf==0||size<=0` first (mov+cmp+je+jbe) is what
 *     the file has; size-first and `&&`+goto spellings flip a branch.
 *   - the target's `xor eax,eax` + `mov bl,1` needs a fourth live value:
 *     probes with only the real locals never emit it (xor ecx/xor ebx at
 *     most); a fifth live value (`m`, global idx, volatile idx, param
 *     homing, early alloc+RMW) does emit `xor` but in the wrong slot and
 *     order, never between the buf load and `mov bl,1`. The zero is the
 *     shared early-return value: the target never materializes the
 *     `return 0` constant elsewhere, ours does (`xor ebx` before the loop).
 *   - /O1 and /Ot give frame-pointer prologues, /Ox matches /O2: no flag
 *     lever. The CFLAGS header stays /O2 /Gd (matches metadata). */
 /* This session, 406/701 -> 450/701 (obj 693 vs target 704), PROVEN retained.
 *   - Loop switches on toupper(*p) directly with char cases
 *     ('N'/'R'/'W'/'Z'): the compiler emits the target's `add eax,-0x4e`
 *     plus mapping-table form for the raw value. The old `- 0x4e` spelling
 *     emits `sub` and is byte-different. Mapping is bijective, behavior
 *     unchanged. The CRT supplies toupper.
 *   - `int r = 0` result var with early `goto done` / tail `r = stream`
 *     reproduces the prologue `xor eax,eax` (shared early-out zero skipping
 *     the tail `mov eax,esi`) and the exact push/test/store prologue order.
 *   - Init order with `r = 0` first reproduces the target's
 *     `xor; mov bl,1; movb [0x14],1; test edi` sequence.
 *   - Loop entry pair (`mov eax,[esp+0x28]; mov esi,eax`) comes free from
 *     switching on the call result (two consumers: switch in eax, cursor
 *     in esi). The old `*sp = ...; switch (*sp)` form loads esi directly.
 *   - Residual, all measured: entry tests `mov al,[eax]; test al,al`
 *     against `cmpb [eax],0` (+1B, no variant pairs it with cmpb);
 *     post-alloc loads stream before mode14 (esi/al) against the target's
 *     mode14-first (cl) order; t18 mode18-test sits inline against far;
 *     size branch uses near jbe against short ja (+4B); header compares use
 *     ecx/edx against eax/edx with a 6B `mov ecx,[addr]` against the
 *     target's 5B A1 `mov eax,[addr]` (+1B); finalize count in edx against
 *     eax. Total gap is 11B (693 vs 704).
 *
 * True size is 701, not the 704 in the annotation nor the 667 in
 * db/server.dll_functions.csv. Disassembly of 0x10009020..0x100092e0:
 * code ends at the `ret` at 0x100092ba, one `nop` pad at 0x100092bb, the
 * 5-entry switch jump table at 0x100092bc, and the 13-byte case index map
 * at 0x100092d0 ending at 0x100092dd. The three bytes from 0x100092dd to
 * the next function at 0x100092e0 are inter-function alignment, so 704
 * over-counts by 3 and 667 counts only the code, excluding both tables.
 * `rebrew test` already compares 701, so the score is against the right
 * length.
 *
 * The 11B size gap is closable but costs alignment. Two changes together
 * give obj 701 exactly:
 *   - `switch (toupper(*p))` with the loop reading `*p` directly (no
 *     `c` hoist) emits the target's `cmp byte ptr [eax],0` entry test and
 *     makes the whole flag loop byte-exact through the jump table.
 *   - The target loads mode18 from [esp+0x18] twice in the sprintf tail
 *     (`mov edx,[esp+0x18]` early, `mov eax,[esp+0x18]` later, each
 *     zero-extended); ours folded both arguments into one load. Passing
 *     the second argument through `*(volatile unsigned char*) &mode18`
 *     forces the reload. This needs `int mode18` with byte-width access
 *     (`*(unsigned char*) &mode18`), the same treatment mode14 already
 *     has: with `unsigned char mode18` the volatile read moves the slot
 *     off [esp+0x18] and the object overshoots to 705.
 * That combination scores 277/701 at obj 701, below the 450/701 kept here,
 * because the positional compare charges the surviving misalignment. By
 * shift-aligned instruction match it is ahead, 170/209 (81.3%) against
 * 169/209 (80.9%), and near-diag matched bytes rise 471 to 486. The
 * 450/693 form is retained since match_count is the recorded score.
 *
 * Residual on the size-correct form, measured: the target keeps mode14 in
 * `cl` (loaded before `mov esi,eax`, while eax still holds the alloc
 * result), which frees eax for the header compares and the finalize RMW;
 * ours loads it into `al` after `mov esi,eax`, so the header compares fall
 * to ecx and the second global loses the 5B A1 encoding. `volatile` on
 * that read pins the order but drops the object to 697. Also unreachable:
 * the mode13 test as `je` (inverting it relocates the plain-buffer block
 * out of line, section 17), the `mode18 = 0` store ahead of the
 * [esi+0x100] store (volatile there costs 4B), and the finalize
 * interleave, where the target hoists the g_stream_count increment between
 * the two flag reads.
 *
 * Follow-up session, held 450/701 (no score change). The two forms are
 * mutually exclusive and the boundary is now located exactly.
 *
 * The 450 form is byte-identical over 0x10d..0x212, the whole inflate and
 * deflate setup, and diverges only in the flag loop and in the finalize
 * tail. Its single loop fault is the entry test: the target emits
 * `cmp byte ptr [eax],0` where the `c` hoist gives `mov al,[eax]` plus
 * `test al,al`, one byte wider. Reading `*p` in the switch removes that
 * byte and makes the loop byte-exact through the jump table, but the same
 * byte then shifts every following block, so match_count falls to 272 (277
 * once the object reaches 701). Three loop spellings that keep the hoist
 * were tried and all reproduce the wide test: an explicit `c = *p` first
 * statement (129), a `while (*p)` head (141), and a `c != 0` condition on
 * a lookahead `p[1]` (153). A `do/while` with the `*p` entry guard gives
 * the narrow test and the same 272. So the byte is not separable from the
 * shift, and 450 is the maximum for the aligned-body family.
 *
 * On the size-correct 701 family the residual is 2 basic blocks, not
 * registers: near-diag reports 27 candidate blocks against the target's
 * 29, verdict STRUCTURAL at 58 percent of the delta, and the target's
 * extra pair is the `test bl,bl` / `je 0xca` at 0x109 that enters the
 * plain-buffer body BELOW its `mov [esp+0x18],bl` store, so the zero store
 * is skipped on the mode18 path. Every source spelling of that entry was
 * measured and none reproduces it: a second label inside plain_setup
 * (263), a guarded `if (mode18 != 0) mode18 = 0;` (155), a redundant
 * self-store on the branch (450, inert), and sinking the clear into the
 * three predecessors (135). Block placement was probed the way section 17
 * describes and behaves as documented: check_header first (129),
 * test_mode18 first (364), test_mode18 past the return (265), and a second
 * predecessor to force it out of line (240).
 *
 * Also ruled out this session. A `--flag-sweep-only` run scores every
 * combination identically (375326.84 across /G3../G4 with /Gd /Oy /Op), so
 * there is no CFLAGS lever. The handoff's parameter-reuse lever does not
 * apply: walking `mode_flags` itself instead of `p` scores 135 in both the
 * hoisted and the direct spelling, because the parameter slot is reloaded
 * per iteration. Tail probes are all inert on the 450 form (450 unless
 * noted): the g_stream_count read-modify-write split into a temp, both sprintf
 * mode18 arguments as masked dwords, a mode14 temp read before the
 * increment, the flag byte built through a named temp, and explicit casts
 * on the xor and shift operands. Forcing the second sprintf argument to
 * reload does emit the target's two `[esp+0x18]` loads and its push order,
 * but costs 4 bytes of object (obj 705) for no match_count. */

extern int g_stream_count;
extern void* __cdecl m_PoolAlloc(void* head, int size, int max_items);
extern void __cdecl m_pool_free(void* pool, void* item);
extern int __cdecl sprintf(char* buf, const char* fmt, ...);

int __cdecl vfs_OpenStream(unsigned char* buf, unsigned int size, char* mode_flags)
{
	char* stream;
	char* path_cursor;
	char current_char;
	int result;
	int mode14;
	unsigned char mode13;
	unsigned char mode18;

	result = 0;
	*(unsigned char*) &mode14 = 1;
	mode18 = 1;
	mode13 = 1;
	current_char = 0;
	if (buf == 0 || size <= 0) {
		goto done;
	}
	for (path_cursor = mode_flags, current_char = *mode_flags; *path_cursor != 0; path_cursor++, current_char = *path_cursor) {
	switch (toupper(current_char)) {
		case 'N':
			mode18 = 0;
			mode13 = 0;
			break;
		case 'R':
			*(unsigned char*) &mode14 = 1;
			break;
		case 'W':
			*(unsigned char*) &mode14 = 0;
			break;
		case 'Z':
			mode18 = 1;
			mode13 = 0;
			break;
		default:
			break;
		}
	}
	stream = (char*) m_PoolAlloc((void*) 0x10034670, 0x140, 0x10);
	*(unsigned char*) (stream + 0x13c) = (unsigned char) ((*(unsigned char*) (stream + 0x13c) & 0xeb) | 0x22);
	if (*(unsigned char*) &mode14 != 0) {
		if (mode13 == 0) {
			goto test_mode18;
		}
		if (size > 10) {
			goto check_header;
		}
	plain_setup:
		mode18 = 0;
		*(char**) (stream + 0x100) = (char*) buf;
		*(unsigned int*) (stream + 0x104) = size;
		*(int*) (stream + 0x108) = 0;
		goto finalize;
	check_header:
		if (buf[0] != *(int*) 0x10029450) {
			goto plain_setup;
		}
		if (buf[1] != *(int*) 0x10029454) {
			goto plain_setup;
		}
		mode18 = 1;
		goto inflate_setup;
	test_mode18:
		if (mode18 == 0) {
			goto plain_setup;
		}
		{
inflate_setup:
			*(char**) (stream + 0x100) = (char*) buf + 10;
			*(unsigned int*) (stream + 0x104) = size - 10;
			*(int*) (stream + 0x10c) = 0;
			*(int*) (stream + 0x110) = 0;
			*(int*) (stream + 0x120) = 0;
			*(int*) (stream + 0x124) = 0;
			if (inflateInit2_((void*) (stream + 0x100), -0xf, (char*) 0x1002706c, 0x38) == 0) {
				goto finalize;
			}
			goto cleanup;
		}
	}
	if (mode18 != 0) {
		if (size < 0x12) {
			goto cleanup;
		}
		buf[0] = *(unsigned char*) 0x10029450;
		buf[1] = *(unsigned char*) 0x10029454;
		buf[2] = 8;
		buf[8] = 0;
		buf[7] = 0;
		buf[6] = 0;
		buf[5] = 0;
		buf[4] = 0;
		buf[3] = 0;
		buf[9] = 0xb;
		*(char**) (stream + 0x100) = 0;
		*(unsigned int*) (stream + 0x104) = 0;
		*(char**) (stream + 0x10c) = (char*) buf + 10;
		*(unsigned int*) (stream + 0x110) = size - 10;
		*(int*) (stream + 0x120) = 0;
		*(int*) (stream + 0x124) = 0;
		*(int*) (stream + 0x138) = crc32(0, 0, 0);
		if (deflateInit2_((void*) (stream + 0x100), -1, 8, -0xf, 8, 0, (char*) 0x1002706c, 0x38) != 0) {
			goto cleanup;
		}
		*(int*) (stream + 0x114) = 0xa;
	} else {
		*(char**) (stream + 0x10c) = (char*) buf;
		*(unsigned int*) (stream + 0x110) = size;
		*(int*) (stream + 0x114) = 0;
	}
finalize:
	if (stream != 0) {
		g_stream_count++;
		*(unsigned char*) (stream + 0x13c) = (unsigned char) (((*(unsigned char*) (stream + 0x13c) & 0xf6) ^ (*(unsigned char*) &mode14 & 1)) | ((mode18 & 1) << 3));
		sprintf(stream, (char*) 0x100294a4, buf, size, mode18, mode18);
	}
	result = (int) stream;
done:
	return result;
cleanup:
	m_pool_free((void*) 0x10034670, stream);
	return 0;
}


