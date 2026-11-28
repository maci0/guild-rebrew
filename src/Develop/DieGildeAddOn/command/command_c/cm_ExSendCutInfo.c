struct cut_4c9d10 {
	int f0;
	int time;
	int ready;
	int fc;
	int id;
	int rest[210];
};
// SIZE 0x35c

extern char cut_ParticipantSlots[];
#include "Develop/client_types.h"
#include "Develop/DieGildeAddOn/command/client_packet_queue.h"
extern int* cut_ActiveCutscene;
extern volatile int gm_GameTicks;

int __cdecl fcn_0064d41a(char*, char*, ...);


/* ADDRESS: GOLDTL 0x004c9d10 */
int __cdecl cm_ExSendCutInfo(char* cmd, char* out)
{
	char buf[0x100];
	int i;

	for (i = 0; i < 16; i++) {
		if (((struct cut_4c9d10*)cut_ParticipantSlots)[i].id == *(int*) (cmd + 0x10)) {
			if (cut_ActiveCutscene != 0 && *cut_ActiveCutscene == *(int*) (cmd + 0x14)) {
				((struct cut_4c9d10*)cut_ParticipantSlots)[i] = (*(struct cut_4c9d10*) cm_IncomingPacketData);
				((struct cut_4c9d10*)cut_ParticipantSlots)[i].fc = 0;
				fcn_0064d41a(buf, "cm_ExSendCutInfo: PlayerId:%i Valid:%i  Ready:%i  Time:%i",
				    ((struct cut_4c9d10*)cut_ParticipantSlots)[i].id, ((struct cut_4c9d10*)cut_ParticipantSlots)[i].ready, ((struct cut_4c9d10*)cut_ParticipantSlots)[i].time, gm_GameTicks);
			}
			break;
		}
	}
	if (i >= 16) {
		if (cut_ActiveCutscene != 0 && *cut_ActiveCutscene == *(int*) (cmd + 0x14))
			fcn_0064d41a(buf, "cm_ExSendCutInfo(): io-buffer has not been written, because player not found (player id %i)",
			    *(int*) (cmd + 0x10));
		return 1;
	}
	if (out != 0) {
		out[0] = 1;
		out[1] = 8;
		*(struct cut_4c9d10**) (out + 6) = &((struct cut_4c9d10*)cut_ParticipantSlots)[i];
	}
	return 0;
}
unsigned char _dpad_9b0820[1536];
