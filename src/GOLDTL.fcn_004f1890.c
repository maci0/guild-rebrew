// FUNCTION: GOLDTL 0x4f1890

extern int g_6652f8[];

int __cdecl fcn_004f1890(int* a1, int* a2)
{
	int n;
	int i;

	i = 0;
	n = g_6652f8[*a2];
	for (; i < n; i++) {
		if (*(int*) (*(char**) (a2 + 4) + i * 0x44) == *a1) {
			return 1;
		}
	}
	return 0;
}
