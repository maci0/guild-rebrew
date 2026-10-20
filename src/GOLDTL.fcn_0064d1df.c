/* D3DX8 external band. Seven adjacent global dword stores; the body is
 * byte-identical (EXACT) against the native first 56 bytes. The stored
 * 73-byte extent merges this 56-byte body with the 16-byte setter at
 * 0x64d217 and one int3 fill byte at 0x64d227. */
/* ADDRESS: GOLDTL 0x0064d1df */
void __cdecl fcn_0064d1df(void)
{
    void *p;

    p = (void *)0x651f28;
    *(void **)0x6b2754 = (void *)0x651bd2;
    *(void **)0x6b2750 = p;
    *(void **)0x6b2758 = (void *)0x651c38;
    *(void **)0x6b275c = (void *)0x651b78;
    *(void **)0x6b2760 = (void *)0x651c20;
    *(void **)0x6b2764 = p;
}
