#include <string.h>

int __cdecl fcn_0046b520(char* s, int v);
int __cdecl fcn_00468df0(int x, int a2, int a3, char* buf, int a5);
int __cdecl fcn_00469110(int id, int max);

/* ADDRESS: GOLDTL 0x00533a60 */
int __cdecl fcn_00533a60(int a1, int a2, int* out, int count, ...)
{
    char buf[32][0x40];
    char* entity;
    char** p;
    int max;
    int i;
    int q;
    int span;
    int start;
    int step;
    int id;

    entity = (char*) 0x1015f40 + a1 * 0x3cc;
    p = &count;
    max = 0;
    if (count > 0) {
        for (i = 0; i < count; i++) {
            strcpy(buf[i], *++p);
            id = fcn_0046b520(buf[i], *(int*) (entity + 0x28c));
            if (id + 0x20 > max) {
                max = id + 0x20;
            }
        }
    }
    q = *(int*) (entity + 0xc) / (count + 1);
    if (max > q) {
        step = max + 8;
        span = step * count;
        if (span > *(int*) (entity + 0xc)) {
            start = (span - *(int*) (entity + 0xc)) / 2 + step / 2;
        } else {
            start = (*(int*) (entity + 0xc) - span) / 2 + step / 2;
        }
    } else {
        step = q;
        start = q;
    }
    start -= max / 2;
    if (count > 0) {
        for (i = 0; i < count; i++) {
            id = fcn_00468df0(start, a2, 0xbf, buf[i], a1);
            out[i] = id;
            *(int*) ((*(char**) 0x1015ea0) + id * 0x2f4 + 0x84) = 0x53;
            fcn_00469110(id, max);
            start += step;
        }
    }
    return 0;
}
