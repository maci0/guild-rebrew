#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"
#include "../../../Units/vfs/vfs.h"
#include "../../game/entity.h"

#include <stdlib.h>

extern void amt_FindEntity26(int);
extern void amt_FindEntity27(int);
extern char gm_RandomMod(int);
extern unsigned char _ftol();
extern void gm_AddOrAccumulateObject(int, int, int);
int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
extern int g_file_version; /* 0x1002d4ec */
extern unsigned char* g_entity_ptr; /* 0x1014d8c0 */
extern int g_aux_entity_count; /* 0x101de454 */
extern int g_aux_entity_buffer; /* 0x101de55c */
extern unsigned int gm_LookupEntityRecordById(unsigned int);
extern int gm_ResolveEntityById(void**, void**, void**, int);
extern void gm_EntitySetField(void);
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

extern int g_citizen_count;
extern int g_save_extra_70;
extern int g_save_extra_74;
extern int g_save_extra_field;

/* Loads graveyard-specific data from a save file. Reads
 * production slots, worker assignments, and field states
 * for graveyard buildings. */

/* ls_LoadEntities — deserializes the static-entity table from the save
 * stream.  Reads the header (2-byte id/count slot reused for the per-record
 * id read, 4-byte header field living in the ctx arg slot, extra fields),
 * then loops `header_field` times reading one entity record (0x21c stride)
 * with version-gated sections.
 *
 * Byte-match note: RELOC 2268/2268.  The reference reuses ONE local slot
 * for the initial 2-byte read and the per-iteration id read (so the C uses a
 * single `id` variable), bounds the loop with `header_field`, and allocates
 * header_field to the dead ctx arg slot (sub esp,0xc — 3 frame dwords). */

// FUNCTION: SERVER 0x10013230
// ls_LoadEntities
int __cdecl ls_LoadEntities(int ctx)
{
	int id;
	int header_field;
	char* slot;
	int* slot_ext_ptr;
	int i;

	if (ls_ReadVfsDataChecked(&id, 2, 1, (void*) ctx) == 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked(&header_field, 4, 1, (void*) ctx) == 0) {
		return 0;
	}
	g_citizen_count = header_field;
	if (ls_ReadVfsDataChecked(&g_save_extra_70, 4, 1, (void*) ctx) == 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked(&g_save_extra_74, 4, 1, (void*) ctx) == 0) {
		return 0;
	}

	if (g_file_version >= 0x10017) {
		int* p = &g_save_extra_field;
		while ((int) p < (int) &g_save_extra_field + 0x20) {
			if (ls_ReadVfsDataChecked(p, 4, 1, (void*) ctx) == 0) {
				return 0;
			}
			p = p + 1;
		}
	}

	for (i = 0; i < header_field; i = i + 1) {
		if (ls_ReadVfsDataChecked(&id, 2, 1, (void*) ctx) == 0) {
			return 0;
		}
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
