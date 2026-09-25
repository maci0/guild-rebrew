// FUNCTION: GOLD 0x40f560
// SIZE: 112

extern char* g_6b7e98;
int __cdecl fcn_0041dd90(char* p);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl fcn_0040f560(char** a, char* r, char* g, char* b, char* al)
{
	char* e;

	e = *a;
	if (!fcn_0041dd90(e)) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
		return 0;
	}
	e[0xca] = *r;
	e[0xc9] = *g;
	e[0xc8] = *b;
	e[0xcb] = *al;
	return 0;
}
