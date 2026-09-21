// FUNCTION: GOLD 0x005df7d1
// SIZE: 11

/* Wall: reference is single-insn `push dword [esp+4]`; every C spelling of a
 * prototyped or unprototyped forward call emits `mov eax,[esp+4]; push eax`.
 * The fold needs the callee body visible in-TU (original TU order). Parked
 * until fcn_005df746 is reversed in the same TU. */
void __cdecl fcn_005df746(int value);

void __cdecl fcn_005df7d1(int value)
{
    fcn_005df746(value);
}
