extern char* g_6b7e98;
// FUNCTION: GOLD 0x40f250
// SIZE: 112

int __cdecl fcn_0041dd90(char* p);
void __cdecl fcn_004273d0(char* g, int h, const char* msg);

int __cdecl fcn_0040f250(char** a, int* x, int* y, int* z)
{
	char* e;
	float fx;
	float fy;
	float fz;

	e = *a;
	if (!fcn_0041dd90(e)) {
		fcn_004273d0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
		return 0;
	}
	fx = *x * 0.01f;
	fy = *y * 0.01f;
	fz = *z * 0.01f;
	*(float*) (e + 0x6c) = fx;
	*(float*) (e + 0x70) = fy;
	*(float*) (e + 0x74) = fz;
	return 0;
}
