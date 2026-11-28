


#include <stdio.h>
#include <string.h>

// SIZE 0x8
typedef struct {
	int id;
	int pad;
} Peer;

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"







// SIZE 0x7c
typedef struct {
	int handle;
	unsigned int crc;
	char pad[0x74];
} Hello;

extern int main_LoopFlags;
extern Peer g_7f3ac0[8];
extern unsigned char gm_ClientModeFlags;
extern char* g_14ac60c;
extern unsigned char gm_PlayerCount;

extern char g_7e2480[];
extern int cm_SaveRequestSlot;
extern char ls_SaveSlotIndex;
typedef struct VFS_DIR VFS_DIR;
extern VFS_DIR* vfs_RootDir;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char str_empty[];

void __cdecl cm_SaveGameAndWait(int, char*);
void __cdecl ls_LoadSavePreview(char*);
void* __cdecl vfs_Tfopen(const char* name, const char* mode, struct VFS_DIR* root);
int __cdecl ls_WriteSaveHeader(void* stream, int flags);
#include "Develop/Units/vfs/vfs.h"
#include "Develop/DieGildeAddOn/loadsave/loadsave.h"
unsigned int __cdecl vfs_CalcCrc32(unsigned char*, unsigned int);
int __cdecl cm_RequestSysMessage(int, void*);
void __cdecl cm_StepCommandQueue(void);
void __cdecl ls_SaveGame(char*, char*, int);
void __cdecl d2_ShowStatusBanner(char*);

void __cdecl ls_SaveNetworkGame(char* name, char* title)
{
	unsigned int crc;
	Hello m;
	char path[0x104];
	char hdr[0xfc];
	int i;
	void* f;
	int n;

	crc = 0;
	main_LoopFlags |= 0x20000;
	for (i = 0; i < 8; i++) {
		g_7f3ac0[i].id = -1;
	}
	if (gm_ClientModeFlags & 4) {
		cm_SaveGameAndWait(main_LoopFlags, g_14ac60c);
		gm_PlayerCount = 0;
		for (i = 0; i < 768; i++) {
			if (((ENTITY_RECORD*)gm_EntitySlotTable)[i].entity_index != 0xffff && (((ENTITY_RECORD*)gm_EntitySlotTable)[i].entity_state == 6 || ((ENTITY_RECORD*)gm_EntitySlotTable)[i].entity_state == 7)) {
				gm_PlayerCount++;
			}
		}
		strcpy(g_7e2480, title);
		ls_SaveSlotIndex = (*(char *)&cm_SaveRequestSlot);
		ls_LoadSavePreview("Gamedata/cities/standard.scr");
		sprintf(path, "Gamedata\\network\\%s.SAV", name);
		f = vfs_Tfopen(path, "wb", vfs_RootDir);
		if (f != 0) {
			ls_WriteSaveHeader(f, 5);
			CloseVfsStream(f);
		}
		f = vfs_Tfopen(path, "rb", vfs_RootDir);
		if (f != 0) {
			ls_LoadSavegameHeader(f, hdr);
			crc = vfs_CalcCrc32((unsigned char*) hdr, 0x78);
			CloseVfsStream(f);
		}
		memset(&m, 0, sizeof(m));
		m.handle = ((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id;
		m.crc = crc;
		cm_RequestSysMessage(0x10, &m);
		n = 0;
		while (n < gm_PlayerCount) {
			n = 0;
			for (i = 0; i < 8; i++) {
				if (g_7f3ac0[i].id != -1) {
					n++;
				}
			}
			cm_StepCommandQueue();
		}
		cm_SaveGameAndWait(main_LoopFlags, g_14ac60c);
		sprintf(path, "Gamedata\\network\\%s.SRV", name);
		ls_SaveGame(path, title, 6);
		sprintf(path, "Gamedata\\network\\%s.SAV", name);
		ls_SaveGame(path, title, 5);
		d2_ShowStatusBanner(str_empty);
	}
}
