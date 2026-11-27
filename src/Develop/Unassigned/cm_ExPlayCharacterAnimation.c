int __cdecl fcn_0064d41a(char *, const char *, int);
int __cdecl ch_FindCharacterByName(char *);
int __cdecl ch_QueuePlayAnimation(int, char *, int);

/* ADDRESS: GOLDTL 0x004cb5d0 */
int __cdecl cm_ExPlayCharacterAnimation(void *s, char *out)
{
    char buf[0x80];
    int r;

    fcn_0064d41a(buf, 0x68b0d8, *(int *)((char *)s + 0x10));
    r = ch_FindCharacterByName(buf);
    if (r == 0) return 2;
    ch_QueuePlayAnimation(r, (char *)s + 0x14, ((unsigned char *)s)[0x44]);
    if (out != 0) {
        out[0] = 2;
        out[1] = 0;
        *(int *)(out + 6) = 0;
    }
    return 0;
}
