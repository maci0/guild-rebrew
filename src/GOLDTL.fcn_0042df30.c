


extern int g_1052c60[0x60];

int __cdecl fcn_0042df30(int a1, int a2)
{
	int i;
	int a;

	for (i = 0, a = (int) g_1052c60; a < (int) (g_1052c60 + 0x60); a += 0xc, i++) {
		if (*(int*) a == a1) {
			(g_1052c60 + 2)[i * 3] = a2;
			return 1;
		}
	}
	return 0;
}
