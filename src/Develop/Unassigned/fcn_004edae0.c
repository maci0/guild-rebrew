struct VFS_DIR;
extern struct VFS_DIR* g_6b7fdc;
void* __cdecl vfs_Tfopen(char* path, char* mode, struct VFS_DIR* root);
unsigned int __cdecl vfs_fwrite(void* buf, int size, int count, char* stream);
int __cdecl CloseVfsStream(void* stream);

/* ADDRESS: GOLDTL 0x004edae0 */
int __cdecl fcn_004edae0(void)
{
	void* f;
	unsigned int magic;
	int i;
	int off;
	char* rec;

	magic = 0x61486d52;
	f = vfs_Tfopen((char*) 0x68dfec, (char*) 0x6790b0, g_6b7fdc);
	if (f == 0) {
		return 0;
	}
	if (vfs_fwrite((char*) &magic, 4, 1, (char*) f) == 0) {
		goto fail;
	}
	if (vfs_fwrite((char*) 0x772fd8, 4, 1, (char*) f) == 0) {
		goto fail;
	}
	for (i = 0; i < *(int*) 0x772fd8; i++) {
		off = i * 12;
		rec = *(char**) 0x772fdc + off;
		if (vfs_fwrite(rec, 1, 1, (char*) f) == 0) {
			goto fail;
		}
		if (vfs_fwrite(rec + 1, 1, 1, (char*) f) == 0) {
			goto fail;
		}
		if (vfs_fwrite(rec + 2, 1, 1, (char*) f) == 0) {
			goto fail;
		}
		if (vfs_fwrite(rec + 3, 1, 1, (char*) f) == 0) {
			goto fail;
		}
		if (vfs_fwrite(rec + 4, 1, 1, (char*) f) == 0) {
			goto fail;
		}
		if (vfs_fwrite(rec + 8, 4, 1, (char*) f) == 0) {
			goto fail;
		}
	}
	if (vfs_fwrite((char*) 0x772fe0, 4, 1, (char*) f) == 0) {
		goto fail;
	}
	for (i = 0; i < *(int*) 0x772fe0; i++) {
		off = i * 12;
		rec = *(char**) 0x772fe4 + off;
		if (vfs_fwrite(rec, 4, 1, (char*) f) == 0) {
			goto fail;
		}
		if (vfs_fwrite(rec + 4, 4, 1, (char*) f) == 0) {
			goto fail;
		}
		if (vfs_fwrite(rec + 8, 4, 1, (char*) f) == 0) {
			goto fail;
		}
	}
	CloseVfsStream(f);
	return 1;
fail:
	CloseVfsStream(f);
	return 0;
}
