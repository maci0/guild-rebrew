// FUNCTION: GOLD 0x40f4f0

extern char* g_6b7e98;
int __cdecl fcn_0041dd90(char* p);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl fcn_0040f4f0(char** a, int* x, int* y, int* z, int* w)
{
	char* e;

	e = *a;
	if (!fcn_0041dd90(e)) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
		return 0;
	}
	*(int*) (e + 0xbc) = *x;
	*(int*) (e + 0xc0) = *y;
	*(int*) (e + 0xc4) = *z;
	*(float*) (e + 0xb8) = (float) *w;
	return 0;
}
