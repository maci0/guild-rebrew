#include "g_772f90.h"

struct VFS_DIR;

extern struct VFS_DIR* g_6b7fdc;
extern int g_772fd8;
extern Draw772* g_772fdc;
extern int g_772fe0;
extern Rec772fe4* g_772fe4;

void* __cdecl fcn_0042ff50(const char* name, const char* mode, struct VFS_DIR* root);
unsigned int __cdecl fcn_004306b0(char* buf, unsigned int size, unsigned int count, void* f);
char* __cdecl m_alloc(unsigned int size, char* label);
void __cdecl m_FreeTracked(void* p);
void __cdecl fcn_00430580(void* f);

/* Loads the alchemy card deck tables. The file starts with a magic dword,
 * then the prototype row count and rows, then the recipe row count and
 * rows. Any short read frees both tables again. */
/* ADDRESS: GOLDTL 0x004ed800 */
int __cdecl fcn_004ed800(void)
{
	void* f;
	unsigned int magic;
	int i;
	int off;

	f = fcn_0042ff50("/gamedata/ai/alchemy.dfn", "rb", g_6b7fdc);
	if (f == 0) {
		goto done;
	}
	if (fcn_004306b0((char*) &magic, 4, 1, f) <= 0) {
		goto fail;
	}
	if (magic != 0x61486d52) {
		goto fail;
	}
	if (fcn_004306b0((char*) &g_772fd8, 4, 1, f) <= 0) {
		goto fail;
	}
	if (g_772fd8 < 1 || g_772fd8 > 100) {
		goto fail;
	}
	if (g_772fdc != 0) {
		m_FreeTracked(g_772fdc);
		g_772fdc = 0;
	}
	g_772fdc = (Draw772*) m_alloc(g_772fd8 * 12, "ahm_AllocPlayerPrototypes");
	if (g_772fdc == 0) {
		goto fail;
	}
	for (i = 0; i < g_772fd8; i++) {
		off = i * 12;
		if (fcn_004306b0((char*) g_772fdc + off, 1, 1, f) <= 0) {
			goto fail;
		}
		if (fcn_004306b0((char*) g_772fdc + off + 1, 1, 1, f) <= 0) {
			goto fail;
		}
		if (fcn_004306b0((char*) g_772fdc + off + 2, 1, 1, f) <= 0) {
			goto fail;
		}
		if (fcn_004306b0((char*) g_772fdc + off + 3, 1, 1, f) <= 0) {
			goto fail;
		}
		if (fcn_004306b0((char*) g_772fdc + off + 4, 1, 1, f) <= 0) {
			goto fail;
		}
		if (fcn_004306b0((char*) g_772fdc + off + 8, 4, 1, f) <= 0) {
			goto fail;
		}
	}
	if (fcn_004306b0((char*) &g_772fe0, 4, 1, f) <= 0) {
		goto fail;
	}
	if (g_772fe0 < 1 || g_772fe0 > 100) {
		goto fail;
	}
	if (g_772fe4 != 0) {
		m_FreeTracked(g_772fe4);
		g_772fe4 = 0;
	}
	g_772fe4 = (Rec772fe4*) m_alloc(g_772fe0 * 12, "ahm_AllocRecipePrototypes");
	if (g_772fe4 == 0) {
		goto fail;
	}
	for (i = 0; i < g_772fe0; i++) {
		off = i * 12;
		if (fcn_004306b0((char*) g_772fe4 + off, 4, 1, f) <= 0) {
			goto fail;
		}
		if (fcn_004306b0((char*) g_772fe4 + off + 4, 4, 1, f) <= 0) {
			goto fail;
		}
		if (fcn_004306b0((char*) g_772fe4 + off + 8, 4, 1, f) <= 0) {
			goto fail;
		}
	}
	fcn_00430580(f);
	return 1;

fail:
	fcn_00430580(f);
done:
	if (g_772fdc != 0) {
		m_FreeTracked(g_772fdc);
		g_772fdc = 0;
	}
	if (g_772fe4 != 0) {
		m_FreeTracked(g_772fe4);
		g_772fe4 = 0;
	}
	g_772fe0 = 0;
	g_772fd8 = 0;
	return 0;
}
