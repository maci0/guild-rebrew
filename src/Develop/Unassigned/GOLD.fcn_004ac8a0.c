typedef struct VFS_DIR VFS_DIR;


void* __cdecl fcn_00430470(const char* name, const char* mode, struct VFS_DIR* root);
unsigned int __cdecl vfs_fwrite(void*, int, int, void*);
int __cdecl fcn_00430aa0(void*);

struct rec_4ac9c0 {
	int a;
	int b;
	int c;
	char name[16];
	char text[16];
};
/* SIZE 0x2c */

struct hist_4ac9c0 {
	int n0;
	int n1;
	struct rec_4ac9c0* r0;
	struct rec_4ac9c0* r1;
};
/* SIZE 0x10 */


/* ADDRESS: GOLD 0x004ac8a0 */
int __cdecl fcn_004ac8a0(struct hist_4ac9c0* h)
{
	int magic;
	void* f;
	int i;

	magic = 0x68466153;
	f = fcn_00430470("/gamedata/ai/historical.dfn", "wb", (*(VFS_DIR**) 0x6333fc));
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
	fcn_00430aa0(f);
	return 0;
fail:
	fcn_00430aa0(f);
out:
	return -1;
}
