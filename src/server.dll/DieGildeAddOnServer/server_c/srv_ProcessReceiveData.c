int g_list_head;
// FUNCTION: SERVER 0x1000a570
#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"
unsigned int __stdcall timeGetTime(void);

/* Command layer (local externs — server.header uses different signatures) */
int __cdecl cm_QueuePlayerCommand(unsigned int* player, unsigned char* data);
int __cdecl cm_ClosePlayerConnection(unsigned int* player_slot);
int __cdecl lb_ExLobbyServerCommand(unsigned int*, int);

/* Entity lifecycle (local externs) */
/* Network functions (local externs — signatures differ from net.h) */
int __cdecl srv_ProcessReceiveData(void);
int __cdecl srv_ReceivePacketHeader(unsigned int* conn);
typedef int(__cdecl* handler_func)(unsigned char* pkt, int param);

extern DWORD WINAPI thread_proc(LPVOID);
int __cdecl srv_QueueCommandForProcessing(unsigned int* conn, unsigned char* pkt); /* 0x1000a8f0 */
extern handler_func g_dispatch_table[]; /* 0x1002c3f8 */
extern int srv_ReceivePacketHeader(unsigned int* conn);
extern int srv_QueueCommandForProcessing(unsigned int* conn, unsigned char* pkt);

/* srv_ProcessReceiveData: drains the receive buffers of all connected
 * player slots. For each connected slot, loops calling
 * srv_ReceivePacketHeader; when a full CommandPacket arrives, validates
 * the connection state flags (0x80 = packet pending) and dispatches:
 * bulk-transfer setup (cmd 0x08/0x09), lobby commands (0x5f),
 * unexpected-request handling, and queuing via
 * srv_QueueCommandForProcessing. Also services the admin connection at
 * 0x114ffe20.
 *
 * NEAR_MATCHING 492/750, obj 749 against 750. Three fixes took it from 473:
 * the volatile stores keep both download globals from sinking below the
 * inlined memset's rep stosd, caching the admin flag byte lets the 0x80 and
 * bit-0 tests share one load, and issuing the memset before those two stores
 * (482 to 492) reproduces the original's order, which sets up the memset's
 * edi/eax first. Dead ends, with the score each produced: swapping the
 * conn[0xb] / conn[0xc] store order 481 (the probe in .scratch/l0/p2.header shows
 * msvc6 emits the target's order either way, so that diff is register
 * naming); hoisting the shared conn+0x1b slot-index store above the 0x10 test
 * 490; do/while for the admin loop 478 at 767 bytes, because msvc6 rotates it
 * and duplicates the body; splitting the admin loop's three exits into
 * separate returns 492 (inert, the two `xor eax,eax` epilogues are a layout
 * choice); hoisting the lobby-branch mask into a temp shared by the store and
 * the sprintf argument 302; folding g_download_buffer + g_download_received
 * four ways 492 (all inert); passing g_download_total_size instead of the
 * local to m_AllocTracked 492, and via a volatile read 347.
 *
 * Residual: the original reads conn[1] as [ebp+4] where msvc6 CSEs our
 * conn+0x18 packet pointer and rewrites it as [eax-0x14], costing 5 bytes
 * from instruction 26 onward. Six spellings of the read (volatile, explicit
 * casts, a temp hoisted above the pointer, and passing conn+6 to
 * cm_QueuePlayerCommand) all keep the CSE. Re-checking the conn[0xb] /
 * conn[0xc] order confirms the earlier 481 note is now 491: an isolated probe
 * (.scratch/w1/p1.header, tb) does emit the target's instruction order for
 * conn[0xb]-first, but in this function's register pressure the CSE survives
 * and only swaps ecx/edx roles, so the current order stays. Hoisting the
 * shared conn+0x1b slot-index store above the 0x10 test scored 490.
 *
 * Re-measured dead ends, with scores: conn[0xb]-before-conn[0xc] 491 (the CSE
 * survives, only the ecx/edx roles swap, confirming the note above); reading
 * conn[1] as *(unsigned int*)((char*)conn + 4) 492 (inert, same CSE); hoisting
 * conn[1] into a block-local temp before both stores 491; writing the memcpy
 * destination as g_download_received + g_download_buffer instead of the
 * reverse 492 (inert — the target's `lea edi,[ecx+eax]` against our `add
 * edi,ecx` is a register-role consequence, not an addend-order one).
 *
 * The admin loop was also rewritten as an if-guarded do/while so the bottom
 * bit-0 test merges with the entry test the way the target's single `test
 * al,1` does. That does raise the positional count to 494, but msvc6 rotates
 * the loop and duplicates the body, growing the function to 767 bytes against
 * the target's 750, so the result is a net regression and the while form
 * stays.
 *
 * Fourth pass on the instruction-25 CSE, all re-measured against 492: aliasing
 * conn through a block-local `unsigned int* c2` and storing c2[0xb] before
 * c2[0xc] 491; hoisting the packet pointer into a local before both stores and
 * passing it to cm_QueuePlayerCommand 491; spelling the cmd-3 guard off that
 * same packet local (`*pkt == 3`) 492 (inert — msvc6 already shares the
 * lea/byte-load pair). Reusing the cached `status` for the 0x400 test instead
 * of re-reading *conn collapses to 172 at 745 bytes: the re-read is load-
 * bearing, because the target's `mov edx,[ebp]` at instruction 28 is a fresh
 * load the cached local cannot produce. The [eax-0x14] rewrite of conn[1]
 * therefore stands as the residual blocker.
 *
 * Fifth pass, all re-measured against 492 and reverted: dropping the admin
 * loop's bottom `if ((admin_flags & 1) == 0) break;` so the while condition
 * alone closes it 490 at 745 bytes; spelling both cmd-3 stores as byte
 * offsets off conn (`*(unsigned int*)((char*)conn + 0x2c)` before +0x30) 491;
 * conn[0xb] before conn[0xc] 491 again; hoisting the shared conn+0x1b
 * slot-index store above the 0x10 test 490; issuing the
 * g_download_total_size store before the inlined memset instead of after 479.
 * An isolated probe of the cmd-3 block (.scratch/L2B/pr/p1.header) reproduces the
 * target's `mov edx,[eax+4]; mov [eax+0x2c],edx` order for the 0xb-first
 * spelling, so the emitted order is available in isolation but the
 * function's register pressure re-derives conn[1] through the packet-pointer
 * CSE regardless. The lobby-branch mask was probed four ways in
 * .scratch/L2B/pr/p4.header: only the shipped shape keeps the full-width
 * `and esi,0xffffff7f`; every temp-hoisting variant narrows it to
 * `and al,0x7f` and loses the target's `mov eax,edx` pair.
 *
 * Fifth pass, all re-measured against 492 and reverted: dropping the two
 * volatile casts and writing the g_download_total_size / g_download_received
 * stores ahead of the memset call, to chase the target's index 100-104 order
 * (both stores and both pushes issued before `rep stosd`), scores 473 -- the
 * target interleaves them between the memset's edi/eax setup and the string
 * op, and plain stores sink below it instead. Swapping the cmd-3 block to
 * store conn[0xb] before conn[0xc], matching the target's index 25-34 order,
 * scores 491, and hoisting the shared conn+0x1b slot-index store above the
 * 0x10 test scores 490, both confirming the earlier notes.
 *
 * The index-25 CSE was also probed in isolation once more
 * (.scratch/w_l2/q1.header, five spellings: shipped, an alias pointer, a packet
 * pointer local assigned after the conn[1] read, a char-pointer guard, and a
 * volatile conn[1] read). Every one emits the target's direct `mov 0x4(%eax)`
 * read, so the `[eax-0x14]` rewrite is purely a whole-function register
 * pressure effect -- with conn homed at [ebp] rather than in a register, the
 * packet pointer is the cheaper base -- and is not addressable by respelling
 * the read.
 *
 * Sixth pass isolated the two remaining size effects and confirmed both are
 * compiler fixed points. Dropping the admin loop's bottom
 * `if ((admin_flags & 1) == 0) break;` is structurally correct -- the target
 * has a single `test al,1` at 0x1000a811 and we emit two -- and it takes the
 * object from 749 to 745 bytes, leaving the 5-byte srv_QueueCommandForProcessing
 * arg hoist as the only remaining size deficit. It still scores 490 because
 * the removed 4 bytes of junk happened to re-align the epilogue, so it is not
 * kept. That arg hoist was then probed twelve ways in .scratch/lane0c/p
 * (q1-q8): with the enclosing slot loop removed msvc6 already emits the
 * target's per-arm `lea/push/push/call` (q2 w1), and with the loop present
 * every variant hoists the shared prefix above the branch -- byte-index vs
 * element-index store spellings, a volatile store, distinct return values in
 * the two arms, inverted branch polarity, splitting the shared `*conn =
 * status` tail, re-reading *conn for the 0x10 test, and masking the stored
 * index. The hoist was read as loop register pressure on this evidence; the
 * eighteenth pass shows it was held by the pre-test slot store instead.
 *
 * Seventh pass found the only formulation that reaches the target's exact
 * 750-byte size, and established it is not the way in. Inverting the 0x10
 * branch so the masked-0x6f case is the fallthrough (`if ((status & 0x10) ==
 * 0)` with the two masks swapped) emits 750 bytes and moves indices 157-159
 * to `==`, but msvc6 still hoists the shared prefix: it sinks the slot-index
 * store below the `lea` instead, which costs more than the hoist recovered,
 * so the score is 474. Combining it with the admin-loop test drop lands on
 * 746 bytes and 402. The 750 is therefore an accident of two shifts
 * cancelling, not the arg hoist being defeated. Same pass, all reverted:
 * hoisting the slot store above the inverted branch 474; the two arms given
 * distinct pointer spellings, distinct result tests, or a result local 492
 * (inert -- tail merging is not driven by the arms being textually equal);
 * one shared call with the mask selected after it 132 at 768 bytes; routing
 * both arms through a `static __inline` wrapper around
 * srv_QueueCommandForProcessing 492 (inert, the prefix hoist survives inlining).
 * The packet-pointer CSE at index 25 was re-probed with the whole file
 * respelled to a single textual form (all byte offsets off conn, all
 * `conn + 6` element form, and the guard byte read as `((unsigned char*)
 * conn)[0x18]`): all 492, confirming the CSE is not fed by having several
 * spellings of the same address. In the 750-byte form the cmd-3 store order
 * and a volatile conn[1] read were re-measured too: 473 each.
 *
 * Eighth pass, all re-measured against 492/750 and reverted. Rewriting the
 * admin loop as a goto chain with a single bottom `if ((admin_flags & 1) != 0)
 * goto admin_loop;` does emit the target's one `test al,1` and raises the
 * positional count to 495, but msvc6 rotates it and duplicates the body, so
 * the object grows to 767 bytes: the compare denominator grows with it and the
 * fraction falls from 492/750 to 495/767, so it is a regression, not a gain.
 * Caching the entry guard's byte into admin_flags so the top and bottom tests
 * share one load is inert on top of that (495 at 767). Dropping the bottom
 * test entirely 490 at 745, confirming the earlier note. The cmd-3 block was
 * re-probed three more ways (conn[0xb] before conn[0xc], the index read
 * hoisted into a block-local, and the guard byte spelled
 * `((unsigned char*) conn)[0x18]`): 491 each, and passing `conn + 6` rather
 * than `(unsigned char*) conn + 0x18` to cm_QueuePlayerCommand, or aliasing
 * both through one local, also 491. The memset block was re-ordered two ways
 * (total-size store before the memset 479, both stores plain rather than
 * volatile 473). The memcpy destination was spelled three more ways (addend
 * order reversed, the received count hoisted into a local, and a char-pointer
 * base): all inert at 492, so the target's `lea edi,[ecx+eax]` against our
 * `add edi,ecx` stays a register-role consequence. The srv_QueueCommandForProcessing
 * arg hoist was probed three more ways (slot store hoisted above the branch
 * with the two arms kept, the same as an explicit if/else, and the 0x10
 * predicate computed into a temp before the store): 490 each. Reordering the
 * unexpected-request block to store pktbuf[0] before masking *conn 476;
 * masking through a named temp 492 (inert).
 *
 * Ninth pass carried over the lever that closed cm_ExProdObjekt (0x1000e140):
 * respelling a loop cursor as a per-iteration index off its base, to break the
 * value-numbering equality msvc6 uses to carry the cursor forward. It does not
 * transfer. The outer slot loop written as `conn = (unsigned int*) (0x101deb00
 * + i * 0x264264)` inside the body, with the same expression as the bound
 * test, compiles 785 bytes at 125: msvc6 materializes the multiply per
 * iteration instead of strength-reducing it back to the pointer walk, so the
 * whole body shifts. The pointer-advance form stays.
 *
 * Also re-measured this pass, all reverted, scores in parentheses. On the
 * srv_QueueCommandForProcessing arg hoist (the 5-byte residual): the two arms
 * given textually distinct address spellings, `(unsigned char*) (conn + 6)`
 * against `&((unsigned char*) conn)[0x18]`, so value numbering cannot prove
 * them equal (inert at 492, msvc6 head-merges on the computed address, not the
 * expression); both arms spelled `(unsigned char*) conn + 0x18` (inert); the
 * slot store spelled off the packet base as `((unsigned char*) (conn + 6))[3]`
 * so it shares no base with the argument (inert); the 0x10 arm's tail store
 * taken out of the shared `set_status` chain and written inline (inert);
 * block-scoped pointer locals per arm (inert, coalesced). The hoist survives
 * every source-level attempt to separate the two arms, confirming the eighth
 * pass's conclusion that it is driven by the enclosing loop's register
 * pressure.
 *
 * Section 25's first-read lever was applied to the lobby block (indices 61-79,
 * where the target reads *conn into ecx and we use eax): hoisting the sprintf
 * argument into `status` before the call is inert at 492, and `*conn &=` in
 * place of `*conn = *conn &` is inert. Reordering the unexpected-request block
 * so the mask is computed into `status`, the pktbuf byte stored, then `*conn`
 * written -- chasing the target's index 146-147 push/store order -- costs a
 * byte and scores 444 at 748. A volatile read of the loop counter `i` at its
 * sprintf argument, to unpin it from the slot store, scores 118 at 780.
 *
 * `total` was narrowed to the cmd-8 block it is used in (score-neutral at 492;
 * the function-scope declaration was a decompilation artifact).
 *
 * Tenth pass, 492/749 SIZE_MISMATCH to 662/750 NEAR_MATCHING (exact target
 * size, +170 positional bytes). Three changes, each load-bearing:
 * (a) the 0x10/tail slot-index store hoisted above the `status & 0x10` test
 * (single store shared by both arms, then the tail arm keeps no store of its
 * own): the hoist is what the original's per-arm `lea/push/push/call` needs,
 * and it also supplies the missing size byte (749 to 750);
 * (b) the admin loop's bottom `if ((admin_flags & 1) == 0) break;` dropped,
 * so the while condition alone closes the loop the way the target's single
 * `test al,1` at 0x1000a811 does (this loses 4 bytes, 749 to 745 on its own);
 * (header) the two together land exactly on 750 with the tail re-aligned.
 * An `i < 9` bound scores identically (662 at 750) but visits a ninth slot at
 * 0x114ffe20 (the admin record) as if it were a player slot, so the pointer
 * bound stays: same slots, same semantics as the proof.
 * Measured on the 662 base, all reverted: every cmd-3 respelling (store order,
 * guard byte-offset/element/index forms, c12-via-status, dword guard, hoisted
 * packet/c1 locals, per-arm locals, c1-based arg, volatile loads) inert at
 * 661-662; lobby sprintf/mask reorderings crater (status-arg 109 at 772,
 * mask-via-status 301-302); memset split/total-first/recv-first 647-660;
 * memcpy dest addend swap, sum/buf/recv locals, volatile addends 661-662;
 * unexpected-arm mask-via-status 129, pktbuf-first 646; 0x10-arm mask-early
 * 175, dup-stores-in-arms 490 at 745; admin pktbuf spellings, ret/flag locals,
 * int flags, flag-cond-loop all inert at 662; per-arm QCP arg mixes inert;
 * hoist address spellings inert; `#pragma optimize("a", on)` craters to 180
 * at 760.
 *
 * Twelfth pass, all re-measured against 662/750 and reverted: cmd-3 guard
 * byte hoisted into a block-local `cmd` (coalesced, inert); alloc call
 * re-reading conn[10] instead of total 355 at 753; per-arm packet local in
 * the 0x10 head only (lea still hoisted, inert); buf+rec hoisted into locals
 * 364 at 745 (src lea moves first but dest homing costs the size byte);
 * memcpy addend through a volatile received read 661.
 *
 * Thirteenth pass, all reverted: 0xc value hoisted into a block-local temp
 * ahead of the 0xb store 661 (the temp takes the register the c1 load
 * needs).
 * Residual 45 `**` in six clusters (byte-neutral scheduling/naming, all at
 * the exact 750 size): cmd-3 packet CSE (25-34, conn[1] via [eax-0x14] not
 * [ebp+4]); lobby sprintf regs (61-69, 75-85); memset interleaving (100-104);
 * memcpy dest lea-vs-add (111-114); unexpected push/store swap (146-147);
 * 0x10-arm lea-before-test (154-158, hoist forces the packet-base rebasing);
 * tail-arm lea (167-169); admin lea edx-vs-eax (211, 213). The c11-first
 * variant shows all registers correct with only c1's base wrong, but every
 * spelling that breaks the packet-base sharing is inert: the VN equality is
 * a whole-function pressure fixed point.
 *
 * Eleventh pass, all re-measured against 662/750 and reverted: lobby sprintf
 * arg through a volatile *conn read 658; memcpy dest/src hoisted into
 * block-scope dst/src locals (chasing `lea edi,[ecx+eax]` via an early src
 * lea) inert at 662; admin pktbuf through a block-local apkt inert; a
 * lobby-branch block-local logbuf alias used by both sprintfs inert; memset
 * through g_download_slots instead of the absolute address inert (same 662,
 * idx99 goes == to ~~). A direct-docker probe loop (workdir mounted at
 * /work, image ENTRYPOINT left intact) now compiles isolated shapes in ~40s
 * for future work. near-diag classifies the delta as 55 structural bytes
 * with the rest reloc-site noise; a targeted flag sweep was launched in
 * background (single-function file, so any winning flags are safe to take).
 * The `~~` operands resolve to the real references: 0x10029a9c "LOBBY mode",
 * 0x100298b0 the server.header path, 0x10029a70/0x10029a54 the two lobby formats,
 * 0x10029a48 "srv_LoadBuf", 0x10029a1c the unexpected-request format, calls
 * to srv_ReceivePacketHeader/lb_ExLobbyServerCommand/cm_QueuePlayerCommand/
 * srv_QueueCommandForProcessing/cm_ClosePlayerConnection/sprintf/
 * LogMessageInternal/m_AllocTracked, and the g_download_* globals at
 * 0x101deac0/0x101deac4/0x101deae8.
 *
 * Fourteenth pass, re-measured against 662/750 and reverted: the unexpected-
 * request mask through `status` (store via the cached local, pktbuf[0] = 2
 * after) is inert at 662; conn[0xb]-before-conn[0xc] at this base scores 661
 * (was 491 at the old 492 base, same CSE, now costs one positional byte).
 * Isolated probes (.scratch pdb_* series, ~20 shapes) confirm per-arm
 * duplicated-tail srv_QueueCommandForProcessing calls are always hoisted above
 * the branch regardless of store symmetry, guard polarity, goto form, or a
 * shared trailing call: the hoist is driven by the slot loop, not the arms.
 * The lobby ecx/eax naming was probed eleven ways (lb1-lb18): an s-temp
 * sprintf arg matches the target push order everywhere except the first
 * push (eax vs ecx), and only at the cost of logging the stale pre-call
 * value, so it is not shippable.
 *
 * Fifteenth pass (this session), all re-measured in-file against 662/750 and
 * reverted. Isolated probes first (.scratch/laneA): conn[0xb]-before-conn[0xc]
 * emits the target's exact store order in isolation (t2/t3/t4 in p_cmd3.header all
 * do), and an alias-pointer read of conn[1] (`c1p = conn + 1`) moves the
 * isolated load from `mov edx,[eax+4]` after the 0x30 store to `mov
 * ecx,[esi+4]` + `mov [esi+2c],ecx` before it; neither transfers, the
 * whole-function CSE re-derives conn[1] through the packet pointer either
 * way. The c1p-alias spelling scores 664 in-file (+2, the push/neg/sbb
 * naming aligns) but keeps `mov edx,[eax-0x14]`, so it is not the fix and is
 * not kept. c0+c1p and c1-first-in-block both 662-664 with the same CSE.
 * Hoisting the packet pointer into a `pkt` local across the cmd-3 arm does
 * not compile in the `if (status & 2)` nesting used here and reverts to 662
 * when repaired. Unexpected-arm `push ebp` before the `mov [ebp],ecx` store
 * was probed three ways (pktbuf-first, mask-via-status-temp, pushed order):
 * all keep store-before-push. Memset-order probes (p_memset.header t1-t4) show the
 * shipped volatile-after-memset is the only shape emitting the target's
 * setup-stores-stringop-call order; a dword loop or unrolled stores lose it.
 * Memcpy probes (p_mcpy.header t1-t5) all emit `lea edi,[edx+ecx]`-family, never
 * the target's `lea edi,[ecx+eax]`: pure register-role naming. The 0x10-arm
 * slot-store placement was re-measured (sinking it into the arm: 490 at 745)
 * and per-arm QCP packet spellings re-probed (p_slot.header t1-t4: all identical
 * `lea/mov/push/push/call`): the hoist stands. Admin-loop probes (p_admin.header)
 * confirm the shipped while form is byte-identical to the target's
 * test/test/je/call/je/mov/test shape in isolation.
 *
 * Sixteenth pass (this session), measured against 662/750. Kept: conn[0xb]
 * before conn[0xc] with a volatile *conn read for the 0x400 ternary (probe D),
 * which raises the positional score to 665/750 at the exact size. The first
 * ** cluster still rebases conn[1]/conn[0xb]/conn[0xc] through the packet
 * LEA (`[eax-0x14]` / `[eax+0x14]` / `[eax+0x18]`) where the target keeps
 * `[ebp+4]` / `[ebp+0x2c]` / `[ebp+0x30]` and pushes the packet between the
 * conn[1] load and the 0xb store. Reverted this pass: volatile conn[1]
 * (inert 662); #pragma optimize(\"y\"/\"g\", off) (154/742 and 146/1229);
 * c1 temp + 0xb-first (661); byte-offset / &addr / volatile-pointer stores
 * (inert or 661); pkt locals before/after stores (inert 665); 0x10 if/else
 * and dropping the duplicate slot store (491/745 — the documented 5-byte
 * call-arg hoist); unexpected-request comma-store (453/749); whole-function
 * volatile conn (401/751); cflags sweep (/Ow /Oa /O1 crater; /O2 /Gd and
 * /Gy stay 665). Probe V (pkt local, header = (unsigned int*)(pkt - 0x18), stores
 * and call through header) is the only shape that emits `[ebp+4]` for conn[1], but
 * it grows to 754 and collapses register roles on the cmd check (al/ecx vs
 * cl/eax), scoring 213. Compact re-derivations (W/X/Y1/V2/V3) fold back to
 * the packet CSE at 665. near-diag on D@665: RELOC 67% of delta with 49
 * structural bytes; first mismatch is the IDX-25 CSE. Residual blocker is
 * still the packet-base VN equality under whole-function pressure, plus the
 * documented 0x10-arm call-arg hoist (PROVEN equivalent).
 *
 * Seventeenth pass (this session), measured against 665/750. Removed the
 * illegal `// CFLAGS: /O2 /Gd` line (cflags belong in rebrew-functions.toml).
 * Re-scored prior `.scratch/prd_cse/hit_*` shapes and new arm variants:
 * hit_load / hit_c_rtl / hit_status clear idx-25 `[ebp+4]` and keep ebp-based
 * 0xb/0xc stores, but grow to 753 and still emit stores before `push eax`
 * (score 513). Compact pkt/header locals fold back to the `[eax-0x14]` CSE at
 * 665, or crater to 213/754 when the guard loses the shared lea/byte-load
 * pair. Comma/RTL argument schedules (push_first, split_stores, c1_then_rtl,
 * 0b_then_push_0c_in_pkt) stay 662-665 with the same CSE. Snip
 * `hit_rtl_0b_then_0c_after` shows both `[ebp+4]` and early `push eax`, but
 * only by deferring the 0xc store past the call (wrong semantics; no
 * shippable source recovered). Residual blocker unchanged: packet-base VN
 * equality under whole-function pressure, plus the push-before-0xb call
 * skeleton the comma forms cannot force at size 750.
 *
 * Eighteenth pass, 665/750 to 687/750 at the exact size. The `hit_load` cmd-3
 * shape and the slot-store placement were one fault, not two, so neither is
 * measurable alone (section 41). Deriving the connection pointer from the
 * packet pointer (`header = (unsigned int*) (pkt - 0x18)`) and issuing both stores
 * through the call's first-argument comma clears the `[eax-0x14]` CSE: the
 * conn[1] read becomes `mov ecx,[ebp+4]` and both stores go back to
 * `[ebp+0x2c]` / `[ebp+0x30]`. On its own that shape runs 753 bytes and
 * scores 513, because it also stops msvc6 hoisting the shared
 * srv_QueueCommandForProcessing prefix, which leaves the pre-test slot store and
 * the tail-arm duplicate both live. Moving the slot store into each 0x10 arm
 * and dropping the pre-test copy supplies exactly those three bytes: the arms
 * emit the target's per-arm `mov [ebp+0x1b],bl` / `lea eax,[ebp+0x18]` /
 * `push eax`, and the object lands back on 750. Together they clear three of
 * the six ** clusters (cmd-3 CSE, 0x10-arm lea-before-test, tail-arm lea) and
 * take ** from 44 to 32. The arg hoist recorded from the eighth pass onward
 * as loop-pressure-driven was in fact held by the pre-test store: with the
 * store per-arm it does not occur.
 *
 * Re-measured against 687/750 this pass and reverted, all at the exact size
 * unless noted. Every declaration order of the five scalars (120
 * permutations, generated in .scratch/l2prd/v) is inert at 665 on the old
 * base: frame layout is not a lever here. Flag sweep over 15 sets: /O2 /Gd
 * with or without /Ot /Oy /Ob0 /Ob1 /Oi /Gy /Gf /GF /G3 /G4 /G5 all 665;
 * /Oy- 151, /Oi- 150, /G6 202 at 762. Cmd-3 push order, ten shapes
 * (stores split out of the comma either way, both in the second argument,
 * conn as the first argument, pkt re-derived from conn, stores written
 * pkt-relative, flag hoisted to a temp, volatile pkt or header locals): 687 when
 * inert, 177-198 when the guard's shared lea/byte-load pair breaks. Memset
 * block, nine orderings (stores before the memset, memset sunk past the
 * alloc or folded into its argument list, either store non-volatile, receive
 * before total, stores in the alloc comma, total re-read volatile): 662-687,
 * none above. Lobby mask five ways and memcpy five ways: inert at 686-687,
 * except the three that re-read *conn volatile, which cost a byte and crater
 * to 325-332 at 751. Unexpected-request block four ways: 671-687. Slot-store
 * arms six ways (byte-index spelling, if/else, packet local before or after
 * the store, store inside the call argument): all inert at 687.
 *
 * Nineteenth pass closed the memset and memcpy clusters together, 687 to 696.
 * They are one fault: the memset must be issued AFTER both global stores and
 * with those stores plain rather than volatile, so its `rep stosd` sinks below
 * the two pushes the way the target's does; that frees eax at the memcpy, and
 * a volatile read of g_download_received there makes msvc6 pick the target's
 * `lea edi,[ecx+eax]` over `add edi,ecx`. Each half regresses alone: the
 * memset reorder on its own scores 674 (it rotates the downstream registers)
 * and the volatile memcpy read on its own 686. Only the pair gains.
 *
 * Residual after the twentieth pass is 49 bytes in four clusters, all
 * byte-neutral scheduling or register naming at the exact 750 size, each
 * returning to zero drift within a few instructions: cmd-3 `push eax` issued
 * after the two stores where the target pushes between the conn[1] load and
 * the 0xb store (17); lobby sprintf register naming (24); the memcpy
 * `lea esi` / `lea edi` order (4); unexpected-request `push ebp` /
 * `mov [ebp],ecx` swap (4). On the lobby cluster, `rebrew diff -r` splits the
 * 24 bytes into a pure eax/ecx/edx rotation at the first sprintf plus the
 * second sprintf's buffer lea, which the target can hoist above the mask only
 * because that rotation leaves ecx free, so the two halves follow one
 * allocation choice.
 *
 * Nineteenth-pass dead ends, all re-measured against 696 and reverted. Cluster
 * A eleven ways: guard byte read off conn with the lea created inside the arm,
 * no packet local at all 502, header aliased to conn 502, the 0x400 test through
 * conn or through the outer status word 177/202, the two stores swapped in the
 * comma 204, each store separately volatile, the ternary inverted, and arg2
 * through a late local. Cluster B twenty ways: every declaration-order
 * permutation, both sprintfs through &buf[0], a separate buffer per sprintf
 * 690-693, an own block-local status 298, a volatile buffer pointer 302, the
 * guard inverted with a tail label, the LOBBY-mode log duplicated into both
 * arms 216, the lb result kept live into the log call 258-265, sprintf's own
 * return value kept live 130, and the lb argument spelled as conn+6. Cluster E
 * nine ways: the store in arg1's comma 680, both stores in the argument list
 * 680, the pktbuf store through a volatile alias 683, a ret-form call 147.
 * Loop shape nine ways: while form 178, index-driven 124, unsigned induction
 * 695, i incremented in the body, the ret local eliminated 136, a byte-wise
 * 0x80 test 165. Cross products A x B, A x E and B x E (96 combinations) are
 * all inert at 696, so unlike the memset/memcpy pair these three clusters are
 * not coupled to each other. Flag sweep: /Ot, /Ox, /G3, /G4, /G5, /GB, /Gy,
 * /GF, /Gs, /Op, /Zp1, /Zp4, /Ob2 and /Oi all inert at 696; /G6 206, /Os 116,
 * /Ow 362, /Oy- 122, /Oi- 151, /Og- 134.
 *
 * Twentieth pass, 696 to 701 at the exact size, in the memcpy arm alone. The
 * nineteenth pass pinned only g_download_received and left the buffer read
 * inline in the address expression; reading BOTH addends through volatile
 * block-locals, received first, issues the two loads ahead of the source lea
 * and shrinks that cluster from 9 bytes to 4. Order and count both matter:
 * buffer-first scores 693, received-only (a plain buf local) 678, and a
 * single volatile received local with the buffer inline 678. The remaining 4
 * bytes there are the `lea esi` / `lea edi` pair issued in the opposite
 * order; a src local declared before, between, or after the two reads, and a
 * char-offset spelling of it, are all inert at 701.
 *
 * Twentieth-pass dead ends, all re-measured against 701 and reverted. Cluster
 * A twelve more ways: the two stores lifted out of the comma into statements
 * (inert), the flag store alone left in the comma (inert), arg2 through a
 * local assigned before the stores (inert), stores split across the two
 * argument comma lists either way (701 and 204), the whole store pair moved
 * into arg2 (inert), a plain non-volatile 0x400 test 690, the ternary spelled
 * as `2 - ((x >> 10) & 1)` 671, conn[1] read through header 218 at 751, arg2
 * re-derived as `(unsigned char*) header + 0x18` 218 at 751, a volatile conn[1]
 * read 170 at 748, and volatile on either store 695-701. Cluster B ten more
 * ways: the lb result kept in a block-local (inert) or in the shared ret
 * local 129 at 774, the status hoisted before the first sprintf (inert), the
 * mask folded into the sprintf argument (inert), a buffer local shared by
 * both sprintfs or scoped to the tail (inert), &buf[0] spellings (inert), a
 * volatile buffer pointer 302 at 758, the guard inverted with a tail label
 * (inert), a byte-wide mask 334 at 751, and the mask through status 300 at
 * 747. Cluster E four ways: pktbuf stored before the mask 685, the mask
 * through status with either store in a comma 471 at 749, both stores in
 * arg1's comma (inert). Memset half four ways: through g_download_slots 689,
 * received stored before total 689, a volatile received store 677. All 120
 * declaration permutations of the five scalars are inert at 701, as are the
 * A x E x D cross products (18 combinations), so the clusters remain
 * independent. near-diag at 701: 226 target instructions against 226
 * compiled, 30 register bytes and 24 structural. The remaining delta is
 * msvc6's scheduler, not a shape that C can express.
 *
 * Twenty-first pass, no gain: about ninety further shapes, all at 701/750 and
 * the exact size unless noted, all reverted. The value of the pass is negative
 * evidence on lever classes not previously tried here.
 *
 * Alias-model levers do not reach the schedule. A `conn_rec` struct type for
 * the cmd-3 arm, with the two stores as `header->cmd` / `header->mode` field writes in
 * the comma or as plain statements, and with the packet pointer taken as the
 * struct's array member, is inert; sourcing the arm's values from struct
 * fields instead of re-reading conn drops to 178 at 752. Section 40's
 * reference-count lever therefore has nothing to act on: the store pair is
 * already two references.
 *
 * C89 `register` hints are ignored by this compiler for these locals: on ret,
 * conn, i, status individually, on all three loop-carried ones together, and
 * on conn plus i, every variant is byte-identical to the baseline.
 *
 * Loop-level levers are inert or regress. i advanced in the body rather than
 * the for-increment, an unsigned i, a char* cursor with conn re-derived per
 * iteration, and the connected guard rewritten as a `continue` are all
 * byte-identical; an `unsigned char` i costs 38 bytes (131 at 788), dropping
 * the named ret local 143 at 732, and an `i < 8` bound 572 at 747.
 *
 * Volatile cannot force the target's push-before-store order in clusters A and
 * E. A volatile pointer local for the call's second argument, for both
 * arguments, or combined with volatile stores, moves the object to 758-766 and
 * scores 182-190; on the E side a volatile pktbuf pointer scores 465 at 758
 * and a volatile *conn store 693. The pushes and the stores are independent
 * operations on distinct objects, so there is no C-level sequence point that
 * orders them.
 *
 * Cluster B's rotation is not fed by the buffer's use count or by any value
 * kept live across the block. Eight buffer-pointer shapes (shared by the head
 * pair, the tail pair, all four calls, one per pair, assigned inside the 0x5f
 * arm, spelled &logbuf_lo[0], and declared before the LOBBY-mode log) are
 * inert, as are a cached guard byte, the lb argument spelled `conn + 6`, a
 * pointer local shared by the guard and the call, the connection re-derived
 * from the packet address in the arm, an `(int)` cast on the sprintf value,
 * and the lb result kept in a block-local. Consuming sprintf's return value in
 * the log call's level argument scores 258 at 756 and the shared ret local 129
 * at 774. Splitting the function-wide status into a separate store-value local
 * (three declaration placements, with and without the cmd-3 read moved) is
 * inert, so the rotation is not a live-range effect of status either.
 *
 * Cluster D's lea order survives every source-level placement of the source
 * address: a src local born before both volatile reads, between them, declared
 * first in the block, as unsigned int* / char* / void*, paired with an
 * explicit dst local in either order, the sum through a third local, and
 * char*-based destination arithmetic with either addend as the base. All
 * twelve are byte-identical. Reversing the addends is inert, buffer-first 693,
 * both plain 674, received-only 678, confirming the twentieth pass.
 *
 * Cluster A's branch structure is likewise not a lever: inverted call-result
 * polarity, the guard inverted with a goto to a tail label, a dword-masked
 * guard compare, the header assignment moved before the conn[1] read, and arg2
 * respelled as `(unsigned char*) conn + 0x18` are all inert; the result in the
 * shared ret local scores 129 at 774 and the 0x400 test through conn rather
 * than header 180 at 748.
 *
 * A x B and A x D x E cross products over the shapes that are not inert alone
 * produce no combination above 701, so the coupling that closed the memset and
 * memcpy pair in the nineteenth pass has no counterpart among the four
 * residual clusters. */


int __cdecl srv_ProcessReceiveData(void)
{
	char logbuf_hi[256];
	char logbuf_lo[256];
	unsigned char pktbuf[156];
	int ret;
	unsigned int* conn;
	int i;
	unsigned int status;
	unsigned char admin_flags;

	for (i = 0, conn = (unsigned int*) 0x101deb00; (int) conn < 0x114ffe20; conn = (unsigned int*) ((char*) conn + 0x264264), i++) {
		if ((*(unsigned char*) conn & 1) != 0) {
			do {
				ret = srv_ReceivePacketHeader(conn);
				if (ret == -1) {
					return -1;
				}
				status = *conn;
				if ((status & 0x80) == 0) {
					break;
				}
				if (status & 2) {
					unsigned char* pkt;
					unsigned int* header;
					/* Deriving header from pkt, and storing through the call's
					 * first argument, keeps conn[1] and both stores on ebp
					 * instead of rebasing them through the packet lea. This
					 * only reaches the target size together with the per-arm
					 * slot store below; on its own it runs three bytes long. */
					pkt = (unsigned char*) conn + 0x18;
					if (*pkt == 3) {
						status = conn[1];
						header = (unsigned int*) (pkt - 0x18);
						if (cm_QueuePlayerCommand(
							(header[0xb] = status,
							 header[0xc] = (*(volatile unsigned int*) header & 0x400) ? 1 : 2,
							 header),
							pkt) == -1) {
							return -1;
						}
					}
					status = *conn & 0xffffff7d | 0x200;
					goto set_status;
				}
				if (status & 0x200) {
					LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x5df, "LOBBY mode", 1);
					if (*(unsigned char*) (conn + 6) == 0x5f) {
						if (lb_ExLobbyServerCommand(conn, (int) ((unsigned char*) conn + 0x18)) == -1) {
							return -1;
						}
						sprintf(logbuf_lo, "status after lb_ExLobbyServerCommand: %i", *conn);
						LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x5e5, logbuf_lo, 1);
					}
					*conn = *conn & 0xffffff7f;
					sprintf(logbuf_lo, "leaving lobby branch: %i", *conn);
					LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x5e9, logbuf_lo, 1);
					goto done_inner;
				}
				if (status & 8) {
					if (*(unsigned char*) (conn + 6) == 8) {
						unsigned int total;
						total = conn[10];
						/* Both stores plain and issued before the memset: that is
						 * what lets msvc6 sink the rep stosd below the two pushes
						 * the way the original does. Making either store volatile,
						 * or moving the memset first, rotates the registers here
						 * and in the memcpy arm below. */
						g_download_total_size = total;
						g_download_received = 0;
						memset((void*) 0x101deac8, 0xff, 32);
						g_download_buffer = (unsigned int) m_AllocTracked(total, "srv_LoadBuf");
					}
					else if (*(unsigned char*) (conn + 6) == 9) {
						unsigned int rec;
						unsigned int buf;
						/* Both addends read through volatile locals, received
						 * first: that order issues the two loads ahead of the
						 * source lea and picks the original's `lea edi,[ecx+eax]`
						 * over `add edi,ecx`. Pinning only one of the two, or
						 * loading the buffer first, loses it. This depends on the
						 * store order above. */
						rec = *(volatile unsigned int*) &g_download_received;
						buf = *(volatile unsigned int*) &g_download_buffer;
						memcpy((void*) (buf + rec), conn + 10, 0x80);
						g_download_received = g_download_received + 0x80;
					}
					if (g_download_received >= g_download_total_size) {
						*conn = *conn & 0xfffffff7;
					}
					status = *conn & 0xffffff7f;
					goto set_status;
				}
				if (status & 4) {
					sprintf(logbuf_hi, "Unexpected Request from connection nr %i", i);
					LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x609, logbuf_hi, 1);
					*conn = *conn & 0xffffff7f;
					pktbuf[0] = 2;
					if (cm_QueuePlayerCommand(conn, pktbuf) == -1) {
						return -1;
					}
					goto done_inner;
				}
				/* The slot store is duplicated per arm rather than issued once
				 * above the test: that is what stops msvc6 hoisting the shared
				 * srv_QueueCommandForProcessing prefix, so each arm keeps the
				 * original's own `mov [ebp+0x1b],bl` / `lea` / `push` / `call`. */
				if (status & 0x10) {
					*((unsigned char*) conn + 0x1b) = (unsigned char) i;
					if (srv_QueueCommandForProcessing(conn, (unsigned char*) (conn + 6)) != 0) {
						return -1;
					}
					status = *conn & 0xffffff6f;
					goto set_status;
				}
				*((unsigned char*) conn + 0x1b) = (unsigned char) i;
				if (srv_QueueCommandForProcessing(conn, (unsigned char*) (conn + 6)) != 0) {
					return -1;
				}
				status = *conn & 0xffffff7f;
			set_status:
				*conn = status;
			done_inner:;
			} while ((*(unsigned char*) conn & 1) != 0);
			if (ret == -1) {
				return -1;
			}
		}
	}

	/* One byte load feeds both flag tests: the original checks 0x80 before
	 * looping back on bit 0, so the loop condition is re-tested at the bottom
	 * off the same `mov al`. All three exits of this loop share the single
	 * `xor eax,eax` epilogue below. */
	while ((*(unsigned char*) 0x114ffe20 & 1) != 0) {
		if (srv_ReceivePacketHeader((unsigned int*) 0x114ffe20) == -1) {
			goto done;
		}
		admin_flags = *(unsigned char*) 0x114ffe20;
		if ((admin_flags & 0x80) != 0) {
			pktbuf[0] = 2;
			cm_QueuePlayerCommand((unsigned int*) 0x114ffe20, pktbuf);
			cm_ClosePlayerConnection((unsigned int*) 0x114ffe20);
			goto done;
		}
	}
done:
	return 0;
}
