extern char* g_1015ea0; /* 0x1015ea0, GUI pool, stride 0x2f4 */
extern char* g_773d78;  /* 0x773d78 */
extern int g_772514;    /* 0x772514 */

int __cdecl fcn_004fdec0(char* name);
int __cdecl d2_SetForm(int k, int i);
int __cdecl fcn_0046f740(int x, int y, int id, int win);
void __cdecl fcn_00472900(int i, int v);
void __cdecl fcn_0046f9b0(int element, int a2);
int __cdecl fcn_0046fac0(int a1, int a2, char* text, int win);
char* __cdecl gm_StartFilteredEntitySearch(int a1, int a2, int a3);
char* __cdecl gm_EntityAccumulate(int entity);
int __cdecl fcn_0050c490(char* a, void** out);
void __cdecl io_AppendText(int a1, ...);
void __cdecl io_FormatTextBuffer(char* buf, char* fmt, ...);

/* ADDRESS: GOLDTL 0x005b5eb0 */
void __cdecl fcn_005b5eb0(int a0, char* a1)
{
    int v8[4];
    char buf[512];
    int* p;
    int i;
    int y;
    int x;
    int v;
    char* name;

    *(int*) 0x777cc0 = 0;
    p = (int*) 0x777cdc;
    do {
        p[-3] = -1;
        p[0] = -1;
        p++;
    } while ((int) p < 0x777ce8);
    d2_SetForm(*(int*) (a0 + 0x234), 1);
    io_AppendText(0x6811b0);
    io_AppendText(0x1a1f);
    d2_SetForm(*(int*) (a0 + 0x234), 3);
    v = fcn_0050c490(a1, (void**) 0x777cc4);
    *(int*) 0x777cc0 = v;
    if (v > 3) {
        v = 3;
        *(int*) 0x777cc0 = 3;
    }
    if (v <= 0) {
        return;
    }
    x = 0x5a;
    y = 10;
    i = 0;
    do {
        v8[0] = fcn_004fdec0("arbeiter_MANN");
        v8[1] = fcn_004fdec0("handwerker_MANN");
        v8[2] = fcn_004fdec0("handwerker2_MANN");
        v8[3] = fcn_004fdec0("handwerker3_MANN");
        fcn_0046f740(0xe, y - 2, 0x5db, g_772514);
        fcn_0046f740(0x10, y,
                     v8[*(int*) (*(int*) (i * 4 + 0x777cc4) + 2) & 3] + 0x639,
                     g_772514);
        fcn_0046f740(0x50, x - 0x5a,
                     *(unsigned short*) (*(int*) (i * 4 + 0x777cc4)) + 0x4b1,
                     g_772514);
        v = *(int*) (i * 4 + 0x777cc4);
        if (*(int*) (v + 0x24) != 0) {
            name = gm_StartFilteredEntitySearch(1, 1, *(unsigned int*) (*(int*) (v + 0x24) + 0xb4));
            if (name != 0) {
                io_FormatTextBuffer(buf, (char*) 0x1a3e, name);
            }
        } else {
            name = gm_EntityAccumulate(v);
            if (*name == 'D') {
                name = g_773d78;
            }
            io_FormatTextBuffer(buf, (char*) 0x1a3e, name);
        }
        v = fcn_0046fac0(0, x - 0x12, buf, g_772514);
        *(int*) (i * 4 + 0x777cdc) = v;
        fcn_00472900(v, 0x56);
        if (a1 != name) {
            v = fcn_0046f740(0, x, 5, g_772514);
            *(int*) (i * 4 + 0x777cd0) = v;
            *(unsigned int*) (g_1015ea0 + 0x5c + v * 0x2f4) = 1;
            *(char**) (g_1015ea0 + 0x2f0 +
                       *(int*) (i * 4 + 0x777cd0) * 0x2f4) = name;
            fcn_00472900(*(int*) (i * 4 + 0x777cd0), 0x56);
            fcn_0046f9b0(*(int*) (i * 4 + 0x777cd0), *(int*) 0x14abc14);
            *(unsigned int*) (g_1015ea0 + 0x1d0 +
                              *(int*) (i * 4 + 0x777cd0) * 0x2f4) = 3;
        }
        i++;
        y += 0x6e;
        x += 0x78;
    } while (i < *(int*) 0x777cc0);
}
