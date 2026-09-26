#include "../command_internal.h"
#include "../../../Units/Error/error.h"

ushort __cdecl gm_AllocSpieler(uint, int, int, ushort, int, uint, uint, uint);
char* __cdecl strncpy(char*, const char*, unsigned int);

// FUNCTION: GOLDTL 0x49d640
// SIZE: 384
// FUNCTION: SERVER 0x1000d570

int __cdecl cm_ExAllocClientSpieler(int cmd, char* result)
{
	unsigned int entity;
	short* entry;
	char* r2;
	int hash_index;
	int off;

	{
		char* c = (char*) cmd;
		unsigned int kind;
		*(int*)(c + 0x10) = g_next_object_id;
		*(int*)(c + 0x45) = rand();
		srv_SeedRandom(*(int*)(c + 0x22));
		if (result)
			kind = 6;
		else
			kind = 7;
		entity = gm_AllocSpieler(kind,
			*(int*)(c + 0x14), *(int*)(c + 0x18),
			*(unsigned short*)(c + 0x1c), 0,
			(unsigned char)*(char*)(c + 0x1e), 0,
			(unsigned char)*(char*)(c + 0x23));
	}
	entity = entity & 0xffff;
	if (entity == 0xffff) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x290f, "gm_AllocSpieler() failed", 1);
		return 1;
	}
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x2917, "ClientSpieler erzeugt", 1);
	off = entity * 0x21c;
	hash_index = 0x99099 * (unsigned char)*(char*)(cmd + 3);
	*(int*)(0x10442d00 + hash_index * 4) = *(int*)(g_slot_table + off + 4);
	strncpy(g_slot_table + off + 0x30, (char*)cmd + 0x25, 0x10);
	entry = gm_GetEntityTableEntry(g_slot_table + off);
	if (entry != 0) {
		*(unsigned short*)entry = *(unsigned short*)(g_slot_table + off + 0x50);
		strncpy((char*)entry + 2, (char*)cmd + 0x35, 0x10);
		strncpy(g_slot_table + off + 0x40, (char*)cmd + 0x35, 0x10);
		r2 = (char*)gm_LookupEntityRecordById(*(int*)(g_slot_table + off + 0x60));
		if (r2 != 0)
			strncpy(r2 + 0x40, (char*)cmd + 0x35, 0x10);
	}
	*(int*)(g_slot_table + off + 0x54) = *(int*)(cmd + 0x1f);
	*(unsigned char*)(g_slot_table + off + 0xc) = *(unsigned char*)(cmd + 0x24);
	if (result != (char*)0) {
		result[0] = 1;
		result[1] = 1;
		*(char**)(result + 6) = g_slot_table + off;
	}
	return 0;
}

