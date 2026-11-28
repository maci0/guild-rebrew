

void __cdecl tb_ShutdownTimer(void);
void __cdecl vfs_exit(char);
void __cdecl tr_FreeStartupBuffer(void);
void __cdecl m_ShutdownAllocator(void);
void __cdecl ShutdownClientLogAndErrorHandler(void);
void __cdecl ShutdownVideo(void);

/* ADDRESS: GOLDDE 0x0051ff90 */
void __cdecl main_ShutdownClientSubsystems(void)
{
	tb_ShutdownTimer();
	vfs_exit(1);
	tr_FreeStartupBuffer();
	m_ShutdownAllocator();
	ShutdownClientLogAndErrorHandler();
	ShutdownVideo();
}
