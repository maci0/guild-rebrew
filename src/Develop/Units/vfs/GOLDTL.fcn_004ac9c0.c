typedef struct VFS_DIR VFS_DIR;
extern VFS_DIR* g_6b7fdc;

void* __cdecl vfs_Tfopen(const char* name, const char* mode, struct VFS_DIR* root);
unsigned int __cdecl vfs_fwrite(void*, int, int, void*);
#include "Develop/Units/vfs/vfs.h"

struct rec_4ac9c0 {
	int a;
	int b;
	int c;
	char name[16];
	char text[16];
};
// SIZE 0x2c

struct hist_4ac9c0 {
	int n0;
	int n1;
	struct rec_4ac9c0* r0;
	struct rec_4ac9c0* r1;
};
// SIZE 0x10


/* ADDRESS: GOLDTL 0x004ac9c0 */
int __cdecl fcn_004ac9c0(struct hist_4ac9c0* h)
{
	int magic;
	void* f;
	int i;

	magic = 0x68466153;
	f = vfs_Tfopen("/gamedata/ai/historical.dfn", "wb", g_6b7fdc);
	if (f == 0)
		goto out;
	if (vfs_fwrite(&magic, 4, 1, f) <= 0)
		goto fail;
	if (vfs_fwrite(&h->n0, 4, 1, f) <= 0)
		goto fail;
	if (vfs_fwrite(&h->n1, 4, 1, f) <= 0)
		goto fail;
	for (i = 0; i < h->n0; i++) {
		if (vfs_fwrite(&h->r0[i].a, 4, 1, f) <= 0)
			goto fail;
		if (vfs_fwrite(&h->r0[i].b, 4, 1, f) <= 0)
			goto fail;
		if (vfs_fwrite(&h->r0[i].c, 4, 1, f) <= 0)
			goto fail;
		if (vfs_fwrite(h->r0[i].name, 0x10, 1, f) <= 0)
			goto fail;
		if (vfs_fwrite(h->r0[i].text, 0x10, 1, f) <= 0)
			goto fail;
	}
	for (i = 0; i < h->n1; i++) {
		if (vfs_fwrite(&h->r1[i].a, 4, 1, f) <= 0)
			goto fail;
		if (vfs_fwrite(&h->r1[i].b, 4, 1, f) <= 0)
			goto fail;
		if (vfs_fwrite(&h->r1[i].c, 4, 1, f) <= 0)
			goto fail;
		if (vfs_fwrite(h->r1[i].name, 0x10, 1, f) <= 0)
			goto fail;
		if (vfs_fwrite(h->r1[i].text, 0x10, 1, f) <= 0)
			goto fail;
	}
	CloseVfsStream(f);
	return 0;
fail:
	CloseVfsStream(f);
out:
	return -1;
}
