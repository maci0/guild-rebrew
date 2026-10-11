extern char* g_6b7e98;
// GLOBAL: GOLD 0x5f2c78
extern char g_676cf8[];
// FUNCTION: GOLD 0x40f8a0

int __cdecl m_is_tracked(void*);
void __cdecl fcn_00425bf0(void*, int, char*);

int __cdecl fcn_0040f8a0(char** a1)
{
	char* p;

	p = *a1;
	if (m_is_tracked(p) == 0) {
		fcn_00425bf0(g_6b7e98, *(int*) ((char*) g_6b7e98 + 0x118), g_676cf8);
		return 0;
	}
	p[0xcd] |= 2;
	return 0;
}
