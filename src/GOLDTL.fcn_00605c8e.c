#ifdef REBREW_ALLOW_NAKED
/* ADDRESS: GOLDTL 0x00605c8e */
__declspec(naked) int fcn_00605c8e(void *self, int a1)
{
    /* TODO: naked body — inline asm (this in ecx),       thiscall + 1 stack arg(s) — MSVC 5.0 has no __thiscall; write the body as inline asm (this in ecx) and end with `ret 4` */}
#else
/* ADDRESS: GOLDTL 0x00605c8e */
int fcn_00605c8e(void *self, int a1)
{
    /* TODO: idiomatic C89 fallback for the comparison build */
    return 0;
}
#endif
