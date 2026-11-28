#include <string.h>

struct VFS_DIR;
extern struct VFS_DIR* vfs_RootDir;
extern int __cdecl CloseVfsStream(void* stream);

void* __cdecl vfs_Tfopen(const char* name, const char* mode, struct VFS_DIR* root);
unsigned int __cdecl vfs_fwrite(const void* data, int size, int count, void* stream);
void __cdecl ls_PrepareSavedSceneRefs(void);
void __cdecl ls_RebindSavedSceneRefs(void);
int __cdecl ls_WriteSaveHeader(void* stream, int flags);
int __cdecl gm_SaveSceneSnapshot(void* stream);
int __cdecl ls_fio_SaveObjekteINST(void* stream);
int __cdecl ls_WriteBuildingEntityState(void* stream);
int __cdecl ls_SaveDynamicEntities(void* stream);
int __cdecl ls_SaveEntities(void* stream);
int __cdecl ls_SaveFiguresAndAnimQueue(void* stream);
int __cdecl ls_SaveMarketsAndSeasons(void* stream);
int __cdecl ls_SaveRelationMatrices(void* stream);
int __cdecl ls_SaveCityStatsAndCrimeGrid(void* stream);
int __cdecl ls_SaveAvatarStatesThunk(void* stream);
int __cdecl he_SaveEvents(void* stream);
int __cdecl ls_SaveCutscenes(void* stream);
int __cdecl ls_SaveHistoryState(void* stream);
int __cdecl ls_SaveNodePools(void* stream);
int __cdecl ls_SaveWeatherAndSlots(void* stream);
int __cdecl amt_fio_SaveAemter(void* stream);
int __cdecl ls_SaveCrimeRecords(void* stream);
int __cdecl ls_SaveMissionJobs(void* stream);
int __cdecl ls_SaveAlchemyDrawSlots(void* stream);
int __cdecl ls_SaveHighOfficeTargets(void* stream);
int __cdecl ls_SaveRoutes(void* stream);
int __cdecl ls_SaveSlot779d00(void* stream);
int __cdecl ls_SaveList774a78(void* stream);

/* ADDRESS: GOLDTL 0x0051e080 */
int __cdecl ls_SaveGame(char* name, char* slot, int flags)
{
	void* stream;

	stream = vfs_Tfopen(name, "wb", vfs_RootDir);
	if (stream == 0)
		return 0;
	strcpy((char*) 0x7e2480, slot);
	ls_PrepareSavedSceneRefs();
	if (ls_WriteSaveHeader(stream, flags) == 0) {
		goto failure;
	}
	vfs_fwrite((void*) 0x699364, 4, 1, stream);
	vfs_fwrite((void*) 0x7749d0, 4, 1, stream);
	vfs_fwrite((void*) 0x7f4c00, 0xe, 1, stream);
	vfs_fwrite((void*) 0x773d75, 1, 1, stream);
	vfs_fwrite(*(char**) 0x773da8 + 4, 4, 1, stream);
	vfs_fwrite((void*) 0x773d68, 4, 1, stream);
	vfs_fwrite((void*) 0x773d6c, 4, 1, stream);
	vfs_fwrite((void*) 0x773d70, 4, 1, stream);
	vfs_fwrite((void*) 0x773d7c, 4, 1, stream);
	vfs_fwrite((void*) 0x100dc00, 0x18, 1, stream);
	vfs_fwrite((void*) 0x699368, 4, 1, stream);
	vfs_fwrite((void*) 0x773d38, 4, 1, stream);
	if (ls_fio_SaveObjekteINST(stream) == 0) {
		CloseVfsStream(stream);
		ls_RebindSavedSceneRefs();
		return 0;
	}
	if (ls_WriteBuildingEntityState(stream) == 0) {
		CloseVfsStream(stream);
		ls_RebindSavedSceneRefs();
		return 0;
	}
	if (ls_SaveDynamicEntities(stream) == 0) {
		CloseVfsStream(stream);
		ls_RebindSavedSceneRefs();
		return 0;
	}
	if (ls_SaveEntities(stream) == 0) {
		CloseVfsStream(stream);
		ls_RebindSavedSceneRefs();
		return 0;
	}
	if (ls_SaveMarketsAndSeasons(stream) == 0) {
		CloseVfsStream(stream);
		ls_RebindSavedSceneRefs();
		return 0;
	}
	if (amt_fio_SaveAemter(stream) == 0) {
		CloseVfsStream(stream);
		ls_RebindSavedSceneRefs();
		return 0;
	}
	if (gm_SaveSceneSnapshot(stream) == 0) {
		CloseVfsStream(stream);
		ls_RebindSavedSceneRefs();
		return 0;
	}
	if (!(flags & 2)) {
		if (ls_SaveCrimeRecords(stream) == 0) {
			CloseVfsStream(stream);
			ls_RebindSavedSceneRefs();
			return 0;
		}
		if (ls_SaveRelationMatrices(stream) == 0) {
			CloseVfsStream(stream);
			ls_RebindSavedSceneRefs();
			return 0;
		}
		if (ls_SaveCityStatsAndCrimeGrid(stream) == 0) {
			CloseVfsStream(stream);
			ls_RebindSavedSceneRefs();
			return 0;
		}
		if (ls_SaveAvatarStatesThunk(stream) == 0) {
			CloseVfsStream(stream);
			ls_RebindSavedSceneRefs();
			return 0;
		}
		if (he_SaveEvents(stream) == 0) {
			CloseVfsStream(stream);
			ls_RebindSavedSceneRefs();
			return 0;
		}
		if (ls_SaveCutscenes(stream) == 0) {
			CloseVfsStream(stream);
			ls_RebindSavedSceneRefs();
			return 0;
		}
		if (ls_SaveHistoryState(stream) == 0) {
			CloseVfsStream(stream);
			ls_RebindSavedSceneRefs();
			return 0;
		}
		if (ls_SaveNodePools(stream) == 0) {
			CloseVfsStream(stream);
			ls_RebindSavedSceneRefs();
			return 0;
		}
		if (ls_SaveWeatherAndSlots(stream) == 0) {
			CloseVfsStream(stream);
			ls_RebindSavedSceneRefs();
			return 0;
		}
		if (ls_SaveFiguresAndAnimQueue(stream) == 0) {
			CloseVfsStream(stream);
			ls_RebindSavedSceneRefs();
			return 0;
		}
		if (ls_SaveMissionJobs(stream) == 0) {
			CloseVfsStream(stream);
			ls_RebindSavedSceneRefs();
			return 0;
		}
		if (ls_SaveSlot779d00(stream) == 0) {
			CloseVfsStream(stream);
			ls_RebindSavedSceneRefs();
			return 0;
		}
		if (ls_SaveList774a78(stream) == 0) {
			CloseVfsStream(stream);
			ls_RebindSavedSceneRefs();
			return 0;
		}
		if (ls_SaveAlchemyDrawSlots(stream) == 0) {
			CloseVfsStream(stream);
			ls_RebindSavedSceneRefs();
			return 0;
		}
		if (ls_SaveHighOfficeTargets(stream) == 0) {
			CloseVfsStream(stream);
			ls_RebindSavedSceneRefs();
			return 0;
		}
		if (ls_SaveRoutes(stream) == 0) {
			CloseVfsStream(stream);
			ls_RebindSavedSceneRefs();
			return 0;
		}
	}
	CloseVfsStream(stream);
	ls_RebindSavedSceneRefs();
	return 1;
failure:
	CloseVfsStream(stream);
	ls_RebindSavedSceneRefs();
	return 0;
}
