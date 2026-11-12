#include "client_scene_resources.h"
void __cdecl m_FreeTracked(void*);

/* ADDRESS: GOLD 0x0043f270 */
void __cdecl fcn_0043f270(void)
{
    unsigned int i;
    unsigned int count;
    int offset;
    char* table;
    char* record;

    count = *(unsigned int*) 0x633744;
    table = *(char**) 0x63374c;
    i = 0;
    offset = 0;
    while (i < count) {
        record = *(char**) (table + offset);
        if (record != 0) {
            if (record[0] == 0x2a) {
                while (*(int*) (record + 0x40) > 0) {
                    fcn_0045fbb0((SCENE_RESOURCE*) record);
                    table = *(char**) 0x63374c;
                    record = *(char**) (table + offset);
                }
            }
            *(int*) (table + offset) = 0;
            table = *(char**) 0x63374c;
            table[offset + 0x40] = 0;
            table = *(char**) 0x63374c;
        }
        i++;
        offset += 0x44;
        count = *(unsigned int*) 0x633744;
    }
    *(unsigned int*) 0x633744 = 0;
    m_FreeTracked(table);
    *(char**) 0x63374c = 0;
    *(int*) 0x5fb970 = 0x43eab0;
}
