#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Develop/Units/m_alloc/m_alloc.h"

typedef struct GOLD_OPTION_4AC440 {
    int id;
    int type;
    int enabled;
    char name[16];
    char other[16];
} GOLD_OPTION_4AC440;

typedef struct GOLD_OPTIONS_4AC440 {
    int second_count;
    int first_count;
    GOLD_OPTION_4AC440* second;
    GOLD_OPTION_4AC440* first;
} GOLD_OPTIONS_4AC440;

int __cdecl fcn_004ac8a0(GOLD_OPTIONS_4AC440*);

/* ADDRESS: GOLD 0x004ac440 */
int __cdecl fcn_004ac440(void)
{
    GOLD_OPTIONS_4AC440 options;
    char path[260];
    char text[256];
    char section[32];
    int i;
    int id;

    options.second_count = 0;
    options.first_count = 0;
    options.second = 0;
    options.first = 0;
    GetModuleFileNameA(*(HMODULE*) 0x75e140, path, 260);
    strrchr(path, '\\')[1] = 0;
    strcat(path, "historical.ini");
    GetPrivateProfileStringA((char*) 0x5f8850, "kcnt", (char*) 0x631090, text, 256, path);
    options.first_count = atoi(text);
    if (options.first_count <= 0)
        return -1;
    GetPrivateProfileStringA((char*) 0x5f8850, "pcnt", (char*) 0x631090, text, 256, path);
    options.second_count = atoi(text);
    if (options.second_count <= 0)
        return -1;
    options.first = (GOLD_OPTION_4AC440*) m_alloc(options.first_count * 44, "hmt_CreateBinaryFile");
    if (options.first == 0)
        return -1;
    options.second = (GOLD_OPTION_4AC440*) m_alloc(options.second_count * 44, "hmt_CreateBinaryFile");
    if (options.second == 0)
        goto fail;
    memset(options.first, 0, options.first_count * 44);
    memset(options.second, 0, options.second_count * 44);
    id = 0;
    for (i = 0; i < options.first_count; i++) {
        options.first[i].id = id++;
        sprintf(section, "k_%i", i);
        GetPrivateProfileStringA(section, "begin", "-1", text, 256, path);
        options.first[i].type = atoi(text);
        GetPrivateProfileStringA(section, "vname", (char*) 0x631090, text, 256, path);
        strncpy(options.first[i].name, text, 15);
        GetPrivateProfileStringA(section, "nname", (char*) 0x631090, text, 256, path);
        strncpy(options.first[i].other, text, 15);
        GetPrivateProfileStringA(section, "end", "-1", text, 256, path);
        options.first[i].enabled = atoi(text);
    }
    for (i = 0; i < options.second_count; i++) {
        options.second[i].id = id++;
        sprintf(section, "p_%i", i);
        GetPrivateProfileStringA(section, "begin", "-1", text, 256, path);
        options.second[i].type = atoi(text);
        GetPrivateProfileStringA(section, "vname", (char*) 0x631090, text, 256, path);
        strncpy(options.second[i].name, text, 15);
        GetPrivateProfileStringA(section, "nname", (char*) 0x631090, text, 256, path);
        strncpy(options.second[i].other, text, 15);
        GetPrivateProfileStringA(section, "end", "-1", text, 256, path);
        options.second[i].enabled = atoi(text);
    }
    if (!fcn_004ac8a0(&options)) {
        m_FreeTracked(options.first);
        options.first = 0;
        m_FreeTracked(options.second);
        return 0;
    }
fail:
    if (options.first != 0) {
        m_FreeTracked(options.first);
        options.first = 0;
    }
    if (options.second != 0)
        m_FreeTracked(options.second);
    return -1;
}
