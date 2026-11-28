extern char g_6b89a8[];
extern char g_6b89ac[];
extern char g_6b89b4[];


void* __cdecl m_alloc(int, void*);

/* ADDRESS: GOLDDE 0x0044bcf0 */
void __cdecl d3s_AllocCache(int count, int maxAge)
{
	*(int*) &g_6b89a8 = count;
	*(int*) &g_6b89ac = maxAge;
	*(void**) &g_6b89b4 = m_alloc(count * 20, "d3s:Cache");
}
