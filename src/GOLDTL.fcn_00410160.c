

extern char* g_6b7e98;
int __cdecl m_is_tracked(char* p);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl fcn_00410160(char** a, int* x, int* y, int* z)
{
	char* e;
	float fx;
	float fy;
	float fz;

	e = *a;
	if (!m_is_tracked(e)) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
		return 0;
	}
	fx = *x * 0.01f;
	fy = *y * 0.01f;
	fz = *z * 0.01f;
	*(float*) (e + 0x74) = fx;
	*(float*) (e + 0x78) = fy;
	*(float*) (e + 0x7c) = fz;
	return 0;
}
