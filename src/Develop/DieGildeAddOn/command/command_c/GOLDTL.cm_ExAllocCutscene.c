#include <string.h>

extern unsigned char g_aed340[];

extern unsigned char g_7747b0;
extern unsigned short g_774970;
extern char g_7f4ca4[];
extern int g_14cbca0;
int g_699368 = 1;

char* __cdecl fcn_004e6ae0(void* src);

/* ADDRESS: GOLDTL 0x004c9e20 */
int __cdecl cm_ExAllocCutscene(int* obj, char* result)
{
    unsigned int payload[69];
    char* entry;
    int ret;
    int idx;

    ret = 0;
    memcpy(payload, g_aed340, sizeof(payload));
    if (g_14cbca0 != -1)
        g_699368 = *(int*) ((char*) obj + 0x10);
    entry = fcn_004e6ae0(payload);
    if (entry != 0) {
        if (g_7747b0 & 4)
            *(unsigned char*) (entry + 0x26) |= 0x80;
        *(int*) (entry + 0x78) = *(int*) ((char*) obj + 0x14);
        if (result != 0) {
            result[0] = 1;
            result[1] = 9;
            *(char**) (result + 6) = entry;
        }
    } else {
        ret = 1;
    }
    if (*(unsigned char*) (entry + 8) == 5) {
        idx = (unsigned short) g_774970;
        if (*(int*) (g_7f4ca4 + idx * 0x21c) != *(int*) (entry + 0x34)) {
            if (!(g_7747b0 & 4))
                *(unsigned char*) (entry + 0x26) &= 0x7f;
        }
    }
    g_699368++;
    return ret;
}
