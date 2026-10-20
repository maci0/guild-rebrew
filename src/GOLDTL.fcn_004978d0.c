#include <string.h>

extern unsigned char g_773d75;
extern char g_67e330[];

short* __cdecl gm_GetEntityTableEntry(char* entity);
void __cdecl fcn_004c4eb0(char* s);
void __cdecl fcn_004c4ef0(char* s);
void __cdecl fcn_004c5150(int a, int b, char c, int n);
void __cdecl fcn_004c5530(char* msg);

/* ADDRESS: GOLDTL 0x004978d0 */
int __cdecl fcn_004978d0(char* a1, char* a2, char* a3)
{
    char msg[0xf8];
    char* e;

    memset(msg, 0, sizeof(msg));
    msg[4] = 0x1c;
    *(int*) (msg + 8) = *(int*) (a1 + 4);
    *(int*) (msg + 0xc) = -1;
    msg[0x36] = 1;
    *(int*) (msg + 0x58) = *(int*) (a2 + 4);
    *(int*) (msg + 0x5c) = *(int*) (a2 + 0x10);
    fcn_004c4eb0(g_67e330);
    fcn_004c5150(-1, *(int*) (a3 + 4), (char) g_773d75,
        (int) (*(float*) (a2 + 0x14)));
    fcn_004c5530(msg);
    fcn_004c4ef0(g_67e330);
    e = (char*) gm_GetEntityTableEntry(a1);
    if (e != 0) {
        *(int*) (e + 0x44) = *(int*) (e + 0x44) + *(float*) (a2 + 0x14);
    }
    return 0xf;
}
