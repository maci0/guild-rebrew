#include "Develop/Units/d2.v1/client_dialog_state.h"

int __cdecl d2_LoadForm(int, int, char *);
void __cdecl d2_UpdateViewportCenter(int);
void __cdecl d2_PositionFormWindows(int, int);
void __cdecl d2_CenterForm(int, int);
int __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl io_AppendText(char *, ...);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CreateButtonRow(int, int, int *, int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl d2_SetElementValue(int, ...);
void __cdecl d2_SetValueGaugeFlags(int, int);
void __cdecl d2_SetValueGaugeLabel(int, int);
int __cdecl d2_GetControlValue(int);
void __cdecl d3_SetGammaParams(float *, float *, float *);
int __cdecl main_RunFrameLoop(void *, int);
void __cdecl io_SaveIniSettings(void);
void __cdecl d3_ApplyGraphicsOptions(void);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDTL 0x005e2660 */
void __cdecl d2_RunAdvancedGfxOptionsDialog(void)
{
    int i, flags, dialog, accepted, first, second, selection[2];
    int a[4], b[4], c[4];
    float x[3], y[3], z[3];
    flags = *(int *)0x7e46ac & ~0x2000;
    accepted = 0;
    dialog = d2_LoadForm(0, 0, (char *)0x6ad2b0);
    d2_UpdateViewportCenter(flags);
    d2_PositionFormWindows(dialog, 1);
    d2_CenterForm(dialog, 2);
    d2_SetForm(dialog, 0);
    d2_InitWindowBounds(*(int *)0x772514);
    d2_SetForm(dialog, 2);
    io_AppendText((char *)0x6ad2a8);
    io_AppendText((char *)0x3fe0);
    io_AppendText((char *)0x67d520);
    d2_SetOverlayAnimation(0, 0);
    d2_SetForm(dialog, 3);
    d2_CreateButtonRow(*(int *)0x772514, 0, selection, 2, *(int *)0x14ac5a8, *(int *)0x14ac5ac);
    a[0] = d2_GetWindowListItem(dialog, 1, 0);
    a[1] = d2_GetWindowListItem(dialog, 1, 1);
    a[2] = d2_GetWindowListItem(dialog, 1, 2);
    a[3] = d2_GetWindowListItem(dialog, 1, 9);
    b[0] = d2_GetWindowListItem(dialog, 1, 3);
    b[1] = d2_GetWindowListItem(dialog, 1, 4);
    b[2] = d2_GetWindowListItem(dialog, 1, 5);
    b[3] = d2_GetWindowListItem(dialog, 1, 10);
    c[0] = d2_GetWindowListItem(dialog, 1, 6);
    c[1] = d2_GetWindowListItem(dialog, 1, 7);
    c[2] = d2_GetWindowListItem(dialog, 1, 8);
    c[3] = d2_GetWindowListItem(dialog, 1, 11);
    for (i = 0; i < 3; i++) {
        d2_SetElementValue(a[i], -50, 50, (int)(((float *)0x776670)[i] * 100.0f));
        d2_SetValueGaugeFlags(a[i], 0x82);
        d2_SetValueGaugeLabel(a[i], ((int *)0x14b52b4)[i]);
        d2_SetElementValue(b[i], 0, 200, (int)(((float *)0x776680)[i] * 100.0f));
        d2_SetValueGaugeFlags(b[i], 0x82);
        d2_SetValueGaugeLabel(b[i], ((int *)0x14b52b4)[i]);
        d2_SetElementValue(c[i], 50, 600, (int)(((float *)0x776690)[i] * 100.0f));
        d2_SetValueGaugeFlags(c[i], 0x82);
        d2_SetValueGaugeLabel(c[i], ((int *)0x14b52b4)[i]);
    }
    d2_SetElementValue(a[3], 0, 100, (int)(*(float *)0x77667c * 100.0f));
    d2_SetElementValue(b[3], 0, 150, (int)(*(float *)0x77668c * 100.0f));
    d2_SetElementValue(c[3], 0, 150, (int)(*(float *)0x77669c * 100.0f));
    while (main_RunFrameLoop((void *)d2_RunAdvancedGfxOptionsDialog, flags)) {
        if (*(int *)0x14ce8e0 || *(unsigned char *)0x14cf950 == 1)
            g_774654 = 1;
        if (*(int *)0x100f1dc != -1) {
            if (*(int *)0x67d370 == selection[0]) {
                accepted = 1;
                g_774654 = 1;
            } else if (*(int *)0x67d370 == selection[1]) {
                g_774654 = 1;
            }
        }
        if (*(int *)0x14ce8d0) {
            for (i = 0; i < 3; i++) {
                first = d2_GetControlValue(a[i]);
                second = d2_GetControlValue(a[3]);
                x[i] = (second + *(float *)0x662914) * (first + 50) * *(float *)0x662d04 - 0.5f;
                first = d2_GetControlValue(b[i]);
                second = d2_GetControlValue(b[3]);
                y[i] = second * (float)first * *(float *)0x662d04;
                first = d2_GetControlValue(c[i]);
                second = d2_GetControlValue(c[3]);
                z[i] = second * (float)first * *(float *)0x662d04;
            }
            d3_SetGammaParams(x, y, z);
        }
    }
    if (accepted) {
        for (i = 0; i < 3; i++) {
            ((float *)0x776670)[i] = d2_GetControlValue(a[i]) * 0.01f;
            ((float *)0x776680)[i] = d2_GetControlValue(b[i]) * 0.01f;
            ((float *)0x776690)[i] = d2_GetControlValue(c[i]) * 0.01f;
        }
        *(float *)0x77667c = d2_GetControlValue(a[3]) * 0.01f;
        *(float *)0x77668c = d2_GetControlValue(b[3]) * 0.01f;
        *(float *)0x77669c = d2_GetControlValue(c[3]) * 0.01f;
        io_SaveIniSettings();
    }
    d3_ApplyGraphicsOptions();
    d2_DestroyForm(dialog);
}
