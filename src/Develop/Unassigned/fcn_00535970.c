extern double g_665e30;

typedef struct {
    float x;
    int y;
    int z;
} Vec535970;

void __cdecl fcn_00412cf0(char *, char *, Vec535970 *, int, int);

/* ADDRESS: GOLDTL 0x00535970 */
void __cdecl fcn_00535970(char *e)
{
    Vec535970 v;

    v.x = *(float *) (e + 0x84) + g_665e30;
    v.y = *(int *) (e + 0x88);
    v.z = *(int *) (e + 0x8c);
    fcn_00412cf0(e, e + 0x4c, &v, 0x46, 0x20);
}
