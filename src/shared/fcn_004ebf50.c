// FUNCTION: GOLD 0x004ebf50
// SIZE: 16
/* Arg+3 tail-jump forwarder into fcn_004fe900.
 * Wall: reference stores to [esp+4] then `jmp` (16B); both call spellings emit
 * `push/call` (15B) — MSVC6 will not tail-jump a prototyped forward call here.
 * Parked. */
void __cdecl fcn_004fe900(int value);

void __cdecl fcn_004ebf50(int value)
{
    value += 3;
    fcn_004fe900(value);
}
