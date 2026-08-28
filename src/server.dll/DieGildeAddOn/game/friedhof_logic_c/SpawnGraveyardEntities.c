/* SpawnGraveyardEntities - proper C */

// FUNCTION: SERVER 0x10010850
// SYMBOL: _SpawnGraveyardEntities
// SIZE: 370

extern int g_entity_type_table;
extern int g_next_object_id;
extern int g_current_year;
extern float g_const_57bc;
extern float g_const_57c0;
int __cdecl gm_RandomMod(int range);
void* __cdecl FindSlotEntryFiltered(void* filter_arg, void* entity, void* cursor,
                                    void* filter, int type);

/* Spawns up to *count* graveyard workers for the entity.  Validates the
 * entity type (0x1d) and maturity level (1..3), then fills each spawned
 * slot's record with a fresh object id, random stats and random role
 * values.  Returns the number of slots spawned. */

int __cdecl SpawnGraveyardEntities(void* entity, int count)
{
	unsigned char type;
	unsigned char* taddr;
	void* slot;
	int i;
	int r;
	int spawned;

	type = *(unsigned char*) entity;
	taddr = (unsigned char*) (type * 0x24c + g_entity_type_table + type);
	if ((*taddr == 0x1d) && (*(taddr + 0x247) >= 1) && (*(taddr + 0x247) <= 3)) {
		spawned = 0;
		if (count > 0) {
			while (spawned < count) {
			slot = FindSlotEntryFiltered(0, entity, 0, (void*) 0x10010700, 0);
			if (slot == 0)
				break;
			*(int*) *(int*) ((char*) slot + 0x10) = g_next_object_id;
			g_next_object_id++;
			*(int*) ((char*) slot + 4) = *(int*) *(int*) ((char*) slot + 0x10);
			*(unsigned short*) ((char*) slot + 8) = 0x7fff;
			*(unsigned char*) ((char*) slot + 0xc) = 0xff;
			*(unsigned short*) ((char*) slot + 0xa) =
			    (unsigned short) (g_current_year + 5);
			for (i = 0; i < 5; i++) {
				r = gm_RandomMod(8) & 0xffff;
				*(unsigned char*) (*(int*) ((char*) slot + 0x10) + 0x24 + i) =
				    (unsigned char) ((float) r * g_const_57c0 + g_const_57bc);
			}
			*(int*) (*(int*) ((char*) slot + 0x10) + 0x2c) =
			    (gm_RandomMod(9) & 0xffff) + 1;
			*(int*) (*(int*) ((char*) slot + 0x10) + 0x30) =
			    (gm_RandomMod(2) & 0xffff) + 1;
			*(int*) (*(int*) ((char*) slot + 0x10) + 0x34) =
			    (gm_RandomMod(0x5e) & 0xffff) + 1;
			*(int*) (*(int*) ((char*) slot + 0x10) + 0x40) =
			    g_current_year - (gm_RandomMod(4) & 0xffff) - 1;
			*(int*) (*(int*) ((char*) slot + 0x10) + 0x38) =
			    gm_RandomMod(2) & 0xffff;
			gm_RandomMod(0x10);
			gm_RandomMod(0x10);
			gm_RandomMod(0x10);
				spawned++;
			}
		}
	}
	return spawned;
}
