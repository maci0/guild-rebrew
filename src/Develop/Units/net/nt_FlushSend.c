


__declspec(dllimport) int __stdcall send(int s, const char* buf, int len, int flags);
__declspec(dllimport) int __stdcall WSAGetLastError(void);

#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned char* g_14cbca8;
extern unsigned short g_14cbcae;
extern unsigned int nt_SentBytes;
void __cdecl nt_LogWinsockError(int err);
void __cdecl nt_CloseClientConnection(void);
void __cdecl nt_RecordPacketStats(unsigned char* p, unsigned int n, char flag);

int __cdecl nt_FlushSend(void)
{
	int n;
	int err;

	if (nt_ClientSocket == -1) {
		return 1;
	}
	if (g_14cbca8 == 0) {
		return 0;
	}
	n = send(nt_ClientSocket, (char*) g_14cbca8 + g_14cbcae, *(unsigned short*) (g_14cbca8 + 1) - g_14cbcae, 0);
	if (n == -1) {
		err = WSAGetLastError();
		if (err == 10035) {
			return 0;
		}
		nt_LogWinsockError(err);
		nt_CloseClientConnection();
		return 1;
	}
	g_14cbcae += n;
	(*(int *)&nt_SentBytes) += n;
	if (g_14cbcae == *(unsigned short*) (g_14cbca8 + 1)) {
		nt_RecordPacketStats(g_14cbca8, g_14cbcae, 0);
		g_14cbca8 = 0;
		g_14cbcae = 0;
	}
	return 0;
}
