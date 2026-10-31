#include "client_video_list.h"

/* ADDRESS: GOLDTL 0x0041f9d0 */
char* __cdecl FindVideoByWindow(void* hwnd)
{
    char* node;
    char* result;

    node = (char*) g_6b6f84;
    result = 0;
    if (node != 0) {
        do {
            if (*(void**) (node + 0x114) == hwnd)
                break;
            node = *(char**) (node + 4);
        } while (node != 0);
        result = node;
    }
    return result;
}
