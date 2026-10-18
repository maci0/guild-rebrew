#include <string.h>

/* The record extent and argument roles are inferred from native accesses. */
/* ADDRESS: GOLDTL 0x00432410 */
int __cdecl fcn_00432410(void* object, const char* name)
{
    char* record;
    int count;
    int index;

    if (object && *(int*)((char*)object + 0x15c)) {
        count = *(int*)((char*)object + 0x144);
        index = 0;
        if (count > 0) {
            record = (char*)object + 0x40;
            do {
                if (!strcmp(name, record))
                    return index;
                ++index;
                record += 0x40;
            } while (index < count);
        }
    }
    return -1;
}
