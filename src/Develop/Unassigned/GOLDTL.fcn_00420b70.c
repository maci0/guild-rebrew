

#include <string.h>
#include "Develop/Units/net/net.h"

#pragma intrinsic(memcpy, memset)

void __cdecl fcn_00420b70(void)
{
	memset(g_14cbcc0, 0, sizeof(g_14cbcc0));
	nt_ReceivedPacketCount = 0;
	nt_ReceivedBytes = 0;
	g_6b7d60 = 0;
	g_6b7d5c = 0;
}
