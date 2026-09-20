// FUNCTION: GOLDTL 0x004edcd0
// SIZE: 16
/* Arg+3 tail-jump forwarder into fcn_00501490.
 * Wall (same class as GOLD fcn_004ebf50): reference stores to [esp+4] then
 * `jmp`; call spellings emit push/call. Parked. */
void __cdecl fcn_00501490(int value);

void __cdecl fcn_004edcd0(int value)
{
    value += 3;
    fcn_00501490(value);
}
