#include "Develop/DieGildeAddOn/game/alchemy_player_prototype.h"

struct VFS_DIR;

extern struct VFS_DIR* vfs_RootDir;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern ALCHEMY_PLAYER_PROTOTYPE* ahm_PlayerPrototypes;
extern int g_772fe0;
extern ALCHEMY_RECIPE_PROTOTYPE* ahm_RecipePrototypes;

void* __cdecl vfs_Tfopen(const char* name, const char* mode, struct VFS_DIR* root);
unsigned int __cdecl vfs_ReadData(char* buf, unsigned int size, unsigned int count, void* f);
char* __cdecl m_alloc(unsigned int size, char* label);
void __cdecl m_FreeTracked(void* p);
void __cdecl CloseVfsStream(void* f);

/* Loads the alchemy card deck tables. The file starts with a magic dword,
 * then the prototype row count and rows, then the recipe row count and
 * rows. Any short read frees both tables again. */
/* ADDRESS: GOLDTL 0x004ed800 */
/* ADDRESS: GOLDDE 0x004d9c50 */
int __cdecl ahm_LoadAlchemyData(void)
{
	void* f;
	unsigned int magic;
	int i;
	int off;

	f = vfs_Tfopen("/gamedata/ai/alchemy.dfn", "rb", vfs_RootDir);
	if (f == 0) {
		goto done;
	}
	if (vfs_ReadData((char*) &magic, 4, 1, f) <= 0) {
		goto fail;
	}
	if (magic != 0x61486d52) {
		goto fail;
	}
	if (vfs_ReadData((char*) &ahm_PlayerPrototypeCount, 4, 1, f) <= 0) {
		goto fail;
	}
	if (ahm_PlayerPrototypeCount < 1 || ahm_PlayerPrototypeCount > 100) {
		goto fail;
	}
	if (ahm_PlayerPrototypes != 0) {
		m_FreeTracked(ahm_PlayerPrototypes);
		ahm_PlayerPrototypes = 0;
	}
	ahm_PlayerPrototypes = (ALCHEMY_PLAYER_PROTOTYPE*) m_alloc(ahm_PlayerPrototypeCount * 12, "ahm_AllocPlayerPrototypes");
	if (ahm_PlayerPrototypes == 0) {
		goto fail;
	}
	for (i = 0; i < ahm_PlayerPrototypeCount; i++) {
		off = i * 12;
		if (vfs_ReadData((char*) ahm_PlayerPrototypes + off, 1, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) ahm_PlayerPrototypes + off + 1, 1, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) ahm_PlayerPrototypes + off + 2, 1, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) ahm_PlayerPrototypes + off + 3, 1, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) ahm_PlayerPrototypes + off + 4, 1, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) ahm_PlayerPrototypes + off + 8, 4, 1, f) <= 0) {
			goto fail;
		}
	}
	if (vfs_ReadData((char*) &g_772fe0, 4, 1, f) <= 0) {
		goto fail;
	}
	if (g_772fe0 < 1 || g_772fe0 > 100) {
		goto fail;
	}
	if (ahm_RecipePrototypes != 0) {
		m_FreeTracked(ahm_RecipePrototypes);
		ahm_RecipePrototypes = 0;
	}
	ahm_RecipePrototypes = (ALCHEMY_RECIPE_PROTOTYPE*) m_alloc(g_772fe0 * 12, "ahm_AllocRecipePrototypes");
	if (ahm_RecipePrototypes == 0) {
		goto fail;
	}
	for (i = 0; i < g_772fe0; i++) {
		off = i * 12;
		if (vfs_ReadData((char*) ahm_RecipePrototypes + off, 4, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) ahm_RecipePrototypes + off + 4, 4, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) ahm_RecipePrototypes + off + 8, 4, 1, f) <= 0) {
			goto fail;
		}
	}
	CloseVfsStream(f);
	return 1;

fail:
	CloseVfsStream(f);
done:
	if (ahm_PlayerPrototypes != 0) {
		m_FreeTracked(ahm_PlayerPrototypes);
		ahm_PlayerPrototypes = 0;
	}
	if (ahm_RecipePrototypes != 0) {
		m_FreeTracked(ahm_RecipePrototypes);
		ahm_RecipePrototypes = 0;
	}
	g_772fe0 = 0;
	ahm_PlayerPrototypeCount = 0;
	return 0;
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_772f90[76];
unsigned char _dpad_772fe4[468];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_772f9c[60];
unsigned char _dpad_772fec[12];
unsigned char _dpad_773018[416];
#endif
