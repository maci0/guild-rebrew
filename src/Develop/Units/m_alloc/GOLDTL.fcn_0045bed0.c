

#include <string.h>

extern int g_10405cc;
extern unsigned int g_10404a0;
extern int g_67bd2c;
extern int g_10405c4;
extern char* g_104049c;
extern int g_10404c0[32];
extern int g_10405c0;
extern int g_1040540[32];
extern int g_10405c8;
extern int g_6b7fac;
extern char g_67bd38[];

void* __cdecl m_alloc(int, void*);

void __cdecl fcn_0045bed0(unsigned int n, int a2)
{
	g_10405cc = 0;
	g_10404a0 = n;
	g_67bd2c = a2;
	g_10405c4 = 0;
	(*(void**)&g_104049c) = m_alloc(n * 0x70, g_67bd38);
	memset(g_10404c0, 0, sizeof(g_10404c0));
	g_10405c0 = 0;
	memset(g_1040540, 0, sizeof(g_1040540));
	g_10405c8 = g_6b7fac;
}
