#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "Develop/Units/m_alloc/m_alloc.h"

int __cdecl fcn_0042e530(const char*);

/* ADDRESS: GOLD 0x0042c9c0 */
int __cdecl fcn_0042c9c0(const char* path)
{
    FILE* stream;
    char line[200];
    char files[128][512];
    char* slash;
    char* start;
    char* finish;
    int count;
    int i;
    unsigned int length;

    count = 0;
    *(int*) 0x6333b8 = 0;
    slash = strrchr(path, '\\');
    if (slash != 0) {
        length = slash - path + 1;
        memcpy((void*) 0xfe7d40, path, length);
        ((char*) 0xfe7d40)[length] = 0;
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
    for (;;) {
        memset(line, 0, sizeof(line));
        fgets(line, 200, stream);
        if (strstr(line, (char*) 0x5f89a4) == 0) {
            start = strstr(line, (char*) 0x5f8954);
            if (start != 0) {
                start = strchr(start, '"');
                if (start == 0)
                    goto fail;
                start++;
                finish = strchr(start, '"');
                if (finish == 0)
                    goto fail;
                *finish = 0;
                *strrchr(start, '.') = 0;
                strcpy(files[count], start);
                count++;
                if (count > 128)
                    goto fail;
            }
        }
        if (feof(stream)) {
            fclose(stream);
            for (i = 0; i < count; i++) {
                if (!fcn_0042e530(files[i]))
                    return 0;
            }
            *(int*) 0xfe7c20 = 1;
            return 1;
        }
    }
fail:
    m_FreeTracked(*(void**) 0x6333c0);
    *(void**) 0x6333c0 = 0;
    return 0;
}
