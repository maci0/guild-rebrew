


extern int g_67a370;

int __cdecl fcn_004ceba0(int x, int y)
{
	char* m;
	int n;
	int v;

	m = *(char**) (((char*)g_67a370) + 0xb0);
	n = *(int*) (m + 0x20);
	if (x > n || x < 0 || y < 0 || y > n) {
		return 0;
	}
	if (x >= n || y >= n) {
		return 0;
	}
	v = *(int*) (*(char**) (m + 0x24) + (y * n + x) * 28);
	if (v == 0 || v == 0xd) {
		return 0;
	}
	return 1;
}
