# Comparison-only choices for independent functions sharing one C symbol.
# Each omitted TU defines only the colliding function. Metadata is unchanged.
set(REBREW_SCAFFOLD_OMITS
  # The selected dialog TU already defines this handler; omit its separate stub.
  "src/fcn_005a6570.c"
  "src/GOLDTL.fcn_004f0900.c"
  "src/GOLDTL.fcn_00508b20.c"
  "src/GOLD.fcn_00576750.c"
  "src/GOLDTL.fcn_4b3b40.c"
  "src/GOLDTL.fcn_5c61c0.c"
)
