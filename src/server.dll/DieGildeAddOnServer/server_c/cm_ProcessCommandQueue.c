/* cm_ProcessCommandQueue - Master Command Router (0x1000aac0).
 *
 * Byte match: 624/639, obj size equals the target (639), NEAR_MATCHING.
 * Levers that moved it from the 118/639 baseline:
 *   - `nextp` keeps &pkt[0x95] in a register across the unlink, matching the
 *     target's `lea eax,[esi+0x95]` (118 -> 121).
 *   - The volatile `type` read pins the byte load ahead of `test ebx,ebx`
 *     instead of folding it into each `cmp byte ptr [esi],imm` (126 -> 136).
 *   - Reading `next` before taking `nextp` orders the [esp+0x10] store (-> 140).
 *   - An explicit `goto held_arm` for the held!=0 case instead of if/else if:
 *     the target tests `held` and branches, it does not chain the compares
 *     (140 -> 182).
 *   - `t2` caches the type byte for the range check, matching the target's
 *     single `mov al,[esi]` feeding both `cmp al,0x6a` and `cmp al,0x20`
 *     (182 -> 187).
 *   - Spelling the range check as `< 0x6a` with the log call in the `else`
 *     puts the log block out of line where the target has it (187 -> 263).
 *   - The same inversion on the dispatch result (`== 0` with the queued path
 *     in the trailing block) moves the queued block out of line (263 -> 376).
 *   - The broadcast loop as do/while with the two skips merged into one
 *     condition drops the pre-test guard the target has no room for
 *     (376 -> 463).
 *   - Testing the connection flag through the `g_connections[...]` subscript
 *     instead of through the `slot` local emits the target's
 *     `test byte ptr [reg*4 + g_connections],1` and closes the size gap
 *     (463 -> 575, obj 639 = target).
 *   - Writing `i = 0` before `slot = g_connections` orders the two loop
 *     inits as the target has them (575 -> 578).
 * `g_connections` is declared `unsigned int[]` so the 0x264264 stride indexes
 * as 0x99099 entries and emits the target's scale-4 `[reg*4 + g_connections]`.
 *
 * Residual as of the twentieth round: 15 bytes at 0x37 and 0x3f-0x4c,
 * one contiguous region.  The two-cluster reading below is the state at
 * the fifteenth round and is kept for the spellings it rules out.
 *   - Indices 17-38: the two dispatch arms are byte-identical to the target
 *     but emitted in the opposite order; the target lays `cmp cl,5` first and
 *     reaches `cmp cl,6` by a forward branch. Every source spelling tried
 *     either kept this order or collapsed the score: natural if/else-if (158),
 *     if/else with the arms swapped (163), a shared `unlink2` tail (162),
 *     the target's own recheck-inline CFG (153), duplicating the recheck into
 *     arm 1 (156).
 *   - Indices 129-131, 156-157, 170-171: `ecx`/`edx` vs `edx`/`eax` in the
 *     index computation. Hoisting the id byte into a local (578), an explicit
 *     `idx` local (578), a `cp` pointer local (578), passing the address
 *     expression directly (576), and reordering the store against the test
 *     (578) all leave the roles unchanged.
 *
 * 2026-09-05: three more CFG spellings aimed at the indices 17-38 arm order,
 * all worse than 578.  Placing `recheck` textually before `held_arm` with an
 * inverted `held == 0` test recompiles byte-identical to this form (578, obj
 * 639): MSVC6 re-lays the blocks in its own layout pass, as section 17 of
 * docs/msvc6-c-shapes.md records.  Nesting the type-5 arm inside an outer
 * `if (held == 0)` and moving `recheck` below the held arm is 158/640
 * (SIZE_MISMATCH), and hoisting the whole held arm to the end of the loop
 * body with a `goto unlink` tail is 162/644 (SIZE_MISMATCH); both rebuild the
 * loop's branch skeleton rather than just reordering the two arms.
 *
 * 2026-09-05, three more, all 578/639 at obj 639 and byte-identical to this
 * form: spelling `recheck` as `if (held == 0) goto unlink; goto advance;`
 * (the target's own branch polarity - MSVC6 normalizes it back), swapping the
 * broadcast-loop compare operands to `*(pkt+3) != i`, and a CFLAGS sweep
 * (/O2 /Gd /G5, /Ox /Gd, /O2 /Gd /Gy, /O2 /Gd /Ob1). Neither residual cluster
 * is reachable from branch spelling or flags.
 *
 * 2026-09-06, five more.  Unchanged at 578/639, obj 639: hoisting `slot` above
 * the `queued` flag test so the arm reads it through the local, an explicit
 * `(unsigned int)` cast on the broadcast-loop id compare, and routing the
 * queued arm's second address through `nextp` before `slot`.  Worse: passing
 * the `&g_connections[...]` address expression directly to
 * cm_QueuePlayerCommand in the queued arm is 576/639, an if/else-if pair with
 * the type-6 arm ending in `goto unlink` is 158/640 (SIZE_MISMATCH), and
 * inlining the shared recheck into the type-5 arm (the target's own layout) is
 * 162/644.  Both residual clusters survive every source form tried.
 *
 * 2026-09-06, a second pass at the indices 17-38 arm order, now reading the
 * near-size candidates instruction-wise rather than by score (section 19).
 * The `if (held == 0) { ... }` head with the type-5 arm inline is the closest
 * shape found: at obj 640 it scores only 158, but its diff shows the target's
 * branch polarity reproduced exactly (`jne held_arm`, `cmp cl,5`, `mov
 * ebx,esi`, `test ebx,ebx`) where the committed form emits the type-6 arm
 * first.  It loses because msvc6 lays `unlink` immediately after the head
 * instead of the recheck block, which costs one byte and shifts everything
 * after.  Reordering the source blocks into the target's own layout (head,
 * held==0 arm, recheck, held_arm, unlink), with recheck spelled both
 * polarities, recompiles byte-identical to the committed 578 form: MSVC6
 * re-lays the blocks in its own pass, as section 17 records.  The one-byte
 * deficit is not reachable from block order.
 *
 * Also neutral at 578/639, obj 639: `if (held)` instead of `if (held != 0)`,
 * an `hz = (held != 0)` flag local, the type-6 arm inverted to `if (type != 6)
 * goto recheck`, an `(unsigned int)` cast on both sides of the broadcast-loop
 * id compare, splitting the broadcast condition into nested `if`s, and testing
 * the queued arm's connection flag as a full `unsigned int` word instead of
 * through the byte cast.  Worse: reading `next` through `nextp` rather than
 * before it is 142/637, and combining the held and type-5 tests into one `&&`
 * is 158/640.
 *
 * 2026-09-06, tenth round: the indices 17-38 gap is one inlined block, and the
 * exact instruction it costs is now identified.  The target reaches its shared
 * `test ebx,ebx` from the type-6 arm by a 2-byte BACKWARD branch
 * (`0x1000ab0b: 75 f2  jne 0x1000aaff`), so arm 1's tail is the join point for
 * both arms.  Every source form splits into two cases:
 *   - a plain `goto recheck` from arm 1 lets msvc6 fuse `je unlink` + `jmp
 *     advance` into one `jne advance` and lay `unlink` inline, which shifts the
 *     whole tail by 13 bytes: 158/640 at obj 640, one byte over.  Inverting the
 *     recheck to `if (held == 0) goto unlink; goto advance;` and adding a
 *     redundant `pkt = held` recompile to the same 640.
 *   - an explicit re-test after the assignment (`held = pkt; if (held == 0)
 *     goto unlink; goto advance;`) does defeat the fusion and reproduces indices
 *     24-45 instruction-for-instruction, dropping the `**` count from 47 to 33,
 *     but msvc6 then emits `test esi,esi` before `mov ebx,esi` and a 6-byte near
 *     `jne` where the target has the 2-byte backward one: 139/643 at obj 643,
 *     four bytes over.  Testing `pkt` instead of `held`, hoisting the shared
 *     test into a `held_test` label (127/641), a volatile read of `held` at the
 *     test (128/648, it homes held to the stack), and `ok = 1` reset in the
 *     type-6 arm (122/643) are all worse.
 * The branch is 2 bytes only because the target's join sits within -128 of the
 * type-6 arm; both of our layouts place it outside that window.  Confirmed in
 * .scratch/l2f/cfg2.c, an isolated probe with a smaller unlink body, which does
 * emit the target's `jne` backward edge (`0x42: 75 ef`) from the same source
 * shape.  The distance, not the spelling, is what blocks it.
 *
 * 2026-09-06, eleventh round, six more CFG spellings on the indices 17-38 arm
 * order, none above 578.  Byte-identical at 578/639, obj 639: the type-5 arm
 * spelled positively (`if (type == 5) { held = pkt; goto recheck; } goto
 * unlink;`), an `else` wrapper around the type-5 arm with the `goto held_arm`
 * kept, `recheck` moved textually above `held_arm` with the type-6 arm
 * inverted to `if (type != 6) goto recheck`, and the same with `recheck`
 * spelled `if (held != 0) goto advance; goto unlink;`.  Worse, all
 * SIZE_MISMATCH: the `if (held == 0)` head with `recheck` after the held arm
 * and an explicit `goto unlink` tail (127/641), the same head with `recheck`
 * nested inside the first arm (127/641), the head plus a duplicated recheck in
 * both arms (139/643), and replacing the held arm's `goto recheck` with a
 * direct `goto advance` (166/644).  Every form that reproduces the target's
 * branch polarity pays at least one byte for the block msvc6 lays inline,
 * which confirms the tenth round's reading: the deficit is the 2-byte backward
 * join edge, not the source spelling.
 *
 * 2026-09-06, twelfth round.  The two residual clusters were re-measured as
 * byte counts rather than instruction counts, using an isolated probe of the
 * whole function (.scratch/pcq_l2f, 0.5 s per compile against the ~3 min of
 * `rebrew test`).  Cluster A (indices 17-38) is 50 of the 57 mismatched bytes,
 * cluster B (129-131, 156-157, 170-171) is the remaining 7, one byte each at
 * 0x1a3, 0x1a5, 0x1a8, 0x1ef, 0x1f3, 0x216, 0x21a.  Closing A alone would give
 * 632/639, so it is where the value is.
 *
 * The layout rule behind cluster A, read off the emitted blocks rather than
 * inferred from scores: msvc6 lays the arm reached by FALLTHROUGH first and
 * hoists the block named by the first `goto` to be that fallthrough.  The
 * target instead reaches its shared `test ebx,ebx` from the type-6 arm by the
 * 2-byte backward `75 f2` at 0x1000ab0b, which requires the type-5 arm (with
 * the join at its tail) to be laid FIRST and the type-6 arm second.  Two
 * families exist and neither is both:
 *   - `if (held != 0) goto held_arm;` with the type-6 arm textually second
 *     (the committed form) lays type-6 first: 578/639 at obj 639, correct size,
 *     wrong arm order.
 *   - `if (held == 0) { type-5 arm } else { type-6 arm }` does lay type-5
 *     first and reproduces the target's `jne held_arm` head AND its 2-byte
 *     backward join exactly, but msvc6 then splices the type-6 arm into the
 *     unlink block's if/else seam, so `unlink` lands between the two arms:
 *     181/640, one byte over.
 * Fourteen further spellings were compiled to move `unlink` past the type-6
 * arm, all in the 143-181/640-642 band: a bare `else { goto held_arm; }` with
 * `recheck` in both polarities, `do { ... } while (0)` with `break` for the
 * unlink exit (both arm orders), the type-6 arm hoisted below `advance:` with
 * a `continue` before it, an explicit `goto unlink` tail on each arm
 * separately and on both, `zero_arm`/`held_arm` label pairs in both textual
 * orders, and inverting the unlink block's own head to `if (pkt != *tab)` under
 * the three best arm bodies (that one also regresses the committed form to
 * 549).  Every form that gets the target's arm order pays the byte for the
 * block msvc6 inlines at the seam.  The join distance is what selects the
 * 2-byte encoding and it is not addressable from C.
 *
 * Cluster B re-probed on the broadcast loop's id compare: an `(unsigned int)`
 * cast on either side, `(int) (unsigned int)` double cast, `(unsigned char) i`
 * on the left, and operand swap to `*(pkt+3) != i` are all byte-identical at
 * 578.  `pkt[3]` subscript form is 401/638 and a `volatile` read is 398/643.
 *
 * Operand audit (2026-09-06): every `~~` in this function resolves correctly.
 * The masked slots hold g_connections (0x101deb00), g_dispatch_table
 * (0x1002c3f8), and calls to LogMessageInternal (0x10003640),
 * cm_QueuePlayerCommand (0x1000a9a0) and ahm_ProcessEntityChain (0x1000ca00).
 * The three string operands were read out of original/server.exe: 0x10029adc
 * is "Multisync!!!", 0x100298b0 is
 * "D:\\Develop\\DieGildeAddOnServer\\server.c", and 0x10029ac0 is
 * "Command-Type out of Range!\n" - all byte-identical to the literals here.
 * Re-verified 2026-09-06 against original/Server/server.dll: the seven call
 * sites in the range disassemble to 0x1000ca00, 0x10003640 x2, 0x1000a9a0 x3
 * and the indirect `[ecx*4 + 0x1002c3f8]`, whose first eight slots hold real
 * handler addresses (0x1000d2e0, 0x1000d330, 0x1000d340, ...), and the three
 * strings re-read identical at their VAs.  No false RELOC here.
 *
 * 2026-09-06, thirteenth round.  Cluster A's one-byte deficit was accounted
 * for exactly, by disassembling the 640-byte candidate against the target
 * rather than reading its score:
 *   target   aaff `test ebx,ebx` + ab01 `je unlink` (2) + ab03 `jmp advance`
 *            (5) = 7 bytes, and the type-6 arm ends `je advance` and falls
 *            through into unlink with no tail jump.
 *   640-byte 0x71 `test ebx,ebx` + 0x73 `jne advance` (6) = 6, saving one, but
 *            its type-6 arm needs a 2-byte `jmp` tail, costing two.  Net +1.
 * So the deficit is not the join's polarity and not the arm order: it is that
 * msvc6 lays `unlink` after the type-5 arm, leaving the type-6 arm to jump
 * over it, where the target lays `unlink` after the type-6 arm.  Confirms
 * section 17: block placement is chosen in msvc6's own layout pass.  Writing
 * the source in the target's exact block order (head, type-5 arm, join,
 * type-6 arm, unlink) with the join in either polarity and the type-6 arm
 * ending in fallthrough recompiles byte-identical to this committed form
 * (582/639 on the isolated probe, 578 through `rebrew test`); adding an
 * explicit `goto unlink` tail to that arm is 177/640.
 *
 * Cluster B re-probed with the same harness, all at the committed score: the
 * id byte read into an `int id` local declared inside the loop body, an
 * `(unsigned int)` compare on both operands.  Worse: the flag test moved ahead
 * of the id compare (573/639) and a byte-width compare (110/632).
 *
 * 2026-09-06, fourteenth round: 578 -> 617/639 at obj 639.  The thirteen
 * previous rounds all read cluster A as an arm-ORDER problem and tried to make
 * msvc6 lay the type-5 arm first.  Every such form pays a byte for the block
 * msvc6 splices at the if/else seam, so none stayed at 639.  The gain came from
 * the opposite direction: keep the committed arm order and delete the join's
 * work instead.  Arm 5 sets `held = pkt` and then falls into `recheck`, whose
 * test msvc6 can prove true, so it folded `je unlink` + `jmp advance` into one
 * `jne advance` and reached `advance` by a 5-byte near jump.  Ending arm 5 with
 * an explicit `goto advance` states that edge directly: the fold disappears,
 * arm 6's `type != 6` exit becomes the only `recheck` predecessor, and 35 more
 * bytes fall into place.  The change is semantically inert (`recheck` is
 * reached from arm 5 only with `held == pkt != 0`, so it always took the
 * `advance` edge) and touches control flow only.
 *
 * 2026-09-06, fifteenth round: 617 -> 624/639 at obj 639.  Cluster B's
 * queued-arm index computation (`mov cl,[esi+3]` + shl/add chain +
 * `lea edx,[eax+eax*8]` + mem-form `test [edx*4+g_connections],1`) vs the
 * target's (`mov cl,[eax*4+g_connections]` + `lea eax,[eax*4+g_connections]`
 * + reg-form `test cl,1`): the target loads the flag byte through the
 * scaled index and reuses eax for the address, never materializing a
 * separate lea temp.  Spelling the arm as a byte-offset computation,
 * `t2 = ((unsigned char*) g_connections)[id * 0x264264]; slot = base + id *
 * 0x264264`, emits the target's `mov cl,[eax*4+g]` + `lea eax,[eax*4+g]` +
 * `test cl,1` exactly (the `* 0x264264` decomposes into the target's own
 * shl/add chain, no imul).  Same form on the multisync arm is neutral
 * (624) and on the memcpy arm is neutral; kept only here.  The `* 0x99099`
 * entry-index form and the `&g_connections[...]` address form both keep
 * the lea-temp + mem-form test.
 *
 * Residual after it: 15 bytes.  Cluster A unchanged (target's
 * `test ebx,ebx; je unlink` after `mov ebx,esi` + 2-byte backward join
 * from arm 6; ours jumps direct).  Cluster B remainder is the id-byte
 * register (target eax, ours ecx) in the broadcast loop, unchanged by
 * init-order swaps, nested-if conditions, guard clauses, hoisting into
 * `t2` or an in-loop local (all 617-624).
 *
 * 2026-09-06, sixteenth round: ~45 isolated probes (.scratch/pcq2/,
 * scored against 639 bytes with the M7 harness; base probe 624/639 at
 * obj 640). Zero-sum accounting for cluster A, read off disassembly:
 * arm-5 tail is target 11B (`mov ebx,esi` + `test ebx,ebx` + `je` +
 * 5-byte `jmp`) vs ours 7B (`mov ebx,esi` + 5-byte `jmp`), while arm 6
 * pays it back (target 2-byte short `jne` to the join vs our 6-byte
 * near `jne` to advance). Net 0 at equal size; fixing one side alone
 * always breaks it. Both-fixed needs the target's exact CFG and every
 * spelling re-lays (section 17).
 * Byte-identical to this form (lever inert): comparison-operand swaps
 * (`0 == held`, `5 != type`, `0 != pkt`, tab-bound direction), all nine
 * declaration permutations, `if (!held)`/`if (held)` spellings, both
 * recheck polarities, `ok` test/init spellings, nested id-outer
 * broadcast guard, mem-form queued-arm flag test, `!(t2 >= 0x6a)`,
 * for/while/tab-loop rewrites, arm-6 assignment order variants.
 * Worse, with scores: `ok = 1` before the type read (615, `mov edi,1`
 * lands before the byte load, confirming type-then-ok order), `ok` as
 * call-result ternary (585, branchless neg/sbb), condition flag-first
 * in the broadcast loop (612), multisync `&&` swapped (616),
 * `<= 0x69` range form (622, wrong cmp byte), unlink store swap (610),
 * freelist store reorder (604), type-first loop top (570),
 * `nextp`-first loop top (201), arm-5 fallthrough into recheck (181),
 * arm-5 explicit retest (189 at obj 656). `handler_func h` temp does
 * not compile (C2275, declaration placement).
 *
 * 2026-09-06, seventeenth round: ~25 fast probes (.scratch/pcq2/, M7
 * scorer; base probe 624/639 there at obj 640 = 624/639 at obj 639
 * through `rebrew test`). The join is now proven attempt-proof from C:
 * every spelling with the same CFG (wC explicit `goto recheck` tail,
 * qQ5/qQ6/qQ7 ok-test reorderings, rR3 if/else tail, zK/zL join
 * elision, pI/pJ positive-polarity arms) recompiles to the identical
 * 15 bytes at obj 639. Any spelling that changes the CFG (vjoin1-5,
 * wA/wB/wD, xE/xF/xG, yH/yI/yJ) cascades to 450-490 mismatched bytes.
 * New since round 16: moving `ok = 1` into arm 6 (sS2/tT2/tT3) moves
 * `mov edi,1` after the dispatch compare and the join still will not
 * form (24-25 bytes); `int type` widens the frame (153/656); t2 as
 * the dispatch index homes it to the stack (267/656); id3/ok/t2
 * hoists in the broadcast loop home to the stack or widen the frame
 * (111-129); for/while rewrites of the broadcast loop keep the ecx id
 * register (416); continue-forms of the arm tails cascade (148-569).
 *
 * 2026-09-08, eighteenth round.  The 15 bytes were re-read with an
 * offset-aligned disassembly differ (.scratch/pcq-l3/adiff.py, which
 * pads the shorter side so an insertion does not shift the rest of the
 * listing) instead of `rebrew diff`, whose 173 `**` lines are mostly
 * that shift.  The delta is one contiguous region and nothing else:
 *   0x36  jne 0x48 vs jne 0x44         (1 byte, the head's displacement)
 *   0x3f  test ebx,ebx / je 0x78 / jmp 0x248   (target, 9 bytes)
 *         vs jmp 0x248 (5 bytes) then arm 6 at 0x44 with a 6-byte
 *         `jne` where the target reaches the join by `75 f2` at 0x4b.
 * Every other mismatched byte in the function is a reloc slot.  So the
 * whole residual is the join block: the target keeps `test ebx,ebx`
 * live, our arm 5 lets msvc6 prove it and fold it away.
 *
 * Both halves of the zero-sum were reproduced separately, each in a
 * form whose block offsets were read off the object rather than
 * inferred from the score (.scratch/pcq-l3/blocks.py):
 *   - This committed form has the target's block order exactly
 *     (arm5 0x38, arm6 0x44, unlink 0x78 against the target's 0x38 /
 *     0x48 / 0x78) and no join.
 *   - The plain `if (held == 0) { ... } else { ... }` head with the
 *     join after it emits the target's `test ebx,ebx` AND its 2-byte
 *     backward `75 e5` from arm 6, but msvc6 then lays unlink at 0x47,
 *     between the two arms, pushing arm 6 to 0x55: 181/639.
 * Twelve further spellings were compiled to hold the live join while
 * keeping unlink last: arm-5 `goto recheck` / `goto advance` / plain
 * fallthrough tails, arm-6 tails ending in fallthrough, `goto unlink`
 * and inverted `if (ok) goto unlink`, `else if (type == 6)` in place of
 * the nested exit, a `held_arm` label with the join above it in both
 * polarities, both join polarities under each, and a `volatile` read of
 * `held` at the join (113/656, it homes held to the stack).  Every one
 * lands in exactly one of the two states above: 624/639 with the target
 * layout and no join, or 149-181/639 with the join and unlink spliced
 * in.  Moving the unlink body textually past `advance:` with a
 * `continue` is 96-104 at obj 640-656.
 *
 * A CFLAGS sweep on the live-join form (/Ox, /Gy, /G5, /G6, /Ob0,
 * /Ob1, /O1, /Oxs, /Oy-, /Og /Oi /Ot /Oy /Gs) does not move it either:
 * every /O2-class flag gives the same 181, the rest are far worse.
 *
 * `/DREBREW_ALLOW_NAKED` in the CFLAGS is inert: the file contains no
 * `#ifdef` on it and no `__asm`, and compiling with and without it
 * gives the same 624/639 at obj 639.  It can be dropped from the
 * metadata whenever the CLI next rewrites that entry.
 *
 * 2026-09-08, nineteenth round: ~40 probes (.scratch/pcq-l4/, same M7
 * scorer, base 624/639 at obj 639).  The layout rule behind the 15
 * bytes is now stated exactly, read off block offsets rather than
 * scores: msvc6 lays the arm that is textually SECOND first, and the
 * join block, when it survives, takes that arm's fallthrough slot.
 * The target needs the opposite pairing (type-5 arm first at 0x38,
 * join at 0x3f, type-6 arm at 0x48, unlink at 0x78), and no source
 * spelling produces it.  Every probe lands in exactly one of three
 * states:
 *   - 624/639 at obj 639, this committed form: the target's block
 *     order exactly, but arm 5's `goto advance` lets msvc6 prove the
 *     join's test and fold it away, so `jne` at 0x36 reaches 0x44
 *     instead of 0x48 and the 4-byte join is absent.
 *   - 181/639 at obj 640: the join survives with the target's own
 *     2-byte backward edge `75 e5`, but msvc6 splices `unlink` into
 *     the join's fallthrough at 0x47 and pushes arm 6 to 0x55.
 *   - 589/639 at obj 640: join and block sizes both correct, arms
 *     mirrored (arm 6 at 0x38, arm 5 at 0x69), head test inverted.
 * The 589 family is the closest structural mirror found and is 50
 * mismatched bytes against this form's 15.
 * New spellings tried, all landing in one of the three: a 12-way
 * systematic sweep over {join polarity} x {arm-5 tail: goto / plain
 * fallthrough} x {arm-6 tail: goto recheck / goto unlink /
 * fallthrough}, `zero_arm`/`held_arm` label pairs in both textual
 * orders, arm 6 placed textually after the join, `do { } while (0)`
 * with `break` for both arm exits, the unlink body's head inverted to
 * `pkt != *tab` under each of the three states, a redundant
 * `goto unlink;` before the `unlink:` label, a second `unlink_a:`
 * label giving unlink a third predecessor, the join's test read from
 * `pkt` instead of `held` (178), `held` laundered as
 * `(char*) nextp - 0x95` (161-187 at obj 656), and a `volatile` read
 * of `pkt` at the assignment (116-131, it homes the local).  A flags
 * sweep on the live-join form (/Ob0, /Gf, /Ox /Ob0, /Oi-) is 181 or
 * worse.
 *
 * 2026-09-08, twentieth round.  The residual was re-measured from
 * scratch: 15 bytes at 0x37 and 0x3f-0x4c, one contiguous region, every
 * other mismatch a relocation slot.  The block layout was then read off
 * each probe's object rather than inferred from its score, matching on
 * `cmp cl,5` / `test ebx,ebx` / `cmp cl,6` / `cmp esi,[ebp]`
 * (.scratch/pcq-l5/sig.py).  Target order is arm5 0x38, join 0x3f,
 * arm6 0x48, unlink 0x78.
 *
 * A 72-way exhaustive cross-product was compiled over the five axes
 * that had each produced a distinct layout: head spelling (goto-label
 * vs if/else), arm-5 tail (goto advance / goto recheck / fallthrough),
 * arm-6 tail (goto unlink / goto recheck / fallthrough), join polarity,
 * and the join's textual position (before or after arm 6).  It yields
 * exactly five block orders and the target's is not among them:
 *   arm5,arm6,unlink        12 probes, 624/639, this committed form
 *   arm6,arm5,unlink        12 probes, 589/639
 *   arm5,join,unlink,arm6   16 probes, 181/639
 *   arm6,arm5,join,unlink   18 probes, 171-177/639
 *   arm5,arm6,join,unlink   14 probes, 142-149/639
 * The rule behind it: the join survives only with two predecessors, and
 * whenever it survives msvc6 fuses its `je unlink` + `jmp advance` into
 * one conditional and lays the surviving successor in the freed
 * fallthrough slot.  That slot is what the target gives to arm 6.  With
 * arm 5 ending `goto advance` the join has a single predecessor whose
 * `held != 0` msvc6 proves, so it deletes the block: that is this form,
 * with the target's own block order but no join.  The two states are
 * mutually exclusive from C.
 *
 * Also measured and ruled out this round: the 656-byte families are
 * really 641 code bytes plus 15 trailing alignment NOPs, so they are 2
 * over, not 17; inverting the unlink head to `pkt != *tab` is 591 on
 * this form and 558 on the live-join form; moving the join block to the
 * bottom of the loop next to `advance:` is 88-92 at obj 672-688;
 * `pkt = next; continue;` in place of `goto advance` on the join and
 * arm tails is 117-520; a trampoline label between the join and unlink
 * in both textual positions is 589; `do { } while (0)` with `break` for
 * the unlink exit is 177.
 *
 * `/DREBREW_ALLOW_NAKED` in the CFLAGS is confirmed inert again: with
 * and without it the object is byte-identical at 624/639.  A CFLAGS
 * sweep on this form (/Ox /Gd, /O2 /Gd /Gy, /O2 /Gd /Ob0, /O2 /Gd /Og)
 * is 624 in every case; /O2 /Gd /G6 is 589 and /O1 /Gd is 93 at obj 541.
 *
 * ===================================================================
 * DOCUMENTED WALL - twenty-first round, 2026-09-08.  Do not spend
 * further rounds on the 15 bytes without new information.
 * ===================================================================
 *
 * The exact delta, from the offset-aligned differ (which pads the
 * shorter side, so an insertion does not shift the rest of the
 * listing).  15 bytes at 0x37 and 0x3f-0x4c; every other mismatch in
 * the function is a relocation slot:
 *
 *   off  target                        ours
 *   36   75 10   jne 0x48              75 0c   jne 0x44
 *   3f   85 db   test ebx,ebx          e9 04 02 00 00  jmp advance
 *   41   74 35   je 0x78 (unlink)      -
 *   43   e9 00 02 00 00  jmp advance   -
 *   44   -                             80 f9 06  cmp cl,6
 *   47   -                             0f 85 fb 01 00 00  jne advance
 *   48   80 f9 06  cmp cl,6            -
 *   4b   75 f2   jne 0x3f (backward)   -
 *
 * So the whole residual is the join block `test ebx,ebx; je unlink;
 * jmp advance` at 0x3f, which the target keeps and we do not, plus the
 * head displacement at 0x37 that follows from its absence.
 *
 * WHY IT CANNOT BE REACHED FROM C.  Block placement is chosen in
 * msvc6's own layout pass (section 17).  Two facts, each read off
 * object block offsets rather than inferred from a score
 * (.scratch/pcq-l5/sig.py locates arm5/join/arm6/unlink by opcode
 * signature):
 *   1. The join survives only with two predecessors.  With arm 5
 *      ending `goto advance` its only edge is arm 6's `type != 6`
 *      exit, where `held != 0` is known, so msvc6 proves the test and
 *      deletes the block.  That is this form: the target's block order
 *      exactly, but no join.
 *   2. Whenever the join does survive, msvc6 fuses its `je unlink` +
 *      `jmp advance` into a single conditional and lays the surviving
 *      successor in the freed fallthrough slot.  That slot is the one
 *      the target gives to arm 6, so arm 6 is pushed past unlink.
 * The target needs the join alive AND arm 6 in the fallthrough slot.
 * From C those are mutually exclusive, which is the real content of
 * the arm-5/arm-6 zero-sum note: each half is reachable alone and the
 * other regresses further than the first gains.
 *
 * RULED OUT, exhaustively.  A 72-way cross-product over head spelling
 * (goto-label vs if/else), arm-5 tail (goto advance / goto recheck /
 * fallthrough), arm-6 tail (goto unlink / goto recheck / fallthrough),
 * join polarity, and the join's textual position yields exactly five
 * block orders, and the target's arm5,join,arm6,unlink is not among
 * them:
 *   arm5,arm6,unlink       12 probes  624/639  this form
 *   arm6,arm5,unlink       12 probes  589/639
 *   arm5,join,unlink,arm6  16 probes  181/639
 *   arm6,arm5,join,unlink  18 probes  171-177/639
 *   arm5,arm6,join,unlink  14 probes  142-149/639
 * A further 24-way sweep removing arm 5's direct `goto unlink` edge, so
 * unlink is reachable only through the join, adds no sixth order and
 * peaks at 589.  Giving the join a second predecessor from arm 6's
 * ok == 0 path is 97/624; from both arms, 181.
 *
 * Also ruled out: inverting the unlink head to `pkt != *tab` (591 here,
 * 558 with the join live); moving the join to the loop bottom beside
 * `advance:` (88-92 at obj 672-688); `pkt = next; continue;` replacing
 * `goto advance` on the join and arm tails (117-520); a trampoline
 * label between join and unlink in both textual positions (589);
 * `do { } while (0)` with `break` for the unlink exit (177);
 * per-arm duplicated join copies (162-189).
 *
 * MEASUREMENT CORRECTION.  The "656-byte" probe families are really
 * 641 code bytes plus 15 trailing alignment NOPs, so they are 2 over,
 * not 17.  Earlier rounds read that padding as real inflation and
 * over-penalised the family that is structurally closest to the
 * target.  Judge probes here by block order, not by match_count: the
 * 142-181 band contains the closest candidates, which is why six
 * rounds of score-driven search circled.
 *
 * ROUND 191 -- THAT ESCAPE HATCH IS NOW EMPIRICALLY CLOSED, and the
 * residual is misdescribed above.  Three findings, all measured:
 *
 * (1) It is NOT "arm order".  Our committed form ALREADY HAS the
 *     reference's exact block order -- arm5 0x38, arm6 0x44, unlink
 *     0x78 against the reference's 0x38 / 0x48 / 0x78, read off the
 *     objects rather than inferred.  The fault is TAIL-SHARING: the
 *     reference shares ONE `jmp advance` between arm5's fallthrough and
 *     arm6's exit, and we duplicate it.  The arithmetic is exactly
 *     zero-sum -- arm5+join is 16B in the reference against our 12B
 *     (-4), arm6 is 48B against our 52B (+4) -- which is precisely why
 *     15 bytes differ at identical size, and why fixing either side
 *     breaks the other.  All 15 bytes are this one fault; byte 0x37 is
 *     just the head displacement shifting because the 4-byte join is
 *     absent.  (`rebrew diff`'s "173 structural" is the desync artifact;
 *     instr_diff shows 2 hunks, 2 reference-only instructions.)
 * (2) sp6 FUSES `je unlink` + `jmp advance` into one `0f85` even though
 *     that is a net 3-byte LOSS: it saves 1 byte locally and costs arm6
 *     4 (a 2-byte backward edge becomes a 6-byte near jump).  The layout
 *     pass is greedy per block, so no size-first flag declines it --
 *     /Os, /O2 /Os, /Ox /Os, /Oxs, /Os /Ob2 and /Og /Os /Oi all score
 *     112-130, far worse, because /Os reshapes the whole function.
 * (3) The hatch itself: a NINTH distinct msvc6 code generator exists
 *     that shapes 90/91's eight-image sweep never included --
 *     `rebrew/msvc:6.0-win9x-win32`, C2.DLL md5 3c21de2c, matching none
 *     of the other eight, CL 12.00.8168, unregistered as a rebrew
 *     toolchain.  It is BYTE-IDENTICAL to sp6 here.  And the live-join
 *     form was then built under all seven distinct generators: every one
 *     puts the join at 0x3f (reference-exact) but arm6 at 0x55 with
 *     unlink spliced into the freed fallthrough slot.  The fusion is
 *     invariant across every MSVC6 generator available and every flag.
 *
 * The reference needs the join alive AND unfused AND arm6 in the
 * fallthrough slot; the fusion makes those mutually exclusive.
 *
 * WHY, PROVEN round 192 -- this is now a mechanism, not an exhaustion
 * argument, and it is the strongest statement available: **the target's
 * join test is provably-true dead code.**  Both predecessors enter with
 * ebx != 0.  arm5 falls through from `mov ebx,esi` where `pkt != 0` is
 * the while guard; arm6 is reached from the head precisely BECAUSE
 * `test ebx,ebx` was nonzero, and its backward `jne` at 0x4b fires
 * before both the call and the `xor ebx,ebx` at 0x6a.  So `je unlink`
 * can never be taken on either path.  msvc6 constant-folds exactly this
 * and deletes the block: **C cannot request a test whose operand the
 * compiler can prove nonzero.**  The reference's bytes carry a redundant
 * test its own optimiser would remove -- this is not a spelling we are
 * failing to find.
 * Corroborated from a second generator: sp5-pp mismatches the IDENTICAL
 * 15 offsets (0x37 and 0x3f-0x4c), so the join's absence is a dataflow
 * consequence and not an sp6 scheduling artefact.  The byte accounting
 * is neutral (14 vs 14), so size was never the obstacle either.
 * Only new information could reopen this: evidence the original was
 * built with optimisation disabled over this region, or inline asm.
 * CLOSED -- retire from the probe rotation rather than re-deriving it.
 * STATUS: PROVEN retained; not a byte match. */

// FUNCTION: SERVER 0x1000aac0

#include <string.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

#include "../server_internal.h"

extern handler_func g_dispatch_table[]; /* 0x1002c3f8 */
int __cdecl ahm_ProcessEntityChain(char* cmd_payload);
int __cdecl cm_QueuePlayerCommand(unsigned int* player, unsigned char* data);
extern void __cdecl LogMessageInternal(char* file, unsigned int line, char* msg, int level);

int __cdecl cm_ProcessCommandQueue(void* a)
{
	char* tab;
	char* pkt;
	char* held;
	char* next;
	char* slot;
	char** nextp;
	int i;
	int ok;
	unsigned char type;
	unsigned char t2;

	(void) a;
	for (tab = (char*) 0x10442cf0; (int) tab < 0x11764010; tab += 0x264264) {
		pkt = *(char**) tab;
		held = 0;
		while (pkt != 0) {
			next = *(char**) (pkt + 0x95);
			nextp = (char**) (pkt + 0x95);
			type = *(volatile unsigned char*) pkt;
			ok = 1;
			if (held == 0) {
				if (type != 5) {
					goto unlink;
				}
				held = pkt;
				goto advance;
			} else {
				if (type != 6) {
					goto recheck;
				}
				if (ahm_ProcessEntityChain(held) == 0) {
					ok = 0;
				}
				nextp = (char**) (held + 0x95);
				next = *nextp;
				pkt = held;
				held = 0;
				if (!ok) {
					goto advance;
				}
			}
		recheck:
			if (held != 0) {
				goto advance;
			}
		unlink:
			/* Unlink pkt from the incoming queue head and push it onto the freelist. */
			if (pkt == *(char**) tab) {
				*(char**) tab = next;
			} else {
				*(char**) (*(char**) (pkt + 0x91) + 0x95) = *nextp;
				*(char**) (*nextp + 0x91) = *(char**) (pkt + 0x91);
			}
			*(char**) (pkt + 0x91) = 0;
			*nextp = *(char**) (tab + 8);
			*(char**) (tab + 8) = pkt;

			t2 = *(unsigned char*) pkt;
			if (t2 < 0x6a) {
				if (t2 == 0x20 && *(unsigned char*) (pkt + 0x10) == 0xe) {
					slot = (char*) &((unsigned int*) g_connections)[(unsigned int) *(unsigned char*) (pkt + 3) * 0x99099];
					if ((*(unsigned char*) slot & 0x40) != 0) {
						LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x72e, "Multisync!!!", 1);
					}
				}
				if (g_dispatch_table[*(unsigned char*) pkt](pkt, 0) == 0) {
				if (*(unsigned char*) pkt == 0x20 && *(unsigned char*) (pkt + 0x10) == 0xe) {
					slot = (char*) g_connections + (unsigned int) *(unsigned char*) (pkt + 3) * 0x264264;
					memcpy((char*) 0x10442c54 + (unsigned int) *(unsigned char*) (pkt + 3) * 0x264264, pkt, 0x99);
					goto advance;
				}
				t2 = ((unsigned char*) g_connections)[(unsigned int) *(unsigned char*) (pkt + 3) * 0x264264];
				slot = (char*) g_connections + (unsigned int) *(unsigned char*) (pkt + 3) * 0x264264;
				if ((t2 & 1) != 0) {
					if (cm_QueuePlayerCommand((unsigned int*) slot, (unsigned char*) pkt) == -1) {
						return -1;
					}
				}
				*(int*) (pkt + 4) = -1;
				i = 0;
				slot = (char*) g_connections;
				do {
					if (i != (int) *(unsigned char*) (pkt + 3) &&
					    (*(unsigned char*) slot & 1) != 0) {
						if (cm_QueuePlayerCommand((unsigned int*) slot, (unsigned char*) pkt) == -1) {
							return -1;
						}
					}
					slot += 0x264264;
					i++;
				} while ((int) slot < 0x114ffe20);
				goto advance;
				}
			queued:
				if ((*(unsigned char*) &((unsigned int*) g_connections)[(unsigned int) *(unsigned char*) (pkt + 3) * 0x99099] & 1) != 0) {
					*(unsigned char*) pkt = 2;
					slot = (char*) &((unsigned int*) g_connections)[(unsigned int) *(unsigned char*) (pkt + 3) * 0x99099];
					if (cm_QueuePlayerCommand((unsigned int*) slot, (unsigned char*) pkt) == -1) {
						return -1;
					}
				}
			} else {
				LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x756, "Command-Type out of Range!\n", 1);
			}
		advance:
			pkt = next;
		}
	}
	return 0;
}

// GLOBAL: SERVER 0x1002c3f8
extern handler_func g_dispatch_table[]; /* 0x1002c3f8 */
