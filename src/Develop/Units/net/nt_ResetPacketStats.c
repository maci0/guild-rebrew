

#include <string.h>
#include "Develop/Units/net/net.h"

#pragma intrinsic(memcpy, memset)

void __cdecl nt_ResetPacketStats(void)
{
	memset(nt_PacketStats, 0, sizeof(nt_PacketStats));
	nt_ReceivedPacketCount = 0;
	nt_ReceivedBytes = 0;
	nt_SentPacketCount = 0;
	nt_SentBytes = 0;
}
