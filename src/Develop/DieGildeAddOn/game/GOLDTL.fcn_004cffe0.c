extern int g_68b7a0;
int __cdecl fcn_00471e30(int);
char __cdecl fcn_00443e10(char*, int*);
int __cdecl fcn_00470820(int, int, char*);

/* ADDRESS: GOLDTL 0x004cffe0 */
void __cdecl fcn_004cffe0(int unused, void* object)
{
    int info[4];
    int cx;
    int cy;

    if (g_68b7a0 != -1) {
        fcn_00471e30(g_68b7a0);
        g_68b7a0 = -1;
    }
    if (fcn_00443e10((char*) *(int*)((char*) *(int*)((char*) object + 0x184) + 0x34), info) != 0) {
        cx = info[0] + 0x30;
        cy = info[1] - 0x1e;
        g_68b7a0 = fcn_00470820(cx, cy, (char*) 0x68b800);
    }
}
