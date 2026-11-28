extern char cm_SecondaryPacketDelta[];
extern char cm_SecondaryPacketDelta[];



#include <string.h>

#pragma intrinsic(memcpy, memset)

/* ADDRESS: GOLDDE 0x004b21f0 */
void __cdecl cm_BeginSecondaryPacketDelta(int* p)
{
	int v;

	v = p[1];
	*(char*) (cm_SecondaryPacketDelta + 4) = 0;
	*(int*) cm_SecondaryPacketDelta = v;
	memset(cm_SecondaryPacketDelta + 5, 0, 119);
	*(int*) (cm_SecondaryPacketDelta + 0x80) = 0;
	*(int*) (cm_SecondaryPacketDelta + 0x94) = (int) p;
}
unsigned char _dpad_aed220[128];
unsigned char _dpad_aed2a0[124];
