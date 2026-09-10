// CFLAGS: /O1 /Gd
// FUNCTION: SERVER 0x1001a643
#include <windows.h>

/* initterm helper: calls the single function pointer at 0x100317d8 (if
 * set), then walks the two .rdata init-vector tables via fcn_1001a758. */

extern void __cdecl fcn_1001a758(void*, void*);   /* 0x1001a758 - initterm loop */
extern void* _FPinit;   /* 0x100317d8 - first init fnptr */

void __cdecl fcn_1001a643(void)
{
    if (_FPinit != NULL)
        ((void (__cdecl*)(void))_FPinit)();
    fcn_1001a758((void*)0x10027008, (void*)0x10027014);
    fcn_1001a758((void*)0x10027000, (void*)0x10027004);
}

// FUNCTION: SERVER 0x1001a758

/* _initterm: calls each non-NULL function pointer in [pfbegin, pfend). */

void __cdecl fcn_1001a758(void** pfbegin, void** pfend)
{
    while (pfbegin < pfend)
    {
        if (*pfbegin != NULL)
            ((void (__cdecl*)(void))*pfbegin)();
        pfbegin++;
    }
}
