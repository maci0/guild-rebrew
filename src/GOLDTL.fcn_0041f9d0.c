#include "client_video_list.h"

/* ADDRESS: GOLD 0x00423740 */
/* ADDRESS: GOLDTL 0x0041f9d0 */
char* __cdecl fcn_0041f9d0(void* hwnd)
{
    char* p;
    char* result;

    p = (char*) g_6b6f84;
    result = 0;
    if (p != 0) {
        do {
            if (*(void**) (p + 0x114) == hwnd)
                break;
            p = *(char**) (p + 4);
        } while (p != 0);
        result = p;
    }
    return result;
}
