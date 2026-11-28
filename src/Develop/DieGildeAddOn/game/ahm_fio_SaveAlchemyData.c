struct VFS_DIR;
#include "Develop/DieGildeAddOn/game/alchemy_player_prototype.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
extern ALCHEMY_PLAYER_PROTOTYPE* ahm_PlayerPrototypes;
extern int g_772fe0;
extern ALCHEMY_RECIPE_PROTOTYPE* ahm_RecipePrototypes;
extern struct VFS_DIR* vfs_RootDir;
void* __cdecl vfs_Tfopen(char* path, char* mode, struct VFS_DIR* root);
unsigned int __cdecl vfs_fwrite(void* buf, int size, int count, char* stream);
int __cdecl CloseVfsStream(void* stream);

/* ADDRESS: GOLDTL 0x004edae0 */
int __cdecl ahm_fio_SaveAlchemyData(void)
{
	void* f;
	unsigned int magic;
	int i;



	magic = 0x61486d52;
	f = vfs_Tfopen((char*) 0x68dfec, g_6790b0, vfs_RootDir);
	if (f == 0) {
		goto no_file;
	}
	if (vfs_fwrite((char*) &magic, 4, 1, (char*) f) <= 0) {
		goto fail;
	}
	if (vfs_fwrite(&ahm_PlayerPrototypeCount, 4, 1, (char*) f) <= 0) {
		goto fail;
	}
	for (i = 0; i < ahm_PlayerPrototypeCount; i++) {


		if (vfs_fwrite(&ahm_PlayerPrototypes[i].b, 1, 1, (char*) f) <= 0) {
			goto fail;
		}
		if (vfs_fwrite(&ahm_PlayerPrototypes[i].c, 1, 1, (char*) f) <= 0) {
			goto fail;
		}
		if (vfs_fwrite(&ahm_PlayerPrototypes[i].d, 1, 1, (char*) f) <= 0) {
			goto fail;
		}
		if (vfs_fwrite(&ahm_PlayerPrototypes[i].e, 1, 1, (char*) f) <= 0) {
			goto fail;
		}
		if (vfs_fwrite(&ahm_PlayerPrototypes[i].k, 1, 1, (char*) f) <= 0) {
			goto fail;
		}
		if (vfs_fwrite(&ahm_PlayerPrototypes[i].f, 4, 1, (char*) f) <= 0) {
			goto fail;
		}
	}
	if (vfs_fwrite(&g_772fe0, 4, 1, (char*) f) <= 0) {
		goto fail;
	}
	for (i = 0; i < g_772fe0; i++) {


		if (vfs_fwrite(&ahm_RecipePrototypes[i].key, 4, 1, (char*) f) <= 0) {
			goto fail;
		}
		if (vfs_fwrite(&ahm_RecipePrototypes[i].a, 4, 1, (char*) f) <= 0) {
			goto fail;
		}
		if (vfs_fwrite(&ahm_RecipePrototypes[i].b, 4, 1, (char*) f) <= 0) {
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
