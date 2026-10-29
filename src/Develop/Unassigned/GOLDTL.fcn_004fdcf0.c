extern void __cdecl SelectTextureSet(void* e, void* o, unsigned int lod, int refresh);

/* ADDRESS: GOLDTL 0x004fdcf0 */
void __cdecl fcn_004fdcf0(int* a0)
{
    int* obj;
    int* ctx;
    int v;
    int* res;
    int* q;
    unsigned int idx;
    int n;

    idx = 0;
    if (a0 == 0)
        return;
    obj = *(int**) ((char*) a0 + 0x184);
    if (obj == 0)
        return;
    ctx = *(int**) ((char*) obj + 0x34);
    v = *(int*) ((char*) obj + 0x88);
    res = (int*) (*(int*) ((char*) ctx + 0x1ec) + 0xf4);
    q = *(int**) ((char*) res + 0x318);
    if (v != 0x10432c0) {
        n = *(volatile int*) ((char*) q + 0x1e8);
        if (n <= 4) {
            idx = (unsigned int) a0[1] % (unsigned int) n;
        } else {
            idx = (unsigned int) 1[a0] & 3;
        }
        *(char*) ((char*) obj + 0x23a) = (char) idx;
    }
    if (*(int*) 0x67530c == *(int*) ((char*) obj + 0x2c))
        SelectTextureSet(ctx, (unsigned int)res, idx, 1);
}