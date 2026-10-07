
// FUNCTION: GOLDTL 0x64e761

/* _initterm: calls each non-0 function pointer in [pfbegin, pfend). */

void __cdecl __initterm(void** pfbegin, void** pfend)
{
    while (pfbegin < pfend)
    {
        if (*pfbegin != 0)
            ((void (__cdecl*)(void))*pfbegin)();
        pfbegin++;
    }
}
