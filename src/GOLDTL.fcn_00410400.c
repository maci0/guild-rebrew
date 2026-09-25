// FUNCTION: GOLDTL 0x00410400
// SIZE: 112

extern char* g_6b7e98;
int __cdecl fcn_0041dd90(char* p);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl fcn_00410400(char** a, int* x, int* y, int* z, int* w)
{
	char* e;

	e = *a;
	if (!fcn_0041dd90(e)) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
		return 0;
	}
	*(int*) (e + 0xc4) = *x;
	*(int*) (e + 0xc8) = *y;
	*(int*) (e + 0xcc) = *z;
	*(float*) (e + 0xc0) = (float) *w;
	return 0;
}
