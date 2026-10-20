#include <string.h>

typedef struct fcn_004d4f30_World {
    char pad00[0x80];
    int listA[16]; /* +0x80 */
    int listB[16]; /* +0xc0 */
} fcn_004d4f30_World;

typedef struct fcn_004d4f30_Slot {
    int id;
    int f4;
    char pad8[0x24];
} fcn_004d4f30_Slot; /* SIZE 0x2c */

extern int g_772ea4;               /* 0x772ea4 */
extern unsigned short* g_772e98;   /* 0x772e98, entity pointer */
extern unsigned short* g_772e9c;   /* 0x772e9c, entity pointer */
extern char* g_772eb4;             /* 0x772eb4, player table */
extern int g_772f08;               /* 0x772f08, object count */
extern char* g_9b9e40[];           /* 0x9b9e40, object pointer table */
extern char g_9b0e20[];            /* 0x9b0e20, 0x35c-byte player records */

int __cdecl gm_LookupEntityRecordById(int search_id);
void* __cdecl fcn_004ceac0(void* rec, char* entity);
void __cdecl fcn_00455350(char* object, float* in, float* out);
void __cdecl fcn_004c67c0(int a1, void* a2);

/* ADDRESS: GOLDTL 0x004d4f30 */
char* __cdecl fcn_004d4f30(fcn_004d4f30_World* world)
{
    int countA;
    int nB;
    int countB;
    int countC;
    char* result;
    int i;
    int n;
    int* p;
    char* rec;
    char* obj;
    fcn_004d4f30_Slot slot;
    fcn_004d4f30_Slot* src;
    float out[4];

    result = 0;
    countC = 0;
    countB = 0;
    if (g_772ea4 != 0) {
        return (char*) g_772ea4;
    }

    countA = 0;
    for (i = 0; i < 0x10; i++) {
        if (world->listA[i] != -1) {
            rec = (char*) gm_LookupEntityRecordById(world->listA[i]);
            if (*(char*) (rec + 8) != 0 && *(char*) (rec + 8) != 4 &&
                *(int*) (*(int*) (*(int*) (rec + 0x184) + 0x34) + 0x218) != 1) {
                countA++;
            }
        }
    }

    nB = 0;
    for (i = 0; i < 0x10; i++) {
        if (world->listB[i] != -1) {
            rec = (char*) gm_LookupEntityRecordById(world->listB[i]);
            if (*(char*) (rec + 8) != 0 && *(char*) (rec + 8) != 4 &&
                *(int*) (*(int*) (*(int*) (rec + 0x184) + 0x34) + 0x218) != 1) {
                nB++;
            }
        }
    }

    if (nB <= 0) {
        result = (char*) g_772e9c;
    } else if (countA <= 0) {
        result = (char*) g_772e98;
    }

    i = 0;
    if (g_772f08 > 0) {
        do {
            if (strstr(g_9b9e40[i], "sp_CONQUER") != 0) {
                fcn_00455350(g_9b9e40[i],
                             (float*) (g_9b9e40[i] + 0x4c), out);
                countB++;
                rec = *(char**) (g_9b9e40[i] + 0x204);
                if (rec != 0 &&
                    *(int*) (rec + 0x16c) == *(int*) &g_772e9c) {
                    countC++;
                }
            }
            i++;
        } while (i < g_772f08);
        if (countB != 0 && countC == countB) {
            result = (char*) g_772e98;
        }
    }

    if (result != 0) {
        i = 0;
        i = 0;
        n = *(unsigned char*) (g_772eb4 + 0x30);
        if (n > 0) {
            p = (int*) (g_772eb4 + 0x34);
            do {
                if (*p != -1) {
                    break;
                }
                i++;
                p++;
            } while (i < n);
        }
        src = (fcn_004d4f30_Slot*) fcn_004ceac0(g_9b0e20 + i * 0x35c,
                                                result);
        slot = *src;
        slot.id = *(int*) (result + 4);
        slot.f4 = 5;
        fcn_004c67c0(*(int*) (g_9b0e20 + i * 0x35c + 0x10), &slot);
    }
    return result;
}
