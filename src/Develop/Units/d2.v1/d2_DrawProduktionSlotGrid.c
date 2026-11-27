extern void __cdecl d2_SetForm(int, int);
extern int __cdecl d2_AddElementToWindow(int, int, int, int);
extern void __cdecl d2_SetElementImage(int, int);
extern void __cdecl d2_PositionControl(int, int, int);
extern void __cdecl d2_UpdateProduktionSlotTile(int, int, int *, int, int, int);
extern void __cdecl ResetDisplayCounters(void);
extern int __cdecl d2_GetControlValue(int);
extern void __cdecl d2_SetDisplayCounter(int, int);

/* ADDRESS: GOLDTL 0x00597940 */
void __cdecl d2_DrawProduktionSlotGrid(int win, int form, int refreshCounters, int extra, short *modePtr)
{
    int *r;
    int width;
    int *p;
    int n;
    int i;
    int col;
    int value;

    r = (int *)(*(int *)((form + win * 0xaf) * 4 + 0x1038144) * 0x3cc + 0x1015f40);
    width = r[3];
    d2_SetForm(win, form);

    p = (int *)0x778d50;
    do {
        if (*p == -1)
            *p = d2_AddElementToWindow(0, 0, 0x743, *(int *)0x772514);
        p += 5;
    } while ((int)p < 0x778da0);

    /* col carries the lane 0x778d4c address for the loop bound only */
    i = 0;
    p = (int *)0x778d50;
    n = *(int *)0x772500;
    col = (int)(p - 1);
    do {
        if (p[-2] != p[-1]) {
            d2_SetElementImage(p[0], p[-1] + 0x741);
            n = *(int *)0x772500;
        }
        value = p[-1];
        p[-2] = value;
        if (value >= 2) {
            p[-4] = (width - *(short *)(n + 0x261a4 + value * 0x54)) >> 1;
            p[-3] = (*(short *)(n + 0x2624e) + 0x23) * i;
        }
        p += 5;
        i += 1;
        col += 0x14;
    } while (col < 0x778d9c);

    d2_SetForm(win, form);

    p = (int *)0x778d50;
    do {
        if (p[-2] >= 2) {
            *(int *)(*(int *)0x1015ea0 + p[0] * 0x2f4 + 0x48) = 0;
            d2_PositionControl(r[1] + p[-4], r[2] + p[-3], *p);
        } else {
            *(int *)(*(int *)0x1015ea0 + p[0] * 0x2f4 + 0x48) = 1;
        }
        p += 5;
    } while ((int)p < 0x778da0);

    col = 0;
    i = 0;
    p = (int *)0x778da0;
    do {
        col += 1;
        if (col > *(int *)(i * 0x14 + 0x778d48)) {
            col = 1;
            do {
                i += 1;
            } while (*(int *)(i * 0x14 + 0x778d48) < 1);
        }
        p[2] = *(int *)(i * 0x14 + 0x778d40) - 0x44 + col * 0x44;
        p[3] = *(int *)(i * 0x14 + 0x778d44);
        if (*modePtr == 0x1db)
            d2_UpdateProduktionSlotTile(win, form, p, refreshCounters, 1, extra);
        else if (*modePtr == 0x1dc)
            d2_UpdateProduktionSlotTile(win, form, p, refreshCounters, 2, extra);
        else
            d2_UpdateProduktionSlotTile(win, form, p, refreshCounters, 3, extra);
        p = (int *)((char *)p + 0x38);
    } while ((int)p < 0x779120);

    if (!refreshCounters)
        return;
    ResetDisplayCounters();

    p = (int *)0x778db0;
    do {
        if (*p != -1) {
            value = d2_GetControlValue(*p);
            d2_SetDisplayCounter(p[-4] + 0xdf, value);
        }
        p += 0xe;
    } while ((int)p < 0x779130);

    p = (int *)0x7796f0;
    do {
        if (*p != -1) {
            value = d2_GetControlValue(*p);
            d2_SetDisplayCounter(p[-4] + 0xdf, value);
        }
        p += 0xe;
    } while ((int)p < 0x7798b0);
}
