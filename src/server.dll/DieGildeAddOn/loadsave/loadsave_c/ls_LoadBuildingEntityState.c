// FUNCTION: SERVER 0x100128f0
#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"
#include "../../../Units/vfs/vfs.h"
#include "../../game/entity.h"

#include <stdlib.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

int __cdecl gv_AllocGraveyardField(int);
extern void amt_FindEntity26(int);
extern void amt_FindEntity27(int);
extern char gm_RandomMod(int);
extern unsigned char _ftol();
extern void gm_AddObjekt(int, int, int);
int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
int __cdecl ls_LoadGraveyardData(int stream_ctx, int dest_buf);
int __cdecl ahm_AllocAhmInfo(int building, int slot);
extern int g_file_version; /* 0x1002d4ec */
extern int g_aux_entity_count; /* 0x101de454 */
extern int g_aux_entity_buffer; /* 0x101de55c */
extern unsigned int gm_LookupEntityRecordById(unsigned int);
extern int gm_ResolveEntityById(void**, void**, void**, int);
extern void gm_EntitySetField(void);
extern int g_save_info[2];
extern int vfs_OpenStream(char*, char*, int);
int ls_LoadSavegameHeader(int, char*);
int ls_LoadExistingEntities(int);
unsigned int ls_LoadBuildingEntityState(unsigned int);
int ls_LoadDynamicEntities(void*);
int ls_LoadEntities(int);
int ls_LoadTownData(int);
extern int amt_fio_LoadAemter(int, int);
extern unsigned int ls_ID2Ptr(void);

/* Loads graveyard-specific data from a save file. Reads
 * production slots, worker assignments, and field states
 * for graveyard buildings.
 *
 * NOTE (round 143): the "constant-caching blocker" is beaten by making the
 * read loop's argument reads VOLATILE, and only that way.  The reference
 * caches the -1 sentinel in ebp (`or ebp,-1` once + `mov [..],ebp` at three
 * sites); under /O2 msvc6 rematerializes `mov dword [..],0xffffffff` instead,
 * the missing saved register shifts every frame slot, and the whole function
 * desyncs.  Writing the eight `ls_ReadVfsDataChecked` field reads as
 * `*(volatile int*) (esi + 0x71)` (the store stays plain) makes /O2 emit the
 * cached form *and* keep the reference's per-call reloads: fixed-offset masked
 * match 347 -> 856 of 1463, object 1464 -> 1472 against the reference's 1463
 * (2026-09-13 probe: 645 matched / 879 reloc; figures above predate later
 * work, retained as the fix's record),
 * failing postlink entries 114 -> 59, .text residual 1404 -> 775 bytes, and
 * whole-binary coverage 88.6% -> 89.3%.
 *
 * The switch is fragile and global — swept, all reverted: volatile at any ONE
 * of the ten field sites leaves the constant rematerialized, the store's own
 * read volatile kills it again, and so do `4 + load_result + ...`, the
 * field-first order, `char*` arithmetic, add-then-constant, a `volatile` store
 * (alone or on top), `unsigned int load_result` (identical) and
 * `load_result = load_result + 0x18` (identical).  This contradicts the note in
 * docs/TODO.md round 24 that a volatile read "regresses to 117/1471".
 *
 * Residual (25 aligned hunks): the read loop's induction form (`mov ebx,8;
 * lea ebp,[ebx-8]` where the reference keeps a plain `xor ebx,ebx` and
 * `lea [ebx+edx+N]`), the store block (`state_ptr[0] |= 1` folds to one store
 * where the reference reloads — forcing that read volatile costs 16 bytes), a
 * `lea esi,[edx+ecx]` / `[ecx+edx]` operand order, and the g_aux_entity_buffer
 * block.  `rebrew prove` reports an EAX=1 vs 0 mismatch on some (3 x 7)
 * explored state pairs — consistent with the read-hook symbolics under the
 * divergent block layout, not confirmed as a real behavioural difference
 * (mnemonics align 100%). */


unsigned int __cdecl ls_LoadBuildingEntityState(unsigned int stream_ctx)
{
	int entity_count;
	int current_index;
	char* esi;
	int load_result;
	int* ebx;
	unsigned int offset;
	int dummy;
	register int neg1;

	gm_ResetAllEntities();

	if (!ls_ReadVfsDataChecked(&entity_count, 4, 1, (void*) stream_ctx)) {
		return 0;
	}

	current_index = 0;

	current_index = 0;
	if (0 < entity_count) {
		offset = 0;
		neg1 = -1;
		while (current_index < entity_count) {
			esi = (char*) (offset + g_entity_ptr);

			if (!ls_ReadVfsDataChecked(esi, 1, 1, (void*) stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x01, 4, 1, (void*) stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x05, 0x20, 1, (void*) stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x25, 2, 1, (void*) stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x27, 2, 1, (void*) stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x29, 2, 1, (void*) stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x2b, 4, 1, (void*) stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x2f, 1, 1, (void*) stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x34, 1, 1, (void*) stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x35, 4, 1, (void*) stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x39, 4, 1, (void*) stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x3d, 4, 1, (void*) stream_ctx)) {
				return 0;
			}

			ebx = (int*) (esi + 0x41);
			if (!ls_ReadVfsDataChecked(ebx, 4, 1, (void*) stream_ctx)) {
				return 0;
			}
			if (*ebx > 4) {
				*ebx = 2;
			}

			if (!ls_ReadVfsDataChecked(esi + 0x45, 4, 1, (void*) stream_ctx)) {
				return 0;
			}

			if (g_file_version >= 0x10028) {
				if (!ls_ReadVfsDataChecked(esi + 0x49, 4, 1, (void*) stream_ctx)) {
					return 0;
				}
			}

			if (g_file_version < 0x10032) {
				if (!ls_ReadVfsDataChecked(&dummy, 4, 1, (void*) stream_ctx)) {
					return 0;
				}
			}

			if (g_file_version >= 0x10057) {
				if (!ls_ReadVfsDataChecked(esi + 0x4d, 4, 1, (void*) stream_ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(esi + 0x51, 4, 1, (void*) stream_ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(esi + 0x55, 4, 1, (void*) stream_ctx)) {
					return 0;
				}
			}

			if (!ls_ReadVfsDataChecked(esi + 0x5a, 2, 1, (void*) stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x5c, 1, 1, (void*) stream_ctx)) {
				return 0;
			}

			if (esi[0] == 0x1e) {
				*(int*) (esi + 0x71) = (int) m_AllocTracked(0x600, (const char*) 0x1002d510);
				for (load_result = 0; load_result < 0x600; load_result += 0x18) {
					if (!ls_ReadVfsDataChecked((void*) (load_result + *(volatile int*) (esi + 0x71)), 4, 1, (void*) stream_ctx)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (*(volatile int*) (esi + 0x71) + load_result + 4),
							4,
							1,
							(void*) stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (*(volatile int*) (esi + 0x71) + load_result + 8),
							1,
							1,
							(void*) stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (*(volatile int*) (esi + 0x71) + load_result + 9),
							1,
							1,
							(void*) stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (*(volatile int*) (esi + 0x71) + load_result + 0xa),
							2,
							1,
							(void*) stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (*(volatile int*) (esi + 0x71) + load_result + 0x10),
							4,
							1,
							(void*) stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 0xc + *(volatile int*) (esi + 0x71)),
							1,
							1,
							(void*) stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 0xd + *(volatile int*) (esi + 0x71)),
							1,
							1,
							(void*) stream_ctx
						)) {
						return 0;
					}
					*(int*) (load_result + 0x14 + *(int*) (esi + 0x71)) = 0;
				}
			}
			else if (esi[0] == 0x48 || esi[0] == 0x49 || esi[0] == 0x4a) {
				if (g_file_version >= 0x10047) {
					load_result = ls_LoadGraveyardData(stream_ctx, (int) esi);
				}
				else {
					if (!ls_ReadVfsDataChecked(esi + 0x65, 0x30, 1, (void*) stream_ctx)) {
						return 0;
					}
					*(int*) (esi + 0x65) = gv_AllocGraveyardField((int) esi);
					goto label_10012d72;
				}
				if (load_result == 0) {
					return 0;
				}
			}
			else if (esi[0] == 0x4b || esi[0] == 0x4c || esi[0] == 0x4d) {
				if (g_file_version >= 0x10049) {
					load_result = ahm_AllocAhmInfo(stream_ctx, (int) esi);
				}
				else {
					int* ahm_info;
					if (!ls_ReadVfsDataChecked(esi + 0x65, 0x30, 1, (void*) stream_ctx)) {
						return 0;
					}
					ahm_info = (int*) m_AllocTracked(0x3c, (const char*) 0x1002d504);
					*(int*) (esi + 0x65) = (int) ahm_info;
					*ahm_info = neg1;
					goto label_10012d72;
				}
				if (load_result == 0) {
					return 0;
				}
			}
			else {
				if (!ls_ReadVfsDataChecked(esi + 0x65, 0x30, 1, (void*) stream_ctx)) {
					return 0;
				}
			}

		label_10012d72:
			if (g_file_version >= 0x10043) {
				if (!ls_ReadVfsDataChecked(esi + 0x99, 0x10, 1, (void*) stream_ctx)) {
					return 0;
				}
			}
			else {
				int* state_ptr = (int*) (esi + 0x99);
				state_ptr[0] = 0;
				state_ptr[1] = 0;
				state_ptr[2] = 0;
				state_ptr[3] = 0;
				state_ptr[0] |= 1;
				state_ptr[3] = neg1;
			}

			*(int*) (esi + 0x30) = 0x1388;
			*(int*) (esi + 0x95) = neg1;
			current_index++;
			offset += 0xa9;
		}
	}

	if (!ls_ReadVfsDataChecked(&g_aux_entity_count, 4, 1, (void*) stream_ctx)) {
		return 0;
	}

	current_index = 0;
	g_aux_entity_buffer = (int) realloc((void*) g_aux_entity_buffer, g_aux_entity_count * 0x60);
	for (load_result = 0; load_result < g_aux_entity_count; load_result++) {
		if (!ls_ReadVfsDataChecked((void*) (current_index + g_aux_entity_buffer), 0x40, 1, (void*) stream_ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked((void*) (current_index + 0x40 + g_aux_entity_buffer), 0x10, 1, (void*) stream_ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked((void*) (current_index + 0x50 + g_aux_entity_buffer), 0x10, 1, (void*) stream_ctx)) {
			return 0;
		}
		current_index += 0x60;
	}

	return 1;
}
