#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"
#include "../../../Units/vfs/vfs.h"
#include "../../game/entity.h"

#include <stdlib.h>

int __cdecl AllocGraveyardField(int);
extern int g_1002576c[];
extern int g_1002575c[];
extern void amt_FindEntity26(int);
extern void amt_FindEntity27(int);
extern char gm_RandomMod(int);
extern unsigned char __ftol();
extern void gm_AddOrAccumulateObject(int, int, int);
extern char g_100a9820[];
extern char g_1014d8e0[];
extern char g_10139820[];
int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
extern int g_save_version;
extern int g_1002d4f0;
extern int g_1002d4f4;
extern char g_1002d4f8;
extern char g_1002d4fc;
extern int DAT_100a8c34;
extern int DAT_10035450;
int __cdecl ls_LoadGraveyardData(int stream_ctx, int dest_buf);
int __cdecl ahm_AllocAhmInfo(int building, int slot);
extern int g_file_version; /* 0x1002d4ec */
;
extern int g_entity_array_ptr; /* 0x1014d8c0 */
;
extern int g_101de454; /* 0x101de454 */
;
extern int g_101de55c; /* 0x101de55c */
;
extern unsigned int gm_LookupEntityRecordById(unsigned int);
extern int gm_ResolveEntityById(void**, void**, void**, int);
extern void gm_EntitySetField(void);
extern int g_101deae8;
extern int g_101deac0;
extern int g_101de560;
extern int g_save_info[2];
extern int OpenVfsStream(char*, char*, int);
int ls_LoadSavegameHeader(int, char*);
int ls_LoadExistingEntities(int);
unsigned int ls_LoadBuildingEntityState(unsigned int);
int ls_LoadDynamicEntities(void*);
int ls_LoadEntities(int);
int ls_LoadTownData(int);
extern int amt_fio_LoadAemter(int, int);
extern unsigned int ls_ID2Ptr(void);

extern int DAT_10035434;
extern int DAT_10035470;
extern int DAT_10035474;
extern int DAT_10035478;

/* Loads graveyard-specific data from a save file. Reads
 * production slots, worker assignments, and field states
 * for graveyard buildings. */

// STUB: SERVER 0x10013230
// ls_LoadEntities

int __cdecl ls_LoadEntities(int ctx)
{
	int record_count;
	int header_field;
	short id;
	char* slot;
	int* slot_ext_ptr;
	int i;

	if (ls_ReadVfsDataChecked(&record_count, 2, 1, (void*) ctx) == 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked(&header_field, 4, 1, (void*) ctx) == 0) {
		return 0;
	}
	DAT_10035434 = header_field;
	if (ls_ReadVfsDataChecked(&DAT_10035470, 4, 1, (void*) ctx) == 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked(&DAT_10035474, 4, 1, (void*) ctx) == 0) {
		return 0;
	}

	if (g_file_version >= 0x10017) {
		int* p = &DAT_10035478;
		while ((int) p < (int) &DAT_10035478 + 0x20) {
			if (ls_ReadVfsDataChecked(p, 4, 1, (void*) ctx) == 0) {
				return 0;
			}
			p = p + 1;
		}
	}

	if (record_count <= 0) {
		return 1;
	}

	for (i = 0; i < record_count; i = i + 1) {
		short rec_id;

		if (ls_ReadVfsDataChecked(&rec_id, 2, 1, (void*) ctx) == 0) {
			return 0;
		}
		id = rec_id;
		slot = (char*) (0x100358a0 + ((int) (unsigned short) id) * 0x21c);
		*(short*) slot = id;

		if (g_file_version >= 0x1003e) {
			if (ls_ReadVfsDataChecked(slot + 0x20c, 4, 1, (void*) ctx) == 0) {
				return 0;
			}
		}
		else {
			*(int*) (slot + 0x20c) = -1;
		}

		if (ls_ReadVfsDataChecked(slot + 2, 1, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 4, 4, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 8, 1, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 9, 1, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0xa, 2, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0xc, 1, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0xd, 1, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x10, 4, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x14, 4, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x18, 4, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x1c, 4, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x20, 4, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x24, 4, 1, (void*) ctx) == 0) {
			return 0;
		}

		if (g_file_version >= 0x1003b) {
			if (ls_ReadVfsDataChecked(slot + 0x28, 2, 1, (void*) ctx) == 0) {
				return 0;
			}
			if (ls_ReadVfsDataChecked(slot + 0x2c, 4, 1, (void*) ctx) == 0) {
				return 0;
			}
		}

		if (ls_ReadVfsDataChecked(slot + 0x30, 0x10, 1, (void*) ctx) == 0) {
			return 0;
		}

		if (g_file_version >= 0x10031) {
			if (ls_ReadVfsDataChecked(slot + 0x40, 0x10, 1, (void*) ctx) == 0) {
				return 0;
			}
		}

		if (ls_ReadVfsDataChecked(slot + 0x50, 2, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x54, 4, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x58, 1, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x5c, 0x20, 1, (void*) ctx) == 0) {
			return 0;
		}

		if (g_file_version >= 0x10024) {
			if (ls_ReadVfsDataChecked(slot + 0x7c, 4, 1, (void*) ctx) == 0) {
				return 0;
			}
		}

		if (ls_ReadVfsDataChecked(slot + 0x80, 5, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x88, 0xa8, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x164, 1, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x165, 1, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x166, 1, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x167, 1, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x168, 1, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x169, 1, 1, (void*) ctx) == 0) {
			return 0;
		}

		*(int*) (slot + 0x16c) = 0;
		if (ls_ReadVfsDataChecked(slot + 0x16c, 4, 1, (void*) ctx) == 0) {
			return 0;
		}
		*(int*) (slot + 0x170) = 0;
		if (ls_ReadVfsDataChecked(slot + 0x170, 4, 1, (void*) ctx) == 0) {
			return 0;
		}

		if (g_file_version >= 0x10020) {
			if (ls_ReadVfsDataChecked(slot + 0x174, 4, 1, (void*) ctx) == 0) {
				return 0;
			}
		}
		else {
			if (ls_ReadVfsDataChecked(slot + 0x174, 2, 1, (void*) ctx) == 0) {
				return 0;
			}
		}

		*(int*) (slot + 0x17c) = 0;
		if (ls_ReadVfsDataChecked(slot + 0x17c, 4, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x180, 1, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x18c, 4, 1, (void*) ctx) == 0) {
			return 0;
		}

		slot_ext_ptr = (int*) (slot + 0x190);
		if (ls_ReadVfsDataChecked(slot_ext_ptr, 4, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (g_file_version < 0x1003e) {
			*slot_ext_ptr = 4;
		}

		if (ls_ReadVfsDataChecked(slot + 0x194, 4, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x198, 4, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x19c, 4, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x1a0, 4, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x1a4, 4, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x1a8, 4, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x1ac, 4, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x1b0, 1, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x1b1, 1, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x1b4, 0x10, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x1c8, 4, 1, (void*) ctx) == 0) {
			return 0;
		}

		if (g_file_version >= 0x10049) {
			if (ls_ReadVfsDataChecked(slot + 0x1cc, 4, 1, (void*) ctx) == 0) {
				return 0;
			}
		}
		else {
			*(int*) (slot + 0x1cc) = 0;
		}

		if (ls_ReadVfsDataChecked(slot + 0x1d0, 4, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x1d4, 0x10, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x1e4, 4, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x1e8, 4, 1, (void*) ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x1ec, 4, 1, (void*) ctx) == 0) {
			return 0;
		}

		if (g_file_version >= 0x1002a) {
			if (ls_ReadVfsDataChecked(slot + 0x1f0, 4, 1, (void*) ctx) == 0) {
				return 0;
			}
		}

		if (g_file_version >= 0x10021) {
			if (ls_ReadVfsDataChecked(slot + 0x1c5, 1, 1, (void*) ctx) == 0) {
				return 0;
			}
		}

		{
			int probe;
			if (ls_ReadVfsDataChecked(&probe, 4, 1, (void*) ctx) == 0) {
				return 0;
			}
			*(int*) (slot + 0x184) = probe;
		}

		if (g_file_version >= 0x10021) {
			if (ls_ReadVfsDataChecked(slot + 0x1f4, 0x18, 1, (void*) ctx) == 0) {
				return 0;
			}
		}

		if (g_file_version >= 0x10036) {
			if (ls_ReadVfsDataChecked(slot + 0x210, 4, 1, (void*) ctx) == 0) {
				return 0;
			}
			if (ls_ReadVfsDataChecked(slot + 0x214, 1, 1, (void*) ctx) == 0) {
				return 0;
			}
			if (ls_ReadVfsDataChecked(slot + 0x215, 1, 1, (void*) ctx) == 0) {
				return 0;
			}
			if (ls_ReadVfsDataChecked(slot + 0x216, 1, 1, (void*) ctx) == 0) {
				return 0;
			}
			if (ls_ReadVfsDataChecked(slot + 0x217, 1, 1, (void*) ctx) == 0) {
				return 0;
			}
			if (ls_ReadVfsDataChecked(slot + 0x218, 1, 1, (void*) ctx) == 0) {
				return 0;
			}
		}
	}

	(void) i;
	return 1;
}
