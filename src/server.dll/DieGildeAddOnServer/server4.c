#include "../Units/Error/error.h"
#include "../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"
#include "server_internal.h"

void __cdecl srv_LogWinsockError(int err_code);
void __cdecl srv_InitBuildingTypeTable(void);
/* Console control handler for graceful shutdown.
 * Handles Ctrl+C and close events. Always returns 0. */

/* Winsock error strings live in winsock_data.c (ordered between m_alloc2 and
 * trees so they land at 0x10028bdc).  Reference them by name — do NOT also
 * spell the same text as a string literal or the bytes emit twice. */
extern char s_Unknown_winsock_error_u_10028bdc[];
extern char s_WSANOTINITIALISED_100293b0[];
extern char s_WSAENETDOWN_10029380[];
extern char s_WSAEFAULT_1002931c[];
extern char s_WSAENOTCONN_100292f0[];
extern char s_WSAEINTR_100292a4[];
extern char s_WSAEINPROGRESS_1002921c[];
extern char s_WSAENETRESET_10029194[];
extern char s_WSAENOTSOCK_10029164[];
extern char s_WSAEOPNOTSUPP_10029068[];
extern char s_WSAESHUTDOWN_10028fc8[];
extern char s_WSAEWOULDBLOCK_10028f6c[];
extern char s_WSAEMSGSIZE_10028f10[];
extern char s_WSAEINVAL_10028e3c[];
extern char s_WSAECONNABORTED_10028da0[];
extern char s_WSAETIMEDOUT_10028d24[];
extern char s_WSAECONNRESET_10028bf8[];

// FUNCTION: SERVER 0x1000ad40
// srv_LogWinsockError

void __cdecl srv_LogWinsockError(int err_code)
{
	char buf[256];

	switch (err_code) {
	case 0x276d:
		LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x769, s_WSANOTINITIALISED_100293b0, 1);
		return;
	case 0x2742:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x76b,
			s_WSAENETDOWN_10029380,
			1
		);
		return;
	case 0x271e:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x76d,
			s_WSAEFAULT_1002931c,
			1
		);
		return;
	case 0x2749:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x76f,
			s_WSAENOTCONN_100292f0,
			1
		);
		return;
	case 0x2714:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x771,
			s_WSAEINTR_100292a4,
			1
		);
		return;
	case 0x2734:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x773,
			s_WSAEINPROGRESS_1002921c,
			1
		);
		return;
	case 0x2744:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x775,
			s_WSAENETRESET_10029194,
			1
		);
		return;
	case 0x2736:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x777,
			s_WSAENOTSOCK_10029164,
			1
		);
		return;
	case 0x273d:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x779,
			s_WSAEOPNOTSUPP_10029068,
			1
		);
		return;
	case 0x274a:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x77b,
			s_WSAESHUTDOWN_10028fc8,
			1
		);
		return;
	case 0x2733:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x77d,
			s_WSAEWOULDBLOCK_10028f6c,
			1
		);
		return;
	case 0x2738:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x77f,
			s_WSAEMSGSIZE_10028f10,
			1
		);
		return;
	case 0x2726:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x781,
			s_WSAEINVAL_10028e3c,
			1
		);
		return;
	case 0x2745:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x783,
			s_WSAECONNABORTED_10028da0,
			1
		);
		return;
	case 0x274c:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x785,
			s_WSAETIMEDOUT_10028d24,
			1
		);
		return;
	case 0x2746:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x787,
			s_WSAECONNRESET_10028bf8,
			1
		);
		return;
	default:
		sprintf(buf, s_Unknown_winsock_error_u_10028bdc, err_code);
		LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x789, buf, 1);
		return;
	}
}

/* Initializes the building type lookup table (42 entries, 0x18 bytes
 * each, base g_office_slots = 0x101de5a0). Zeroes the table, stamps
 * id=i / unk=-1 / unk2=-1 per entry, then assigns each entry's type code
 * (bytes at +0x8) from the 1,1,2,3,4,4,5,6,7,7,... sequence.
 *
 * RESOLVED (2026-09-10): the zero-fill is the original's hand-written
 * 24-byte block-fill prelude (docs/msvc6-allocator.md Finding 19), never
 * emitted by any msvc6 C spelling.  The count is homed in a volatile
 * [ebp-4] slot under `#pragma optimize("y", off)`, reproducing the target's
 * `mov [ebp-4],0x3f0` / `mov ebx,[ebp-4]` pair, and the fill is a minimal
 * inline-asm block naming dest and count; the function is now RELOC
 * 372/372.  The loop and the 42 constant stores stay pure C.  The notes
 * below are the C-only history that established the prelude is not
 * reachable from C.
 *
 * STATUS: PROVEN (semantic proof, byte-blocked). The target's leading
 * memset uses the dest-alignment prelude (lea ecx,[edi+edi*2]; and ecx,3;
 * sub ebx,ecx; jle; rep stosb/stosd/stosb) with the count spilled to
 * [ebp-4] and an ebp frame. No C formulation or flag/toolchain
 * combination (msvc4.0-7.0, SP1-SP6, ~45 shapes, 96-flag sweep)
 * reproduces it — msvc6 always emits `mov ecx,0xfc; rep stosd` for the
 * constant count, so the function compiles to 334B (261/372 matching);
 * everything after the memset (loop + 42 constant stores with their
 * mov al,N grouping) is byte-identical. See docs/msvc6-allocator.md
 * "m_PoolAlloc / srv_InitBuildingTypeTable — blocked (alignment-prefixed
 * memset)".
 *
 * Re-verified 2026-08-27: ~130 further probes (base 6.0 + SP1-SP6 ×
 * /Og- /Oi /Oy- /O1 /Ox /G6, param-operand and struct-copy memsets,
 * volatile/address-taken counts and dests, full-function bodies through
 * `rebrew test`) confirm 261/372 / 334B is the ceiling — every variant
 * compiles to the plain dword+tail memset. The prelude appears in the
 * target only when the count is memory-resident; msvc6's inliner emits
 * the plain form for any C shape.
 *
 * Correction (2026-09-05): the claim above that no shape reaches the
 * split memset is wrong.  A `volatile int n = 0x3f0` count does emit
 * `mov ecx,[n]; mov edx,ecx; shr ecx,2; rep stosd; mov ecx,edx;
 * and ecx,3; rep stosb`, and adding `#pragma optimize("y", off)` also
 * reproduces the target's `push ebp; mov ebp,esp; push ecx` frame with
 * the count spilled to [ebp-4].  What is still missing is the
 * dest-alignment prelude (`lea ecx,[edi+edi*2]; and ecx,3; sub ebx,ecx;
 * jle`), which needs the count live in ebx across the memset.  Probed
 * dest via pointer global, dest via local copy, and count kept live
 * afterwards: none produce it.  The volatile-count version scores
 * 192/372 at 355B, worse than the current 261/372 at 334B, so the plain
 * memset stays.  Ceiling claim holds; the mechanism note did not.
 *
 * Re-probed against the section 13 and 14 levers.  `#pragma optimize("y",
 * off)` plus a length homed in a local and read back through a volatile
 * alias does reproduce the original's `push ebp; mov ebp, esp; push ecx;
 * mov dword ptr [ebp-4], 0x3f0; mov ebx, [ebp-4]` prologue exactly, and
 * closes 24 of the 38-byte size deficit (334 to 358 against 372), but it
 * scores 255/372 against the plain form's 261 because the prelude itself
 * still does not appear and the two streams stay misaligned.  The residual
 * 14 bytes are exactly the prelude.  Also swept eight optimisation flag
 * sets (/G5, /G6, /Ox, /Ob2, /Oi, /Og /Oi /Ot /Gs, /O1, /Oxs) and ten more
 * memset spellings across dest provenance, fill byte, and non-constant
 * length: `lea ecx,[edi+edi*2]` appears in none of them, matching the
 * section 11 finding.
 *
 * 2026-09-05: five more memset spellings disassembled in .scratch/mid
 * (explicit size_t cast on the constant, a constant laundered through a
 * cancelling parameter expression, dest via an `extern char*` pointer
 * global, dest as a parameter, and a count read from an extern int).  The
 * memory-resident count forms give the plain `shr ecx,2; rep stosd; and
 * ecx,3; rep stosb` split without the dest-alignment prelude; every
 * constant-count form collapses to `mov ecx,0xfc; rep stosd`.  No change
 * made; the file stays at 261/372.
 *
 * 2026-09-05 (L2c): the original's `push ebp; mov ebp,esp; push ecx` frame and
 * its `mov [ebp-4],0x3f0` / `mov ebx,[ebp-4]` count pair ARE reachable in C:
 * `#pragma optimize("y", off)` (section 13) plus a frame-resident count, either
 * a `volatile int n` or a plain `int n` read through a volatile alias at the
 * memset, reproduces both (.scratch/L2c/p3.c `r2`/`r3`, p3b.c).  Neither is
 * kept: the memset still expands to the plain two-rep
 * `shr ecx,2; rep stosd; and ecx,3; rep stosb` split rather than the
 * three-rep dest-alignment prelude, and the extra prologue instructions shift
 * the stream, scoring 256 and 255 against the plain form's 261.  Also probed
 * without effect: the count reused in the loop bound to force it into a
 * callee-saved register (adds a push esi, not ebx), and the table base taken
 * from a local.  The section 11 blocker stands: the prelude is a different
 * memset template, not a residency or scheduling difference.
 *
 * 2026-09-06: the remaining untested hypothesis was dest alignment - the
 * target's `lea ecx,[edi+edi*2]; and ecx,3` computes a byte count that aligns
 * the destination, which msvc6 would only emit when it cannot prove the dest
 * is dword-aligned.  Twelve probes in .scratch/l2b8p, compiled and
 * disassembled, cover every way to hide that alignment: dest as a scalar
 * `extern char` rather than an array, dest as a pointer parameter, dest as
 * `array + extern_int` (a runtime offset), dest through an `extern char*`
 * global, a `#pragma pack(1)` struct array, a `sizeof`-derived count, a
 * variable fill byte from a global, and each of those crossed with a
 * memory-resident count (`volatile int`, and a plain int read through a
 * volatile alias) and with /Oi, /Ox /Gd /Ot, /Og /Oi /Ot /Gs and /O2 /Gd /G3.
 * Not one emits the three-rep prelude: every unknown-alignment dest still
 * gives the plain `shr ecx,2; rep stosd; mov ecx,edx; and ecx,3; rep stosb`,
 * and every constant count collapses to `mov ecx,0xfc; rep stosd`.  Dest
 * alignment is not the lever either; the prelude is a memset template msvc6
 * 6.0 does not select from C.
 *
 * 2026-09-06 (L2 lane0): the last untried opacity was a count and a dest that
 * are not locals at all, so msvc6 cannot bound either.  An `extern int` count
 * and an `extern char*` dest, in all four combinations and crossed with a
 * frame-resident count under `#pragma optimize("y", off)`, still emit only the
 * two-rep split (`shr ecx,2; rep stosd; and ecx,3; rep stosb`) and never the
 * three-rep dest-alignment prelude (.scratch/lane0/p3.c `r1`..`r6`).  The
 * section 11 blocker stands with genuinely opaque operands, which is the
 * strongest form of the test available from C.
 *
 * 2026-09-06 (L2 lane2): the remaining axis was the code generator's own
 * template selection rather than the source shape.  A CL flag sweep over the
 * constant-count memset (/G3, /G5, /G6, /Ox, /Os, /Ot, /Ow, /Oa, /Za, /Oi-,
 * /O1, /Gz, /Gr, /O2 /Ot /Oi, /Oy-) emits either `mov ecx,0xfc; rep stosd` or
 * nothing inlined at all, never the three-rep prelude
 * (.scratch/lane2/ms.c).  Nor do a byte-fill for loop, a memset through a
 * `char* volatile` dest, an address-taken frame count, or a struct assignment
 * from a static zero (.scratch/lane2/ms2.c `r1`..`r4`; the struct form emits
 * `rep movsl`, a different template again).  No change made; the file stays
 * at 261/372.
 *
 * 2026-09-06 (M7): the prelude's head count is `lea ecx,[edi+edi*2]; and ecx,3`,
 * which is `(dest * 3) & 3`; section 11 had only ever probed the arithmetically
 * equal `(-dest) & 3`, since 3 == -1 (mod 4).  Writing the multiply literally
 * still emits `neg edx; and edx,3` (.scratch/M7/m1.c `z1`/`z2`), so msvc6
 * canonicalises the two spellings to the same instruction pair and the `lea`
 * form is not reachable from either.  The three-rep split is likewise absent:
 * both variants emit four reps as two complete memset expansions, matching the
 * section 11 finding on the align-up split.  No change made; still 261/372.
 *
 * 2026-09-06 (L2 lane0, twelfth round): re-tested the one condition the notes
 * name as the prelude's requirement, the count live in ebx and the dest live
 * in edi ACROSS the memset, by keeping both in locals that are stored back to
 * externs afterwards (.scratch/pcq_l2f/ms/m2.c `r6`).  That does put the count
 * in ebx and the dest in edi exactly as the target does, and it is the closest
 * register assignment any probe has produced, yet the expansion is still the
 * two-rep `shr ecx,2; rep stosd; mov ecx,ebx; and ecx,3; rep stosb` with no
 * `lea ecx,[edi+edi*2]` head.  Also null: a 3-byte-element struct dest, a dest
 * offset by an extern int, and a count formed as the product of two externs
 * (m1.c `r1`..`r3`), all of which collapse to the same split or to
 * `mov ecx,0xfc; rep stosd`.  Register residency is therefore not the trigger;
 * the prelude is a separate memset template, as section 11 states.  The 38-byte
 * deficit is entirely that template.  No change made; still 261/372 at 334B.
 *
 * 2026-09-06 (M13): two measurements bound the remaining work.
 * First, the deficit is only the prelude: disassembled off-file and aligned on
 * the loop body (`mov [eax-4],cl; mov [eax],edx; mov [eax+0x10],edx`), every
 * byte from the loop to the last table store is identical to the original
 * except 44 four-byte runs, and each of those is a DIR32 slot whose
 * target-minus-candidate delta is exactly g_office_slots (0x101DE5A0).  The
 * only non-slot residue is the 3-byte epilogue: the target's frame teardown
 * `mov esp,ebp; pop ebp; ret` against our bare `ret`.  Nothing in the body
 * needs reshaping.
 * Second, the prelude is not a service-pack difference.  The same probe
 * (a `volatile int` count into memset) compiled in rebrew/msvc:6.0-win32,
 * 6.0-sp3, 6.0-sp5 and 6.0-sp6 emits the identical two-rep expansion in all
 * four; no MSVC6 build available here produces three reps
 * (.scratch/M13/sp.c).  `#pragma optimize("a", on)` and the frame pragma of
 * section 13 are both inert on the score (334B/261 either way), and the
 * volatile-count form still measures worse (358B/256).  Left PROVEN.
 *
 * 2026-09-06 (L2 lane0, thirteenth round): the prelude was located in the
 * binary rather than searched for in C, which settles what it is.  The exact
 * byte string `8d 0c 7f` (lea ecx,[edi+edi*2]) occurs six times in
 * original/Server/server.dll, at 0x10006730, 0x10006929, 0x10006e0d,
 * 0x10008f0c, 0x1000b057 and 0x10017611, inside m_AllocTracked,
 * m_init, m_PoolAlloc, vfs_ReadData, this function and
 * gm_AllocGebaeude.  All six are inline expansions with the identical 22-byte
 * tail (`83 e1 03 2b d9 7e 0c ... 03 cb`), and 0x10008f0c is the memcpy form
 * (rep movsb/movsd/movsb) of the same template, so it belongs to both
 * intrinsics.  Every one of the six sits in a function that is still
 * unmatched, so no local file demonstrates the shape.  Two sweeps against a
 * detector validated on the target's own bytes (grep for `8d 0c 7f`, six hits
 * in the binary): twenty flag sets on a five-shape memcpy probe, and thirteen
 * memset shapes covering an address-taken count, a pointer-to-local count, a
 * struct-member count, a call-result dest (the provenance the other five sites
 * share), a pointer-difference count, and a dest offset by an extern.  Zero
 * hits in all thirty-three (.scratch/L2b/p1.c-p4.c, sw.sh).  Whatever selects
 * the template is not the count's residency, the dest's provenance, or the
 * flags.  No change made; the file stays at 261/372 at 334B.
 *
 * 2026-09-08: the M13 result restated as a whole-stream measurement, since the
 * flat byte diff (111 differing bytes) overstates the gap.  Sequence-aligning
 * the two instruction streams with absolute operands normalized puts the
 * candidate at instruction +16 of the target: 53 of its 62 instructions are
 * then identical, and the 16 target-only head instructions are exactly the
 * ebp frame plus the prelude (push ebp / mov ebp,esp / push ecx / push ebx /
 * push edi / mov [ebp-4],0x3f0 / mov edi,g_office_slots / mov ebx,[ebp-4] /
 * xor eax,eax / lea ecx,[edi+edi*2] / and ecx,3 / sub ebx,ecx / jle /
 * rep stosb / mov ecx,ebx / and ebx,3).  Of the 9 remaining differences, 6 are
 * the prelude's own trailing reps and the pops it displaces, 2 are the
 * `mov eax,table` / `cmp eax,end` induction-base pair whose operands are the
 * table symbol, and 1 is the `mov esp,ebp` frame teardown.  The 42 unrolled
 * `mov byte ptr [..],N` stores and the loop are instruction-for-instruction
 * identical, differing only in the DIR32 addend.  Nothing outside the frame
 * and the prelude needs reshaping.
 *
 * 2026-09-08 (L3): the whole-stream result restated in bytes, which is what
 * the 138-byte figure in the blocker needs to be read against.  Aligning the
 * streams and summing encoded instruction lengths (.scratch/l3-inv-bt/
 * bytealign.py) gives 311 of the target's 372 bytes aligned-identical, 53
 * target-only bytes in the head, and 8 target-only bytes after it.  The 53 is
 * the ebp frame (23B: push ebp / mov ebp,esp / push ecx / push ebx / push edi
 * / mov [ebp-4],0x3f0 / mov edi,tbl / mov ebx,[ebp-4] / xor eax,eax) plus the
 * prelude (26B) plus 4B of the pops it displaces; the 8 is the induction-base
 * pair and the `mov esp,ebp` teardown, both of which exist only because the
 * frame does.  So the entire 111-byte positional deficit is one fault: the
 * candidate's head is 38 bytes short, which shifts every later byte.  The
 * 29 tail mismatches are that shift, not wrong code: each is one immediate of
 * a `mov byte ptr [addr],N` store reading against its neighbour seven bytes
 * away (0x08f target 0x10 got 0x0c, 0x096 target 0x08 got 0x0d, ... at stride
 * 7), and the 42 stores are instruction-identical under alignment.
 *
 * Nothing outside the prelude is left to fix.  Measured this pass, none kept:
 * a plain `int` count local, an address-taken count, a double-escaped
 * `int**` count (all constant-fold, inert at 261/334B); a spare `char[4]`
 * local to force a frame (inert); a `volatile int` count, which does grow the
 * object to 355B and lifts aligned-identical instructions from 57 to 60 but
 * emits its own `mov [esp+4]` / `mov ecx,[esp+4]` / `mov edx,ecx` head and a
 * split `mov ecx,edx; and ecx,3`, scoring 192/372 positionally.  Twenty
 * CFLAGS sets (/O1 /Ox /Oxs /Oxt /Od, /Oi /Oi- /Og /Ot /Os /Ob2 /Oy- /Gy /GB
 * /G3 /G5 /G6 /Ze) in .scratch/l3-inv-bt/flagsweep.sh: every one either ties
 * 261 or loses, and none emits the `lea ecx,[edi+edi*2]` prelude.
 *
 * Promoted to PROVEN via `rebrew prove 0x1000b040` (2026-08-27) with
 * 252 --watch-va (every dword of the 0x3f0-byte table) and
 * --loop-bound 400: for void functions the prover skips the EAX/EDX
 * comparison (undefined at exit) and compares only the watched memory;
 * the DIR32 patch preserves each operand's addend (symbol_va + addend)
 * and no longer writes compiled offsets into the original blob. The
 * high loop bound is required because angr's LoopSeer counts each
 * rep-stosd iteration — the memset alone is 252 iterations. */

extern char g_office_slots[];

// FUNCTION: SERVER 0x1000b040
// srv_InitBuildingTypeTable

#pragma optimize("y", off)
void __cdecl srv_InitBuildingTypeTable(void)
{
	char* slot_cursor;
	int i;
	volatile int n;

	n = 0x3f0;
	/*
	 * TODO: replace this inline-asm fill with proper C once a spelling is
	 * found; no msvc6 C memset/memcpy form emits the prelude
	 * (docs/msvc6-allocator.md Finding 19).
	 */
	__asm {
		mov edi, offset g_office_slots
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
	i = 0;
	slot_cursor = g_office_slots + 4;
	do {
		*(slot_cursor - 4) = (char) i;
		*(int*) slot_cursor = -1;
		*(int*) (slot_cursor + 0x10) = -1;
		slot_cursor += 0x18;
		i++;
	} while ((int) slot_cursor < (int) (g_office_slots + 0x3f4));

	*(unsigned char*) (g_office_slots + 0x8) = 0x1;
	*(unsigned char*) (g_office_slots + 0x20) = 0x1;
	*(unsigned char*) (g_office_slots + 0x38) = 0x2;
	*(unsigned char*) (g_office_slots + 0x50) = 0x3;
	*(unsigned char*) (g_office_slots + 0x68) = 0x4;
	*(unsigned char*) (g_office_slots + 0x80) = 0x4;
	*(unsigned char*) (g_office_slots + 0x98) = 0x5;
	*(unsigned char*) (g_office_slots + 0xb0) = 0x6;
	*(unsigned char*) (g_office_slots + 0xc8) = 0x7;
	*(unsigned char*) (g_office_slots + 0xe0) = 0x7;
	*(unsigned char*) (g_office_slots + 0xf8) = 0x8;
	*(unsigned char*) (g_office_slots + 0x110) = 0x9;
	*(unsigned char*) (g_office_slots + 0x128) = 0xa;
	*(unsigned char*) (g_office_slots + 0x140) = 0xb;
	*(unsigned char*) (g_office_slots + 0x158) = 0xc;
	*(unsigned char*) (g_office_slots + 0x170) = 0xd;
	*(unsigned char*) (g_office_slots + 0x188) = 0xe;
	*(unsigned char*) (g_office_slots + 0x1a0) = 0xf;
	*(unsigned char*) (g_office_slots + 0x1b8) = 0x10;
	*(unsigned char*) (g_office_slots + 0x1d0) = 0x11;
	*(unsigned char*) (g_office_slots + 0x1e8) = 0x12;
	*(unsigned char*) (g_office_slots + 0x200) = 0x13;
	*(unsigned char*) (g_office_slots + 0x218) = 0x14;
	*(unsigned char*) (g_office_slots + 0x230) = 0x15;
	*(unsigned char*) (g_office_slots + 0x248) = 0x16;
	*(unsigned char*) (g_office_slots + 0x260) = 0x17;
	*(unsigned char*) (g_office_slots + 0x278) = 0x18;
	*(unsigned char*) (g_office_slots + 0x290) = 0x19;
	*(unsigned char*) (g_office_slots + 0x2a8) = 0x1a;
	*(unsigned char*) (g_office_slots + 0x2c0) = 0x1b;
	*(unsigned char*) (g_office_slots + 0x2d8) = 0x1c;
	*(unsigned char*) (g_office_slots + 0x2f0) = 0x1d;
	*(unsigned char*) (g_office_slots + 0x308) = 0x1e;
	*(unsigned char*) (g_office_slots + 0x320) = 0x1f;
	*(unsigned char*) (g_office_slots + 0x338) = 0x20;
	*(unsigned char*) (g_office_slots + 0x350) = 0x21;
	*(unsigned char*) (g_office_slots + 0x368) = 0x22;
	*(unsigned char*) (g_office_slots + 0x380) = 0x23;
	*(unsigned char*) (g_office_slots + 0x398) = 0x24;
	*(unsigned char*) (g_office_slots + 0x3b0) = 0x25;
	*(unsigned char*) (g_office_slots + 0x3c8) = 0x26;
	*(unsigned char*) (g_office_slots + 0x3e0) = 0x27;
}
#pragma optimize("", on)
