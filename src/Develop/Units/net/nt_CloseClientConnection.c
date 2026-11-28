#include "Develop/DieGildeAddOn/game/game_data.h"
extern int nt_WsaInitialized;
extern void (__stdcall *imp_shutdown)(int, int);
extern void (__stdcall *imp_closesocket)(int);
extern void (__stdcall *imp_WSACleanup)(void);

/* ADDRESS: GOLD 0x00424c30 */
/* ADDRESS: GOLDTL 0x00421050 */
/* ADDRESS: GOLDDE 0x0041df20 */
void __cdecl nt_CloseClientConnection(void)
{
	if (nt_ClientSocket != -1) {
		imp_shutdown(nt_ClientSocket, 2);
		imp_closesocket(nt_ClientSocket);
		nt_ClientSocket = -1;
		nt_ConnectionClosed = 1;
	}
	imp_WSACleanup();
	nt_WsaInitialized = 0;
}
