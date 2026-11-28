extern char str_fmt_s[];
#include <string.h>

void __cdecl io_FormatTextBuffer(void* out, int id, ...);
void __cdecl d2_ShowPrivilegMessage(void* buf, int a, char* b);

/* ADDRESS: GOLDTL 0x004f8570 */
/* ADDRESS: GOLDDE 0x004e4350 */
int __cdecl fcn_004f8570(char* entity, int* request)
{
    char buf[0x200];

    if (*request != 3 && *request != 1) {
        return 1;
    }
    if ((unsigned char) entity[0x166] != 0x1b && (unsigned char) entity[0x166] != 0xf &&
        (unsigned char) entity[0x166] != 0x15 && (unsigned char) entity[0x166] != 0xd) {
        return 1;
    }
    if (*request == 3 && entity[2] == 6) {
        memset(buf, 0, 0x200);
        io_FormatTextBuffer(buf, 0x1da2, (entity[9] ? 0x27b : 0x253) + (unsigned char) entity[0x166]);
        d2_ShowPrivilegMessage(buf, 0, (char*) 0x657c7);
        return 2;
    }
    if (*request == 1 && entity[2] == 6) {
        io_FormatTextBuffer(((char*) request) + 0x14, (int) &str_fmt_s, 0x1da1);
    }
    return 2;
}
