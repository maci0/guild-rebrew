#include "Develop/client_types.h"
extern unsigned short g_7e1f74;
extern unsigned short gm_GameTimeHour;
extern unsigned char gm_ClientModeFlags;
extern int g_7766a8;
extern int g_6a3774;
extern pos14_7f4c00 gm_SyncGameTime;




void __cdecl gm_AddTime(char*, int, int, int);

void __cdecl gm_AdvanceGameClock(void)
{
	int t;
	int h;
	int m;

	if ((g_7e1f74 < 0x17 && gm_GameTimeHour < 0x17) || (gm_ClientModeFlags & 0x80) != 0) {
		t = (int) ((g_7766a8 * 0.00625f + 0.5) * g_6a3774);
		h = t / 3600;
		m = (t - h * 3600) / 60;
		gm_AddTime((char*)&gm_SyncGameTime, h, m, t - (h * 60 + m) * 60);
	}
}
