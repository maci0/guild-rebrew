#include <stdarg.h>
#include "GOLDTL.fcn_00506e70_gconf.h"

/* ADDRESS: GOLDTL 0x00506e70 */
int __cdecl gm_HasEntityClassOrGrade(unsigned int idx, int count, ...)
{
    unsigned char *t;
    va_list p;
    int i;
    int found;

    found = 0;
    t = g_slot_table + (idx & 0xffff) * 0x21c;
    if (count <= -1)
        return found;
    va_start(p, count);
    for (i = 0; i < count; i++) {
        if (found)
            break;
        {
            int value;
            value = va_arg(p, int);
            if (t[0x166] == value)
                found = 1;
            else if (t[0x169] == value)
                found = 1;
        }
    }
    va_end(p);
    return found;
}
