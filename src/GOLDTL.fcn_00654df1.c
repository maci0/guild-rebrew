/* Not expressible in C89: x87 register-convention CRT helper, not just an
 * inventory defect.  0x00654df1 is a real entry (call sites at 0x00654ca6
 * and 0x00654d1d) that takes its operand in st(0), tests the fractional part
 * (frndint/fcomp/fnstsw/sahf) and returns 0, 1 or 2 in eax through the
 * out-of-line returns at 0x00654e16/0x00654e17/0x00654e1e.  MSVC 6 passes
 * float arguments on the stack, so no C89 declaration emits this convention.
 * The 111-byte inventory extent is also wrong: this body ends at 0x00654e24
 * (52 bytes).  0x00654e25 begins a separate CRT math wrapper (push esi;
 * sub esp,0x74; fnsave/frstor around the call to 0x0065504c, then a tail jump
 * to 0x006532f9) that runs to 0x00654e56, and 0x00654e57..0x00654e5f is a
 * nine-byte int3 run.  Correct extents: 0x00654df1 = 52, 0x00654e25 = 50. */
/* ADDRESS: GOLDTL 0x00654df1 */
int __cdecl fcn_00654df1(void)
{
    return 0;
}
