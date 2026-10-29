extern char g_67dae0[];
extern char g_67dad4[];
extern char g_67dac4[];


void* __cdecl m_alloc(int, char*);

void* __cdecl fcn_0047abd0(int a1, int a2, int a3)
{
	void* p;

	p = m_alloc(0x38, g_67dae0);
	*(int*) ((char*) p + 0x24) = a1;
	*(int*) ((char*) p + 0x28) = (int) m_alloc(a1 * 4, g_67dad4);
	*(int*) ((char*) p + 0x2c) = a2;
	*(int*) ((char*) p + 0x30) = (int) m_alloc(a2 * 12, g_67dac4);
	return p;
}
