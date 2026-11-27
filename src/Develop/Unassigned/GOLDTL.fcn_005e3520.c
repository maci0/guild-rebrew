extern int g_100f1dc;
int __cdecl fcn_00470820(int, int, char *);
void __cdecl fcn_00537320(int);
void __cdecl fcn_00471db0(int, int);
void __cdecl fcn_00471d80(int, int);
int __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
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
void __cdecl fcn_005e2660(void);
int __cdecl d2_GetControlValue(int);
void __cdecl fcn_005e12d0(void);
void __cdecl d3_ApplyGraphicsOptions(void);
void __cdecl fcn_005e1ca0(void);
void __cdecl d2_DestroyForm(int);

void __cdecl gm_ApplyGameSettings(void);
void __cdecl fcn_00527420(void);
void __cdecl fcn_00526db0(char *);
int __cdecl d2_GetHudThemeResourceId(void);
void __cdecl d2_EnterMenuScreen(void);

/* ADDRESS: GOLDTL 0x005e3520 */
void __cdecl fcn_005e3520(void)
{
  int v1, sel0, sel1, selection[2];
  unsigned int v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16;
  v1 = 0;
  v16 = *(unsigned int *)0x7e46ac & ~0x2000;
  v3 = fcn_00470820(0,0,(char *)0x6ad30c);
  fcn_00537320(v16);
  fcn_00471db0(v3,1);
  fcn_00471d80(v3,2);
  d2_SetForm(v3,0);
  fcn_005340f0(*(unsigned int *)0x772514);
  d2_SetOverlayAnimation(0,0);
  d2_SetForm(v3,2);
  io_AppendText((char *)0x1c59);
  d2_SetForm(v3,1);
  v4 = d2_GetWindowListItem(v3,1,0);
  v5 = d2_GetWindowListItem(v3,1,1);
  v6 = d2_GetWindowListItem(v3,1,2);
  v7 = d2_GetWindowListItem(v3,1,3);
  v8 = d2_GetWindowListItem(v3,1,4);
  v9 = d2_GetWindowListItem(v3,1,5);
  v10 = d2_GetWindowListItem(v3,1,6);
  v11 = d2_GetWindowListItem(v3,1,9);
  v12 = d2_GetWindowListItem(v3,1,10);
  v13 = d2_GetWindowListItem(v3,1,0xb);
  v14 = d2_GetWindowListItem(v3,1,0xc);
  d2_SetElementValue(v4,0,0xa0,*(unsigned int *)0x7766a8);
  d2_SetValueGaugeFlags(v4,0x882);
  d2_SetValueGaugeLabel(v4,*(unsigned int *)0x14ac578);
  d2_SetElementValue(v5,0,500,*(unsigned int *)0x7766b0);
  d2_SetValueGaugeFlags(v5,0x882);
  d2_SetValueGaugeLabel(v5,*(unsigned int *)0x14ac57c);
  d2_SetElementValue(v6,0,100,*(unsigned int *)0x7766b4);
  d2_SetValueGaugeFlags(v6,0x882);
  d2_SetValueGaugeLabel(v6,*(unsigned int *)0x14ac580);
  d2_SetElementValue(v7,0,100,*(unsigned int *)0x7766ac & 0xff);
  d2_SetValueGaugeFlags(v7,0x882);
  d2_SetValueGaugeLabel(v7,*(unsigned int *)0x14ac584);
  d2_SetElementValue(v8,0,1,*(unsigned int *)0x7766b8 & 0xff);
  d2_SetValueGaugeFlags(v8,0x82);
  d2_SetValueGaugeLabel(v8,*(unsigned int *)0x14ac588);
  d2_SetValueGaugeStepLabels(v8,2,*(unsigned int *)0x14ac50c,*(unsigned int *)0x14ac510);
  d2_SetSlotVisibility(v8,0);
  d2_SetElementValue(v9,0,1,*(unsigned char *)0x7766ba);
  d2_SetValueGaugeFlags(v9,0x82);
  d2_SetValueGaugeLabel(v9,*(unsigned int *)0x14ac58c);
  d2_SetValueGaugeStepLabels(v9,2,*(unsigned int *)0x14ac50c,*(unsigned int *)0x14ac510);
  d2_SetElementValue(v10,0,1,*(unsigned char *)0x7766bb);
  d2_SetValueGaugeFlags(v10,0x82);
  d2_SetValueGaugeLabel(v10,*(unsigned int *)0x14ac590);
  d2_SetValueGaugeStepLabels(v10,2,*(unsigned int *)0x14ac50c,*(unsigned int *)0x14ac510);
  d2_SetElementValue(v11,0,4,*(unsigned int *)0x776708 & 0xff);
  d2_SetValueGaugeFlags(v11,0x82);
  d2_SetValueGaugeLabel(v11,*(unsigned int *)0x14ac594);
  d2_SetValueGaugeStepLabels(v11,5,*(unsigned int *)0x14ac4f8,*(unsigned int *)0x14ac4fc,*(unsigned int *)0x14ac500,*(unsigned int *)0x14ac504,*(unsigned int *)0x14ac508);
  d2_SetElementValue(v12,0,1,*(unsigned char *)0x776709);
  d2_SetValueGaugeFlags(v12,0x82);
  d2_SetValueGaugeLabel(v12,*(unsigned int *)0x14ac598);
  d2_SetValueGaugeStepLabels(v12,2,*(unsigned int *)0x14ac50c,*(unsigned int *)0x14ac510);
  d2_SetSlotVisibility(v12,0);
  d2_SetElementValue(v14,0,1,*(unsigned int *)0x77670c & 0xff);
  d2_SetValueGaugeFlags(v14,0x82);
  d2_SetValueGaugeLabel(v14,*(unsigned int *)0x14ac5a4);
  d2_SetValueGaugeStepLabels(v14,2,*(unsigned int *)0x14ac50c,*(unsigned int *)0x14ac510);
  d2_SetElementValue(v13,0,1,*(unsigned char *)0x77670b);
  d2_SetValueGaugeFlags(v13,0x82);
  d2_SetValueGaugeLabel(v13,*(unsigned int *)0x14ac5a0);
  d2_SetValueGaugeStepLabels(v13,2,*(unsigned int *)0x14ac50c,*(unsigned int *)0x14ac510);
  d2_SetForm(v3,3);
  d2_CreateButtonRow(*(unsigned int *)0x772514,0,&selection[0],2,*(unsigned int *)0x14ac5a8,*(unsigned int *)0x14ac5ac);
  sel0 = selection[0];
  sel1 = selection[1];
  if (main_RunFrameLoop((void *)fcn_005e3520,v16)) {
    do {
      if ((*(unsigned int *)0x14ce8e0) || (*(unsigned char *)0x14cf950 == 1))
        *(unsigned int *)0x774654 = 1;
      if (g_100f1dc != -1) {
        v15 = *(unsigned int *)0x67d370;
        if (v15 == sel0) {
          v1 = 1;
          *(unsigned int *)0x774654 = 1;
        }
        else if (v15 == sel1) {
          *(unsigned int *)0x774654 = 1;
        }
      }
    } while (main_RunFrameLoop((void *)fcn_005e3520,v16));
    if (v1) {
      *(unsigned int *)0x7766a8 = d2_GetControlValue(v4);
      *(unsigned char *)0x7766ac = (unsigned char)d2_GetControlValue(v7);
      *(unsigned int *)0x7766b0 = d2_GetControlValue(v5);
      *(int *)0x7766b4 = d2_GetControlValue(v6);
      *(unsigned char *)0x7766b8 = 0;
      *(unsigned char *)0x7766ba = (unsigned char)d2_GetControlValue(v9);
      *(unsigned char *)0x7766bb = (unsigned char)d2_GetControlValue(v10);
      *(unsigned char *)0x776709 = (unsigned char)d2_GetControlValue(v12);
      *(unsigned char *)0x77670b = (unsigned char)d2_GetControlValue(v13);
      *(unsigned char *)0x77670c = (unsigned char)d2_GetControlValue(v14);
      v16 = d2_GetControlValue(v11);
      if (v16 != (*(unsigned int *)0x776708 & 0xff)) {
        *(unsigned char *)0x776708 = (unsigned char)d2_GetControlValue(v11);
        d2_SetFormVisibility(v3,0);
        if (*(unsigned char *)0x774964) {
          fcn_00527420();
          fcn_00526db0((char *)d2_GetHudThemeResourceId());
          d2_EnterMenuScreen();
          *(unsigned int *)0x774714 = 1;
        }
      }
      fcn_005e12d0();
      gm_ApplyGameSettings();
    }
  }
  d2_DestroyForm(v3);
}
