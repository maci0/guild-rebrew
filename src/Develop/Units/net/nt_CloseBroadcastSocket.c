extern int nt_BroadcastSocket;

extern int (__stdcall *imp_closesocket)(int);

/* ADDRESS: GOLDDE 0x00401c90 */
void __cdecl nt_CloseBroadcastSocket(void)
{
	int h;

	h = nt_BroadcastSocket;
	if (h != -1) {
		imp_closesocket(h);
		nt_BroadcastSocket = -1;
	}
}
