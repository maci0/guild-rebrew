extern int sv_ClickedObjekt, d2_SelectedEntityUiFlags, g_14b59e4, g_14b5b38;
void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void (__cdecl *)(void *), int);
int __cdecl RegisterStatusText(char *, int, int);
void __cdecl d2_RunZigeunerBlutracheDialog(void *);
void __cdecl d2_RunEhrerbietungDialog(void *);
/* ADDRESS: GOLDTL 0x005e6840 */
/* ADDRESS: GOLDDE 0x005c7b00 */
void __cdecl d2_RunContactMenu(void *a) {
 int x = 0, y = 0;
 d2_ClearStatusTextSlots();
 while (main_RunFrameLoop(d2_RunContactMenu, 0x67fff)) {
  if (d2_SelectedEntityUiFlags & 0x200) {
   x = RegisterStatusText("contact_BLUTRACHE", g_14b59e4, 0x16);
   y = RegisterStatusText("contact_EHRERBIETUNG", g_14b5b38, 0x16);
  }
  if (sv_ClickedObjekt) {
   if (sv_ClickedObjekt == x) d2_RunZigeunerBlutracheDialog(a);
   else if (sv_ClickedObjekt == y) d2_RunEhrerbietungDialog(a);
  }
 }
}
