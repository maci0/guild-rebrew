

void __cdecl fcn_0042de60(void);
void __cdecl vfs_exit(char);
void __cdecl fcn_0042e0e0(void);
void __cdecl m_ShutdownAllocator(void);
void __cdecl fcn_0041d850(void);
void __cdecl fcn_0041e650(void);

void __cdecl fcn_00538790(void)
{
	fcn_0042de60();
	vfs_exit(1);
	fcn_0042e0e0();
	m_ShutdownAllocator();
	fcn_0041d850();
	fcn_0041e650();
}
