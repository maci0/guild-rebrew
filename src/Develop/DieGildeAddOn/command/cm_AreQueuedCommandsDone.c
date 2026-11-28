


// SIZE 0xa
typedef struct {
	unsigned char state;
	char pad[9];
} Slot10;

extern unsigned int g_100581c;
extern unsigned int g_aed204;
#include "Develop/client_types.h"
extern COMMAND_STATUS_SLOT cm_CommandStatusQueue[0x8000];

int __cdecl cm_AreQueuedCommandsDone(void)
{
	unsigned int i;
	unsigned int end;
	int r;

	i = g_100581c;
	end = g_aed204;
	r = 1;
	while (i != end) {
		if (i >= end) {
			break;
		}
		if (((Slot10*)cm_CommandStatusQueue)[i & 0x7fff].state == 0) {
			return 0;
		}
		if (((Slot10*)cm_CommandStatusQueue)[i & 0x7fff].state == 2) {
			r = -1;
		}
		i++;
		if (i >= end) {
			break;
		}
	}
	return r;
}
