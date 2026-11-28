char *__cdecl strstr(const char *, const char *);
extern char __cdecl SelectTextureSet(void *e, void *o, unsigned char lod, char refresh);

/* ADDRESS: GOLDTL 0x0040f470 */
/* ADDRESS: GOLDDE 0x0040e270 */
char __cdecl d3_SelectMatchingTextureSet(void *self, void *other)
{
    if (*(void **)((char *)self + 0x1cc) != 0) {
        if (strstr((char *)self, (char *)other) != 0)
            SelectTextureSet(self, *(void **)((char *)self + 0x1cc),
                             *(unsigned char *)((char *)other + 0xc8), 1);
    }
    return 1;
}
