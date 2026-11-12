#include <string.h>

void __cdecl io_FormatTextBuffer(void* out, int id, ...);
void __cdecl fcn_004fa5f0(void* buf, int a, char* b);

/* ADDRESS: GOLDTL 0x004f8570 */
int __cdecl fcn_004f8570(char* a1, int* a2)
{
    char buf[0x200];

    if (*a2 != 3 && *a2 != 1) {
        return 1;
    }
    if ((unsigned char) a1[0x166] != 0x1b && (unsigned char) a1[0x166] != 0xf &&
        (unsigned char) a1[0x166] != 0x15 && (unsigned char) a1[0x166] != 0xd) {
        return 1;
    }
    if (*a2 == 3 && a1[2] == 6) {
        memset(buf, 0, 0x200);
        io_FormatTextBuffer(buf, 0x1da2, (a1[9] ? 0x27b : 0x253) + (unsigned char) a1[0x166]);
        fcn_004fa5f0(buf, 0, (char*) 0x657c7);
        return 2;
    }
    if (*a2 == 1 && a1[2] == 6) {
        io_FormatTextBuffer(((char*) a2) + 0x14, 0x679060, 0x1da1);
    }
    return 2;
}
