/* CRT band. Import thunk array, not a function: 56 consecutive
 * `jmp dword ptr [IAT]` stubs, 6 bytes each, from 0x006606ba to 0x00660809
 * (slots 0x662174 upward, non-monotonic after 0x662180). A C body cannot emit
 * a bare import jump, and the stored 336-byte extent is a table of thunks.
 * Non-C class (import thunks, merged extent). */
/* ADDRESS: GOLDTL 0x006606ba */
int __cdecl fcn_006606ba(void)
{
    /* Import thunk array, not C. */
    return 0;
}
