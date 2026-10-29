/* Import forwarder: jmp dword ptr [0x662444].  Not a C body; the pointer call
 * in a void wrapper is the only C form that emits the bare indirect jump. */
/* ADDRESS: GOLDTL 0x0042b2e0 */
void __cdecl fcn_0042b2e0(void)
{
    (*(void (__stdcall **)(void))0x662444)();
}
