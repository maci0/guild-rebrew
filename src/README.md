# Reconstructed sources

`Develop/` follows the original source tree recorded in the binaries. Shared game
units and their client counterparts belong there when the evidence supports that
placement. Files directly in this directory still await module identification or
safe consolidation; an address-based filename is temporary.

See [source layout and placement evidence](../docs/source-layout.md) and
[original naming conventions](../docs/naming_conventions.md). A reconstructed
module placement does not establish the original compilation-unit filename.

Move function and data identities with `rebrew source rehome`, preserve target
compiler settings, and verify every affected target. Keep original library code
separate from game reversing progress and avoid duplicate global storage.

`Develop/Units/Msx/msx.c` is a verified eleven-function shared client unit. Its
header supplies canonical declarations to callers. Use the fixed `source merge`
writer to move identities along with their bodies, including legacy marker inputs.

Character animation, script callbacks and sound tasks now sit in
`Develop/DieGildeAddOn/game/`, beside the canonical `ch_motion.h` declarations.
This placement follows native character diagnostics and task dependencies; their
exact original compilation units remain unproven. The shared `character.c` now
reproduces both native scene and dummy layouts under the configured client build
selector, with one body each for `ch_MoveCharacter2Universe` and `TakeObjectScript`.
