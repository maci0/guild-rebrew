#include <string.h>

struct rec9c760 {
    unsigned char tag;
    int a;
    int b;
    int d[3];
};

extern int __cdecl ai_SelectPrivilegeAction(int, int, int, void *, void *);

/* ADDRESS: GOLDTL 0x0049c760 */
int __cdecl ai_StartUseAmt(int a, int b, int c, int *o1, int *o2)
{
    struct rec9c760 first;
    struct rec9c760 second;

    if (a != 0)
        return 0;
    if (c != 0)
        return 0;
    first.tag = 0;
    first.a = 0;
    first.b = 0;
    if (ai_SelectPrivilegeAction(0, b, 0, &first, &second) == 0)
        return 0;
    memcpy(o1, &first, sizeof(first));
    memcpy(o2, &second, sizeof(second));
    return 0x27;
}
