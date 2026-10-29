/* ADDRESS: GOLDTL 0x005e0060 */
int __cdecl fcn_005e0060(int count, char *base)
{
    int index;
    int *entry;

    index = 2;
    if (count <= 2)
        return -1;
    entry = (int *)(base + 0x448);
    do {
        if (*entry == -1)
            return index;
        index++;
        entry = (int *)((char *)entry + 0x220);
    } while (index < count);
    return -1;
}
