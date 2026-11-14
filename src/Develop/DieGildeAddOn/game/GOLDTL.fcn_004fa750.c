#include <string.h>

typedef struct {
    unsigned char count;
    char pad[3];
    int value;
    char tail[0x10];
} CellStat;

char* __cdecl gm_StartFilteredEntitySearch(int, int);
char* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl fcn_004fa6f0(char* pos, int* x, int* y);
int __cdecl fcn_0050cf50(void* e, int k);

/* ADDRESS: GOLDTL 0x004fa750 */
void __cdecl fcn_004fa750(void)
{
    float values[64];
    char* e;
    int x;
    int y;
    int i;
    int j;
    int t; int index;
    CellStat* row;
    row = (CellStat*) 0x99ef84; memset(values, 0, sizeof(values));
    do {
        for (j = 0; j < 8; j++) {
            row[j].count = 0;
        }
        row += 8;
    } while ((int) row < (int) 0x99f584);
    e = gm_StartFilteredEntitySearch(1, 6);
    while (e != 0) {
        if (*(char**) (e + 0x61) != 0
            && fcn_004fa6f0(*(char**) (e + 0x61) + 0x4c, &x, &y) != 0) {
            index = x * 8 + y; t = fcn_0050cf50(e, *(signed char*) (e + 0x5c));
            ((CellStat*) 0x99ef84)[index].count++;
            values[index] = (float) t;
        }
        e = gm_FindNextFilteredEntity();
    }
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (((CellStat*) 0x99ef84)[i * 8 + j].count != 0) {
                ((CellStat*) 0x99ef84)[i * 8 + j].value =
                    (int) (values[i * 8 + j] / ((CellStat*) 0x99ef84)[i * 8 + j].count);
            } else {
                ((CellStat*) 0x99ef84)[i * 8 + j].value = 0;
            }
        }
    }
}
