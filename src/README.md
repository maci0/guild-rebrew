# Reconstructed sources

`Develop/` follows attested original paths. Root `GOLD*.fcn_*.c` files await
module identification or safe consolidation. See [placement evidence](../docs/source-layout.md)
and [naming conventions](../docs/naming_conventions.md); matching code alone
does not establish its original compilation unit.

Keep shared logic in one definition, target-specific differences evidenced, and
storage owned once. Before moving or merging source, review all-target providers,
original TU context and linked baselines with `rebrew source organize review`;
verify affected targets and compare complete artifacts afterward.

The shared MSX unit is `Develop/Units/Msx/msx.c`. Character animation, scene,
script and sound-task helpers live under `Develop/DieGildeAddOn/game/`, using
canonical subsystem headers. Their exact original compilation units remain
inferred where native path evidence is absent.
