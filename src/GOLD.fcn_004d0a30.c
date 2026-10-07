/* Gold scans 32 records at 0x00930600; TL scans its 768-slot world table. */
#include <string.h>

extern int g_67a370;
extern char g_930600[];
extern char* g_7e4260[32];

void __cdecl fcn_004da480(void)
{
    int self;
    int n;
    int i;

    self = g_67a370;
    memset(g_7e4260, 0, sizeof(g_7e4260));

    n = 0;
    for (i = 0; i < 32; i++) {
        if (n >= 31) {
            break;
        }
        if (*(char**) (g_930600 + i * 0x21c + 0x184) != 0 &&
            *(int*) (*(char**) (g_930600 + i * 0x21c + 0x184) + 0x88) == self) {
            g_7e4260[n] = g_930600 + i * 0x21c;
            n++;
        }
    }
}
