#include "client_video_list.h"

/* ADDRESS: GOLDTL 0x0041f9b0 */
char* __cdecl FindVideoById(int id)
{
    char* node;
    char* result;

    node = (char*) g_6b6f84;
    result = 0;
    if (node != 0) {
        do {
            if (*(int*) (node + 8) == id)
                break;
            node = *(char**) (node + 4);
        } while (node != 0);
        result = node;
    }
    return result;
}
