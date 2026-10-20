/* CRT band. Import thunk array, not a function: 31 consecutive
 * `jmp dword ptr [IAT]` stubs, 6 bytes each, from 0x00660600 to 0x006606b9
 * (slots 0x6620f8 and up). A C body cannot emit a bare import jump, and the
 * stored 186-byte extent is a table of thunks. Non-C class (import thunks,
 * merged extent). */
/* ADDRESS: GOLDTL 0x00660600 */
int __cdecl fcn_00660600(void)
{
    /* Import thunk array, not C. */
    return 0;
}
