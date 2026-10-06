// FUNCTION: GOLDTL 0x004100c0

extern char* g_6b7e98;
int __cdecl fcn_0041dd90(char* p);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl fcn_004100c0(char** a, int* x, int* y, int* z, int* w, int* v)
{
	char* e;
	float fx;
	float fy;
	float fz;
	float fw;
	float fv;

	e = *a;
	if (!fcn_0041dd90(e)) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
		return 0;
	}
	fx = *x * 0.01f;
	fy = *y * 0.01f;
	fz = *z * 0.01f;
	fv = *v * 0.01f;
	fw = *w * 0.01f;
	*(float*) (e + 0x58) = fx;
	*(float*) (e + 0x5c) = fy;
	*(float*) (e + 0x60) = fz;
	*(float*) (e + 0x64) = fw;
	*(float*) (e + 0xbc) = fv;
	return 0;
}
