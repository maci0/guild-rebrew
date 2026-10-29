extern char* g_6b7e88;
extern int g_6b7d7c;



void __cdecl fcn_004232f0(void);
void __cdecl m_FreeTracked(int);
int __cdecl fcn_0042a2d0(int);

void __cdecl fcn_00422100(void)
{
	fcn_004232f0();
	if ((*(int*)&g_6b7e88) != 0) {
		m_FreeTracked((*(int*)&g_6b7e88));
		(*(int*)&g_6b7e88) = 0;
	}
	if (g_6b7d7c != 0) {
		fcn_0042a2d0(g_6b7d7c);
		g_6b7d7c = 0;
	}
}
