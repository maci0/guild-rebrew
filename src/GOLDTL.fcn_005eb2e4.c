/* Import/dispatch thunk: native extents begin with "jmp dword ptr [0x6ad670]"
 * (6 bytes, the tail call below) and continue at 0x005eb2ea with an
 * ECX-relative float routine (1/d scale of +0 and +4 into a caller buffer,
 * "ret 8") that the inventory merged into this SIZE.  A C89 body cannot put
 * the object in ECX, so only the thunk is reproduced here. */
/* ADDRESS: GOLDTL 0x005eb2e4 */
void __cdecl fcn_005eb2e4(void)
{
    (*(void (__cdecl **)(void))0x6ad670)();
}
