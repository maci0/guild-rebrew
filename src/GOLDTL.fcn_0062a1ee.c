void __cdecl fcn_006299c0(void);

/* ADDRESS: GOLDTL 0x0062a1ee */
/* Five-byte tail-jump thunk: jmp 0x006299c0 (an EH-constructor helper that
 * opens with _EH_prolog, so it has no C body of its own).  The remaining 13
 * bytes of the 18-byte inventory extent are int3 alignment padding. */
void __cdecl fcn_0062a1ee(void)
{
    fcn_006299c0();
}
