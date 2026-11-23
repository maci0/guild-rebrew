int __cdecl fcn_00470820(int, int, char *);
void __cdecl fcn_00537320(int);
void __cdecl fcn_00471db0(int, int);
void __cdecl fcn_00471d80(int, int);
int __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl io_AppendText(char *, ...);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00533a60(int, int, int *, int, ...);
int __cdecl fcn_00472250(int, int, int);
void __cdecl d2_SetElementValue(int, ...);
void __cdecl fcn_00468cd0(int, int);
void __cdecl fcn_00468b80(int, int);
int __cdecl fcn_00471f80(int);
void __cdecl fcn_0041b820(float *, float *, float *);
int __cdecl fcn_005373e0(void *, int);
void __cdecl fcn_005e12d0(void);
void __cdecl d3_ApplyGraphicsOptions(void);
void __cdecl fcn_00471e30(int);

/* ADDRESS: GOLDTL 0x005e2660 */
void __cdecl fcn_005e2660(void)
{
    int i, flags, dialog, accepted, first, second, selection[2];
    int a[4], b[4], c[4];
    float x[3], y[3], z[3];
    flags = *(int *)0x7e46ac & ~0x2000;
    accepted = 0;
    dialog = fcn_00470820(0, 0, (char *)0x6ad2b0);
    fcn_00537320(flags);
    fcn_00471db0(dialog, 1);
    fcn_00471d80(dialog, 2);
    d2_SetForm(dialog, 0);
    fcn_005340f0(*(int *)0x772514);
    d2_SetForm(dialog, 2);
    io_AppendText((char *)0x6ad2a8);
    io_AppendText((char *)0x3fe0);
    io_AppendText((char *)0x67d520);
    d2_SetOverlayAnimation(0, 0);
    d2_SetForm(dialog, 3);
    fcn_00533a60(*(int *)0x772514, 0, selection, 2, *(int *)0x14ac5a8, *(int *)0x14ac5ac);
    a[0] = fcn_00472250(dialog, 1, 0);
    a[1] = fcn_00472250(dialog, 1, 1);
    a[2] = fcn_00472250(dialog, 1, 2);
    a[3] = fcn_00472250(dialog, 1, 9);
    b[0] = fcn_00472250(dialog, 1, 3);
    b[1] = fcn_00472250(dialog, 1, 4);
    b[2] = fcn_00472250(dialog, 1, 5);
    b[3] = fcn_00472250(dialog, 1, 10);
    c[0] = fcn_00472250(dialog, 1, 6);
    c[1] = fcn_00472250(dialog, 1, 7);
    c[2] = fcn_00472250(dialog, 1, 8);
    c[3] = fcn_00472250(dialog, 1, 11);
    for (i = 0; i < 3; i++) {
        d2_SetElementValue(a[i], -50, 50, (int)(((float *)0x776670)[i] * 100.0f));
        fcn_00468cd0(a[i], 0x82);
        fcn_00468b80(a[i], ((int *)0x14b52b4)[i]);
        d2_SetElementValue(b[i], 0, 200, (int)(((float *)0x776680)[i] * 100.0f));
        fcn_00468cd0(b[i], 0x82);
        fcn_00468b80(b[i], ((int *)0x14b52b4)[i]);
        d2_SetElementValue(c[i], 50, 600, (int)(((float *)0x776690)[i] * 100.0f));
        fcn_00468cd0(c[i], 0x82);
        fcn_00468b80(c[i], ((int *)0x14b52b4)[i]);
    }
    d2_SetElementValue(a[3], 0, 100, (int)(*(float *)0x77667c * 100.0f));
    d2_SetElementValue(b[3], 0, 150, (int)(*(float *)0x77668c * 100.0f));
    d2_SetElementValue(c[3], 0, 150, (int)(*(float *)0x77669c * 100.0f));
    while (fcn_005373e0((void *)fcn_005e2660, flags)) {
        if (*(int *)0x14ce8e0 || *(unsigned char *)0x14cf950 == 1)
            *(int *)0x774654 = 1;
        if (*(int *)0x100f1dc != -1) {
            if (*(int *)0x67d370 == selection[0]) {
                accepted = 1;
                *(int *)0x774654 = 1;
            } else if (*(int *)0x67d370 == selection[1]) {
                *(int *)0x774654 = 1;
            }
        }
        if (*(int *)0x14ce8d0) {
            for (i = 0; i < 3; i++) {
                first = fcn_00471f80(a[i]);
                second = fcn_00471f80(a[3]);
                x[i] = (second + *(float *)0x662914) * (first + 50) * *(float *)0x662d04 - *(float *)0x6628cc;
                first = fcn_00471f80(b[i]);
                second = fcn_00471f80(b[3]);
                y[i] = second * (float)first * *(float *)0x662d04;
                first = fcn_00471f80(c[i]);
                second = fcn_00471f80(c[3]);
                z[i] = second * (float)first * *(float *)0x662d04;
            }
            fcn_0041b820(x, y, z);
        }
    }
    if (accepted) {
        for (i = 0; i < 3; i++) {
            ((float *)0x776670)[i] = fcn_00471f80(a[i]) * 0.01f;
            ((float *)0x776680)[i] = fcn_00471f80(b[i]) * 0.01f;
            ((float *)0x776690)[i] = fcn_00471f80(c[i]) * 0.01f;
        }
        *(float *)0x77667c = fcn_00471f80(a[3]) * 0.01f;
        *(float *)0x77668c = fcn_00471f80(b[3]) * 0.01f;
        *(float *)0x77669c = fcn_00471f80(c[3]) * 0.01f;
        fcn_005e12d0();
    }
    d3_ApplyGraphicsOptions();
    fcn_00471e30(dialog);
}
