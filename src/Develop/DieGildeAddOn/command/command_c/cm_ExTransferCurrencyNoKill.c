extern unsigned char g_city_records[4 * 0x2f4];
#include "../command_internal.h"
#include "../../game/entity.h"

void __cdecl gm_SubObjectNoKill(unsigned int, unsigned int, unsigned int);
void __cdecl gm_AddObjekt(int, unsigned int, int);

// FUNCTION: GOLDTL 0x4c7c50
// SIZE: 2064
// FUNCTION: SERVER 0x1000d8a0

int __cdecl cm_ExTransferCurrencyNoKill(int cmd, char* result)
{
	int field_result;

	*(int*) (cmd + 0x18) = g_next_object_id;
	if (*(int*) (cmd + 0x14) != -1) {
		field_result = gm_GetFieldByType((char*) cmd, *(int*) (cmd + 0x14));
		*(int*) (cmd + 0x14) = field_result;
		gm_SubObjectNoKill(
			field_result,
			(unsigned int) (unsigned short) ((unsigned int*) (g_city_records + 0x54))[(unsigned int) *(unsigned char*) (cmd + 0x1c) * 189],
			*(int*) (cmd + 0x1d)
		);
	}
	if (*(int*) (cmd + 0x10) != -1) {
		field_result = gm_GetFieldByType((char*) cmd, *(int*) (cmd + 0x10));
		*(int*) (cmd + 0x10) = field_result;
		gm_AddObjekt(
			field_result,
			(unsigned int) (unsigned short) ((unsigned int*) (g_city_records + 0x54))[(unsigned int) *(unsigned char*) (cmd + 0x1c) * 189],
			*(int*) (cmd + 0x1d)
		);
	}
	if (result != (char*) 0) {
		*result = '\x01';
	}
	return 0;
}

