/* Not a function entry.  0x0041a8c3 is the interior early-return epilogue of
 * the routine that starts at 0x0041a380 (mov eax,[0x6b5ddc]; sub esp,0x24;
 * push ebx/esi/edi).  Its allocation guard at 0x0041a3a0 does
 * "je 0x0041a8c3", so this block reloads the adapter count from [0x6b5de8]
 * and returns through the enclosing frame's pops (pop edi; pop esi;
 * pop ebx; add esp,0x24; ret) without any prologue of its own.  The main
 * epilogue at 0x0041a8ba differs only in returning ecx.  The 13-byte extent
 * ends with the alignment nop at 0x0041a8cf, so it is one instruction past
 * the real block.  No C89 body emits a frame it does not own. */
/* ADDRESS: GOLDTL 0x0041a8c3 */
int __cdecl fcn_0041a8c3(void)
{
    return 0;
}
