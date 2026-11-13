#include <stdio.h>
#include <string.h>
char* __cdecl m_alloc(int, const char*);
void __cdecl fcn_004fe370(void);
void __cdecl gm_KillAllSpieler(void);
void __cdecl srv_SeedRandomWithTime(void);
extern char *g_entity_type_table, *g_item_def_table; extern unsigned char *g_entity_ptr; extern unsigned short *g_query_base;
/* ADDRESS: GOLD 0x004fe570 */
int __cdecl fcn_004fe570(char* prefix)
{
    char path[0x200];
    char* d; char* src;
    char* p;
    char* items;
    char* instances;
    FILE* file;
    int i;
    int j;
    int n;
    unsigned short id;
    unsigned int index;

    for (src = (char*) 0x7e3ff8, d = (char*) 0x7d6a64; (int) src < 0x7e4ebc; src += 0x2f4, d += 0x2a90) {

        *(int*) (d - 4) = *(int*) (src - 0x50);
        *(int*) d = 1000;
        *(int*) (d + 4) = *(int*) src;
        *(int*) (d + 8) = 1000;
        memcpy(d + 0xc, (void*) 0x6178a8, 0x2a80);
    }
    g_entity_type_table = m_alloc(0xca78, "f3_gm:lpGebaeudePROT");
    if (!g_entity_type_table)
        return -1;
    instances = m_alloc(0xa900, "f3_gm:lpGebaeudeINST");
    g_entity_ptr = (unsigned char*) instances;
    memset(instances, 0, 0xa900);
    if (!g_entity_ptr)
        return -2;
    sprintf(path, "%s%s", prefix, "A_Geb.dat");
    file = fopen(path, "rb");
    if (!file)
        return -3;
    fread(g_entity_type_table, 0x24d, 0x58, file);
    fclose(file);
    g_item_def_table = m_alloc(0xb9dc, "f3_gm:lpObjektePROT");
    if (!g_item_def_table)
        return -4;
    instances = m_alloc(0x14f218, "f3_gm:lpObjekteINST");
    g_query_base = (unsigned short*) instances;
    if (!instances)
        return -5;
    memset(instances, 0, 0x14f218);
    sprintf(path, "%s%s", prefix, "A_Obj.dat");
    file = fopen(path, "rb");
    if (!file)
        return -6;
    fread(g_item_def_table, 0x41, 0x2dc, file);
    fclose(file);
    fcn_004fe370();
    gm_KillAllSpieler();
    for (i = 0; i < 0xca78; i += 0x24d) {
        p = g_entity_type_table + i;
        items = g_item_def_table;
        n = 0;
        for (j = 0; j < 0x40; j++) {
            id = *(unsigned short*) (p + 0x23 + j * 2);
            if (id == 0xffff)
                continue;
            index = id & 0x7fff;
            if ((items[index * 0x41] == 2 || items[index * 0x41] == 6) &&
                index != 0xfd && (id & 0x8000))
                n++;
        }
        p[0x21] = (unsigned char) (p[0x21] + n);
    }
    srv_SeedRandomWithTime();
    return 0;
}
