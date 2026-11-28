extern unsigned char gm_ActiveTownIndex;
#include <string.h>

unsigned char *__cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_RandomMod(int);
#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl cm_RequestTransferCurrencyNoKill(int, int, unsigned char, int);
void __cdecl io_FormatTextBuffer(void *, int, ...);
void __cdecl he_PostEntityMessage(int, int, void *, int, int, void *);

/* Coefficients follow native operands; helper organization is inferred. */
static __inline int RandomMoneyTransfer(void *request, double increment, double scale)
{
    int n;
    double d;
    char buf[0x100];
    unsigned char *entity;
    int amount;
    unsigned int len;

    entity = gm_LookupEntityRecordById(*(int *)request);
    if (entity == 0)
    {
        return 1;
    }
    n = gm_RandomMod(3) & 0xffff;
    d = (double)n + increment;
    n = gm_CalcPersonWealth(*(short *)entity);
    amount = (int)(((double)n * d) * scale);
    io_FormatTextBuffer(buf, *(unsigned short *)((char *)request + 4) + 0x12e7, amount);
    cm_RequestTransferCurrencyNoKill(*(int *)request, -1, gm_ActiveTownIndex, amount);
    len = strlen(buf);
    he_PostEntityMessage(*(int *)((char *)entity + 4), *(int *)((char *)entity + 4), buf, 0x100 < len, 0x603, 0);
    return 0;
}

/* ADDRESS: GOLDDE 0x004a4f70 */
int __cdecl gm_HandleEntityMsg06(void *request)
{
    return RandomMoneyTransfer(request, 1.0, 0.01);
}
int __cdecl gm_HandleEntityMsg08(void *request)
{
#ifdef REBREW_GOLD
    return RandomMoneyTransfer(request, 2.0, 0.01);
#else
    return RandomMoneyTransfer(request, 1.0, 0.01);
#endif
}
#ifdef REBREW_GOLD
int __cdecl gm_HandleEntityMsg0bGold(void *request)
{
    return RandomMoneyTransfer(request, 2.0, 1.0 / 120.0);
}
#endif
