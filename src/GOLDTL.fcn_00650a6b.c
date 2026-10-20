/* Not a standalone function.  This 24-byte block is the local-unwind funclet
 * that 0x00650a55 calls inside the EH vector-constructor iterator
 * ??_L@YGXPAXIHP6EX0@Z1@Z; it reads the enclosing frame ([ebp-0x20],
 * [ebp-0x1c]) and calls 0x0065098d with four arguments when the guard flag is
 * clear.  The bytes require the parent EBP frame, so no C89 body emits them. */
/* ADDRESS: GOLDTL 0x00650a6b */
int __cdecl fcn_00650a6b(void)
{
    return 0;
}
