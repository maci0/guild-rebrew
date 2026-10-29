#include "client_video_list.h"

/* ADDRESS: GOLDTL 0x0041f9b0 */
char* __cdecl fcn_0041f9b0(int id)
{
    char* p;
    char* result;

    p = (char*) g_6b6f84;
    result = 0;
    if (p != 0) {
        do {
            if (*(int*) (p + 8) == id)
                break;
            p = *(char**) (p + 4);
        } while (p != 0);
        result = p;
    }
    return result;
}
