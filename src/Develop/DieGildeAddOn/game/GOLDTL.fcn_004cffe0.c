extern int g_68b7a0;
int __cdecl d2_DestroyForm(int);
char __cdecl d3_GetObjectScreenRect(char*, int*);
int __cdecl d2_LoadForm(int, int, char*);

/* ADDRESS: GOLDTL 0x004cffe0 */
void __cdecl d2_ShowCombatCommandForm(int unused, void* object)
{
    int info[4];
    int cx;
    int cy;

    if (g_68b7a0 != -1) {
        d2_DestroyForm(g_68b7a0);
        g_68b7a0 = -1;
    }
    if (d3_GetObjectScreenRect((char*) *(int*)((char*) *(int*)((char*) object + 0x184) + 0x34), info) != 0) {
        cx = info[0] + 0x30;
        cy = info[1] - 0x1e;
        g_68b7a0 = d2_LoadForm(cx, cy, (char*) 0x68b800);
    }
}
