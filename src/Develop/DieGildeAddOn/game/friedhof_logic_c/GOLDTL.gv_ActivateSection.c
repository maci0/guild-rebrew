/* gv_ActivateSection - proper C */

extern char g_7f4ca0[];
extern char g_7f4ca0[];
// FUNCTION: GOLD 0x4f0af0
// SIZE: 304
// FUNCTION: GOLDTL 0x4f2c00
// SIZE: 304


#include "rebrew_types.h"
#include "rebrew_globals.h"
extern unsigned short* g_entity_table_end; /* TL 0x773da8 (server 0x1003546c) */
extern char* g_entity_type_table; /* TL 0x868050 (server 0x100a8c30) */
extern int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
/* TL data VAs re-derived from disasm — GOLDTL has no data layout, so these
 * externs shadow the shared server-header symbols (which resolve to server
 * image VAs in the TL link). */

/* Validates and activates a graveyard section: resolves the section's
 * entity, checks the grave slot is a free graveyard field, then enables
 * the production slots of the worker array for the section's field type. */

int __cdecl gv_ActivateSection(void* cmd)
{
	void* entity;
	void* workers;
	void* resolved;
	unsigned short grave_id;
	unsigned char field_id;
	int field_type;

	gm_ResolveEntityById(&entity, 0, 0, *(int*) ((char*) cmd + 8));
	if (entity) {
		grave_id = *(unsigned short*) ((char*) entity + 0x27);
		if (grave_id != 0xffff) {
			if (g_7f4ca0 + grave_id * 0x21c != (char*) g_entity_table_end) {
				field_id = *(unsigned char*) entity;
				if (((unsigned char*)g_entity_type_table)[field_id + field_id * 588] != 0x1d) {
					return -2;
				}
				workers = *(void**) ((char*) entity + 0x65);
				if (!workers) {
					return -3;
				}
				gm_ResolveEntityById(0, 0, &resolved, *(int*) ((char*) cmd + 4));
				if (!resolved) {
					return -6;
				}
				field_type = *(int*) ((char*) cmd + 0xc);
				if (field_type == 3) {
					if (*(int*) ((char*) workers + 0x14)
					    && *(int*) ((char*) workers + 4) >= 3) {
						*(char*) ((char*) workers + 0x1b) = 1;
						*(char*) ((char*) workers + 0x1a) = 1;
						*(char*) ((char*) workers + 0x19) = 1;
						return 0;
					}
					return -7;
				}
				if (field_type == 2) {
					if (*(int*) ((char*) workers + 0x10) != 0) {
						if (*(int*) ((char*) workers + 4) >= 2) {
							*(char*) ((char*) workers + 0x1a) = 1;
							*(char*) ((char*) workers + 0x19) = 1;
							return 0;
						}
					}
					return -7;
				}
				if (field_type == 1) {
					if (*(int*) ((char*) workers + 0xc) == 0) {
						return -7;
					}
					*(char*) ((char*) workers + 0x19) = 1;
					return 0;
				}
				return -8;
			}
		}
	}
	return -1;
}
