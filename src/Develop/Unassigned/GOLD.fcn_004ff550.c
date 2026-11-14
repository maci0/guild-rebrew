#include "Develop/DieGildeAddOn/game/game_data.h"
void __cdecl fcn_00500d60(int*, char*);
void __cdecl fcn_004fec10(int);
void __cdecl fcn_00501fe0(int);
int __cdecl fcn_004ff8c0(int, int);
int __cdecl fcn_004ff950(int, int);
float __cdecl fcn_004ffa10(int, int);
/* DATA TODO: native .data virtual-tail city table0x7e3fa0 stride0x2f4,
 * city outputs0x7d6a60 stride0x2a90, item records through0x2a90;
 * 0x6f1bc5 current city byte, 0x1460ae0 state int. */
/* ADDRESS: GOLD 0x004ff550 */
void __cdecl fcn_004ff550(int city, int* date)
{
    char calendar[10];
    int year, month, tableOffset, outputOffset, count, index, lo, hi, value, previousYear, i;
    int *p, *out;
    unsigned char kind;
    fcn_00500d60(date, calendar);
    year = *(short*) (calendar + 2);
    month = calendar[1];
    tableOffset = city * 0x2f4;
    outputOffset = city * 0x2a90;
    count = 0;
    p = (int*) (tableOffset + 0x7e3fa4);
    do {
        if (p[0] >= p[2]) break;
        ++count;
        p += 2;
    } while (count < 9);
    index = 0;
    p = (int*) (tableOffset + 0x7e3fa4);
    while (index < count) {
        if (*p >= year) break;
        ++index;
        p += 2;
    }
    out = (int*) (outputOffset + 0x7d6a60);
    if (index >= count - 1) {
        *out = *(int*) (tableOffset + 0x7e3fa0 + count * 8);
    } else {
        hi = *(int*) (tableOffset + 0x7e3fa4 + index * 8);
        if (year == hi) {
            value = *(int*) (tableOffset + 0x7e3fa8 + index * 8);
            *out = ((month + (year - hi) * 12) *
                (*(int*) (tableOffset + 0x7e3fb0 + index * 8) - value)) /
                ((*(int*) (tableOffset + 0x7e3fac + index * 8) - hi) * 12) + value;
        } else if (index > 0) {
            lo = *(int*) (tableOffset + 0x7e3fa0 + index * 8);
            previousYear = *(int*) (tableOffset + 0x7e3f9c + index * 8);
            *out = ((month + (year - previousYear) * 12) *
                (*(int*) (tableOffset + 0x7e3fa8 + index * 8) - lo)) /
                ((hi - previousYear) * 12) + lo;
        } else {
            *out = *(int*) (tableOffset + 0x7e3fa8);
        }
    }
    *out = out[1] * *out / 1000;
    count = 0;
    p = (int*) (tableOffset + 0x7e3ff4);
    do {
        if (p[0] >= p[2]) break;
        ++count;
        p += 2;
    } while (count < 9);
    index = 0;
    p = (int*) (tableOffset + 0x7e3ff4);
    while (index < count) {
        if (*p >= year) break;
        ++index;
        p += 2;
    }
    out = (int*) (outputOffset + 0x7d6a68);
    if (index >= count - 1) {
        *out = *(int*) (tableOffset + 0x7e3ff0 + count * 8);
    } else {
        hi = *(int*) (tableOffset + 0x7e3ff4 + index * 8);
        if (year == hi) {
            value = *(int*) (tableOffset + 0x7e3ff8 + index * 8);
            *out = ((month + (year - hi) * 12) *
                (*(int*) (tableOffset + 0x7e4000 + index * 8) - value)) /
                ((*(int*) (tableOffset + 0x7e3ffc + index * 8) - hi) * 12) + value;
        } else if (index > 0) {
            lo = *(int*) (tableOffset + 0x7e3ff0 + index * 8);
            previousYear = *(int*) (tableOffset + 0x7e3fec + index * 8);
            *out = ((month + (year - previousYear) * 12) *
                (*(int*) (tableOffset + 0x7e3ff8 + index * 8) - lo)) /
                ((hi - previousYear) * 12) + lo;
        } else {
            *out = *(int*) (tableOffset + 0x7e3ff8);
        }
    }
    *out = out[1] * *out / 1000;
    p = (int*) (outputOffset + 0x7d6aa0);
    for (i = 0; i < 0x55; ++i, p += 0x20) {
        kind = (((unsigned char*) g_item_def_table))[*(unsigned short*) (p - 12) * 0x41];
        if (kind != 0x17 && kind != 0x25) {
            value = fcn_004ff8c0(city, i);
            *(float*) (p - 4) = (float) (((double) value - *(float*) (p - 4)) * 0.5 + *(float*) (p - 4));
        }
        if (city == *(unsigned char*) 0x6f1bc5) p[1] = fcn_004ff950(city, i);
        else p[1] = p[0];
        *(float*) (p + 2) = fcn_004ffa10(city, i);
        if (*(char*) (p + 4)) *(float*) (p - 4) = (float) p[1];
        p[-8] = 0;
        p[-7] = 0;
        p[-5] = 0;
        p[-6] = 0;
    }
    if (*(int*) 0x1460ae0 == -1) {
        fcn_004fec10(city);
        fcn_00501fe0(city);
    }
}
