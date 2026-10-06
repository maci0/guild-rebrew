// FUNCTION: GOLD 0x0040ba10
// FUNCTION: GOLDTL 0x0040c930

extern char* g_6b7e98;
char* __cdecl fcn_00403b90(int id, int* v);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

char* __cdecl fcn_0040c930(int* a, int* b, int* c, int* d)
{
	int v[4];
	char* o;

	v[0] = *b;
	v[1] = *c;
	v[2] = *d;
	o = fcn_00403b90(*a, v);
	if (o == 0) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "object not created");
	} else {
		*(int*) (o + 0x30) = *(int*) (g_6b7e98 + 0x104);
	}
	return o;
}
