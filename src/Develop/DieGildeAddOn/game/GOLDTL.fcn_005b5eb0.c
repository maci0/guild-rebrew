extern char* g_1015ea0; /* 0x1015ea0, GUI pool, stride 0x2f4 */
extern char* g_773d78;  /* 0x773d78 */
extern int g_14abc14;
extern int d2_CurrentWindowId;    /* 0x772514 */
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl fcn_004fdec0(char* name);
int __cdecl d2_SetForm(int k, int i);
int __cdecl d2_AddElementToWindow(int x, int y, int id, int win);
void __cdecl d2_SetElementFont(int i, int v);
void __cdecl fcn_0046f9b0(int element, int a2);
char* __cdecl gm_StartFilteredEntitySearch(int a1, int a2, int a3);
char* __cdecl gm_EntityAccumulate(int entity);
int __cdecl fcn_0050c490(char* a, void** out);
void __cdecl io_AppendText(int a1, ...);
void __cdecl io_FormatTextBuffer(char* buf, int fmt, ...);

/* ADDRESS: GOLDTL 0x005b5eb0 */
void __cdecl fcn_005b5eb0(int windowContext, char* entityName)
{
    int workerIcons[4];
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
    d2_SetForm(*(int*) (windowContext + 0x234), 1);
    io_AppendText(0x6811b0);
    io_AppendText(0x1a1f);
    d2_SetForm(*(int*) (windowContext + 0x234), 3);
    v = fcn_0050c490(entityName, (void**) 0x777cc4);
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
        workerIcons[0] = fcn_004fdec0("arbeiter_MANN");
        workerIcons[1] = fcn_004fdec0("handwerker_MANN");
        workerIcons[2] = fcn_004fdec0("handwerker2_MANN");
        workerIcons[3] = fcn_004fdec0("handwerker3_MANN");
        d2_AddElementToWindow(0xe, y - 2, 0x5db, d2_CurrentWindowId);
        d2_AddElementToWindow(0x10, y,
                     workerIcons[*(int*) (*(int*) (i * 4 + 0x777cc4) + 2) & 3] + 0x639,
                     d2_CurrentWindowId);
        d2_AddElementToWindow(0x50, x - 0x5a,
                     *(unsigned short*) (*(int*) (i * 4 + 0x777cc4)) + 0x4b1,
                     d2_CurrentWindowId);
        v = *(int*) (i * 4 + 0x777cc4);
        if (*(int*) (v + 0x24) != 0) {
            name = gm_StartFilteredEntitySearch(1, 1, *(unsigned int*) (*(int*) (v + 0x24) + 0xb4));
            if (name != 0) {
                io_FormatTextBuffer(buf, 0x1a3e, name);
            }
        } else {
            name = gm_EntityAccumulate(v);
            if (*name == 'D') {
                name = g_773d78;
            }
            io_FormatTextBuffer(buf, 0x1a3e, name);
        }
        v = d2_ShowTxt(0, x - 0x12, buf, d2_CurrentWindowId);
        *(int*) (i * 4 + 0x777cdc) = v;
        d2_SetElementFont(v, 0x56);
        if (entityName != name) {
            v = d2_AddElementToWindow(0, x, 5, d2_CurrentWindowId);
            *(int*) (i * 4 + 0x777cd0) = v;
            *(unsigned int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[v].value_05c)) = 1;
            *(char**) (&((D2_CONTROL_TL*)g_1015ea0)
                       [*(int*) (i * 4 + 0x777cd0)].associated_object) = name;
            d2_SetElementFont(*(int*) (i * 4 + 0x777cd0), 0x56);
            fcn_0046f9b0(*(int*) (i * 4 + 0x777cd0), g_14abc14);
            *(unsigned int*) (&((D2_CONTROL_TL*)g_1015ea0)
                              [*(int*) (i * 4 + 0x777cd0)].flags_1d0) = 3;
        }
        i++;
        y += 0x6e;
        x += 0x78;
    } while (i < *(int*) 0x777cc0);
}
