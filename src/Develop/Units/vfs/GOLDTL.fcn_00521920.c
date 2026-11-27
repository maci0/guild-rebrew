/* File-based savegame loader: opens the file, validates the savegame
 * header and version range, then walks the loader chain of the in-memory
 * counterpart (fcn_00525b40) with the per-version steps. */

#include <string.h>
#include "client_types.h"

extern char* cm_LoadBuf;
extern int ls_SaveVersion;
extern int gm_NextEntityId;
extern int g_699368;
extern int g_7749d0;
extern pos14_7f4c00 gm_GameTime;
extern pos14_7f4c00 g_7e1f70;
extern unsigned char g_773d75;
extern char* gm_CityEntity;
extern int g_773d68;
extern int g_773d6c;
extern int gm_EntityCount;
extern int g_773d7c;
extern int cm_LastCrimeId;
extern int g_100dc00;
extern char* gm_RichterKatholisch;
extern char* gm_RichterEvangelisch;
extern int g_7747b4;
extern int g_6b8300;
extern char g_7e2480[];
extern char g_7f3a5c[];
extern char g_7f39c0[];

#include "Develop/Units/vfs/vfs.h"
extern struct VFS_DIR* g_6b7fdc;
#include "Develop/DieGildeAddOn/loadsave/loadsave.h"

void* __cdecl vfs_Tfopen(const char* cpath, const char* cmode, struct VFS_DIR* root);
void __cdecl gm_KillAllSpieler(void);
void __cdecl ch_ClearCharacters(void);
void __cdecl d3_ClearAllSceneContexts(void);
int __cdecl fcn_005222a0(void* stream);
int __cdecl fcn_00524040(void* stream);
int __cdecl ls_LoadExistingEntities(void* stream);
int __cdecl fcn_00522510(void* stream);
void __cdecl m_FreeTracked(char* p);
int __cdecl amt_fio_LoadAemter(void* stream, int version);
int __cdecl fcn_004f4c40(void* stream);
int __cdecl ls_LoadGameMatrices(void* stream);
int __cdecl fcn_005246e0(unsigned int stream);
int __cdecl fcn_00524b40(void* stream);
int __cdecl fcn_00524b50(void* stream);
int __cdecl fcn_00524fc0(void* stream);
int __cdecl ls_LoadHistoryState(void* stream);
int __cdecl fcn_005252d0(void* stream);
int __cdecl ls_LoadTabAndWeatherState(void* stream);
unsigned int __cdecl gm_RebuildLoadedReferences(void);
int __cdecl d3_SelectSceneContext(int a, int b);
void __cdecl d3_RebuildWorldScene(void);
void __cdecl fcn_00514fc0(void);
int __cdecl ls_LoadCharacter(void* stream);
char* __cdecl gm_LookupEntityRecordById(int handle);
int __cdecl ls_LoadMissionJobs(void* stream);
int __cdecl ls_LoadSlot779d00(void* stream);
int __cdecl ls_LoadList774a78(void* stream);
int __cdecl ls_LoadAlchemyDrawSlots(void* stream);
int __cdecl ls_LoadHighOfficeTargets(void* stream, int version);
int __cdecl fcn_004c0840(int stream);
void __cdecl d3_RefreshBuildingPennants(void);
void __cdecl d3_ResetWorldSceneState(void);
void __cdecl fcn_00516de0(int a, char b);

/* ADDRESS: GOLDTL 0x00521920 */
int __cdecl ls_LoadSavegame(char* cpath)
{
	void* stream;
	int version;

	stream = vfs_Tfopen(cpath, (char*) 0x6750e8, g_6b7fdc);
	if (stream == 0) {
		goto ret0;
	}
	gm_KillAllSpieler();
	ch_ClearCharacters();
	gm_CityEntity = 0;
	gm_RichterKatholisch = 0;
	gm_RichterEvangelisch = 0;
	d3_ClearAllSceneContexts();
	if (ls_LoadSavegameHeader(stream, g_7f39c0) == 0) {
		goto fail;
	}
	version = *(int*) g_7f39c0;
	if (version > 0x1005a) {
		goto fail;
	}
	if (version < 0x10026) {
		goto fail;
	}
	if (ls_ReadVfsDataChecked(&gm_NextEntityId, 4, 1, stream) == 0) {
		goto fail;
	}
	if (ls_ReadVfsDataChecked(&g_7749d0, 4, 1, stream) == 0) {
		goto fail;
	}
	if (ls_ReadVfsDataChecked(&gm_GameTime, 0xe, 1, stream) == 0) {
		goto fail;
	}
	if (ls_ReadVfsDataChecked(&g_773d75, 1, 1, stream) == 0) {
		goto fail;
	}
	if (ls_ReadVfsDataChecked(&gm_CityEntity, 4, 1, stream) == 0) {
		goto fail;
	}
	if (ls_ReadVfsDataChecked(&g_773d68, 4, 1, stream) == 0) {
		goto fail;
	}
	if (ls_ReadVfsDataChecked(&g_773d6c, 4, 1, stream) == 0) {
		goto fail;
	}
	if (ls_ReadVfsDataChecked(&gm_EntityCount, 4, 1, stream) == 0) {
		goto fail;
	}
	if (ls_SaveVersion >= 0x10022) {
		ls_ReadVfsDataChecked(&g_773d7c, 4, 1, stream);
	}
	ls_ReadVfsDataChecked(&g_100dc00, 0x18, 1, stream);
	g_7e1f70 = gm_GameTime;
	if (!(g_7f39c0[4] & 2)) {
		g_7747b4 = *(int*) 0x7f3a58;
	}
	if (ls_SaveVersion >= 0x10030) {
		ls_ReadVfsDataChecked(&g_699368, 4, 1, stream);
	}
	if (ls_SaveVersion >= 0x1003d) {
		ls_ReadVfsDataChecked(&cm_LastCrimeId, 4, 1, stream);
	} else {
		cm_LastCrimeId = 1000000;
	}
	if (ls_LoadExistingEntities(stream) == 0) {
		goto fail;
	}
	if (fcn_00522510(stream) == 0) {
		goto fail;
	}
	if (ls_LoadDynamicEntities(stream) == 0) {
		goto fail;
	}
	if (ls_LoadEntities(stream) == 0) {
		goto fail;
	}
	if (fcn_00524040(stream) == 0) {
		goto fail;
	}
	if (ls_SaveVersion >= 0x10045 && amt_fio_LoadAemter(stream, ls_SaveVersion) == 0) {
		goto fail;
	}
	if (fcn_005222a0(stream) == 0) {
		goto fail;
	}
	if (g_7f39c0[4] & 2) {
		CloseVfsStream(stream);
		gm_RichterKatholisch = 0;
		gm_RichterEvangelisch = 0;
		if (gm_RebuildLoadedReferences()) {
			return 1;
		}
		goto fail;
	}
	if (ls_SaveVersion < 0x10045 && amt_fio_LoadAemter(stream, ls_SaveVersion) == 0) {
		goto fail;
	}
	if (fcn_004f4c40(stream) == 0) {
		goto fail;
	}
	if (ls_SaveVersion >= 0x10016 && ls_LoadGameMatrices(stream) == 0) {
		goto fail;
	}
	if (fcn_005246e0((unsigned int) stream) == 0) {
		goto fail;
	}
	if (ls_SaveVersion >= 0x1002a && fcn_00524b40(stream) == 0) {
		goto fail;
	}
	if (fcn_00524b50(stream) == 0) {
		goto fail;
	}
	if (fcn_00524fc0(stream) == 0) {
		goto fail;
	}
	if (ls_LoadHistoryState(stream) == 0) {
		goto fail;
	}
	if (fcn_005252d0(stream) == 0) {
		CloseVfsStream(stream);
		gm_RebuildLoadedReferences();
		return 0;
	}
	if (ls_SaveVersion >= 0x1002e && ls_LoadTabAndWeatherState(stream) == 0) {
		goto fail;
	}
	if (gm_RebuildLoadedReferences() == 0) {
		goto fail;
	}
	d3_SelectSceneContext(0, 1);
	d3_RebuildWorldScene();
	fcn_00514fc0();
	if (ls_LoadCharacter(stream) == 0) {
		CloseVfsStream(stream);
		m_FreeTracked(cm_LoadBuf);
		cm_LoadBuf = 0;
		return 0;
	}
	gm_RichterKatholisch = gm_LookupEntityRecordById((int) gm_RichterKatholisch);
	gm_RichterEvangelisch = gm_LookupEntityRecordById((int) gm_RichterEvangelisch);
	if (ls_LoadMissionJobs(stream) == 0) {
		CloseVfsStream(stream);
		m_FreeTracked(cm_LoadBuf);
		cm_LoadBuf = 0;
		return 0;
	}
	if (ls_SaveVersion >= 0x10029 && ls_LoadSlot779d00(stream) == 0) {
		CloseVfsStream(stream);
		m_FreeTracked(cm_LoadBuf);
		cm_LoadBuf = 0;
		return 0;
	}
	if (ls_SaveVersion >= 0x10047 && ls_LoadList774a78(stream) == 0) {
		CloseVfsStream(stream);
		m_FreeTracked(cm_LoadBuf);
		cm_LoadBuf = 0;
		return 0;
	}
	if (ls_SaveVersion >= 0x10049 && ls_LoadAlchemyDrawSlots(stream) == 0) {
		CloseVfsStream(stream);
		m_FreeTracked(cm_LoadBuf);
		cm_LoadBuf = 0;
		return 0;
	}
	if (ls_SaveVersion >= 0x10052 && ls_LoadHighOfficeTargets(stream, ls_SaveVersion) == 0) {
		CloseVfsStream(stream);
		m_FreeTracked(cm_LoadBuf);
		cm_LoadBuf = 0;
		return 0;
	}
	if (ls_SaveVersion >= 0x10053 && fcn_004c0840((int) stream) == 0) {
		CloseVfsStream(stream);
		m_FreeTracked(cm_LoadBuf);
		cm_LoadBuf = 0;
		return 0;
	}
	CloseVfsStream(stream);
	d3_RefreshBuildingPennants();
	d3_RebuildWorldScene();
	d3_ResetWorldSceneState();
	fcn_00516de0(g_6b8300, 1);
	strcpy(g_7e2480, g_7f3a5c);
	return 1;

fail:
	CloseVfsStream(stream);
ret0:
	return 0;
}
