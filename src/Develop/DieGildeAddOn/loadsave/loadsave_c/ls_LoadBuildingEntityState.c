// GLOBAL: SERVER 0x101de454
extern int g_aux_entity_count; /* 0x101de454 */

// GLOBAL: SERVER 0x101de55c
extern int g_aux_entity_buffer; /* 0x101de55c */
// FUNCTION: SERVER 0x100128f0
#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"
#include "../../../Units/vfs/vfs.h"
#include "../../game/entity.h"

#include <stdlib.h>
#include <string.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

int __cdecl gv_AllocGraveyardField(int);
int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
int __cdecl ls_LoadGraveyardData(int stream_ctx, int dest_buf);
int __cdecl ahm_AllocAhmInfo(int building, int slot);
extern int g_file_version; /* 0x1002d4ec */
extern int g_aux_entity_count; /* 0x101de454 */
extern int g_aux_entity_buffer; /* 0x101de55c */
unsigned int ls_LoadBuildingEntityState(unsigned int);

/* Loads graveyard-specific data from a save file. Reads
 * production slots, worker assignments, and field states
 * for graveyard buildings.
 *
 * Shape notes (whole-image linked residue 5404 -> 4740 over the byte-offset form):
 * - The outer loop, the 0x1e arm and the aux loop are counted index loops
 *   (`ptr + i * 0xa9`; `base + i * 0x18 + N` with `i < 0x40`;
 *   `buf + i * 0x60 + N`).  Strength reduction then gives the reference's
 *   `xor ebx,ebx` / `lea [ebx+edx+N]` induction, its `mov ecx,ebx;
 *   add ecx,edx` first site, `lea esi,[edx+ecx]`, and `xor esi,esi` inside
 *   the aux guard.  Byte-offset loops (`i += 0x18`) put the load on the left
 *   of every address sum and lose 2 bytes at the first site.
 * - The state block is `memset` + `|= 1` (docs/msvc6-c-shapes.md section 71).
 *   Its extra candidates are what give the -1 sentinel `ebp` (`or ebp,-1` once,
 *   three `mov [..],ebp`), so the field reads need no `volatile` any more; with
 *   the plain loads the scheduler also hoists each load above the pushes, as
 *   the reference does.
 * - The state block addresses `esi + 0x99` directly (no `state_ptr` local).
 *   That lets c2 prove `[eax]` and `[esi+0xa5]` disjoint without /Ow, which
 *   is what places the 0xa5 store inside the `|= 1` read-modify-write.
 * - Byte-exact at the link under the default `/O2 /Gd` (measured, whole-image
 *   .text 4740 -> 4735).  Under `/O2 /Gd /Ow` the 0x4b-0x4d arm emits
 *   `add esp,8` before `mov [ebx],eax` (the stores stop aliasing), 5 bytes. */


unsigned int __cdecl ls_LoadBuildingEntityState(unsigned int stream_ctx)
{
	int entity_count;
	int current_index;
	char* esi;
	int load_result;
	int* ebx;
	int dummy;
	register int neg1;

	gm_ResetAllEntities();

	if (!ls_ReadVfsDataChecked(&entity_count, 4, 1, (void*) stream_ctx)) {
		return 0;
	}

	current_index = 0;
	if (0 < entity_count) {
		neg1 = -1;
		while (current_index < entity_count) {
			esi = (char*) (g_entity_ptr + current_index * 0xa9);

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
				*(int*) (esi + 0x71) = (int) m_AllocTracked(0x600, "f3g:PlantMap");
				for (load_result = 0; load_result < 0x40; load_result++) {
					if (!ls_ReadVfsDataChecked((void*) (*(int*) (esi + 0x71) + load_result * 0x18), 4, 1, (void*) stream_ctx)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (*(int*) (esi + 0x71) + load_result * 0x18 + 4),
							4,
							1,
							(void*) stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (*(int*) (esi + 0x71) + load_result * 0x18 + 8),
							1,
							1,
							(void*) stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (*(int*) (esi + 0x71) + load_result * 0x18 + 9),
							1,
							1,
							(void*) stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (*(int*) (esi + 0x71) + load_result * 0x18 + 0xa),
							2,
							1,
							(void*) stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (*(int*) (esi + 0x71) + load_result * 0x18 + 0x10),
							4,
							1,
							(void*) stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (*(int*) (esi + 0x71) + load_result * 0x18 + 0xc),
							1,
							1,
							(void*) stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (*(int*) (esi + 0x71) + load_result * 0x18 + 0xd),
							1,
							1,
							(void*) stream_ctx
						)) {
						return 0;
					}
					*(int*) (*(int*) (esi + 0x71) + load_result * 0x18 + 0x14) = 0;
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
					ahm_info = (int*) m_AllocTracked(0x3c, "AHM_INFO");
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
				memset(esi + 0x99, 0, 0x10);
				*(int*) (esi + 0x99) |= 1;
				*(int*) (esi + 0xa5) = neg1;
			}

			*(int*) (esi + 0x30) = 0x1388;
			*(int*) (esi + 0x95) = neg1;
			current_index++;
		}
	}

	if (!ls_ReadVfsDataChecked(&g_aux_entity_count, 4, 1, (void*) stream_ctx)) {
		return 0;
	}

	g_aux_entity_buffer = (int) realloc((void*) g_aux_entity_buffer, g_aux_entity_count * 0x60);
	for (load_result = 0; load_result < g_aux_entity_count; load_result++) {
		if (!ls_ReadVfsDataChecked((void*) (g_aux_entity_buffer + load_result * 0x60), 0x40, 1, (void*) stream_ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked((void*) (g_aux_entity_buffer + load_result * 0x60 + 0x40), 0x10, 1, (void*) stream_ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked((void*) (g_aux_entity_buffer + load_result * 0x60 + 0x50), 0x10, 1, (void*) stream_ctx)) {
			return 0;
		}
	}

	return 1;
}
