// FUNCTION: GOLDTL 0x00410470

extern char* g_6b7e98;
int __cdecl m_is_tracked(char* p);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl fcn_00410470(char** a, char* r, char* g, char* b, char* al)
{
	char* e;

	e = *a;
	if (!m_is_tracked(e)) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
		return 0;
	}
	e[0xd2] = *r;
	e[0xd1] = *g;
	e[0xd0] = *b;
	e[0xd3] = *al;
	return 0;
}
