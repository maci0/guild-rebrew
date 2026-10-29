/* File-based savegame loader: opens the file, validates the savegame
 * header and version range, then walks the loader chain of the in-memory
 * counterpart (fcn_00525b40) with the per-version steps. */

#include <string.h>
#include "client_types.h"

extern char* cm_LoadBuf;
extern int g_6a23ac;
extern int g_699364;
extern int g_699368;
extern int g_7749d0;
extern pos14_7f4c00 g_7f4c00;
extern pos14_7f4c00 g_7e1f70;
extern unsigned char g_773d75;
extern char* g_773da8;
extern int g_773d68;
extern int g_773d6c;
extern int g_773d70;
extern int g_773d7c;
extern int g_773d38;
extern int g_100dc00;
extern char* gm_RichterKatholisch;
extern char* gm_RichterEvangelisch;
extern int g_7747b4;
extern int g_6b8300;
extern char g_7e2480[];
extern char g_7f3a5c[];
extern char g_7f39c0[];

#include "Develop/Units/vfs/vfs.h"
#include "Develop/DieGildeAddOn/loadsave/loadsave.h"

void* __cdecl vfs_Tfopen(const char* cpath, const char* cmode, struct VFS_DIR* root);
void __cdecl gm_KillAllSpieler(void);
void __cdecl fcn_0040c070(void);
void __cdecl fcn_00510930(void);
int __cdecl fcn_005222a0(void* stream);
int __cdecl fcn_00524040(void* stream);
int __cdecl ls_LoadExistingEntities(void* stream);
int __cdecl fcn_00522510(void* stream);
void __cdecl m_FreeTracked(char* p);
int __cdecl amt_fio_LoadAemter(void* stream, int version);
int __cdecl fcn_004f4c40(void* stream);
int __cdecl fcn_00524610(void* stream);
int __cdecl fcn_005246e0(unsigned int stream);
int __cdecl fcn_00524b40(void* stream);
int __cdecl fcn_00524b50(void* stream);
int __cdecl fcn_00524fc0(void* stream);
int __cdecl fcn_005251c0(void* stream);
int __cdecl fcn_005252d0(void* stream);
int __cdecl fcn_005255b0(void* stream);
unsigned int __cdecl fcn_00525670(void);
int __cdecl fcn_004432d0(int a, int b);
void __cdecl fcn_00514f10(void);
void __cdecl fcn_00514fc0(void);
int __cdecl ls_LoadCharacter(void* stream);
char* __cdecl fcn_00508e40(int handle);
int __cdecl fcn_004b6580(void* stream);
int __cdecl fcn_00592370(void* stream);
int __cdecl fcn_005b1ff0(void* stream);
int __cdecl fcn_004edec0(void* stream);
int __cdecl fcn_004adba0(void* stream, int version);
int __cdecl fcn_004c0840(int stream);
void __cdecl fcn_0052de50(void);
void __cdecl fcn_00516f60(void);
void __cdecl fcn_00516de0(int a, char b);

/* ADDRESS: GOLDTL 0x00521920 */
int __cdecl fcn_00521920(char* cpath)
{
	void* stream;
	int version;

	stream = vfs_Tfopen(cpath, (char*) 0x6750e8, *(void**) 0x6b7fdc);
	if (stream == 0) {
		goto ret0;
	}
	gm_KillAllSpieler();
	fcn_0040c070();
	g_773da8 = 0;
	gm_RichterKatholisch = 0;
	gm_RichterEvangelisch = 0;
	fcn_00510930();
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
	if (ls_ReadVfsDataChecked(&g_699364, 4, 1, stream) == 0) {
		goto fail;
	}
	if (ls_ReadVfsDataChecked(&g_7749d0, 4, 1, stream) == 0) {
		goto fail;
	}
	if (ls_ReadVfsDataChecked(&g_7f4c00, 0xe, 1, stream) == 0) {
		goto fail;
	}
	if (ls_ReadVfsDataChecked(&g_773d75, 1, 1, stream) == 0) {
		goto fail;
	}
	if (ls_ReadVfsDataChecked(&g_773da8, 4, 1, stream) == 0) {
		goto fail;
	}
	if (ls_ReadVfsDataChecked(&g_773d68, 4, 1, stream) == 0) {
		goto fail;
	}
	if (ls_ReadVfsDataChecked(&g_773d6c, 4, 1, stream) == 0) {
		goto fail;
	}
	if (ls_ReadVfsDataChecked(&g_773d70, 4, 1, stream) == 0) {
		goto fail;
	}
	if (g_6a23ac >= 0x10022) {
		ls_ReadVfsDataChecked(&g_773d7c, 4, 1, stream);
	}
	ls_ReadVfsDataChecked(&g_100dc00, 0x18, 1, stream);
	g_7e1f70 = g_7f4c00;
	if (!(g_7f39c0[4] & 2)) {
		g_7747b4 = *(int*) 0x7f3a58;
	}
	if (g_6a23ac >= 0x10030) {
		ls_ReadVfsDataChecked(&g_699368, 4, 1, stream);
	}
	if (g_6a23ac >= 0x1003d) {
		ls_ReadVfsDataChecked(&g_773d38, 4, 1, stream);
	} else {
		g_773d38 = 1000000;
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
	if (g_6a23ac >= 0x10045 && amt_fio_LoadAemter(stream, g_6a23ac) == 0) {
		goto fail;
	}
	if (fcn_005222a0(stream) == 0) {
		goto fail;
	}
	if (g_7f39c0[4] & 2) {
		CloseVfsStream(stream);
		gm_RichterKatholisch = 0;
		gm_RichterEvangelisch = 0;
		if (fcn_00525670()) {
			return 1;
		}
		goto fail;
	}
	if (g_6a23ac < 0x10045 && amt_fio_LoadAemter(stream, g_6a23ac) == 0) {
		goto fail;
	}
	if (fcn_004f4c40(stream) == 0) {
		goto fail;
	}
	if (g_6a23ac >= 0x10016 && fcn_00524610(stream) == 0) {
		goto fail;
	}
	if (fcn_005246e0((unsigned int) stream) == 0) {
		goto fail;
	}
	if (g_6a23ac >= 0x1002a && fcn_00524b40(stream) == 0) {
		goto fail;
	}
	if (fcn_00524b50(stream) == 0) {
		goto fail;
	}
	if (fcn_00524fc0(stream) == 0) {
		goto fail;
	}
	if (fcn_005251c0(stream) == 0) {
		goto fail;
	}
	if (fcn_005252d0(stream) == 0) {
		CloseVfsStream(stream);
		fcn_00525670();
		return 0;
	}
	if (g_6a23ac >= 0x1002e && fcn_005255b0(stream) == 0) {
		goto fail;
	}
	if (fcn_00525670() == 0) {
		goto fail;
	}
	fcn_004432d0(0, 1);
	fcn_00514f10();
	fcn_00514fc0();
	if (ls_LoadCharacter(stream) == 0) {
		CloseVfsStream(stream);
		m_FreeTracked(cm_LoadBuf);
		cm_LoadBuf = 0;
		return 0;
	}
	gm_RichterKatholisch = fcn_00508e40((int) gm_RichterKatholisch);
	gm_RichterEvangelisch = fcn_00508e40((int) gm_RichterEvangelisch);
	if (fcn_004b6580(stream) == 0) {
		CloseVfsStream(stream);
		m_FreeTracked(cm_LoadBuf);
		cm_LoadBuf = 0;
		return 0;
	}
	if (g_6a23ac >= 0x10029 && fcn_00592370(stream) == 0) {
		CloseVfsStream(stream);
		m_FreeTracked(cm_LoadBuf);
		cm_LoadBuf = 0;
		return 0;
	}
	if (g_6a23ac >= 0x10047 && fcn_005b1ff0(stream) == 0) {
		CloseVfsStream(stream);
		m_FreeTracked(cm_LoadBuf);
		cm_LoadBuf = 0;
		return 0;
	}
	if (g_6a23ac >= 0x10049 && fcn_004edec0(stream) == 0) {
		CloseVfsStream(stream);
		m_FreeTracked(cm_LoadBuf);
		cm_LoadBuf = 0;
		return 0;
	}
	if (g_6a23ac >= 0x10052 && fcn_004adba0(stream, g_6a23ac) == 0) {
		CloseVfsStream(stream);
		m_FreeTracked(cm_LoadBuf);
		cm_LoadBuf = 0;
		return 0;
	}
	if (g_6a23ac >= 0x10053 && fcn_004c0840((int) stream) == 0) {
		CloseVfsStream(stream);
		m_FreeTracked(cm_LoadBuf);
		cm_LoadBuf = 0;
		return 0;
	}
	CloseVfsStream(stream);
	fcn_0052de50();
	fcn_00514f10();
	fcn_00516f60();
	fcn_00516de0(g_6b8300, 1);
	strcpy(g_7e2480, g_7f3a5c);
	return 1;

fail:
	CloseVfsStream(stream);
ret0:
	return 0;
}
