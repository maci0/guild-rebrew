int __cdecl fcn_0064d41a(char *, const char *, int);
int __cdecl fcn_004032b0(char *);
int __cdecl fcn_00406340(int, char *, int);

/* ADDRESS: GOLDTL 0x004cb5d0 */
int __cdecl fcn_004cb5d0(void *s, char *out)
{
    char buf[0x80];
    int r;

    fcn_0064d41a(buf, 0x68b0d8, *(int *)((char *)s + 0x10));
    r = fcn_004032b0(buf);
    if (r == 0) return 2;
    fcn_00406340(r, (char *)s + 0x14, ((unsigned char *)s)[0x44]);
    if (out != 0) {
        out[0] = 2;
        out[1] = 0;
        *(int *)(out + 6) = 0;
    }
    return 0;
}
