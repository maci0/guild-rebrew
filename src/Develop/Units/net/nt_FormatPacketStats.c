extern char nt_PacketStats[];
/* Formats the network statistics summary and its 106 hourly rows. */

#include <stdio.h>

extern unsigned int nt_ReceivedPacketCount;
extern unsigned int nt_ReceivedBytes;
extern unsigned int nt_SentPacketCount;
extern unsigned int nt_SentBytes;
#include "Develop/DieGildeAddOn/game/game_data.h"


/* ADDRESS: GOLDTL 0x00420bf0 */
/* ADDRESS: GOLDDE 0x0041db50 */
void __cdecl nt_FormatPacketStats(void)
{
	unsigned int i;
	char buf[256];
	unsigned int* p;

	sprintf(buf, "Recv: %u Packets w/ %u bytes, Send: %u Packets w/ %u bytes", nt_ReceivedPacketCount, nt_ReceivedBytes, nt_SentPacketCount, nt_SentBytes);
	p = (unsigned int*) &nt_PacketStats;
	for (i = 0; i < 0x6a; i++, p += 4) {
		sprintf(buf, "%u. Recv: %u Packets (%02f%%) w/ %u bytes (%02f%%), Send: %u Packets (%02f%%) w/ %u bytes (%02f%%)", i,
		        p[0],
		        ((double) p[0] * 100.0) / nt_ReceivedPacketCount,
		        p[1],
		        ((double) p[1] * 100.0) / nt_ReceivedBytes,
		        p[2],
		        ((double) p[2] * 100.0) / nt_SentPacketCount,
		        p[3],
		        ((double) p[3] * 100.0) / nt_SentBytes);
	}
}
