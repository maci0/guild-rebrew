// FUNCTION: GOLDTL 0x00410470
// SIZE: 112

extern char* g_6b7e98;
int __cdecl fcn_0041dd90(char* p);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl fcn_00410470(char** a, char* r, char* g, char* b, char* al)
{
	char* e;

	e = *a;
	if (!fcn_0041dd90(e)) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
		return 0;
	}
	e[0xd2] = *r;
	e[0xd1] = *g;
	e[0xd0] = *b;
	e[0xd3] = *al;
	return 0;
}
