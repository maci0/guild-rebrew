typedef struct {
	int f0;
	int f4;
	char st[0xe];
	char pad16[2];
	int f18;
	int f1c;
	char f20;
	char pad21[3];
} rec24;
// SIZE 0x24

extern signed char g_6a3440;
extern char g_10069a0[];

unsigned int __cdecl vfs_fwrite(void* buf, int size, int count, char* stream);

/* ADDRESS: GOLDTL 0x004b64b0 */
int __cdecl fcn_004b64b0(char* file)
{
	int i;

	if (!file)
		return 0;
	if (vfs_fwrite(&g_6a3440, 1, 1, file) == -1)
		return 0;
	for (i = 0; i < 128; i++) {
		if (vfs_fwrite(&((rec24*)g_10069a0)[i].f0, 4, 1, file) == -1)
			return 0;
		if (vfs_fwrite(&((rec24*)g_10069a0)[i].f4, 4, 1, file) == -1)
			return 0;
		if (vfs_fwrite(((rec24*)g_10069a0)[i].st, 0xe, 1, file) == -1)
			return 0;
		if (vfs_fwrite(&((rec24*)g_10069a0)[i].f18, 4, 1, file) == -1)
			return 0;
		if (vfs_fwrite(&((rec24*)g_10069a0)[i].f1c, 4, 1, file) == -1)
			return 0;
		if (vfs_fwrite(&((rec24*)g_10069a0)[i].f20, 1, 1, file) == -1)
			return 0;
	}
	return 1;
}
