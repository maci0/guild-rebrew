# MSVC6 register allocation

Register and stack assignments depend on live ranges, uses, calls and the full
translation unit. A source experiment measures that context, not a general rule.
Expression-level differences belong in [C shapes](msvc6-c-shapes.md).

## Read the native value flow

For ordinary x86 C conventions, EAX, ECX and EDX are caller-saved; EBX, ESI, EDI
and EBP are callee-saved. Check unusual helpers rather than assuming their ABI.

Trace a value from its definition through every reaching path. Record partial
register writes, calls, spills, reloads and the exact consumer width. A register
name alone does not establish which source variable it holds.

## What affects allocation

- A constant used across several operations may become a register candidate.
  A single-use constant may remain immediate.
- Keeping an index live can preserve a native induction form. Returning the
  equivalent pointer may make the index dead and change the whole loop.
- Loop exits and shared return blocks can change save/restore placement.
- Address-taking, aliasing, declarations and definition order can change spills.
- Equal access counts do not establish a unique stack-slot assignment.

Declaration reordering, renaming, `register` and `volatile` are not reliable
controls for a desired register. `volatile` also changes observable accesses;
use it only with evidence for those accesses, not to improve a score.

## Stack slots

Track entry ESP and every push, pop, stack adjustment and callee cleanup.
Resolve each displacement at that instruction. Compilers can reuse dead parameter
or saved-register slots; reserved frame bytes do not prove a local array or struct.
A diagnostic sentinel can identify a slot, but must not become production state.

Compare complete objects after a type/context change. Keep rejected variants
bounded and consult [negative results](codegen-walls.md) before repeating them.


## Archived findings

<details>
<summary>Historical sections and address lookup</summary>

The [November 5 archive](archive/2026-11-05-documentation.tar.xz) preserves the full
`docs/msvc6-allocator.md` notebook, including corrections and receipt paths. Entries below locate
historical claims, not current instructions or verdicts. Hex values include
code/data addresses and constants.

```sh
tar -xOf docs/archive/2026-11-05-documentation.tar.xz docs/msvc6-allocator.md | less
```

| Historical section | Referenced hex values |
| --- | --- |
| <a id="msvc-60-register-allocation"></a>MSVC 6.0 register allocation | - |
| <a id="index"></a>Index | - |
| <a id="methodology"></a>Methodology | - |
| <a id="register-set--baseline-from-rebrew-docs"></a>Register set & baseline (from rebrew docs) | - |
| <a id="finding-1-the-zero-register-is-allocated-once-and-reused"></a>Finding 1: the "zero register" is allocated once and reused | `0x10016460` |
| <a id="finding-2-the-live-range-across-loop-flip-the-big-one"></a>Finding 2: the LIVE-RANGE-ACROSS-LOOP flip (the big one) | - |
| <a id="what-does-not-trigger-or-fix-the-flip-all-tested-byte-compared"></a>What does NOT trigger or fix the flip (all tested, byte-compared) | - |
| <a id="finding-3-flag-variables-first-tested-flag-gets-dl-second-gets-bl"></a>Finding 3: flag variables: first-tested flag gets `dl`, second gets `bl` | - |
| <a id="finding-4--1-stores-immediate-vs-register-is-a-consequence"></a>Finding 4: `-1` stores: immediate vs register is a *consequence* | - |
| <a id="finding-5-esi-pushpop-placement-tracks-its-live-range"></a>Finding 5: `esi` push/pop placement tracks its live range | - |
| <a id="finding-6-shared-storecall-tail-needs-both-values-in-the-same-register"></a>Finding 6: shared store+call tail needs both values in the same register | `0x10016561`, `0x10016566` |
| <a id="practical-recipe-for-writing-matching-c"></a>Practical recipe for writing matching C | `0x10016460` |
| <a id="finding-7-address-taken-parameter-kills-the-callee-save-base"></a>Finding 7: address-taken parameter kills the callee-save base | `0x1000cf30`, `0x1000d730` |
| <a id="finding-8b-multi-branch-dispatch-register-cascade"></a>Finding 8b: multi-branch dispatch register cascade | `0x1000ec00` |
| <a id="finding-8d-value-propagation-splits-shared-blocks"></a>Finding 8d: value propagation splits shared blocks | `0x10017400` |
| <a id="finding-8c-the-convertible-head-pattern-summary"></a>Finding 8c: the convertible head pattern (summary) | `0x10013230` |
| <a id="finding-8-multi-call-value-base-converts-cleanly"></a>Finding 8: multi-call value base converts cleanly | `0x10013230` |
| <a id="finding-8e-a-convertible-recipe-verified"></a>Finding 8e: a CONVERTIBLE recipe (verified) | `0x203bcb6`, `0x10006cc0`, `0x1000b1c0`, `0x1000b290`, `0x1000baf0`, `0x1002a0a0`, `0x101de5a4` |
| <a id="open-questions"></a>Open questions | - |
| <a id="gm_calculateproductionvalue-0x10019720-recursion--fpu"></a>gm_CalculateProductionValue (0x10019720): recursion + FPU | `0x101de450` |
| <a id="gm_eval_slotvoll-0x10019d30-converted-patterns-that-mattered"></a>gm_eval_SlotVoll (0x10019d30): CONVERTED, patterns that mattered | - |
| <a id="gm_checkinventorycapacity-0x10019ed0-blocked-grapeephole"></a>gm_CheckInventoryCapacity (0x10019ed0): blocked (GRA/peephole) | - |
| <a id="sim_priorityupdate-0x10015400-converted-frame-size-oracle"></a>sim_PriorityUpdate (0x10015400): CONVERTED (frame-size oracle) | - |
| <a id="sim_startentityquerybytype-0x10015460-blocked-gra"></a>sim_StartEntityQueryByType (0x10015460): blocked (GRA) | - |
| <a id="sim_advancegameclock-0x100155c0-blocked-arg4-live-range-split"></a>sim_AdvanceGameClock (0x100155c0): blocked (arg4 live-range split) | `0x10035880`, `0x88888889`, `0xaaaaaaab` |
| <a id="receivepacketheader-0x1000a340-solved-reloc-delta-0"></a>ReceivePacketHeader (0x1000a340): SOLVED (RELOC, delta 0) | - |
| <a id="gm_randomstatmodifier-0x10018450-blocked-byte-vs-dword-load"></a>gm_RandomStatModifier (0x10018450): blocked (byte vs dword load) | - |
| <a id="loop-form-finding-gm_findslotbyid-0x10016240-ahm_queryentitybuildingtype-0x1000c6a0"></a>Loop-form finding (gm_FindSlotById 0x10016240, ahm_QueryEntityBuildingType 0x1000c6a0) | - |
| <a id="ahm_initrandomentity-0x1000c600-reloc-109109"></a>ahm_InitRandomEntity (0x1000c600): RELOC 109/109 | - |
| <a id="gm_cleanupobjectentities-0x10015cf0-blocked-addressing-mode-roles"></a>gm_CleanupObjectEntities (0x10015cf0): blocked (addressing-mode roles) | - |
| <a id="cm_exchangefloat-0x1000eb70-reloc-135135"></a>cm_ExChangeFloat (0x1000eb70): RELOC 135/135 | - |
| <a id="analyzeinstruction-0x10003260-solved-exact"></a>AnalyzeInstruction (0x10003260): SOLVED (EXACT) | - |
| <a id="cm_chkmovecredits-0x1000cb20-converted-call-site-byte-view"></a>cm_ChkMoveCredits (0x1000cb20): CONVERTED (call-site byte view) | - |
| <a id="gm_resolveentitybyid-0x10015e90-blocked-existing-loop-counter-register"></a>gm_ResolveEntityById (0x10015e90): blocked (existing-loop counter register) | - |
| <a id="cm_exmodifystat-0x100100a0-blocked-fpu-clamp-compare-forms"></a>cm_ExModifyStat (0x100100a0): blocked (FPU clamp compare forms) | - |
| <a id="plt_checkzoneavailability-0x10014ff0-done-induction-base-folding"></a>plt_CheckZoneAvailability (0x10014ff0): DONE (induction-base folding) | `0x10014f30`, `0x100150a0` |
| <a id="plt_setplantmap-0x100150a0-done-constant-coalescing--byte-reg-pairing"></a>plt_SetPlantMap (0x100150a0): DONE (constant coalescing + byte-reg pairing) | `0xffffffff` |
| <a id="processsenddata-0x1000a860-solved-reloc-delta-0"></a>ProcessSendData (0x1000a860): SOLVED (RELOC, delta 0) | `0x264143`, `0x2641f4`, `0x264264`, `0x101deb00`, `0x114ffe20` |
| <a id="m_poolalloc-0x10006d20--srv_initbuildingtypetable-0x1000b040-blocked-alignment-prefixed-memset"></a>m_PoolAlloc (0x10006d20) / srv_InitBuildingTypeTable (0x1000b040): blocked (alignment-prefixed memset) | `0x10006728`, `0x10006730`, `0x10006929`, `0x10006e0d`, `0x10008f0c`, `0x1000b057`, `0x10017611` |
| <a id="the-prelude-is-hand-written-asm-not-a-compiler-expansion-2026-09-04"></a>The prelude is hand-written asm, not a compiler expansion (2026-09-04) | - |
| <a id="reviewed-goldtl-inline-helpers-2026-10-09"></a>Reviewed GOLDTL inline helpers (2026-10-09) | `0x0043f6b0`, `0x0043f76b`, `0x00449ba0`, `0x00449c6f`, `0x00469140`, `0x004691f8` |
| <a id="reviewed-goldtl-building-table-initializer-2026-10-10"></a>Reviewed GOLDTL building-table initializer (2026-10-10) | `0x004e7810`, `0x004e7827`, `0x10006580`, `0x10006730`, `0x10006929`, `0x10006c00`, `0x10006d20`, `0x10006df7`, `0x10006e0d`, `0x10008f0c`, `0x1000b040`, `0x1000b046`, `0x1000b057`, `0x10017611`, `0x101de994` |
| <a id="m_init-0x100068e0-re-verified-2026-08-27-same-conclusion"></a>m_init (0x100068e0): re-verified 2026-08-27, same conclusion | `0x1001a7f7`, `0x117640c4` |
| <a id="lb_explayerlist-0x100145e0-done-struct-for-layout--auto-zero--tail-layout"></a>lb_ExPlayerlist (0x100145e0): DONE (struct-for-layout + auto-zero + tail layout) | `0xffffffff` |
| <a id="amt_swapofficeholders-0x1000b880-solved-reloc-delta-0"></a>amt_SwapOfficeHolders (0x1000b880): SOLVED (RELOC, delta 0) | - |
| <a id="gm_killspieler-0x10017fb0-fenced--proven-267278-scheduling-swap"></a>gm_KillSpieler (0x10017fb0): FENCED + PROVEN (267/278, scheduling swap) | `0x10035434`, `0x10035880`, `0x100358a4`, `0x100358fc` |
| <a id="ls_loadexistingentities-0x100127d0-fenced--proven-271282"></a>ls_LoadExistingEntities (0x100127d0): FENCED + PROVEN (271/282) | `0x10035450`, `0x100a8c34` |
| <a id="srv_init-0x10009d30-solved-reloc-delta-0"></a>srv_Init (0x10009d30): SOLVED (RELOC, delta 0) | `0x10024068`, `0x1002406c`, `0x10117688`, `0x10117690`, `0x101176ec` |
| <a id="cm_exchangebits-0x1000eaa0-solved-reloc-delta-0"></a>cm_ExChangeBits (0x1000eaa0): SOLVED (RELOC, delta 0) | - |
| <a id="ls_id2ptr-0x10014070-blocked-lazy-ebp-save-first-draft"></a>ls_ID2Ptr (0x10014070): blocked (lazy ebp save, first draft) | - |
| <a id="cm_exallocthemapredigt-0x1000f2f0-solved-reloc-172172"></a>cm_ExAllocThemaPredigt (0x1000f2f0): SOLVED (RELOC 172/172) | `0x264264`, `0x1000f379` |
| <a id="cm_exclearlagerslot-0x1000e690-solved-reloc-delta-0"></a>cm_ExClearLagerslot (0x1000e690): SOLVED (RELOC, delta 0) | - |
| <a id="m_pool_free-0x10006e30-solved-reloc-delta-0"></a>m_pool_free (0x10006e30): SOLVED (RELOC, delta 0) | `0x10028888`, `0x10028b94` |
| <a id="m_shutdownallocator-0x10006c00-done-reloc-283283"></a>m_ShutdownAllocator (0x10006c00): DONE (RELOC 283/283) | - |
| <a id="gm_randomstatmodifier-0x10018450-blocked-char-value-representation"></a>gm_RandomStatModifier (0x10018450): blocked (char value representation) | - |
| <a id="closevfsstream-0x10008d10-solved-reloc-delta-0"></a>CloseVfsStream (0x10008d10): SOLVED (RELOC, delta 0) | - |
| <a id="ahm_initrandomentity-0x1000c600-done-reloc-109109"></a>ahm_InitRandomEntity (0x1000c600): DONE (RELOC 109/109) | - |
| <a id="sim_startentityquerybytype-0x10015460-blocked-argtable-register-roles"></a>sim_StartEntityQueryByType (0x10015460): blocked (arg/table register roles) | - |
| <a id="amt_updateentitylinks-0x1000ba30-solved-reloc-delta-0"></a>amt_UpdateEntityLinks (0x1000ba30): SOLVED (RELOC, delta 0) | - |
| <a id="gm_findentitybyowner-0x10019c60-blocked-loop-register-roles"></a>gm_FindEntityByOwner (0x10019c60): blocked (loop register roles) | - |
| <a id="cm_exchangedesire-0x1000e9c0-solved-reloc-delta-0"></a>cm_ExChangeDesire (0x1000e9c0): SOLVED (RELOC, delta 0) | - |
| <a id="cm_exsetattribute-0x1000e8d0-solved-reloc-delta-0"></a>cm_ExSetAttribute (0x1000e8d0): SOLVED (RELOC, delta 0) | - |
| <a id="cm_exremovelinkedobject-0x1000f0d0-solved-reloc-delta-0"></a>cm_ExRemoveLinkedObject (0x1000f0d0): SOLVED (RELOC, delta 0) | - |
| <a id="cm_exchangeattribute-0x1000e7d0-solved-reloc-delta-0"></a>cm_ExChangeAttribute (0x1000e7d0): SOLVED (RELOC, delta 0) | - |
| <a id="session-findings-five-more-conversions--two-register-role-blockers"></a>Session findings: five more conversions + two register-role blockers | - |
| <a id="converted-to-byte-identical-c-all-reloc-verified-via-rebrew-verify-245245-build-hash-c7ac331f"></a>Converted to byte-identical C (all RELOC, verified via `rebrew verify` 245/245, build hash c7ac331f) | `0x1000cbd0`, `0x1000cde0`, `0x1000d110`, `0x1000fd50`, `0x100151e0` |
| <a id="blocked-documented-with-preserved-c-see-file-comments"></a>Blocked (documented with preserved C, see file comments) | `0x1000c710`, `0x1000c864`, `0x1000d570`, `0x10013230`, `0x100146c0`, `0x10015950`, `0x100170e0`, `0x10017176`, `0x100358a0` |
| <a id="deep-dive-the-unsigned-char-zero-extension-form-and-idiom-resolved"></a>Deep-dive: the unsigned-char zero-extension form (and-idiom): resolved | `0x1000c710` |
| <a id="the-three-forms-and-when-each-appears"></a>The three forms and when each appears | - |
| <a id="the-liveness-lever-what-keeps-the-byte-live"></a>The liveness lever (what keeps the byte live) | - |
| <a id="related--x--c-negation-idiom"></a>Related: `-(x != c)` negation idiom | - |
| <a id="refines-the-codegen_patternsmd-not-controllable-row"></a>Refines the CODEGEN_PATTERNS.md "NOT controllable" row | - |
| <a id="deep-dive-the-rebrew-flag-sweep-tiers-never-fully-swept"></a>Deep-dive: the rebrew flag-sweep tiers (never fully swept) | - |
| <a id="ahm_getcommandpayloadsize-follow-up-494--742-three-more-levers-found"></a>ahm_GetCommandPayloadSize follow-up: 494 → 742 (three more levers found) | - |
| <a id="register-role-residue-confirmed-for-ahm_getcommandpayloadsize-742752"></a>Register-role residue confirmed for ahm_GetCommandPayloadSize (742/752) | - |
| <a id="finding-12-named-local-vs-anonymous-csed-load-the-eaxecx-lever"></a>Finding 12: named local vs anonymous CSE'd load (the eax↔ecx lever) | - |
| <a id="allocator-internals-from-reversing-c2dll-p2-backend"></a>Allocator internals (from reversing c2.dll, p2 backend) | `0x4af800`, `0x10016290`, `0x10018850`, `0x10018c28`, `0x10018c38`, `0x10700000`, `0x10703558`, `0x10703ed5`, `0x10705166`, `0x10705193`, `0x107053c9`, `0x10705507`, `0x1070de4c`, `0x10713312`, `0x1071431d`, `0x107169f2`, `0x1071b8c0`, `0x1071b94b`, `0x1071da32`, `0x1071e238`, `0x1071e25e`, `0x1071f87a`, `0x1071f895`, `0x1071f8de`, `0x1071f94e`, `0x10720802`, `0x1072090e`, `0x10721daa`, `0x10724a49`, `0x10726e85`, `0x10727781`, `0x10727977`, `0x107279c2`, `0x10727a51`, `0x10727ca9`, `0x10727d01`, `0x107351b7`, `0x107603b2`, `0x10799204`, `0x10799214`, `0x10799218`, `0x1079d6ec`, `0x1079d710`, `0x1079d74c`, `0x1079d750`, `0x1079d88c`, `0x1079f220`, `0x107a04dc`, `0x107ac0b4`, `0x107ac2dc`, `0x107ac730`, `0x107adff4`, `0x107ae038`, `0x107ae040`, `0x107b15fc` |
| <a id="finding-13-lb_explayerlist-0x100145e0-struct-fields-beat-array-index-counters"></a>Finding 13: lb_ExPlayerlist (0x100145e0): struct-fields beat array-index counters | - |
| <a id="finding-14-ah-relative-masks-read-the-byte-before-the-mask"></a>Finding 14: AH-relative masks (read the byte before the mask) | `0x10014a50` |
| <a id="finding-15-comdat-placement-functions-in-a-file-must-be-va-contiguous"></a>Finding 15: COMDAT placement: functions in a file must be VA-contiguous | `0x10002770`, `0x10014bf0`, `0x10014ee0`, `0x10014f80`, `0x10018850` |
| <a id="0x10014ee0-word-table-search-naked-placeholder-kept"></a>0x10014ee0: word-table search (naked placeholder kept) | `0x1002d878`, `0x1002d8be` |
| <a id="finding-16-three-new-blocker-patterns-cm_-family"></a>Finding 16: three new blocker patterns (cm_* family) | `0x1000cb20`, `0x1000e690`, `0x1000eb70`, `0x100100a0`, `0x100104a0`, `0x10019c60` |
| <a id="finding-17-signed--1-byte-compares-materialize-0xff-via-or-reg0xff"></a>Finding 17: signed `-1` byte compares materialize 0xff via `or reg,0xff` | `0x10003260` |
| <a id="finding-18-memory-operand-byte-params-local-vs-global-load-form"></a>Finding 18: memory-operand byte params: local vs global load form | `0x100034c0` |
| <a id="finding-19-m_init-0x100068e0-memset-alignment-pass--param-slot-spill"></a>Finding 19: m_init (0x100068e0): memset alignment-pass + param-slot spill | `0x10008e40` |
| <a id="client-tracked-free-crt-binding-2026-10-11"></a>Client tracked-free CRT binding (2026-10-11) | `0x0041ddd0`, `0x00422620`, `0x005dec24`, `0x0064dfda` |
| <a id="shared-tracked-free-implementation-2026-10-11"></a>Shared tracked-free implementation (2026-10-11) | `0x0041ddd0`, `0x00422620`, `0x10006820` |
| <a id="finding-20-m_freetracked-0x10006820-transient-register-alternation-185188"></a>Finding 20: m_FreeTracked (0x10006820): transient-register alternation (185/188) | - |
| <a id="finding-21-the--flag-chain-splits-only-in-sibling-specific-register-contexts"></a>Finding 21: the `?:` flag chain splits only in sibling-specific register contexts | `0x1000b990`, `0x1000ba30` |
| <a id="finding-22-amt_swapofficeholders-0x1000b880-register-name-residue-264263"></a>Finding 22: amt_SwapOfficeHolders (0x1000b880): register-name residue (264/263) | - |
| <a id="finding-23-amt_validateofficecandidate-0x1000b1c0-fail-block-sinking--loop-rotation"></a>Finding 23: amt_ValidateOfficeCandidate (0x1000b1c0): fail-block sinking + loop rotation | `0x101de5a0`, `0x101de5a4`, `0x101de870` |
| <a id="finding-24-ahm_clampfloatvalue-0x1000c3c0-three-fpu-return-blocks"></a>Finding 24: ahm_ClampFloatValue (0x1000c3c0): three FPU return blocks | - |
| <a id="finding-25-m_pool_free-0x10006e30-block-param-register--fatal-placement"></a>Finding 25: m_pool_free (0x10006e30): block param register + fatal placement | `0x10028888`, `0x10028b94` |
| <a id="finding-26-sim_priorityupdate-0x10015400-frame-vs-arg-slot-reuse"></a>Finding 26: sim_PriorityUpdate (0x10015400): frame vs arg-slot reuse | - |
| <a id="finding-27-sim_startentityquerybytype-0x10015460-callee-saved-roles"></a>Finding 27: sim_StartEntityQueryByType (0x10015460): callee-saved roles | - |
| <a id="finding-28-sim_advancegameclock-0x100155c0-arg4-preserve-vs-reload"></a>Finding 28: sim_AdvanceGameClock (0x100155c0): arg4 preserve vs reload | `0x88888889`, `0xaaaaaaab` |
| <a id="finding-29-gm_cleanupobjectentities-0x10015cf0-sib-baseindex-roles"></a>Finding 29: gm_CleanupObjectEntities (0x10015cf0): SIB base/index roles | - |
| <a id="finding-30-gm_checkentitytype-0x10017ab0-lea-vs-folded-table-load"></a>Finding 30: gm_CheckEntityType (0x10017ab0): lea vs folded table load | - |
| <a id="finding-31-ahm_processentitychain-0x1000ca00-do-while-inversion"></a>Finding 31: ahm_ProcessEntityChain (0x1000ca00): do-while inversion | `0x1002c5a0` |
| <a id="finding-32-cm_getbuildingstatcount-0x100104a0-branchless-if-conversion--lea-fold"></a>Finding 32: cm_GetBuildingStatCount (0x100104a0): branchless if-conversion + lea fold | - |
| <a id="finding-33-cm_chkmovecredits-0x1000cb20-arg3-lea-hoist-3-bytes"></a>Finding 33: cm_ChkMoveCredits (0x1000cb20): arg3-lea hoist (3 bytes) | - |
| <a id="finding-34-cm_exchangefloat-0x1000eb70-offset-register-role"></a>Finding 34: cm_ExChangeFloat (0x1000eb70): offset-register role | - |
| <a id="finding-35-cm_exmodifystat-0x100100a0-fpu-re-compare-fold"></a>Finding 35: cm_ExModifyStat (0x100100a0): FPU re-compare fold | - |
| <a id="finding-36-cm_exallocthemapredigt-0x1000f2f0-add-edi-fold--dead-store-elimination"></a>Finding 36: cm_ExAllocThemaPredigt (0x1000f2f0): add-edi fold + dead-store elimination | `0x10442d08` |
| <a id="finding-37-cm_exmoveobjekt-0x1000e530-node-spill-fixed-point--store1-address-form"></a>Finding 37: cm_ExMoveObjekt (0x1000e530): node-spill fixed point + store1 address form | - |
| <a id="finding-38-cm_exchangeattribute-0x1000e7d0-loop-register-pairing-swap"></a>Finding 38: cm_ExChangeAttribute (0x1000e7d0): loop register-pairing swap | - |
| <a id="finding-39-cm_exchangebits-0x1000eaa0-pre-resolve-field-store-materialization"></a>Finding 39: cm_ExChangeBits (0x1000eaa0): pre-resolve field store materialization | - |
| <a id="finding-40-cm_exchangedesire-0x1000e9c0-family-store-materialization--fpu-clamp"></a>Finding 40: cm_ExChangeDesire (0x1000e9c0): family store materialization + FPU clamp | - |
| <a id="finding-41-cm_exremovelinkedobject-0x1000f0d0-prologue-scheduling"></a>Finding 41: cm_ExRemoveLinkedObject (0x1000f0d0): prologue scheduling | - |
| <a id="finding-42-cm_exclearlagerslot-0x1000e690-family-store-materialization-short-base"></a>Finding 42: cm_ExClearLagerslot (0x1000e690): family store materialization (short* base) | - |
| <a id="finding-43-cm_exsetattribute-0x1000e8d0-loop-head-offset-read-scheduling"></a>Finding 43: cm_ExSetAttribute (0x1000e8d0): loop-head offset-read scheduling | - |
| <a id="finding-44-gv_updateproductionprogress-0x10011790-arg-order--sum-register-fixed-points"></a>Finding 44: gv_UpdateProductionProgress (0x10011790): arg-order + sum-register fixed points | - |
| <a id="finding-45-gv_activategraveyardsection-0x10011660-error-block-placement"></a>Finding 45: gv_ActivateGraveyardSection (0x10011660): error-block placement | - |
| <a id="finding-46-gv_getslotentry-0x100105b0-shared-return-0-epilogue"></a>Finding 46: gv_GetSlotEntry (0x100105b0): shared return-0 epilogue | - |
| <a id="finding-47-findslotentryfiltered-0x10010710-walk-in-the-parameter-not-a-local"></a>Finding 47: FindSlotEntryFiltered (0x10010710): walk in the parameter, not a local | - |
| <a id="finding-48-gv_spawnentities-0x10010850-prologue-region-split-cold-path-saves"></a>Finding 48: gv_SpawnEntities (0x10010850): prologue region-split (cold-path saves) | `0x10002770`, `0x10010700` |
| <a id="finding-49-ls_initnewdynastyentity-0x100122e0-768x768-fill-induction-variable-elimination"></a>Finding 49: ls_InitNewDynastyEntity (0x100122e0): 768x768 fill induction-variable elimination | `0x100a9820`, `0x10139820` |
| <a id="finding-50-gv_allocgraveyardfield-0x100109d0-allocfield-init-loop-allocation"></a>Finding 50: gv_AllocGraveyardField (0x100109d0): alloc/field-init loop allocation | `0x1002d474`, `0xffffffff` |
| <a id="finding-51-m_alloctracked-0x10006580-frame--zero-register-fixed-point"></a>Finding 51: m_AllocTracked (0x10006580): frame + zero-register fixed point | `0x10028888` |
| <a id="finding-52-stack-slots-are-coloured-over-live-ranges-so-declaration-order-is-usually-inert"></a>Finding 52: stack slots are coloured over live ranges, so declaration order is usually inert | `0x10002770`, `0x1000d930`, `0x100128f0`, `0x10015f70` |
| <a id="finding-53-callee-saved-assignment-can-be-an-allocator-tie-break-that-no-c-names"></a>Finding 53: callee-saved assignment can be an allocator tie-break that no C names | `0x10015f70` |
| <a id="finding-54-strength-reduction-is-decided-by-the-values-uses-not-by-how-the-address-is-spelled"></a>Finding 54: strength reduction is decided by the value's uses, not by how the address is spelled | `0x1000bdf0`, `0x10018850`, `0x10019ed0` |
| <a id="finding-55-the-frame-can-be-right-while-the-slot-map-is-not"></a>Finding 55: the frame can be right while the slot map is not | `0x10018850` |
| <a id="finding-56-a-short-objects-out-of-line-data-is-still-misplaced-even-when-the-pad-step-fixes-the-following-symbols"></a>Finding 56: a short object's out-of-line data is still misplaced even when the pad step fixes the following symbols | `0x10002e99`, `0x10002e9e`, `0x10009020` |
| <a id="finding-57-reporting-note-a-per-function-residue-number-is-only-comparable-within-one-composition"></a>Finding 57: reporting note: a per-function residue number is only comparable within one composition | - |
| <a id="finding-58-inter-object-size-the-constraint-is-have--paddedwant-and-every-real-body-below-the-reference-span-is-free"></a>Finding 58: inter-object size: the constraint is `have <= padded(want)`, and every real body *below* the reference span is free | `0x1000ec00` |
| <a id="correction-to-finding-15s-amendment"></a>Correction to Finding 15's amendment | `0x10018850` |
| <a id="finding-59-relocation-accounting-matched-under-counts-because-msvc6-relocates-memory-operands-but-not-absolute-immediates"></a>Finding 59: relocation accounting: `matched` under-counts, because msvc6 relocates memory operands but not absolute immediates | `0x100093a0`, `0x101de9a0`, `0x101deb00` |
| <a id="finding-60-reading-out-the-frame-slot-map-with-sentinel-initials-an-instrument"></a>Finding 60: reading out the frame slot map with sentinel initials (an instrument) | `0x1000d930` |
| <a id="finding-61-volatile-on-a-local-is-a-per-variable-fixed-point-not-a-general-register-eviction-knob"></a>Finding 61: `volatile` on a local is a per-variable fixed point, not a general register-eviction knob | `0x10008a90`, `0x10009020`, `0x1000a570`, `0x1000aac0`, `0x1000bdf0`, `0x1000d930`, `0x1000e140` |
| <a id="finding-62-the-ebxedi-rotation-is-unsteerable-by-construction-round-307"></a>Finding 62: the ebx/edi rotation is unsteerable by construction (round 307) | `0x10015f70` |
| <a id="finding-63-slot-homes-are-canonicalized-live-set-cardinality-does-not-move-them-round-361"></a>Finding 63: slot homes are canonicalized; live-set cardinality does not move them (round 361) | `0x1000d930`, `0x1000d986`, `0x1000d98e`, `0x1000d993`, `0x1000d999`, `0x10015e90` |
| <a id="finding-64-the-callee-saved-home-order-is-a-fixed-invariant-of-value-count-not-of-anything-in-the-source-round-846-isolated"></a>Finding 64: the callee-saved home order is a fixed invariant of *value count*, not of anything in the source (round 846, isolated) | - |
| <a id="finding-65-the-accumulator-homes-are-decided-by-role-competition-for-esi-and-edi-not-by-cardinality-round-847-isolated"></a>Finding 65: the accumulator homes are decided by *role competition for `esi` and `edi`*, not by cardinality (round 847, isolated) | `0x10015f70` |
| <a id="finding-66-crashdumps-2-register-frame-difference-is-four-deferred-restores-not-a-prologue-shape-round-992"></a>Finding 66: `CrashDump`'s 2-register frame difference is FOUR deferred restores, not a prologue shape (round 992) | `0x1000282c`, `0x1000282d`, `0x10002dac`, `0x10002dad`, `0x10002dae`, `0x10002de5`, `0x10002de6`, `0x10002de7`, `0x10002e17`, `0x10002e18`, `0x10002e19`, `0x10002e49`, `0x10002e4a`, `0x10002e4b`, `0x10002e66`, `0x10002e68`, `0x10002e6d`, `0x10024010` |
| <a id="finding-67-crashdumps-deferred-save-is-a-register-role-assignment-and-the-headers-2-is-stale-round-993"></a>Finding 67: `CrashDump`'s deferred save is a REGISTER-ROLE assignment, and the header's −2 is stale (round 993) | `0x1000281d`, `0x1000281f`, `0x1000282c`, `0x1000282e`, `0x10002843`, `0x10002880`, `0x10024034` |
| <a id="finding-67-addendum-the-swapped-pair-is-ebpedi-and-three-probes-confirm-no-c-lever-round-994"></a>Finding 67 addendum: the swapped pair is `ebp`/`edi`, and three probes confirm no C lever (round 994) | `0x1000281d`, `0x1000281f`, `0x1000282e`, `0x10002843`, `0x10002880`, `0x10002f18`, `0x10024034` |
| <a id="finding-68-register-pressure-matches-on-all-19-carriers-the-residue-is-pure-register-choice-round-1004"></a>Finding 68: register PRESSURE matches on all 19 carriers; the residue is pure register CHOICE (round 1004) | `0x1000282c` |
| <a id="finding-69-gm_objectsavailbles-ebxedi-roles-three-new-spellings-none-lands-inert-in-the-header-is-not-always-exactly-0-round-1029"></a>Finding 69: `gm_ObjectsAvailble`'s `ebx`/`edi` roles: three new spellings, none lands; "inert" in the header is not always exactly 0 (round 1029) | `0x10015f70` |
| <a id="finding-70-18-of-19-carriers-have-the-references-exact-frame-only-crashdump-differs-round-1041"></a>Finding 70: 18 of 19 carriers have the reference's exact frame; only CrashDump differs (round 1041) | - |
| <a id="finding-71-crashdumps-register-roles-hinge-on-one-priority-comparison-stack-slots-follow-references-per-byte-round-1145-traced-in-c2"></a>Finding 71: CrashDump's register roles hinge on one priority comparison; stack slots follow references per byte (round 1145, traced in c2) | `0x10002c5c`, `0x107405b6` |
| <a id="finding-72-a-multi-use-constant-is-a-colouring-candidate-its-register-follows-range-overlap-round-1145"></a>Finding 72: a multi-use constant is a colouring candidate; its register follows range overlap (round 1145) | `0x1071f7b3` |
| <a id="finding-73-crashdumps-frame-fill-tie-0x10002c5c-against-the-cross-jump-picker-and-dag-rules-traced-in-c2"></a>Finding 73: CrashDump's frame-fill tie (0x10002c5c) against the cross-jump, picker and DAG rules (traced in c2) | `0x00200800`, `0x00800000`, `0x00800800`, `0x00a00800`, `0x00a40800`, `0x10002770`, `0x10002c5d`, `0x10002e9c`, `0x10002f1c`, `0x107028f1`, `0x107047f9`, `0x1070481b`, `0x10704a6d`, `0x10704b70`, `0x1070fbbc`, `0x10711276`, `0x10711aef`, `0x107146ce`, `0x107146d9`, `0x1071774d`, `0x1071b184`, `0x1071c086`, `0x1071d000`, `0x10720798`, `0x10720e12`, `0x10721ab2`, `0x10722246`, `0x1072351f`, `0x10723553`, `0x10723701`, `0x10723779`, `0x10723ad5`, `0x10723c43`, `0x10723d07`, `0x10723d1d`, `0x10723d22`, `0x10723ff1`, `0x10723ffa`, `0x10724395`, `0x10724569`, `0x10724590`, `0x10724597`, `0x10724599`, `0x1072459e`, `0x10724677`, `0x107258b7`, `0x1072631f`, `0x10726361`, `0x10726408`, `0x1072642b`, `0x10726c99`, `0x1072700d`, `0x10727042`, `0x10727781`, `0x107278ae`, `0x10727977`, `0x107280c0`, `0x107280d4`, `0x107290e7`, `0x1072ff79`, `0x107308df`, `0x1073090b`, `0x1073f57c`, `0x1073f5ba`, `0x1073f646`, `0x1073f648`, `0x107400e7`, `0x1074f598`, `0x107601e5`, `0x107603e8`, `0x10760434`, `0x10760541`, `0x10760574`, `0x107605d5`, `0x107606cc`, `0x107664db`, `0x10767b45`, `0x10786ef0`, `0x10799204`, `0x10799214`, `0x1079d6b0`, `0x1079f144`, `0x1079f16c`, `0x107ac054`, `0x107ac058`, `0x107ac098`, `0x107ac0a4`, `0x107ac0b4`, `0x107ac0b8`, `0x107ac0bc`, `0x107ac0d8`, `0x107ac118`, `0x107ac11c`, `0x107ac348`, `0x107ac34c`, `0x107ac378`, `0x107ae23c`, `0x80a00800`, `0xc000001d`, `0xc000008e`, `0xc00000fd`, `0xffffffff` |
| <a id="finding-74-processor-pack-c2-client-targets-routine-map-rules-and-open-cases"></a>Finding 74: Processor Pack c2 (client targets): routine map, rules and open cases | `0x402090`, `0x414830`, `0x414960`, `0x4af800`, `0x4c6090`, `0x4ce210`, `0x4fc3a0`, `0x50be50`, `0x58ee70`, `0x5c8400`, `0x5ce800`, `0x5d63e0`, `0x5db8e0`, `0x4000003`, `0x10700000`, `0x107044e9`, `0x10704511`, `0x10707a0b`, `0x10707b6e`, `0x10708374`, `0x10708393`, `0x107083bd`, `0x107083c0`, `0x10708a6e`, `0x10709a8e`, `0x10709a99`, `0x1070a2e4`, `0x1070c32b`, `0x1070c645`, `0x1070c662`, `0x1070c669`, `0x1070de4c`, `0x1070f234`, `0x1070f273`, `0x1070f289`, `0x1070f297`, `0x1070f6b1`, `0x1070f91d`, `0x1070f96f`, `0x10713312`, `0x10715094`, `0x107150b4`, `0x10715107`, `0x107159a9`, `0x10715bc0`, `0x1071d925`, `0x1071f7b3`, `0x10721c0f`, `0x107278ae`, `0x10731413`, `0x10731552`, `0x1073a2c4`, `0x1073cf92`, `0x107ac480`, `0x107ac5b4`, `0x107ad5fc`, `0x107ae398`, `0x107ae3cc`, `0x107b1418`, `0x107b15fc`, `0x107b1a00`, `0x107b1b8c`, `0x107b6888`, `0x107b690c`, `0x107b6978`, `0x107b6998`, `0x107b69a8`, `0x107c49d4` |
| <a id="unused-shared-function-declarations-can-alter-spill-slot-assignment"></a>Unused shared function declarations can alter spill-slot assignment | `0x482f20` |
| <a id="vfs-client-copy-provenance-2026-10-09"></a>VFS client copy provenance (2026-10-09) | `0x42e740`, `0x42e8f7`, `0x42e949`, `0x430910`, `0x4309e9` |
| <a id="addfile-operand-lifetime-controls-2026-10-12"></a>AddFile operand lifetime controls (2026-10-12) | `0x42e740`, `0x42e8f7`, `0x42e949` |
| <a id="narrow-factory-inputs-and-a-reused-count-slot-goal68-2026-10-16"></a>Narrow factory inputs and a reused count slot (Goal68, 2026-10-16) | - |

</details>
