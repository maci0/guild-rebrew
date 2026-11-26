

extern void* g_6b7d80;
extern void* g_6b7d84;
void __cdecl sbs_DestroySB(void);
void __cdecl msx_ReleaseSampleHandle(void* p);
void __cdecl m_FreeTracked(void* p);
void __cdecl d3snd_Shutdown(void);

void __cdecl fcn_00425880(void)
{
	sbs_DestroySB();
	if (g_6b7d80 != 0) {
		msx_ReleaseSampleHandle(g_6b7d80);
		g_6b7d80 = 0;
	}
	if (g_6b7d84 != 0) {
		m_FreeTracked(g_6b7d84);
		g_6b7d84 = 0;
	}
	d3snd_Shutdown();
}
