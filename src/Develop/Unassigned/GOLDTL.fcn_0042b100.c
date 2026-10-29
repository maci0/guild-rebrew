


extern int* g_6b7ed0[16];

int __cdecl fcn_0042b100(void)
{
	int i;

	for (i = 0; i < 0x10; i++) {
		if (g_6b7ed0[i] == 0) {
			return i;
		}
	}
	return -1;
}
