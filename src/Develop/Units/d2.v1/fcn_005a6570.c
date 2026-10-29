extern int g_14ce8e0;
extern int g_100f1dc;
extern int g_774654;

void* __cdecl fcn_00470820(int a, int b, char* name);
void __cdecl fcn_00471b60(int dlg);
void __cdecl d2_SetForm(int dlg, int a);
int __cdecl fcn_00519190(int id, ...);
int __cdecl fcn_00472250(int dlg, int a, int b);
void __cdecl fcn_00472380(int w, int a, int b, int c);
int __cdecl fcn_005373e0(void* fn, int name);
int __cdecl fcn_00471f80(int w);
void __cdecl fcn_004c4510(char* o, int v);
void __cdecl fcn_004c4570(int a, int b, int c, void* p);
void __cdecl fcn_004c5360(void);
int __cdecl fcn_00471e30(int dlg);

/* ADDRESS: GOLDTL 0x005a6570 */
void __cdecl fcn_005a6570(char* o)
{
    char* dlg;
    int id;
    int w1;
    int w2;

    dlg = fcn_00470820(0, 0, "locations\\geldleihe\\geldleihe_WechselGebuehren");
    fcn_00471b60((int) dlg);
    d2_SetForm((int) dlg, 2);
    fcn_00519190(0x1908);
    d2_SetForm((int) dlg, 1);
    id = fcn_00519190(0x1907);
    w1 = fcn_00472250((int) dlg, 1, id);
    w2 = fcn_00472250((int) dlg, 1, id + 1);
    fcn_00472380(w2, 3, 0xf, *(int*) (o + 0x69));
    fcn_00472380(w1, 3, 0xf, *(int*) (o + 0x6d));

    while (fcn_005373e0((void*) 0x5a6570, 0x677c7) != 0) {
        if (g_14ce8e0 != 0 || g_100f1dc == 1)
            g_774654 = 1;
        if (g_100f1dc == 2) {
            int a;
            int b;

            a = fcn_00471f80(w2);
            b = fcn_00471f80(w1);
            fcn_004c4510(o, *(int*) (o + 1));
            fcn_004c4570(4, 1, 0x69, &a);
            fcn_004c4570(4, 1, 0x6d, &b);
            fcn_004c5360();
            g_774654 = 1;
        } else if (g_100f1dc == 1) {
            g_774654 = 1;
        }
    }
    fcn_00471e30((int) dlg);
}
