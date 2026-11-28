#include "Develop/client_types.h"

extern float g_665bf8; /* 1020.0 */
extern float g_665bfc; /* 1380.0 */
extern float g_665c00; /* 360.0 */

int __cdecl gm_CompareGameTime(int* a, int* b);
int __cdecl sim_SetSyncParams(int* a, int mode, int b, int c);

/* ADDRESS: GOLDTL 0x0050cad0 */
int __cdecl gm_CalcWorkMinutesBetween(int* startTime, int* endTime)
{
    pos14_7f4c00 cur;
    int v3;
    int minutes;
    int v5;
    int v6;
    int v7;
    float dayMinutes;
    if (gm_CompareGameTime(startTime, endTime) > 0) {
        return 0;
    }
    cur = *(pos14_7f4c00*) startTime;
    v3 = cur.a;
    v7 = endTime[0];
    if (v3 < v7) {
        dayMinutes = (float) (*(unsigned short*) ((char*) &cur + 4) * 60 + *(int*) ((char*) &cur + 6));
        if (g_665c00 > dayMinutes) goto clamp1;
        if (dayMinutes < g_665bfc) {
        clamp1:
            dayMinutes = (g_665c00 > dayMinutes ? g_665c00 : dayMinutes);
        } else {
            dayMinutes = g_665bfc;
        }
        v5 = (int) dayMinutes;
        minutes = (int) (g_665bfc - (float) v5);
        cur.a = v3 + 1;
        sim_SetSyncParams((int*) &cur, 6, 0, 0);
        v3 = cur.a;
    } else {
        minutes = 0;
    }
    if (v3 < v7) {
        v7 -= v3;
        do {
            dayMinutes = (float) minutes + g_665bf8;
            minutes = (int) dayMinutes;
        } while (--v7);
    }
    dayMinutes = (float) (*(unsigned short*) ((char*) endTime + 4) * 60 + *(int*) ((char*) endTime + 6));
    if (g_665c00 > dayMinutes) goto clamp2;
    if (dayMinutes < g_665bfc) {
    clamp2:
        dayMinutes = (g_665c00 > dayMinutes ? g_665c00 : dayMinutes);
    } else {
        dayMinutes = g_665bfc;
    }
    v5 = (int) dayMinutes;
    dayMinutes = (float) (*(unsigned short*) ((char*) &cur + 4) * 60 + *(int*) ((char*) &cur + 6));
    if (g_665c00 > dayMinutes) goto clamp3;
    if (dayMinutes < g_665bfc) {
    clamp3:
        dayMinutes = (g_665c00 > dayMinutes ? g_665c00 : dayMinutes);
    } else {
        dayMinutes = g_665bfc;
    }
    v6 = (int) dayMinutes;
    return (minutes - v6) + v5;
}
