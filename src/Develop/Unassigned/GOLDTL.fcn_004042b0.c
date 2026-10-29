/* ADDRESS: GOLDTL 0x004042b0 */
int __cdecl fcn_004042b0(void *self)
{
    void *p;
    void *v;
    int lim;

    p = *(void **)((char *)self + 0x70);
    if (p == 0 && *(void **)((char *)self + 0x80) == 0)
        return 1;
    if (p != 0) {
        v = *(void **)((char *)p + 0x68);
        if (*(int *)((char *)v + 0x154) != -1)
            lim = *(int *)((char *)v + 0x154);
        else
            lim = *(int *)((char *)v + 0x148);
        if (*(int *)p >= lim)
            return 1;
        return (*(unsigned char *)((char *)p + 0x6d) >> 5) & 1;
    }
    return 0;
}
