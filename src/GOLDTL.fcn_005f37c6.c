/* ADDRESS: GOLDTL 0x005f37c6 */
int __fastcall fcn_005f37c6(void *self)
{
    unsigned i;

    for (i = 0; i < 4; i++) {
        if (*(int *)((char *)self + 8 + i * 4) != -1)
            return *(int *)((char *)self + 8 + i * 4) +
                   *(int *)((char *)self + 0x1c);
    }
    return -1;
}
