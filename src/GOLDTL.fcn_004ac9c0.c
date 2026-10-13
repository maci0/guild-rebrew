typedef struct VFS_DIR VFS_DIR;
extern VFS_DIR* g_6b7fdc;

void* __cdecl fcn_0042ff50(char*, char*, int);
unsigned int __cdecl fcn_00430910(void*, int, int, void*);
int __cdecl CloseVfsStream(void* stream);

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

// FUNCTION: GOLDTL 0x4ac9c0
// FUNCTION: GOLD 0x004ac8a0

int __cdecl fcn_004ac9c0(struct hist_4ac9c0* h)
{
	int magic;
	void* f;
	int i;

	magic = 0x68466153;
	f = fcn_0042ff50("/gamedata/ai/historical.dfn", "wb", (int) g_6b7fdc);
	if (f == 0)
		goto out;
	if (fcn_00430910(&magic, 4, 1, f) <= 0)
		goto fail;
	if (fcn_00430910(&h->n0, 4, 1, f) <= 0)
		goto fail;
	if (fcn_00430910(&h->n1, 4, 1, f) <= 0)
		goto fail;
	for (i = 0; i < h->n0; i++) {
		if (fcn_00430910(&h->r0[i].a, 4, 1, f) <= 0)
			goto fail;
		if (fcn_00430910(&h->r0[i].b, 4, 1, f) <= 0)
			goto fail;
		if (fcn_00430910(&h->r0[i].c, 4, 1, f) <= 0)
			goto fail;
		if (fcn_00430910(h->r0[i].name, 0x10, 1, f) <= 0)
			goto fail;
		if (fcn_00430910(h->r0[i].text, 0x10, 1, f) <= 0)
			goto fail;
	}
	for (i = 0; i < h->n1; i++) {
		if (fcn_00430910(&h->r1[i].a, 4, 1, f) <= 0)
			goto fail;
		if (fcn_00430910(&h->r1[i].b, 4, 1, f) <= 0)
			goto fail;
		if (fcn_00430910(&h->r1[i].c, 4, 1, f) <= 0)
			goto fail;
		if (fcn_00430910(h->r1[i].name, 0x10, 1, f) <= 0)
			goto fail;
		if (fcn_00430910(h->r1[i].text, 0x10, 1, f) <= 0)
			goto fail;
	}
	CloseVfsStream(f);
	return 0;
fail:
	CloseVfsStream(f);
out:
	return -1;
}
