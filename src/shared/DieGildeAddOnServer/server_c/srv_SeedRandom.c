/* srv_SeedRandom - srand(seed) wrapper (0x1001a150).

 * A 12-byte thunk the reference keeps next to srv_SeedRandomWithTime and the
 * other random helpers: six command handlers call IT, not the CRT `_srand`
 * (cm_ExAllocSpieler 0x1000d476, cm_ExAllocClientSpieler 0x1000d58b,
 * cm_ExEmployWorker 0x1000f74b, cm_ExCreateCitizen 0x1000f9b2,
 * cm_ExAllocGraveyardWorker 0x10010328, cm_ExAllocAlchemist 0x10010368).
 * Calling `srand` directly from those six sites is relocation-masked by
 * `rebrew test`, which is why the difference survived as six RELOC passes and
 * a catalog entry that read this thunk as LIBCMT's `_srand`.
 */

// FUNCTION: SERVER 0x1001A150

extern void __cdecl srand(unsigned int);

void __cdecl srv_SeedRandom(unsigned int seed)
{
	srand(seed);
}
