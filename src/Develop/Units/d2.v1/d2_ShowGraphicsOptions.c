extern int d2_DialogButtonAction;
int __cdecl d2_LoadForm(int, int, char *);
void __cdecl d2_UpdateViewportCenter(int);
void __cdecl d2_PositionFormWindows(int, int);
void __cdecl d2_CenterForm(int, int);
int __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl io_AppendText(char *, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl d2_SetSlotVisibility(int, int);
void __cdecl d2_SetElementValue(int, ...);
void __cdecl d2_SetValueGaugeFlags(int, int);
void __cdecl d2_SetValueGaugeLabel(int, int);
void __cdecl d2_SetValueGaugeStepLabels(int, int, ...);
void __cdecl d2_CreateButtonRow(int, int, int *, int, ...);
int __cdecl main_RunFrameLoop(void *, int);
void __cdecl d2_SetFormVisibility(int, int);
void __cdecl d2_RunAdvancedGfxOptionsDialog(void);
int __cdecl d2_GetControlValue(int);
void __cdecl io_SaveIniSettings(void);
void __cdecl d3_ApplyGraphicsOptions(void);
void __cdecl io_LoadIniSettings(void);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDTL 0x005e2b60 */
void __cdecl d2_ShowGraphicsOptions(void)
{
  int v1, selection[3];
  unsigned char v2, v3;
  unsigned int v4, v5, v6, v7, v8, v9, v10, v11, v12, v14, v15;
  v14 = *(unsigned int *)0x7e46ac & ~0x2000;
  v1 = 0;
  v4 = d2_LoadForm(0,0,(char *)0x6ad2d4);
  d2_UpdateViewportCenter(v14);
  d2_PositionFormWindows(v4,1);
  d2_CenterForm(v4,2);
  d2_SetForm(v4,0);
  d2_InitWindowBounds(*(unsigned int *)0x772514);
  d2_SetOverlayAnimation(0,0);
  d2_SetForm(v4,2);
  io_AppendText((char *)0x1c5a);
  d2_SetForm(v4,1);
  v15 = d2_GetWindowListItem(v4,1,0);
  v5 = d2_GetWindowListItem(v4,1,1);
  v6 = d2_GetWindowListItem(v4,1,2);
  v7 = d2_GetWindowListItem(v4,1,3);
  v8 = d2_GetWindowListItem(v4,1,4);
  v9 = d2_GetWindowListItem(v4,1,5);
  d2_SetSlotVisibility(v7,0);
  v10 = d2_GetWindowListItem(v4,1,6);
  v11 = d2_GetWindowListItem(v4,1,7);
  v12 = d2_GetWindowListItem(v4,1,8);
  d2_SetElementValue(v15,0,2,*(unsigned int *)0x77534c & 0xff);
  d2_SetValueGaugeFlags(v15,0x82);
  d2_SetValueGaugeLabel(v15,*(unsigned int *)0x14ac4bc);
  d2_SetValueGaugeStepLabels(v15,3,*(unsigned int *)0x14ac4ec,*(unsigned int *)0x14ac4f0,*(unsigned int *)0x14ac4f4);
  d2_SetElementValue(v5,0,2,*(unsigned int *)0x776664 & 0xff);
  d2_SetValueGaugeFlags(v5,0x82);
  d2_SetValueGaugeLabel(v5,*(unsigned int *)0x14ac4c0);
  d2_SetValueGaugeStepLabels(v5,3,*(unsigned int *)0x14ac4e0,*(unsigned int *)0x14ac4e4,*(unsigned int *)0x14ac4e8);
  d2_SetElementValue(v6,0,2,*(unsigned int *)0x776664 >> 8 & 0xff);
  d2_SetValueGaugeFlags(v6,0x82);
  d2_SetValueGaugeLabel(v6,*(unsigned int *)0x14ac4c4);
  d2_SetValueGaugeStepLabels(v6,3,*(unsigned int *)0x14ac4e0,*(unsigned int *)0x14ac4e4,*(unsigned int *)0x14ac4e8);
  d2_SetElementValue(v7,0,2,*(unsigned int *)0x776668 >> 0x10 & 0xff);
  d2_SetValueGaugeFlags(v7,0x82);
  d2_SetValueGaugeLabel(v7,*(unsigned int *)0x14ac4c8);
  d2_SetValueGaugeStepLabels(v7,3,*(unsigned int *)0x14ac4e0,*(unsigned int *)0x14ac4e4,*(unsigned int *)0x14ac4e8);
  d2_SetElementValue(v8,0,1,*(unsigned int *)0x776668 & 0xff);
  d2_SetValueGaugeFlags(v8,0x82);
  d2_SetValueGaugeLabel(v8,*(unsigned int *)0x14ac4cc);
  d2_SetValueGaugeStepLabels(v8,2,*(unsigned int *)0x14ac50c,*(unsigned int *)0x14ac510);
  d2_SetElementValue(v9,0,1,*(unsigned int *)0x776664 >> 0x10 & 0xff);
  d2_SetValueGaugeFlags(v9,0x82);
  d2_SetValueGaugeLabel(v9,*(unsigned int *)0x14ac4d0);
  d2_SetValueGaugeStepLabels(v9,2,*(unsigned int *)0x14ac4e0,*(unsigned int *)0x14ac4e8);
  d2_SetElementValue(v10,0,2,*(unsigned int *)0x776664 >> 0x18);
  d2_SetValueGaugeFlags(v10,0x82);
  d2_SetValueGaugeLabel(v10,*(unsigned int *)0x14ac4d4);
  d2_SetValueGaugeStepLabels(v10,3,*(unsigned int *)0x14ac4e0,*(unsigned int *)0x14ac4e4,*(unsigned int *)0x14ac4e8);
  d2_SetElementValue(v11,0x32,100,100 - (*(unsigned int *)0x77666c & 0xff));
  d2_SetValueGaugeFlags(v11,0x882);
  d2_SetValueGaugeLabel(v11,*(unsigned int *)0x14ac4d8);
  d2_SetElementValue(v12,0,2,*(unsigned int *)0x776668 >> 8 & 0xff);
  d2_SetValueGaugeFlags(v12,0x82);
  d2_SetValueGaugeLabel(v12,*(unsigned int *)0x14ac4dc);
  d2_SetValueGaugeStepLabels(v12,3,*(unsigned int *)0x14ac4e0,*(unsigned int *)0x14ac4e4,*(unsigned int *)0x14ac4e8);
  if (*(unsigned char *)0x774964)
    d2_SetSlotVisibility(v15,0);
  d2_SetForm(v4,3);
  d2_CreateButtonRow(*(unsigned int *)0x772514,0,&selection[0],3,*(unsigned int *)0x14ac5a8,*(unsigned int *)0x14ac5ac,(char *)0x6ad2cc);
  if (main_RunFrameLoop((void *)d2_ShowGraphicsOptions,v14)) {
    do {
      if ((*(unsigned int *)0x14ce8e0) || (*(unsigned char *)0x14cf950 == 1))
        *(unsigned int *)0x774654 = 1;
      if (d2_DialogButtonAction != -1) {
        if (*(unsigned int *)0x67d370 != selection[0]) {
          if (*(unsigned int *)0x67d370 != selection[1]) {
            if (*(unsigned int *)0x67d370 == selection[2]) {
              d2_SetFormVisibility(v4,0);
              d2_RunAdvancedGfxOptionsDialog();
              d2_SetFormVisibility(v4,1);
              d2_SetSlotVisibility(v7,0);
              if (*(unsigned char *)0x774964)
                d2_SetSlotVisibility(v15,0);
            }
          }
          else {
            *(unsigned int *)0x774654 = 1;
          }
        }
        else {
          v1 = 1;
          *(unsigned int *)0x774654 = 1;
        }
      }
    } while (main_RunFrameLoop((void *)d2_ShowGraphicsOptions,v14));
    if (v1) {
      v2 = d2_GetControlValue(v5);
      *(unsigned char *)0x776664 = v2;
      v2 = d2_GetControlValue(v6);
      *(unsigned char *)0x776665 = v2;
      v2 = d2_GetControlValue(v9);
      *(unsigned char *)0x776666 = v2;
      v2 = d2_GetControlValue(v10);
      *(unsigned char *)0x776667 = v2;
      v2 = d2_GetControlValue(v8);
      *(unsigned char *)0x776668 = v2;
      v2 = d2_GetControlValue(v12);
      *(unsigned char *)0x776669 = v2;
      v2 = d2_GetControlValue(v7);
      *(unsigned char *)0x77666a = v2;
      v3 = d2_GetControlValue(v11);
      *(unsigned char *)0x77666c = 100 - v3;
      io_SaveIniSettings();
      d3_ApplyGraphicsOptions();
    }
  }
  v14 = d2_GetControlValue(v15);
  if ((v14 != (*(unsigned int *)0x77534c & 0xff)) && (v1)) {
    v2 = d2_GetControlValue(v15);
    *(unsigned char *)0x77534c = v2;
    io_SaveIniSettings();
    *(unsigned int *)0x774958 = 0;
    *(unsigned int *)0x774954 = 1;
    *(unsigned int *)0x77495c = 1;
    io_LoadIniSettings();
  }
  d2_DestroyForm(v4);
}
