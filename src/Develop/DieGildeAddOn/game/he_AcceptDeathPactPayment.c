#include "Develop/DieGildeAddOn/game/client_data.h"

extern unsigned char gm_ActiveTownIndex;

void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl io_FormatTextBuffer(void*, int, int, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, int);
extern void __cdecl gm_AddTime(char*, int, int, int);

/* Timed action 0x8B (grave debt) START: due is now; late in the day (hour >= 0x17) the
 * action is rescheduled to 0xc with the longer delay, otherwise the short one. */
/* ADDRESS: GOLDTL 0x00579320 */
void __cdecl fcn_00579320(char* a0)
{
	*(pos14_7f4c00*) (a0 + 0x52) = gm_GameTime;
	if (*(unsigned short*) (a0 + 0x56) >= 0x17) {
		gm_AddTime(a0 + 0x52, 0x18, 0, 0);
		*(unsigned short*) (a0 + 0x56) = 0xc;
		*(int*) (a0 + 0x70) = 0;
		return;
	}
	gm_AddTime(a0 + 0x52, 6, 0, 0);
	*(int*) (a0 + 0x70) = 0;
}

void __cdecl he_AcceptDeathPactPayment(void* recipient, void* entity)
{
	char buf[0x400];

	cm_RequestTransferCurrencyNoKill(*(int*) recipient, *(int*) ((char*) entity + 4),
	    gm_ActiveTownIndex, *(int*) ((char*) recipient + 0xc));
	cm_RequestChangeBits(*(int*) ((char*) entity + 4), 0x1cc, 4, 1, 0);
	io_FormatTextBuffer(buf, 0x40fe, *(unsigned short*) entity, *(int*) ((char*) recipient + 0xc));
	he_PostEntityMessage(*(int*) recipient, -1, buf, 1, 0x5f4, 0);
}
