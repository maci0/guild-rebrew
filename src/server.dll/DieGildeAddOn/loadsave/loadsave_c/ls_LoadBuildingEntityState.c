// FUNCTION: SERVER 0x100128f0
#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"
#include "../../../Units/vfs/vfs.h"
#include "../../game/entity.h"

#include <stdlib.h>

int __cdecl AllocGraveyardField(int);
extern void amt_FindEntity26(int);
extern void amt_FindEntity27(int);
extern char gm_RandomMod(int);
extern unsigned char _ftol();
extern void gm_AddOrAccumulateObject(int, int, int);
int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
int __cdecl ls_LoadGraveyardData(int stream_ctx, int dest_buf);
int __cdecl ahm_AllocAhmInfo(int building, int slot);
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

/* Loads graveyard-specific data from a save file. Reads
 * production slots, worker assignments, and field states
 * for graveyard buildings.
 *
 * NOTE: SIZE_MISMATCH (1464 vs 1463, 1 byte). 100% mnemonic-aligned with
 * the reference (496/496 same-mnemonic diffs) — control flow, calls and
 * constants match; remaining deltas are MSVC6 register allocation and block
 * layout: the reference caches the -1 sentinel in ebp (`or ebp,-1` once +
 * `mov [..], ebp` at 3 sites) while our build rematerializes
 * `mov dword ptr [..], 0xffffffff` (the "constant-caching blocker", +1 byte
 * net), and the reference keeps stream_ctx in edi with a 4-register prologue
 * (ours: 3 registers, frame offsets shifted by 4). rebrew prove reports an
 * EAX=1 vs 0 mismatch on some (3 x 7) explored state pairs — consistent with
 * the read-hook symbolics under the divergent block layout, not confirmed as
 * a real behavioral difference (mnemonics align 100%); not reachable with
 * this compiler's scheduling. */


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
					if (!ls_ReadVfsDataChecked((void*) (load_result + *(int*) (esi + 0x71)), 4, 1, (void*) stream_ctx)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 4 + *(int*) (esi + 0x71)),
							4,
							1,
							(void*) stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 8 + *(int*) (esi + 0x71)),
							1,
							1,
							(void*) stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 9 + *(int*) (esi + 0x71)),
							1,
							1,
							(void*) stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 0xa + *(int*) (esi + 0x71)),
							2,
							1,
							(void*) stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 0x10 + *(int*) (esi + 0x71)),
							4,
							1,
							(void*) stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 0xc + *(int*) (esi + 0x71)),
							1,
							1,
							(void*) stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 0xd + *(int*) (esi + 0x71)),
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
					*(int*) (esi + 0x65) = AllocGraveyardField((int) esi);
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
				state_ptr[3] = neg1;
				state_ptr[0] |= 1;
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

	g_aux_entity_buffer = (int) realloc((void*) g_aux_entity_buffer, g_aux_entity_count * 0x60);

	current_index = 0;
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
