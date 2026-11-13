# What a measurement proves

Choose the artifact that decides the claim. Keep the compile inputs, native extent,
operand bindings and receipt together. Current status belongs in managed metadata,
not a copied score table.

| Evidence | Establishes | Does not establish |
| --- | --- | --- |
| Complete native CFG/data-flow review | The reviewed semantics and contracts | Original C spelling or byte identity |
| Complete object EXACT | Object bytes agree | Linked placement or full image identity |
| Object RELOC | Agreement under the applied relocation policy | Correct unresolved operands or selected providers |
| Bounded semantic proof/fixtures | Agreement under modeled inputs, calls and bounds | Unmodeled runtime behavior or byte identity |
| Raw linked EXACT | Function bytes at the native VA agree | Every other function/data record agrees |
| Whole-file comparison | Complete file bytes agree | Original source ownership or C recovery |
| Layout/data metadata | Recorded extents, roles and ownership evidence | New allocations or verified bytes |

## Comparison scope

Use the complete native function, including all reachable blocks and embedded
switch data. Separate following alignment only with boundary evidence. A matching
prefix or first-return scan can omit later cases, callbacks or cleanup.

Compare exact operands and literal payloads. Relocation masking, structural scores
and matching symbol names can hide the wrong target. Resolve each module/VA
identity; a shared spelling does not make two definitions interchangeable.

Different file sizes count as differences. A same-offset score can fall when
artificial filler or copied data is removed; that is not a reason to restore them.
A residue count is not a count of independent semantic errors.

## Stack arithmetic

Resolve ESP-relative addresses with every pending push and stack adjustment at
that instruction. [Register allocation](msvc6-allocator.md#stack-slots) covers
stack-slot tracking.

## x87 conditions

FCOM/FCOMP encode the comparison bits in `AH & 0x45`: greater=`0x00`, less=`0x01`,
equal=`0x40`, unordered=`0x45`. PF reports even parity of the masked byte.

| Idiom | Branch taken for |
| --- | --- |
| TEST AH,0x05; JP | Greater, equal, unordered |
| TEST AH,0x44; JP | Greater, less, unordered |
| AND AX,0x4100; JNE | Less, equal, unordered |

Trace ST0/ST1 order, pops and branch destinations separately. Memory operand widths do not
prove intermediate rounding or a source type. Signed zero and unordered values
can distinguish expressions that agree on ordinary inputs.

## Failures and freshness

A timeout, stale context, failed build or missing receipt supplies no byte verdict.
Cached results require current source/header/compiler/binary and binding inputs.
`verify --no-cache` bypasses verdict caching, not necessarily object caching.
An unchanged byte result does not validate a changed native identity or provider.

Write corrections as new provenance entries. Do not overwrite a failed receipt or
restore a verdict merely to recover an aggregate count.

Older write-ups are in the [archive](goal-history.md#full-notebooks) under this filename.
