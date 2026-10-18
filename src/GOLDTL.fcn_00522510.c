/* Client building-table reader. Stream is an opaque VFS pointer, not a VFS_FILE. */

void __cdecl gm_ResetAllEntities(void);
#include "Develop/DieGildeAddOn/loadsave/loadsave.h"
void* __cdecl m_alloc(unsigned int size, const char* tag);

int __cdecl ahm_AllocAhmInfo(void* stream, int entity);
int __cdecl gv_AllocGraveyardField(int entity);
void* __cdecl realloc(void* p, unsigned int size);
void* __cdecl memset(void* dst, int value, unsigned int count);

extern unsigned char* g_entity_ptr;
extern int g_6a23ac;
extern int g_aux_entity_count;
extern int g_aux_entity_buffer;

/* ADDRESS: GOLDTL 0x00522510 */
int __cdecl fcn_00522510(void* stream)
{
	int entity_count;
	int current_index;
	char* building_entity;
	int load_result;
	int* state_slot;
	int legacy_value;
	register int invalid_value;

	gm_ResetAllEntities();

	if (!ls_ReadVfsDataChecked(&entity_count, 4, 1, stream)) {
		return 0;
	}

	current_index = 0;
	if (0 < entity_count) {
		invalid_value = -1;
		while (current_index < entity_count) {
			building_entity = (char*) (g_entity_ptr + current_index * 0xa9);

			if (!ls_ReadVfsDataChecked(building_entity, 1, 1, stream)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(building_entity + 0x01, 4, 1, stream)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(building_entity + 0x05, 0x20, 1, stream)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(building_entity + 0x25, 2, 1, stream)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(building_entity + 0x27, 2, 1, stream)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(building_entity + 0x29, 2, 1, stream)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(building_entity + 0x2b, 4, 1, stream)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(building_entity + 0x2f, 1, 1, stream)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(building_entity + 0x34, 1, 1, stream)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(building_entity + 0x35, 4, 1, stream)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(building_entity + 0x39, 4, 1, stream)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(building_entity + 0x3d, 4, 1, stream)) {
				return 0;
			}

			state_slot = (int*) (building_entity + 0x41);
			if (!ls_ReadVfsDataChecked(state_slot, 4, 1, stream)) {
				return 0;
			}
			if (*state_slot > 4) {
				*state_slot = 2;
			}

			if (!ls_ReadVfsDataChecked(building_entity + 0x45, 4, 1, stream)) {
				return 0;
			}

			if (g_6a23ac >= 0x10028) {
				if (!ls_ReadVfsDataChecked(building_entity + 0x49, 4, 1, stream)) {
					return 0;
				}
			}

			if (g_6a23ac < 0x10032) {
				if (!ls_ReadVfsDataChecked(&legacy_value, 4, 1, stream)) {
					return 0;
				}
			}

			if (g_6a23ac >= 0x10057) {
				if (!ls_ReadVfsDataChecked(building_entity + 0x4d, 4, 1, stream)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(building_entity + 0x51, 4, 1, stream)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(building_entity + 0x55, 4, 1, stream)) {
					return 0;
				}
			}

			if (!ls_ReadVfsDataChecked(building_entity + 0x5a, 2, 1, stream)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(building_entity + 0x5c, 1, 1, stream)) {
				return 0;
			}

			if (building_entity[0] == 0x1e) {
				*(int*) (building_entity + 0x71) = (int) m_alloc(0x600, "f3g:PlantMap");
				for (load_result = 0; load_result < 0x40; load_result++) {
					if (!ls_ReadVfsDataChecked((void*) (*(int*) (building_entity + 0x71) + load_result * 0x18), 4, 1, stream)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked((void*) (*(int*) (building_entity + 0x71) + load_result * 0x18 + 4), 4, 1, stream)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked((void*) (*(int*) (building_entity + 0x71) + load_result * 0x18 + 8), 1, 1, stream)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked((void*) (*(int*) (building_entity + 0x71) + load_result * 0x18 + 9), 1, 1, stream)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked((void*) (*(int*) (building_entity + 0x71) + load_result * 0x18 + 0xa), 2, 1, stream)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked((void*) (*(int*) (building_entity + 0x71) + load_result * 0x18 + 0x10), 4, 1, stream)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked((void*) (*(int*) (building_entity + 0x71) + load_result * 0x18 + 0xc), 1, 1, stream)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked((void*) (*(int*) (building_entity + 0x71) + load_result * 0x18 + 0xd), 1, 1, stream)) {
						return 0;
					}
					*(int*) (*(int*) (building_entity + 0x71) + load_result * 0x18 + 0x14) = 0;
				}
			}
			else if (building_entity[0] == 0x48 || building_entity[0] == 0x49 || building_entity[0] == 0x4a) {
				if (g_6a23ac >= 0x10047) {
					load_result = ls_LoadGraveyardData(stream, (unsigned char*) building_entity);
				}
				else {
					if (!ls_ReadVfsDataChecked(building_entity + 0x65, 0x30, 1, stream)) {
						return 0;
					}
					*(int*) (building_entity + 0x65) = gv_AllocGraveyardField((int) building_entity);
					goto label_tail;
				}
				if (load_result == 0) {
					return 0;
				}
			}
			else if (building_entity[0] == 0x4b || building_entity[0] == 0x4c || building_entity[0] == 0x4d) {
				if (g_6a23ac >= 0x10049) {
					load_result = ahm_AllocAhmInfo(stream, (int) building_entity);
				}
				else {
					int* ahm_info;
					if (!ls_ReadVfsDataChecked(building_entity + 0x65, 0x30, 1, stream)) {
						return 0;
					}
					ahm_info = (int*) m_alloc(0x3c, "AHM_INFO");
					*(int*) (building_entity + 0x65) = (int) ahm_info;
					*ahm_info = invalid_value;
					goto label_tail;
				}
				if (load_result == 0) {
					return 0;
				}
			}
			else {
				if (!ls_ReadVfsDataChecked(building_entity + 0x65, 0x30, 1, stream)) {
					return 0;
				}
			}

		label_tail:
			if (g_6a23ac >= 0x10043) {
				if (!ls_ReadVfsDataChecked(building_entity + 0x99, 0x10, 1, stream)) {
					return 0;
				}
			}
			else {
				memset(building_entity + 0x99, 0, 0x10);
				*(int*) (building_entity + 0x99) |= 1;
				*(int*) (building_entity + 0xa5) = invalid_value;
			}

			*(int*) (building_entity + 0x30) = 0x1388;
			*(int*) (building_entity + 0x95) = invalid_value;
			current_index++;
		}
	}

	if (!ls_ReadVfsDataChecked(&g_aux_entity_count, 4, 1, stream)) {
		return 0;
	}

	g_aux_entity_buffer = (int) realloc((void*) g_aux_entity_buffer, g_aux_entity_count * 0x60);
	for (load_result = 0; load_result < g_aux_entity_count; load_result++) {
		if (!ls_ReadVfsDataChecked((void*) (g_aux_entity_buffer + load_result * 0x60), 0x40, 1, stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked((void*) (g_aux_entity_buffer + load_result * 0x60 + 0x40), 0x10, 1, stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked((void*) (g_aux_entity_buffer + load_result * 0x60 + 0x50), 0x10, 1, stream)) {
			return 0;
		}
	}

	return 1;
}
