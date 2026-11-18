extern char g_67dae0[];
extern char g_67dad4[];
extern char g_67dac4[];


void* __cdecl m_alloc(int, char*);

void* __cdecl fcn_0047abd0(int wordCount, int entryCount, int a3)
{
	void* p;

	p = m_alloc(0x38, g_67dae0);
	*(int*) ((char*) p + 0x24) = wordCount;
	*(int*) ((char*) p + 0x28) = (int) m_alloc(wordCount * 4, g_67dad4);
	*(int*) ((char*) p + 0x2c) = entryCount;
	*(int*) ((char*) p + 0x30) = (int) m_alloc(entryCount * 12, g_67dac4);
	return p;
}
