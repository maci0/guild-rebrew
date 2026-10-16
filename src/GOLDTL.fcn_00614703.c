#ifdef REBREW_ALLOW_NAKED
/* ADDRESS: GOLDTL 0x00614703 */
__declspec(naked) int fcn_00614703(void *self, int a1, int a2, int a3, int a4, int a5, int a6)
{
    /* TODO: naked body — inline asm (this in ecx),       thiscall + 6 stack arg(s) — MSVC 5.0 has no __thiscall; write the body as inline asm (this in ecx) and end with `ret 24` */}
#else
/* ADDRESS: GOLDTL 0x00614703 */
int fcn_00614703(void *self, int a1, int a2, int a3, int a4, int a5, int a6)
{
    /* TODO: idiomatic C89 fallback for the comparison build */
    return 0;
}
#endif
