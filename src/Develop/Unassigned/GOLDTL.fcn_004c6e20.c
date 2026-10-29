#include <string.h>

int __cdecl fcn_004be340(char *p);
int __cdecl fcn_004c4df0(unsigned short n, void *src);
int __cdecl fcn_004c4330(void *buf);

/* ADDRESS: GOLDTL 0x004c6e20 */
void __cdecl fcn_004c6e20(char *a0, char *a1)
{
    char buf[0x9c];
    char items[0x200];
    int count;
    int i;
    char *p;
    char *dst;
    char *src;

    p = a1;
    count = fcn_004be340(p);
    buf[0] = 0x68;
    *(int *)(buf + 0x10) = *(int *)(a0 + 2);
    *(int *)(buf + 0x14) = count;
    if (count > 0) {
        dst = items;
        for (i = count; i > 0; i--) {
            src = p;
            p = *(char **)(p + 0x3c);
            memcpy(dst, src, 0x40);
            dst += 0x40;
        }
    }
    fcn_004c4df0((unsigned short)(count << 6), items);
    fcn_004c4330(buf);
}
