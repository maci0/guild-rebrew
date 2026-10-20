/* ADDRESS: GOLDTL 0x0064de75 */
/* D3DX8/CRT band (external_ranges 0x5e0000-0x64ffff). Not reconstructible in
 * C89: the native body takes its input in x87 st(0), returns through st(0)
 * and cl, and has no stack arguments (cdecl with no parameters). That is an
 * FPU-stack calling convention with no C equivalent; the body is a rounding
 * helper (frndint / fcompp) that multiplies by a double constant at
 * 0x6b2360. No C89 expression compiles to those bytes, and __asm bodies are
 * out of scope. Left as a comparison stub.
 */
int __cdecl fcn_0064de75(void)
{
    return 0;
}
