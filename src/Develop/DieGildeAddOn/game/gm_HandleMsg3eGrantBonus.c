extern unsigned char g_773d75;
#include <string.h>

int __cdecl fcn_0042e410(int);
unsigned char *__cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_0050b750(int, unsigned char);
int __cdecl gm_ApplyRandomEntityDefect(int *);
int __cdecl gm_HasActiveSpecialObject(void *, int);
void __cdecl io_FormatTextBuffer(void *, int, ...);
void __cdecl he_PostEntityMessage(int, int, void *, int, int, void *);
int __cdecl cm_RequestTransferCurrencyNoKill(int, int, unsigned char, int);

/* ADDRESS: GOLDTL 0x004bb720 */
unsigned int __cdecl gm_HandleMsg3eGrantBonus(void *request)
{
    char buf[1024];
    unsigned char *entity;
    int h;
    unsigned int len;

    h = fcn_0050b750((fcn_0042e410(5) & 0xffff) + 1, g_773d75);
    entity = gm_LookupEntityRecordById(*(int *)request);
    if (entity == 0)
    {
        return 1;
    }
    if (gm_HasActiveSpecialObject(entity, 0x290) != 0)
    {
        return 0x400;
    }
    if (gm_ApplyRandomEntityDefect((int *)entity) == 0)
    {
        return 0x400;
    }
    io_FormatTextBuffer(buf, *(unsigned short *)((char *)request + 4) + 0x12e7, h);
    len = strlen(buf);
    he_PostEntityMessage(*(int *)((char *)entity + 4), *(int *)((char *)entity + 4), buf, 0x100 < len, 0x603, 0);
    cm_RequestTransferCurrencyNoKill(-1, *(int *)request, g_773d75, h);
    return 0;
}
