

extern float* g_6b5d0c;
extern char* g_6b5d10;
extern char* g_6b5d14;
void __cdecl m_FreeTracked(int);

void __cdecl fcn_004195f0(void)
{
	if (g_6b5d0c != 0) {
		m_FreeTracked((int) g_6b5d0c);
		g_6b5d0c = 0;
		m_FreeTracked((int) g_6b5d10);
		g_6b5d10 = 0;
		m_FreeTracked((int) g_6b5d14);
		g_6b5d14 = 0;
		g_6b5d10 = 0;
		g_6b5d0c = 0;
	}
}
