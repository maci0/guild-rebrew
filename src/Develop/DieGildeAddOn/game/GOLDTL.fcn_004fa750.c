#include <string.h>

typedef struct {
    unsigned char count;
    char pad[3];
    int value;
    char tail[0x10];
} CellStat;

extern CellStat g_99ef84[8][8];

char* __cdecl gm_StartFilteredEntitySearch(int, int);
char* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl fcn_004fa6f0(char* pos, int* x, int* y);
int __cdecl gm_CalculateGebaeudeValue(void* e, int k);

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
    CellStat* q;
    row = g_99ef84[0]; memset(values, 0, sizeof(values));
    do {
        q = row;
        j = 8;
        do {
            q->count = 0;
            q++;
        } while (--j);
        row = q;
    } while ((int) row < (int) g_99ef84 + 0x600);
    e = gm_StartFilteredEntitySearch(1, 6);
    while (e != 0) {
        if (*(char**) (e + 0x61) != 0
            && fcn_004fa6f0(*(char**) (e + 0x61) + 0x4c, &x, &y) != 0) {
            index = x * 8 + y; t = gm_CalculateGebaeudeValue(e, *(signed char*) (e + 0x5c));
            ((CellStat*)g_99ef84)[index].count++;
            values[index] = (float) t;
        }
        e = gm_FindNextFilteredEntity();
    }
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (g_99ef84[i][j].count != 0) {
                g_99ef84[i][j].value =
                    (int) (values[i * 8 + j] / g_99ef84[i][j].count);
            } else {
                g_99ef84[i][j].value = 0;
            }
        }
    }
}
