extern int g_6b7f90;
extern int* g_6b7ed0[16];
extern int* g_6b7f10[16];
extern int* g_6b7f50[16];
extern void (__stdcall* g_6623a8)(int);

int __cdecl fcn_0042b120(int a1);
void __cdecl fcn_0041ddd0(void* p);

/* ADDRESS: GOLDTL 0x0042a2d0 */
int __cdecl fcn_0042a2d0(int* a0)
{
    int r;
    int i;

    r = 0;
    if (g_6b7f90 != r && (i = fcn_0042b120((int) a0)) >= r) {
        g_6623a8(*a0);
        if (g_6b7f10[i] != r) {
            fcn_0041ddd0(g_6b7f10[i]);
            g_6b7f10[i] = r;
        }
        if (g_6b7f50[i] != r) {
            fcn_0041ddd0(g_6b7f50[i]);
            g_6b7f50[i] = r;
        }
        fcn_0041ddd0(a0);
        g_6b7ed0[i] = r;
    } else {
        r = -1;
    }
    return r;
}
