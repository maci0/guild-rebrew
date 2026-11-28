#include "Develop/DieGildeAddOn/game/event_callbacks.h"

#include "Develop/DieGildeAddOn/game/game_data.h"

/* Inferred name and source home; byte views preserve the native strided accesses. */
/* ADDRESS: GOLDTL 0x004e4f10 */
/* ADDRESS: GOLDDE 0x004d1890 */
void __cdecl cut_ResetEventSlots(int* event)
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
        slot = (int*) (cut_ParticipantSlots + 0xc + n * 0x35c);
        i = 0;
        slot[-3] = 1;
        slot[-1] = 0;
        slot[-2] = 0;
        slot[0] = 1;
        if (event != 0) {
            slot[1] = *id;
            if (*(unsigned char*) (event + 2) == 3) {
                for (; i < *(unsigned char*) ((char*) event + 0x30); i++) {
                    participant = (int*) (cut_ParticipantSlots + 0x10 + i * 0x35c);
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
