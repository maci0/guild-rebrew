extern char* g_104049c;
extern unsigned int g_10404a0;
extern int g_10405cc;
extern int g_10405c4;
extern int g_67bd2c;

void __cdecl fcn_0045bfb0(char* p);
void __cdecl m_FreeTracked(void* p);

// FUNCTION: GOLDTL 0x45c1e0
void __cdecl fcn_0045c1e0(void)
{
	unsigned int i;
	char* p;

	p = g_104049c;
	for (i = 0; i < g_10404a0; i++, p += 0x70) {
		while (*(int*) (p + 0x40) > 0) {
			fcn_0045bfb0(p);
		}
	}
	m_FreeTracked(g_104049c);
	g_104049c = 0;
	g_10405cc = 0;
	g_10405c4 = 0;
	g_67bd2c = 0;
}
