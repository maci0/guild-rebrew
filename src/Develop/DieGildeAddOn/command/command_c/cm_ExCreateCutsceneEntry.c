#include <string.h>
#include "Develop/DieGildeAddOn/command/client_packet_queue.h"
extern unsigned char gm_ClientModeFlags;
void __cdecl ReportClientMessage(const char* message);

/* Inferred distinct client handler name; native diagnostic text is retained. */
/* ADDRESS: GOLDTL 0x004c9ee0 */
/* ADDRESS: GOLDDE 0x004b76c0 */
int __cdecl cm_ExCreateCutsceneEntry(char* command, char* result)
{
    unsigned int payload[69];
    char* entry;

    (void) command;
    memcpy(payload, cm_IncomingPacketData, sizeof(payload));
    entry = cut_AllocCutscene(payload);
    if (entry == 0) {
        ReportClientMessage("cm_ExAllocCutscene(): Cutscene-Queue is full!");
        return 1;
    }
    if (gm_ClientModeFlags & 4)
        entry[0x26] |= 0x80;
    if (result != 0) {
        result[0] = 1;
        result[1] = 9;
        *(char**) (result + 6) = entry;
    }
    return 0;
}
