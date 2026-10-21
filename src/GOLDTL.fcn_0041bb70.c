/* Hand-written assembly, not C: the body dispatches on g_14ce86c (cases 0x17,
 * 0x18, 0x15/0x16) and converts a packed pixel to component bytes through the
 * three pointer arguments at [esp+0x1c], [esp+0x20], [esp+0x24]. Two of the
 * cases save and restore the whole register set as 16-bit halves with
 * `pushaw` (0x0041bb96, 0x0041bc15) / `popaw` (0x0041bbca, 0x0041bc49) around
 * word-sized `and ax` / `shr ax` masks, which msvc 6.0 never emits. The last
 * instruction is `ret` at 0x0041bcac, so the real extent is 317 bytes; the
 * stored 320 continues over three 0x90 NOPs. Non-C class (hand-written
 * assembly). Extent spec: 0x0041bb70=317. */
/* ADDRESS: GOLDTL 0x0041bb70 */
int __cdecl fcn_0041bb70(void)
{
    /* Hand-written assembly routine, not C. */
    return 0;
}
