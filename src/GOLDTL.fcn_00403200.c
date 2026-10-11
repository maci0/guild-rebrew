extern void* g_14d0020[];
extern char g_67536c[];
// GLOBAL: GOLDTL 0x67534c
extern char g_67534c[];
// FUNCTION: GOLDTL 0x403200

#include <string.h>

void* __cdecl m_AllocTracked(int, char*);
void __cdecl m_FreeTracked(void*);
void __cdecl fcn_0041d9e0(char*);

void* __cdecl fcn_00403200(void)
{
	int i = 0;
	void* p;

	p = (void*) m_AllocTracked(0x244, g_67536c);
	memset(p, 0, 0x244);
	if (g_14d0020[i] != 0) {
		while (i < 0x300 && g_14d0020[++i] != 0) {
		}
	}
	if (i < 0x300) {
		g_14d0020[i] = p;
		*(int*) p = i;
		return p;
	}
	m_FreeTracked(p);
	fcn_0041d9e0(g_67534c);
	return 0;
}
