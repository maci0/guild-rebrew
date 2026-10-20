/* Native body probes CPUID leaves 0x80000000/0x80000001 (under pushal/popal)
 * and returns bit 31 of the extended feature flags (3DNow!).  MSVC 6 has no
 * CPUID intrinsic in C mode and this project forbids inline assembly, so the
 * bytes cannot be emitted from C89.  Native length 56. */
/* ADDRESS: GOLDTL 0x006132e7 */
int __cdecl fcn_006132e7(void)
{
    return 0;
}
