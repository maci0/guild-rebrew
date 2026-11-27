extern int __cdecl fcn_00503fe0(int a, int b, int c);
extern void __cdecl d2_EnterBuildingObjekt(void *p, int a, void *b);
extern char g_006b5c60;

/* ADDRESS: GOLDTL 0x0057f2e0 */
void __cdecl d2_InitTutCh2GildeStep(int mode)
{
    int obj;

    if (mode != 1)
        return;
    obj = fcn_00503fe0(1, 5, 10);
    if (obj != 0)
        d2_EnterBuildingObjekt((void *)obj, -1, &g_006b5c60);
}
