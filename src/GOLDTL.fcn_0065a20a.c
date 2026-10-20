extern void __cdecl fcn_0065756f(void);

/* ADDRESS: GOLDTL 0x0065a20a */
/* Five-byte funclet stub: jmp 0x0065756f, the CRT assert/notify routine
 * (callers: assert and the local EH block at 0x0065a205).  It is entered
 * from inside that EH block with the enclosing frame live.  The remaining 24
 * bytes of the 29-byte inventory extent are the next function,
 * 0x0065a20f. */
void __cdecl fcn_0065a20a(void)
{
    fcn_0065756f();
}
