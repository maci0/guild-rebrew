#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern char io_MessageFormatBuf[];
extern char str_empty[];



void __cdecl io_FormatTextBuffer(void*, int, int, int, int, int, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);

/* ADDRESS: GOLDDE 0x00596b50 */
void __cdecl he_NotifyAblassPurchase(void* entity, void* recipient, int church, int payout, int cost)
{
	char t;
	int tag;

	t = *(char*) ((char*) recipient + 2);
	if (t == 6 || t == 7) {
		if (*(char*) ((char*) recipient + 0xc) == 0) {
			tag = 0x20b7;
		} else {
			tag = ((*(int*)&gm_GameTime) >= 0x75) ? 0x20b9 : 0x20b8;
		}
		io_FormatTextBuffer(io_MessageFormatBuf, 0x20b6, *(unsigned short*) entity, church, cost, payout, tag);
		he_PostEntityMessage(*(int*) ((char*) recipient + 4), -1, io_MessageFormatBuf, 0, 0x5ff, str_empty);
	}
}
