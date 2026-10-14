/* ADDRESS: GOLD 0x01468ae0 */
extern void* g_1468ae0[];


#include <string.h>

void* __cdecl m_alloc(int, char*);
void __cdecl fcn_00422620(void*);
void __cdecl fcn_004222b0(char*);

void* __cdecl fcn_004029c0(void)
{
	int i = 0;
	void* p;

	p = (void*) m_alloc(0x244, (char*) 0x5f12f4);
	memset(p, 0, 0x244);
	if (g_1468ae0[i] != 0) {
		while (i < 0x300 && g_1468ae0[++i] != 0) {
		}
	}
	if (i < 0x300) {
		g_1468ae0[i] = p;
		*(int*) p = i;
		return p;
	}
	fcn_00422620(p);
	fcn_004222b0((char*) 0x5f12d4);
	return 0;
}
