

#include <math.h>

extern int g_6b86d4;
extern float g_1040d00[0x400];
extern int g_6b86fc;
extern int g_6b8700;
extern void* g_6b870c;
extern int g_6b8704;
extern int g_6b8708;
extern void* g_1041d04;
extern char g_67bc38[];
extern char g_67bc28[];

void* __cdecl m_alloc(int, void*);

void __cdecl fcn_00450a30(int nlist, int nactive)
{
	int i;

	g_6b86d4 = 0;
	for (i = 0; i < 0x400; i++) {
		g_1040d00[i] = 1.0f - (float) acos(i * 0.0009765625f) * 0.63661975f;
	}
	g_6b86fc = nactive;
	g_6b8700 = 0;
	g_6b870c = m_alloc(nactive * 12, g_67bc38);
	g_6b8704 = nlist;
	g_6b8708 = 0;
	g_1041d04 = m_alloc(nlist * 12, g_67bc28);
}
