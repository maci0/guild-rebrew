#include <stdio.h>
#include "Develop/Units/m_alloc/m_alloc.h"
extern int g_0063319c;
extern int* g_6b7d78;
char* __cdecl fcn_00422760(int, int*);
void __cdecl fcn_004237f0(void*, int);
#define I32(p) (*(int*)(p))
/* ADDRESS: GOLD 0x00426ba0 */
int __cdecl fcn_00426ba0(char* target)
{
    char* previous;
    char* bank;
    char* voice;
    char* row;
    char* name;
    int i;
    int cursor;
    int rc;
    rc = 0;
    previous = 0;
    if (!g_0063319c)
        return 1;
    if (!I32(0x633194) || !target) {
        rc = -1;
    } else {
        bank = (char*)g_6b7d78;
        while (bank) {
            if (bank == target)
                break;
            previous = bank;
            bank = *(char**)(bank + 0x13c);
        }
        if (bank && --I32(bank + 0x140) <= 0) {
            if (previous)
                *(char**)(previous + 0x13c) = *(char**)(bank + 0x13c);
            else
                g_6b7d78 = *(int**)(bank + 0x13c);
            name = target + 0x32;
            sprintf((char*)0x1460920, "Unloading Samplebank %s ... MemUsed before unloading %d bytes.", name, I32(0x633194));
            for (i = 0; i < I32(bank + 0x134); i++) {
                row = *(char**)(bank + 0x138) + i * 0x40;
                if (*(char**)(row + 0x38)) {
                    cursor = 0;
                    voice = fcn_00422760((int)row, &cursor);
                    while (voice) {
                        fcn_004237f0(voice, 0);
                        I32(voice + 4) = 0;
                        cursor++;
                        voice = fcn_00422760(I32(bank + 0x138) + i * 0x40, &cursor);
                    }
                    row = *(char**)(bank + 0x138) + i * 0x40;
                    if (row[0x36] == 1)
                        I32(0x633194) += -12 - I32(*(char**)(row + 0x38) + 4);
                    else
                        I32(0x633194) += -12 - I32(*(char**)(row + 0x38) + 8);
                    m_FreeTracked(*(void**)(*(char**)(bank + 0x138) + i * 0x40 + 0x38));
                    I32(*(char**)(bank + 0x138) + i * 0x40 + 0x38) = 0;
                    I32(*(char**)(bank + 0x138) + i * 0x40 + 0x38) = 0;
                }
            }
            I32(0x633194) += -0x144 - I32(bank + 0x134) * 0x40;
            sprintf((char*)0x1460920, "Finished unloading Samplebank %s ... MemUsed after unloading %d bytes.", name, I32(0x633194));
            m_FreeTracked(bank);
        }
    }
    return rc;
}
