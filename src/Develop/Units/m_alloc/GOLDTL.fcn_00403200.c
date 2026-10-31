extern void* g_14d0020[];
extern char g_67536c[];
extern char g_67534c[];


#include <string.h>

void* __cdecl m_alloc(int, char*);
void __cdecl m_FreeTracked(void*);
#include "Develop/Units/Error/error_message.h"

void* __cdecl ch_Create(void)
{
	int i = 0;
	void* p;

	p = (void*) m_alloc(0x244, g_67536c);
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
	ReportClientMessage(g_67534c);
	return 0;
}
