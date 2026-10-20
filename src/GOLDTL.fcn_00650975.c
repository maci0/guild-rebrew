/* Not a standalone function.  This 24-byte block is the local-unwind funclet
 * that 0x0065095f calls inside FrameUnwindToState; it reads the enclosing
 * frame ([ebp-0x1c]) and calls 0x0065098d with four arguments when the guard
 * flag is clear.  The bytes require the parent EBP frame, so no C89 body
 * emits them. */
/* ADDRESS: GOLDTL 0x00650975 */
int __cdecl fcn_00650975(void)
{
    return 0;
}
