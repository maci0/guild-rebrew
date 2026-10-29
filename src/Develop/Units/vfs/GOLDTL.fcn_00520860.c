extern char g_869480[0x300][0x300];
extern char g_90e0a0[0x300][0x300];




unsigned int __cdecl vfs_fwrite(void*, int, int, int);

int __cdecl fcn_00520860(int x)
{
	int i;
	int j;

	for (j = 0; j < 0x300; j++) {
		for (i = 0; i < 0x300; i++) {
			if (vfs_fwrite(&g_869480[j][i], 1, 1, x) <= 0) {
				return 0;
			}
		}
	}
	for (j = 0; j < 0x300; j++) {
		for (i = 0; i < 0x300; i++) {
			if (vfs_fwrite(&g_90e0a0[j][i], 1, 1, x) <= 0) {
				return 0;
			}
		}
	}
	return 1;
}
