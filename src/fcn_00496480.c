int __cdecl fcn_004c6ae0(unsigned int, int);
int __cdecl fcn_004c5530(void *);

/* ADDRESS: GOLDTL 0x00496480 */
int __cdecl fcn_00496480(int *a, unsigned char *b)
{
    char t[0xf8];

    fcn_004c6ae0(a[1], -(int)(*(unsigned int *)(b + 0x10)));
    *(unsigned int *)(t + 0x08) = a[1];
    *(unsigned int *)(t + 0x0c) = a[1];
    t[0x36] = 1;
    t[0x04] = 0x60;
    t[0x5a] = b[4];
    fcn_004c5530(t);
    return 5;
}
