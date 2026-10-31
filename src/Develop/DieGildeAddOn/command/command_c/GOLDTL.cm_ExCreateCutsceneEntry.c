#include <string.h>
#include "client_packet_queue.h"
extern unsigned char g_7747b0;
void __cdecl ReportClientMessage(const char* message);

/* Inferred distinct client handler name; native diagnostic text is retained. */
/* ADDRESS: GOLDTL 0x004c9ee0 */
int __cdecl cm_ExCreateCutsceneEntry(char* command, char* result)
{
    unsigned int payload[69];
    char* entry;

    (void) command;
    memcpy(payload, g_aed340, sizeof(payload));
    entry = fcn_004e6ae0(payload);
    if (entry == 0) {
        ReportClientMessage("cm_ExAllocCutscene(): Cutscene-Queue is full!");
        return 1;
    }
    if (g_7747b0 & 4)
        entry[0x26] |= 0x80;
    if (result != 0) {
        result[0] = 1;
        result[1] = 9;
        *(char**) (result + 6) = entry;
    }
    return 0;
}
