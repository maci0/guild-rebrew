extern unsigned char g_773d75;
#include <string.h>

unsigned char *__cdecl fcn_00508e40(int);
int __cdecl gm_RandomMod(int);
#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl fcn_004c51a0(int, int, unsigned char, int);
void __cdecl fcn_0051af00(void *, int, ...);
void __cdecl fcn_00545d40(int, int, void *, int, int, void *);

/* Coefficients follow native operands; helper organization is inferred. */
static __inline int RandomMoneyTransfer(void *a1, double increment, double scale)
{
    int n;
    double d;
    char buf[0x100];
    unsigned char *p;
    int r;
    unsigned int len;

    p = fcn_00508e40(*(int *)a1);
    if (p == 0)
    {
        return 1;
    }
    n = gm_RandomMod(3) & 0xffff;
    d = (double)n + increment;
    n = gm_WalkEntityChain(*(short *)p);
    r = (int)(((double)n * d) * scale);
    fcn_0051af00(buf, *(unsigned short *)((char *)a1 + 4) + 0x12e7, r);
    fcn_004c51a0(*(int *)a1, -1, g_773d75, r);
    len = strlen(buf);
    fcn_00545d40(*(int *)((char *)p + 4), *(int *)((char *)p + 4), buf, 0x100 < len, 0x603, 0);
    return 0;
}

int __cdecl fcn_004b6ce0(void *a1)
{
    return RandomMoneyTransfer(a1, 1.0, 0.01);
}
int __cdecl fcn_004b6f00(void *a1)
{
#ifdef REBREW_GOLD
    return RandomMoneyTransfer(a1, 2.0, 0.01);
#else
    return RandomMoneyTransfer(a1, 1.0, 0.01);
#endif
}
#ifdef REBREW_GOLD
int __cdecl fcn_004b6ef0(void *a1)
{
    return RandomMoneyTransfer(a1, 2.0, 1.0 / 120.0);
}
#endif
