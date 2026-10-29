#include <string.h>

struct rec9c760 {
    unsigned char tag;
    int a;
    int b;
    int d[3];
};

extern int __cdecl fcn_004a9b20(int, int, int, void *, void *);

/* ADDRESS: GOLDTL 0x0049c760 */
int __cdecl fcn_0049c760(int a, int b, int c, int *o1, int *o2)
{
    struct rec9c760 v1;
    struct rec9c760 v2;

    if (a != 0)
        return 0;
    if (c != 0)
        return 0;
    v1.tag = 0;
    v1.a = 0;
    v1.b = 0;
    if (fcn_004a9b20(0, b, 0, &v1, &v2) == 0)
        return 0;
    memcpy(o1, &v1, sizeof(v1));
    memcpy(o2, &v2, sizeof(v2));
    return 0x27;
}
