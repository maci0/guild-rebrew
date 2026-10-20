/* CRT band. Not one function: 0x0042b2e0 is a 16-byte import forwarder
 * (`jmp dword ptr [0x662444]` plus 10 NOPs) and the stored 144-byte extent
 * continues into the real 128-byte body at 0x0042b2f0, which has no metadata
 * row. A C body cannot produce a bare import jump plus padding, and the row is
 * over-merged. Extent spec: 0x0042b2e0=16 and a new entry 0x0042b2f0=128.
 * Non-C class (import thunk, merged extent). */
/* ADDRESS: GOLDTL 0x0042b2e0 */
int __cdecl fcn_0042b2e0(void)
{
    /* Import forwarder, not C. */
    return 0;
}
