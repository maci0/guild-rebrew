/* ADDRESS: GOLDTL 0x006052b9 */
/* D3DX8 band (external_ranges 0x5e0000-0x64ffff). The inventory extent
 * matched no unique archive member. The native body is thiscall with one
 * stack argument (ret 4); C89 cannot express that, and MSVC 6 rejects
 * __thiscall in C, so the metadata binding stays cdecl and self is passed
 * explicitly. Body logic is faithful; the prologue and return differ.
 */
int fcn_006052b9(void *self, void *a1)
{
    unsigned i;
    int *p;

    i = *(unsigned *)((char *)self + 0x108) + 1;
    if (*(unsigned *)((char *)self + 0x104) <= i)
        return 0;
    do {
        p = (int *)(*(char **)((char *)self + 0xfc) + i * 8);
        if (*(char *)(*(char **)((char *)self + 0x100) + i) == 0)
            *p = ((int *)a1)[*p];
        i++;
    } while (i < *(unsigned *)((char *)self + 0x104));
    return 0;
}
