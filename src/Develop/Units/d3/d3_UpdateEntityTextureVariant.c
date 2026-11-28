extern char d3_Universes[];
extern int g_67530c;
extern char __cdecl SelectTextureSet(void* e, void* o, unsigned char lod, char refresh);

/* ADDRESS: GOLDTL 0x004fdcf0 */
void __cdecl d3_UpdateEntityTextureVariant(int* a0)
{
    char* obj;
    char* ctx;
    char* res;
    char* q;
    unsigned int idx;

    idx = 0;
    if (a0 == 0)
        return;
    obj = *(char**) ((char*) a0 + 0x184);
    if (obj == 0)
        return;
    ctx = *(char**) (obj + 0x34);
    res = *(char**) (ctx + 0x1ec) + 0xf4;
    q = *(char**) (res + 0x318);
    if (*(char**) (obj + 0x88) != d3_Universes) {
        if (*(int*) (q + 0x1e8) <= 4) {
            idx = (unsigned int) a0[1] % (unsigned int) *(int*) (q + 0x1e8);
        } else {
            idx = (unsigned int) a0[1] & 3;
        }
        *(char*) (obj + 0x23a) = (char) idx;
    }
    if (g_67530c == *(int*) (obj + 0x2c))
        SelectTextureSet(ctx, res, (unsigned char) idx, 1);
}