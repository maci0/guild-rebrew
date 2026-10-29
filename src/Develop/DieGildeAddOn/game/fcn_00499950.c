#include <string.h>
#pragma intrinsic(memset)

int __cdecl fcn_00508e40(int id);
int __cdecl fcn_004faaf0(int e);
int __cdecl fcn_004c4eb0(char* name);
int __cdecl fcn_004c5530(char* msg);
int __cdecl fcn_004c4ef0(char* name);

/* ADDRESS: GOLDTL 0x00499950 */
int __cdecl fcn_00499950(int a, char* b)
{
    char buf[0xf8];
    int e;
    int v;

    if (*(char*) b != 7)
        return 0;
    e = (int) fcn_00508e40(*(int*) (b + 4));
    if (e == 0)
        return 0;
    memset(buf, 0, sizeof(buf));
    buf[4] = 0x1a;
    v = *(int*) (b + 0x10);
    *(int*) (buf + 8) = *(int*) (a + 4);
    *(int*) (buf + 0xc) =
        (*(int*) (a + 0x170) != 0) ? *(int*) (*(int*) (a + 0x170) + 1) : -1;
    *(char*) (buf + 0x36) = 1;
    *(int*) (buf + 0x84) = v;
    *(int*) (buf + 0x60) = *(int*) (e + 4);
    *(float*) 0x1009374 = *(float*) 0x1009354 * *(float*) (b + 0x14);
    *(float*) 0x100937c = *(float*) 0x100935c * *(float*) (b + 0x14);
    *(float*) 0x1009384 = *(float*) 0x1009364 * *(float*) (b + 0x14);
    *(float*) 0x100938c = *(float*) 0x100936c * *(float*) (b + 0x14);
    *(int*) (buf + 0x58) = fcn_004faaf0(e);
    fcn_004c4eb0("pruegel");
    fcn_004c5530(buf);
    fcn_004c4ef0("pruegel");
    return 0x18;
}
