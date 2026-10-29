extern void* g_14d0020[];
extern char g_67536c[];



#include <string.h>

int __cdecl m_alloc(int, char*);

void* __cdecl fcn_00403270(int a1)
{
	void* p;

	p = (void*) m_alloc(0x244, g_67536c);
	memset(p, 0, 0x244);
	if (g_14d0020[a1] != 0) {
		return 0;
	}
	g_14d0020[a1] = p;
	*(int*) p = a1;
	return p;
}
