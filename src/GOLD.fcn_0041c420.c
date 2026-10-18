/* ADDRESS: GOLD 0x0041c420 */
int __cdecl fcn_0041c420(int depth)
{
    if (depth == 8)
        return 0x800;
    if (depth == 16)
        return 0x400;
    if (depth == 24)
        return 0x200;
    if (depth == 32)
        return 0x100;
    return 0;
}
