#ifdef REBREW_ALLOW_NAKED
/* ADDRESS: GOLDTL 0x0060f24d */
__declspec(naked) int fcn_0060f24d(void *self, int a1, int a2, int a3)
{
    /* TODO: naked body — inline asm (this in ecx),       thiscall + 3 stack arg(s) — MSVC 5.0 has no __thiscall; write the body as inline asm (this in ecx) and end with `ret 12` */}
#else
/* ADDRESS: GOLDTL 0x0060f24d */
int fcn_0060f24d(void *self, int a1, int a2, int a3)
{
    /* TODO: idiomatic C89 fallback for the comparison build */
    return 0;
}
#endif
