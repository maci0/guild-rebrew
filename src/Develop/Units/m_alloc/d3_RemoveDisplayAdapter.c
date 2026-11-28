

#include "Develop/Units/d3/display_adapter_info.h"

extern DISPLAY_ADAPTER_INFO* g_6b5dd0;
extern unsigned int g_6b5de8;
void __cdecl m_FreeTracked(void* p);
void* __cdecl fcn_0064d740(void* dst, const void* src, unsigned int n);

void __cdecl d3_RemoveDisplayAdapter(int idx)
{
	m_FreeTracked(g_6b5dd0[idx].data);
	g_6b5dd0[idx].data = 0;
	if (--g_6b5de8 != 0) {
		m_FreeTracked(g_6b5dd0[idx].data);
		g_6b5dd0[idx].data = 0;
		fcn_0064d740(&g_6b5dd0[idx], &g_6b5dd0[idx + 1], g_6b5de8 * sizeof(DISPLAY_ADAPTER_INFO) - idx * sizeof(DISPLAY_ADAPTER_INFO));
		return;
	}
	m_FreeTracked(g_6b5dd0);
	g_6b5dd0 = 0;
}
