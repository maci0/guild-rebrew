void *memset(void *, int, unsigned int);
int __cdecl fcn_004ae170(int);
int __cdecl fcn_004c5530(void *);

/* ADDRESS: GOLDTL 0x004b1740 */
int __cdecl fcn_004b1740(void)
{
    unsigned char buf[0xf8];
    int i;
    unsigned char *p;

    memset(buf, 0, 0xf8);
    i = 0;
    p = (unsigned char *)0x7f4ca4;
    for (;;) {
        if (fcn_004ae170(i)) {
            memset(buf, 0, 0xf8);
            buf[0x04] = 0x57;
            *(unsigned int *)(buf + 0x08) = *(unsigned int *)p;
            *(unsigned int *)(buf + 0x0c) = *(unsigned int *)p;
            *(unsigned int *)(buf + 0x28) = *(unsigned int *)0x7f4c00;
            *(unsigned int *)(buf + 0x2c) = ((i & 3) + 0xa) & 0xffff;
            *(unsigned int *)(buf + 0x30) = *(unsigned int *)0x7f4c08;
            *(unsigned short *)(buf + 0x34) = *(unsigned short *)0x7f4c0c;
            buf[0x36] = 1;
            fcn_004c5530(buf);
        }
        i++;
        p += 0x21c;
        if (p >= (unsigned char *)0x85a0a4) break;
    }
    return 1;
}
