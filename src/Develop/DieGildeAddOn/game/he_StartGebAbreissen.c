#include "client_types.h"

extern pos14_7f4c00 g_current_year;

char *__cdecl gm_StartFilteredEntitySearch(int arg_count, ...);
void __cdecl cm_RequestChangeBits(int id, int a2, int a3, int a4, int a5);

/* ADDRESS: GOLDTL 0x005641b0 */
void __cdecl he_StartGebAbreissen(void *event)
{
    char *entity;

    entity = gm_StartFilteredEntitySearch(1, 1, *(int *)((char *)event + 0xac));
    if (entity != 0)
        cm_RequestChangeBits(*(int *)(entity + 1), 0x5a, 2, 0x400, 0);
    *(pos14_7f4c00 *)((char *)event + 0x52) = g_current_year;
}
