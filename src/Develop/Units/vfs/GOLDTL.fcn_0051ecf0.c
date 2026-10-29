/* Writes the building table read back by ls_LoadBuildingEntityState, the plant
 * map, graveyard and alchemist records of special buildings, then the
 * building-site boxes. */

extern unsigned char* g_entity_ptr;
extern int g_aux_entity_count;
extern int g_aux_entity_buffer;

unsigned int __cdecl vfs_fwrite(void* buf, int size, int count, char* stream);
void* __cdecl realloc(void* p, unsigned int size);
int __cdecl fcn_004eed10(char* stream, char* rec);
int __cdecl fcn_004f3900(char* stream, char* rec);

/* ADDRESS: GOLDTL 0x0051ecf0 */
int __cdecl fcn_0051ecf0(char* file)
{
	int count;
	int i;
	char* esi;
	int j;

	count = 0;
	for (i = 0; i < 0x100; i++) {
		if (g_entity_ptr[i * 0xa9] != 0) {
			count++;
		}
	}
	if (vfs_fwrite(&count, 4, 1, file) <= 0) {
		return 0;
	}
	for (i = 0; i < 0x100; i++) {
		esi = (char*) (g_entity_ptr + i * 0xa9);
		if (esi[0] == 0) {
			continue;
		}
		if (vfs_fwrite(esi, 1, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x01, 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x05, 0x20, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x25, 2, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x27, 2, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x29, 2, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x2b, 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x2f, 1, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x34, 1, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x35, 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x39, 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x3d, 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x41, 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x45, 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x49, 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x4d, 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x51, 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x55, 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x5a, 2, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x5c, 1, 1, file) <= 0) {
			return 0;
		}
		if (esi[0] == 0x1e) {
			for (j = 0; j < 0x40; j++) {
				if (vfs_fwrite((void*) (*(int*) (esi + 0x71) + j * 0x18), 4, 1, file) <= 0) {
					return 0;
				}
				if (vfs_fwrite((void*) (*(int*) (esi + 0x71) + j * 0x18 + 4), 4, 1, file) <= 0) {
					return 0;
				}
				if (vfs_fwrite((void*) (*(int*) (esi + 0x71) + j * 0x18 + 8), 1, 1, file) <= 0) {
					return 0;
				}
				if (vfs_fwrite((void*) (*(int*) (esi + 0x71) + j * 0x18 + 9), 1, 1, file) <= 0) {
					return 0;
				}
				if (vfs_fwrite((void*) (*(int*) (esi + 0x71) + j * 0x18 + 0xa), 2, 1, file) <= 0) {
					return 0;
				}
				if (vfs_fwrite((void*) (*(int*) (esi + 0x71) + j * 0x18 + 0x10), 4, 1, file) <= 0) {
					return 0;
				}
				if (vfs_fwrite((void*) (*(int*) (esi + 0x71) + j * 0x18 + 0xc), 1, 1, file) <= 0) {
					return 0;
				}
				if (vfs_fwrite((void*) (*(int*) (esi + 0x71) + j * 0x18 + 0xd), 1, 1, file) <= 0) {
					return 0;
				}
			}
		}
		else if (esi[0] == 0x48 || esi[0] == 0x49 || esi[0] == 0x4a) {
			if (fcn_004f3900(file, esi) == 0) {
				return 0;
			}
		}
		else if (esi[0] == 0x4b || esi[0] == 0x4c || esi[0] == 0x4d) {
			if (fcn_004eed10(file, esi) == 0) {
				return 0;
			}
		}
		else {
			if (vfs_fwrite(esi + 0x65, 0x30, 1, file) <= 0) {
				return 0;
			}
		}
		if (vfs_fwrite(esi + 0x99, 0x10, 1, file) <= 0) {
			return 0;
		}
	}
	if (vfs_fwrite(&g_aux_entity_count, 4, 1, file) <= 0) {
		return 0;
	}
	g_aux_entity_buffer = (int) realloc((void*) g_aux_entity_buffer, g_aux_entity_count * 0x60);
	for (i = 0; i < g_aux_entity_count; i++) {
		if (vfs_fwrite((void*) (g_aux_entity_buffer + i * 0x60), 0x40, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite((void*) (g_aux_entity_buffer + i * 0x60 + 0x40), 0x10, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite((void*) (g_aux_entity_buffer + i * 0x60 + 0x50), 0x10, 1, file) <= 0) {
			return 0;
		}
	}
	return 1;
}
