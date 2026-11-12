struct VFS_DIR;
#include "g_772f90.h"
extern int g_772fd8;
extern Draw772* g_772fdc;
extern int g_772fe0;
extern Rec772fe4* g_772fe4;
extern char g_6790b0[];
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



	magic = 0x61486d52;
	f = vfs_Tfopen((char*) 0x68dfec, g_6790b0, g_6b7fdc);
	if (f == 0) {
		goto no_file;
	}
	if (vfs_fwrite((char*) &magic, 4, 1, (char*) f) <= 0) {
		goto fail;
	}
	if (vfs_fwrite(&g_772fd8, 4, 1, (char*) f) <= 0) {
		goto fail;
	}
	for (i = 0; i < g_772fd8; i++) {


		if (vfs_fwrite(&g_772fdc[i].b, 1, 1, (char*) f) <= 0) {
			goto fail;
		}
		if (vfs_fwrite(&g_772fdc[i].c, 1, 1, (char*) f) <= 0) {
			goto fail;
		}
		if (vfs_fwrite(&g_772fdc[i].d, 1, 1, (char*) f) <= 0) {
			goto fail;
		}
		if (vfs_fwrite(&g_772fdc[i].e, 1, 1, (char*) f) <= 0) {
			goto fail;
		}
		if (vfs_fwrite(&g_772fdc[i].k, 1, 1, (char*) f) <= 0) {
			goto fail;
		}
		if (vfs_fwrite(&g_772fdc[i].f, 4, 1, (char*) f) <= 0) {
			goto fail;
		}
	}
	if (vfs_fwrite(&g_772fe0, 4, 1, (char*) f) <= 0) {
		goto fail;
	}
	for (i = 0; i < g_772fe0; i++) {


		if (vfs_fwrite(&g_772fe4[i].key, 4, 1, (char*) f) <= 0) {
			goto fail;
		}
		if (vfs_fwrite(&g_772fe4[i].a, 4, 1, (char*) f) <= 0) {
			goto fail;
		}
		if (vfs_fwrite(&g_772fe4[i].b, 4, 1, (char*) f) <= 0) {
			goto fail;
		}
	}
	CloseVfsStream(f);
	return 1;
fail:
	CloseVfsStream(f);
no_file:
	return 0;
}
