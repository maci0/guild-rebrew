extern char* g_6b7fd0;
extern char* g_6b7fd4;
extern char* g_6b7fd8;
void __cdecl m_FreeTracked(void* ptr);

/* ADDRESS: GOLDTL 0x0042e0e0 */
void __cdecl fcn_0042e0e0(void)
{
	if (g_6b7fd8 != 0 && g_6b7fd8 >= g_6b7fd0) {
		m_FreeTracked(g_6b7fd8);
		g_6b7fd0 = 0;
		g_6b7fd4 = 0;
		g_6b7fd8 = 0;
		return;
	}
	__asm { int 3 }
}
