#include "client_cursor.h"
extern int g_01467390;
extern int g_0146739c;
extern int g_14673a0;
void __cdecl fcn_004112e0(void);
/* Inferred 0x4c queued snapshot view; remaining storage ownership is unknown. */
typedef struct GOLD_INPUT_SNAPSHOT {
    short coordinate[6];
    int value[15];
    int pending;
} GOLD_INPUT_SNAPSHOT;

/* ADDRESS: GOLD 0x00411440 */
void __cdecl fcn_00411440(void)
{
    GOLD_INPUT_SNAPSHOT* current = (GOLD_INPUT_SNAPSHOT*) 0x1467380;
    GOLD_INPUT_SNAPSHOT* snapshots = (GOLD_INPUT_SNAPSHOT*) 0x1467440;
    int i;
    if (CursorOsBypass) {
        g_01467380 = CursorX1;
        g_01467382 = CursorY1;
        current->coordinate[2] = *(short*) 0x14683c4;
    }
    current->value[0] = 0;
    current->value[3] = 0;
    g_14673a0 = 0;
    current->value[8] = 0;
    current->value[9] = 0;
    current->value[12] = 0;
    for (i = 0; i < 32; i++) {
        if (snapshots[i].pending) {
            snapshots[i].pending = 0;
            current->value[0] = snapshots[i].value[0];
            g_01467390 = snapshots[i].value[1];
            current->value[2] = snapshots[i].value[2];
            current->value[3] = snapshots[i].value[3];
            g_0146739c = snapshots[i].value[4];
            g_14673a0 = snapshots[i].value[5];
            current->value[6] = snapshots[i].value[6];
            current->value[7] = snapshots[i].value[7];
            current->value[8] = snapshots[i].value[8];
            current->value[9] = snapshots[i].value[9];
            current->value[10] = snapshots[i].value[10];
            current->value[11] = snapshots[i].value[11];
            current->value[12] = snapshots[i].value[12];
            current->value[14] = snapshots[i].value[14];
            current->value[13] = snapshots[i].value[13];
            current->coordinate[3] = snapshots[i].coordinate[3];
            current->coordinate[4] = snapshots[i].coordinate[4];
            current->coordinate[5] = snapshots[i].coordinate[5];
            break;
        }
    }
    fcn_004112e0();
}
