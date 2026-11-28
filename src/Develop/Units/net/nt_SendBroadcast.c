#include "g_1552000.h"
extern int nt_BroadcastSocket;
extern struct sin_402220 nt_BroadcastAddr;



extern int (__stdcall *g_662350)(int, int, int, int, int, int);

/* ADDRESS: GOLDDE 0x00401cb0 */
void __cdecl nt_SendBroadcast(int buf, int len)
{
	int h;

	h = nt_BroadcastSocket;
	if (h != -1) {
		g_662350(h, buf, len, 0, (int) &nt_BroadcastAddr, 0x10);
	}
}
