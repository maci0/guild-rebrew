extern int g_7746a0, g_7746d8, g_14b59e4, g_14b5b38;
void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void (__cdecl *)(void *), int);
int __cdecl fcn_005338d0(char *, int, int);
void __cdecl fcn_005e53b0(void *);
void __cdecl fcn_005e6360(void *);
/* ADDRESS: GOLDTL 0x005e6840 */
void __cdecl fcn_005e6840(void *a) {
 int x = 0, y = 0;
 fcn_005338a0();
 while (fcn_005373e0(fcn_005e6840, 0x67fff)) {
  if (g_7746d8 & 0x200) {
   x = fcn_005338d0("contact_BLUTRACHE", g_14b59e4, 0x16);
   y = fcn_005338d0("contact_EHRERBIETUNG", g_14b5b38, 0x16);
  }
  if (g_7746a0) {
   if (g_7746a0 == x) fcn_005e53b0(a);
   else if (g_7746a0 == y) fcn_005e6360(a);
  }
 }
}
