#include "Develop/DieGildeAddOn/game/event_callbacks.h"

extern char g_9b0e20[];

/* Inferred name and source home; byte views preserve the native strided accesses. */
/* ADDRESS: GOLDTL 0x004e4f10 */
void __cdecl fcn_004e4f10(int* event)
{
    int* slot;
    int* participant;
    int* cell;
    int* id;
    int i;
    int j;
    int n;

    id = event + 13;
    for (n = 0; n < 16; n++) {
        slot = (int*) (g_9b0e20 + 0xc + n * 0x35c);
        i = 0;
        slot[-3] = 1;
        slot[-1] = 0;
        slot[-2] = 0;
        slot[0] = 1;
        if (event != 0) {
            slot[1] = *id;
            if (*(unsigned char*) (event + 2) == 3) {
                for (; i < *(unsigned char*) ((char*) event + 0x30); i++) {
                    participant = (int*) (g_9b0e20 + 0x10 + i * 0x35c);
                    if (*(int*) participant != -1) {
                        cell = participant + 0x22;
                        for (j = 16; j != 0; j--) {
                            cell[-1] = -1;
                            cell[0] = 0;
                            cell += 11;
                        }
                    }
                }
            }
        } else {
            slot[1] = -1;
        }
        *(unsigned char*) (slot + 2) = 0;
        id++;
    }
}
