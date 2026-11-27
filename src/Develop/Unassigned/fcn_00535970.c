extern double g_665e30;

typedef struct {
    float x;
    int y;
    int z;
} D3_OFFSET_VEC3;

void __cdecl d3_AnimateObjectTransform(char *, char *, D3_OFFSET_VEC3 *, int, int);

/* ADDRESS: GOLDTL 0x00535970 */
void __cdecl fcn_00535970(char *e)
{
    D3_OFFSET_VEC3 v;

    v.x = *(float *) (e + 0x84) + g_665e30;
    v.y = *(int *) (e + 0x88);
    v.z = *(int *) (e + 0x8c);
    d3_AnimateObjectTransform(e, e + 0x4c, &v, 0x46, 0x20);
}
