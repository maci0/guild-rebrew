#include "client_types.h"

extern pos14_7f4c00 g_current_year;

char *__cdecl gm_StartFilteredEntitySearch(int arg_count, ...);
void __cdecl fcn_004c5420(int id, int a2, int a3, int a4, int a5);

/* ADDRESS: GOLDTL 0x005641b0 */
void __cdecl fcn_005641b0(void *a0)
{
    char *v;

    v = gm_StartFilteredEntitySearch(1, 1, *(int *)((char *)a0 + 0xac));
    if (v != 0)
        fcn_004c5420(*(int *)(v + 1), 0x5a, 2, 0x400, 0);
    *(pos14_7f4c00 *)((char *)a0 + 0x52) = g_current_year;
}
