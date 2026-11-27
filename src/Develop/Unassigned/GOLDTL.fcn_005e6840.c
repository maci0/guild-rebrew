extern int g_7746a0, g_7746d8, g_14b59e4, g_14b5b38;
void __cdecl fcn_005338a0(void);
int __cdecl main_RunFrameLoop(void (__cdecl *)(void *), int);
int __cdecl RegisterStatusText(char *, int, int);
void __cdecl d2_RunZigeunerBlutracheDialog(void *);
void __cdecl d2_RunEhrerbietungDialog(void *);
/* ADDRESS: GOLDTL 0x005e6840 */
void __cdecl d2_RunContactMenu(void *a) {
 int x = 0, y = 0;
 fcn_005338a0();
 while (main_RunFrameLoop(d2_RunContactMenu, 0x67fff)) {
  if (g_7746d8 & 0x200) {
   x = RegisterStatusText("contact_BLUTRACHE", g_14b59e4, 0x16);
   y = RegisterStatusText("contact_EHRERBIETUNG", g_14b5b38, 0x16);
  }
  if (g_7746a0) {
   if (g_7746a0 == x) d2_RunZigeunerBlutracheDialog(a);
   else if (g_7746a0 == y) d2_RunEhrerbietungDialog(a);
  }
 }
}
