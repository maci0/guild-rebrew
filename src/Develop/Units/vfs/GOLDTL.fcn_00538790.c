

void __cdecl tb_ShutdownTimer(void);
void __cdecl vfs_exit(char);
void __cdecl fcn_0042e0e0(void);
void __cdecl m_ShutdownAllocator(void);
void __cdecl ShutdownClientLogAndErrorHandler(void);
void __cdecl ShutdownVideo(void);

void __cdecl fcn_00538790(void)
{
	tb_ShutdownTimer();
	vfs_exit(1);
	fcn_0042e0e0();
	m_ShutdownAllocator();
	ShutdownClientLogAndErrorHandler();
	ShutdownVideo();
}
