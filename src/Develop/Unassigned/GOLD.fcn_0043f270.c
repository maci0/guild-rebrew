#include "client_scene_resources.h"
void __cdecl m_FreeTracked(void*);

typedef struct SLOT_44 {
    char* record;
    char pad4[0x3c];
    char flag;
} SLOT_44;

/* ADDRESS: GOLD 0x0043f270 */
void __cdecl d3_ShutdownFloorTileCache(void)
{
    unsigned int i;
    unsigned int count;
    SLOT_44* table;
    char* record;

    count = *(unsigned int*) 0x633744;
    table = *(SLOT_44**) 0x63374c;
    i = 0;
    if (i < count) {
      do {
        record = table[i].record;
        if (record != 0) {
            if (record[0] == 0x2a) {
                while (*(int*) (record + 0x40) > 0) {
                    fcn_0045fbb0((SCENE_RESOURCE*) record);
                    table = *(SLOT_44**) 0x63374c;
                    record = table[i].record;
                }
            }
            table[i].record = 0;
            table = *(SLOT_44**) 0x63374c;
            table[i].flag = 0;
            table = *(SLOT_44**) 0x63374c;
        }
        i++;
        count = *(unsigned int*) 0x633744;
      } while (i < count);
    }
    *(unsigned int*) 0x633744 = 0;
    m_FreeTracked(table);
    *(char**) 0x63374c = 0;
    *(int*) 0x5fb970 = 0x43eab0;
}
