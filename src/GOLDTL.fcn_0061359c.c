#ifdef REBREW_ALLOW_NAKED
/* ADDRESS: GOLDTL 0x0061359c */
__declspec(naked) int fcn_0061359c(void *self, int a1, int a2)
{
    /* TODO: naked body — inline asm (this in ecx),       thiscall + 2 stack arg(s) — MSVC 5.0 has no __thiscall; write the body as inline asm (this in ecx) and end with `ret 8` */}
#else
/* ADDRESS: GOLDTL 0x0061359c */
int fcn_0061359c(void *self, int a1, int a2)
{
    /* TODO: idiomatic C89 fallback for the comparison build */
    return 0;
}
#endif
