#include <stdio.h>
#include <string.h>
char* __cdecl m_alloc(int, const char*);
void __cdecl fcn_004fe370(void);
void __cdecl gm_KillAllSpieler(void);
void __cdecl srv_SeedRandomWithTime(void);

/* ADDRESS: GOLD 0x004fe570 */
int __cdecl fcn_004fe570(char* prefix)
{
    char path[0x200];
    char* d;
    char* p;
    char* items;
    char* instances;
    FILE* file;
    int i;
    int j;
    int n;
    unsigned short id;
    unsigned int index;

    for (i = 0; i < 5; i++) {
        d = (char*) 0x7d6a60 + i * 0x2a90;
        *(int*) d = *(int*) (0x7e3fa8 + i * 0x2f4);
        *(int*) (d + 4) = 1000;
        *(int*) (d + 8) = *(int*) (0x7e3ff8 + i * 0x2f4);
        *(int*) (d + 0xc) = 1000;
        memcpy(d + 0x10, (void*) 0x6178a8, 0x2a80);
    }
    *(char**) 0x7e3f30 = m_alloc(0xca78, "f3_gm:lpGebaeudePROT");
    if (!*(void**) 0x7e3f30)
        return -1;
    instances = m_alloc(0xa900, "f3_gm:lpGebaeudeINST");
    *(char**) 0x889f74 = instances;
    memset(instances, 0, 0xa900);
    if (!*(void**) 0x889f74)
        return -2;
    sprintf(path, "%s%s", prefix, "A_Geb.dat");
    file = fopen(path, "rb");
    if (!file)
        return -3;
    fread(*(void**) 0x7e3f30, 0x24d, 0x58, file);
    fclose(file);
    *(char**) 0x91aaf0 = m_alloc(0xb9dc, "f3_gm:lpObjektePROT");
    if (!*(void**) 0x91aaf0)
        return -4;
    instances = m_alloc(0x14f218, "f3_gm:lpObjekteINST");
    *(char**) 0x7e3f34 = instances;
    if (!instances)
        return -5;
    memset(instances, 0, 0x14f218);
    sprintf(path, "%s%s", prefix, "A_Obj.dat");
    file = fopen(path, "rb");
    if (!file)
        return -6;
    fread(*(void**) 0x91aaf0, 0x41, 0x2dc, file);
    fclose(file);
    fcn_004fe370();
    gm_KillAllSpieler();
    for (i = 0; i < 0xca78; i += 0x24d) {
        p = *(char**) 0x7e3f30 + i;
        items = *(char**) 0x91aaf0;
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
