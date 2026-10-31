extern unsigned char g_773d75;
#include <string.h>

int __cdecl fcn_0042e410(int);
unsigned char *__cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_0050b750(int, unsigned char);
int __cdecl fcn_00508540(int *);
int __cdecl fcn_005c6270(void *, int);
void __cdecl io_FormatTextBuffer(void *, int, ...);
void __cdecl fcn_00545d40(int, int, void *, int, int, void *);
int __cdecl fcn_004c51a0(int, int, unsigned char, int);

/* ADDRESS: GOLDTL 0x004bb720 */
unsigned int __cdecl fcn_004bb720(void *a0)
{
    char buf[1024];
    unsigned char *p;
    int h;
    unsigned int len;

    h = fcn_0050b750((fcn_0042e410(5) & 0xffff) + 1, g_773d75);
    p = gm_LookupEntityRecordById(*(int *)a0);
    if (p == 0)
    {
        return 1;
    }
    if (fcn_005c6270(p, 0x290) != 0)
    {
        return 0x400;
    }
    if (fcn_00508540((int *)p) == 0)
    {
        return 0x400;
    }
    io_FormatTextBuffer(buf, *(unsigned short *)((char *)a0 + 4) + 0x12e7, h);
    len = strlen(buf);
    fcn_00545d40(*(int *)((char *)p + 4), *(int *)((char *)p + 4), buf, 0x100 < len, 0x603, 0);
    fcn_004c51a0(-1, *(int *)a0, g_773d75, h);
    return 0;
}
