#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "Develop/Units/m_alloc/m_alloc.h"

int __cdecl txt_LoadTextPointerTable(const char*);

/* ADDRESS: GOLD 0x0042c9c0 */
int __cdecl txt_LoadTextDefinitionList(const char* path)
{
    FILE* stream;
    char line[200];
    char files[128][512];
    char* slash;
    char* start;
    char* finish;
    int count;
    int i;

    count = 0;
    *(int*) 0x6333b8 = 0;
    slash = strrchr(path, '\\');
    if (slash != 0) {
        memcpy((void*) 0xfe7d40, path, slash - path + 1);
        ((char*) 0xfe7d40)[slash - path + 1] = 0;
    } else {
        *(char*) 0xfe7d40 = *(char*) 0x631090;
    }
    stream = fopen(path, (char*) 0x5f831c);
    if (stream == 0) {
        MessageBoxA(0, (char*) 0x5f8b64, (char*) 0x5f8b88, 0x30);
        m_FreeTracked(*(void**) 0x6333c0);
        *(void**) 0x6333c0 = 0;
        return 0;
    }
    do {
        memset(line, 0, sizeof(line));
        fgets(line, 200, stream);
        if (strstr(line, (char*) 0x5f89a4) == 0) {
            start = strstr(line, (char*) 0x5f8954);
            if (start != 0) {
                start = strchr(start, '"');
                if (start == 0) {
                    m_FreeTracked(*(void**) 0x6333c0);
                    *(void**) 0x6333c0 = 0;
                    return 0;
                }
                start++;
                finish = strchr(start, '"');
                if (finish == 0) {
                    m_FreeTracked(*(void**) 0x6333c0);
                    *(void**) 0x6333c0 = 0;
                    return 0;
                }
                *finish = 0;
                *strrchr(start, '.') = 0;
                strcpy(files[count++], start);
                if (count > 128) {
                    m_FreeTracked(*(void**) 0x6333c0);
                    *(void**) 0x6333c0 = 0;
                    return 0;
                }
            }
        }
    } while (!feof(stream));
    fclose(stream);
    for (i = 0; i < count; i++) {
        if (!txt_LoadTextPointerTable(files[i]))
            return 0;
    }
    *(int*) 0xfe7c20 = 1;
    return 1;
}
