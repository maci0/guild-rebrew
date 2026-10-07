// FUNCTION: GOLD 0x0042ec80

/* Chains the IAT double-reader (0x005eb284) into the RELOC LCG setter.
 * First call goes through the IAT slot: declare via function pointer. */
typedef int (__cdecl *thunk_t)(void);
extern int __cdecl fcn_005de77a(int value);

void __cdecl fcn_0042ec80(void)
{
    fcn_005de77a(((thunk_t) *(void**) 0x005eb284)());
}
