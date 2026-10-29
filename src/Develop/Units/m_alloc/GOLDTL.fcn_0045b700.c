

#include <stdlib.h>

extern char g_67bd1c[];
extern char g_67bd08[];
extern char g_67bcf4[];

void* __cdecl m_alloc(int, void*);
void __cdecl fcn_0045b290(char*, int);

char* __cdecl fcn_0045b700(int a1, int n, int a3)
{
	char* g = 0;

	if (n != 0) {
		g = (char*) m_alloc(0x34, g_67bd1c);
		*(int*) (g + 0x30) = a3;
		*(int*) (g + 0x20) = abs(n);
		*(void**) (g + 0x28) = m_alloc(abs(n) * abs(n), g_67bd08);
		if (n > 0) {
			*(void**) (g + 0x24) = m_alloc(*(int*) (g + 0x20) * *(int*) (g + 0x20) * 0x1c, g_67bcf4);
		} else {
			*(void**) (g + 0x24) = 0;
		}
		if (*(void**) (g + 0x28) != 0) {
			fcn_0045b290(g, a1);
		}
	}
	return g;
}
