/* ADDRESS: GOLDTL 0x0064e780 */
/* Not a standalone function.  This 5-byte block is the shared return path of
 * the strchr-style CRT function at 0x0064e790, which jumps back to it with
 * `je 0x0064e780`:
 *   lea eax,[edx-1] / pop ebx / ret
 * It runs in the caller's frame (EBX saved by the parent, EDX the live
 * cursor) and is followed by 11 bytes of `lea esp,[esp]` alignment.  The GOLD
 * twin is byte-identical at 0x005df0f0, ahead of the same function at
 * 0x005df100.  No C89 definition emits a frameless block entered
 * mid-function, so the body stays empty. */
void __cdecl fcn_0064e780(void)
{
}
