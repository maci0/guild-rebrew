#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"

#include <string.h>
typedef int(__cdecl* ALLOCFN)(int, int, int);

#pragma intrinsic(memcpy, memset)

// SIZE 0x2c
#pragma pack(push, 1)
// SIZE 0x43
typedef struct {
	short active;
	int id;
	char pad[0x3d];
} Record;
#pragma pack(pop)

extern char* g_entity_table; /* 0x101de450 */
extern int g_entity_type_table;
extern unsigned char g_current_season;
extern char* g_item_def_table;
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);

extern int g_object_count;
extern char g_100314b8[];
extern char g_10031004[];
extern char g_10031484[];

// STUB: SERVER 0x10017c40
// gm_AllocBuildingContents

int __cdecl gm_AllocBuildingContents(char* geb, int obj_id)
{
	char* obj;
	char* type_entry;
	unsigned int btype;
	int slot_idx;
	unsigned short slot_val;
	unsigned int item_index;
	char item_class;
	char* query;
	unsigned char limit_val;
	unsigned short obj_type;
	unsigned int season;
	char* season_base;
	char* cart_obj;
	char* goods_iter;
	char* slot_iter;
	int goods_count;

	if (g_item_def_table == 0) {
		return 0;
	}
	if (g_entity_type_table == 0) {
		return 0;
	}
	if (g_object_count + 0x40 >= 0x5008) {
		return 0;
	}

	obj = gm_AllocObjekt(*(int*) (geb + 1), obj_id, 1);

	btype = *(unsigned char*) geb;
	type_entry = (char*) (g_entity_type_table + btype + btype * 0x24c);

	/* scan component table at type_entry+0x23 to find slot matching obj_id */
	slot_idx = 0;
	if ((*(unsigned short*) (type_entry + 0x23) & 0x7fff) != (unsigned short) obj_id) {
		do {
			slot_idx = slot_idx + 1;
		} while ((*(unsigned short*) (type_entry + 0x23 + slot_idx * 2 + 2) & 0x7fff) != (unsigned short) obj_id);
	}
	slot_idx = slot_idx + 1;

	/* process remaining slots in the component table */
	if (slot_idx < 0x40) {
		do {
			slot_val = *(unsigned short*) (type_entry + 0x23 + slot_idx * 2);
			if (slot_val == 0) {
				break;
			}
			if (slot_val != 0xffff) {
				item_index = slot_val & 0x7fff;
				item_class = *(char*) (g_item_def_table + item_index * 0x41);
				if (item_class == '\x02' || item_class == '\x06') {
					slot_idx = 0x40;
				}
				else if ((slot_val & 0x8000) != 0) {
					gm_AllocObjekt(*(int*) (obj + 2), item_index, 1);
				}
			}
			slot_idx = slot_idx + 1;
		} while (slot_idx < 0x40);
	}

	/* first entity query: worker type 0x2a */
	query = (char*) gm_StartEntityQuery(*(int*) (obj + 0x14), 1, 0, 0x2a);
	if (query != (char*) 0) {
		*(int*) (query + 0x0e) = 2;
		*(int*) (query + 0x06) = *(int*) (geb + 1);
		limit_val = *(unsigned char*) (type_entry + 0x23d);
		if (limit_val == 0 && *(unsigned char*) (type_entry + 0x23e) == 0 &&
			*(unsigned char*) (type_entry + 0x23f) != 0) {
			*(unsigned char*) (query + 0x1c) = *(unsigned char*) (type_entry + 0x23f);
		}
		else {
			if (limit_val < 2) {
				limit_val = 2;
			}
			*(unsigned char*) (query + 0x1c) = limit_val;
			limit_val = *(unsigned char*) (type_entry + 0x23e);
			if (limit_val < 2) {
				limit_val = 2;
			}
			*(unsigned char*) (query + 0x1d) = limit_val;
		}
	}

	/* second entity query: merchant type 0x116 */
	query = (char*) gm_StartEntityQuery(*(int*) (obj + 0x14), 2, 0x116, 0, 6);
	if (query != (char*) 0) {
		*(int*) (query + 0x0e) = 2;
		*(int*) (query + 0x06) = *(int*) (obj + 2);
		limit_val = *(unsigned char*) (type_entry + 0x23d);
		if (limit_val == 0 && *(unsigned char*) (type_entry + 0x23e) == 0 &&
			*(unsigned char*) (type_entry + 0x23f) != 0) {
			if (*(unsigned char*) (type_entry + 0x23f) < 6) {
				*(unsigned char*) (query + 0x1c) = 6;
			}
			else {
				*(unsigned char*) (query + 0x1c) = *(unsigned char*) (type_entry + 0x23f);
			}
		}
		else {
			if (limit_val < 6) {
				limit_val = 6;
			}
			*(unsigned char*) (query + 0x1c) = limit_val;
			limit_val = *(unsigned char*) (type_entry + 0x23e);
			if (limit_val < 6) {
				limit_val = 6;
			}
			*(unsigned char*) (query + 0x1d) = limit_val;
		}
	}

	/* market stall check: types 0x92-0x97 or 0x2db */
	obj_type = *(unsigned short*) obj;
	if (!((obj_type >= 0x92 && obj_type <= 0x97) || obj_type == 0x2db)) {
		return (int) obj;
	}

	/* compute seasonal slot array base: season * (16*season + season) * 5 * 8 * 16 ... */
	season = (unsigned int) (unsigned char) g_current_season;
	{
		unsigned int a = (season << 4) + season;
		unsigned int d = a + a * 4;
		unsigned int s = season + d * 8;
		season_base = (char*) (0x1009B770 + (s << 4));
	}

	query = (char*) gm_StartEntityQuery(*(int*) (obj + 0x14), 1, 0x116, 0);
	if (query != (char*) 0) {
		*(unsigned char*) (query + 0x1c) = 0x0c;
		*(unsigned char*) (query + 0x1d) = 0;
		*(int*) (query + 0x0e) = 3;
	}
	else {
		ReportMessage(g_100314b8);
	}

	cart_obj = gm_AllocObjekt(*(int*) (obj + 2), 0xff, 1);
	goods_count = 0;
	goods_iter = (char*) 0x1002DDE0;
	slot_iter = season_base + 4;

	do {
		if (*(unsigned short*) (slot_iter + 0x38) == *(unsigned short*) geb && *(int*) slot_iter != 0) {
			if (goods_count >= 0x10) {
				LogMessageInternal(g_10031004, 0x16a6, g_10031484, 1);
			}
			else {
				gm_AllocObjekt(*(int*) (cart_obj + 2), (unsigned int) *(unsigned short*) goods_iter, 1);
				goods_count = goods_count + 1;
			}
		}
		goods_iter = goods_iter + 0x80;
		slot_iter = slot_iter + 0x80;
	} while (goods_iter < (char*) 0x10030860);

	return (int) obj;
}

/* Wrapper around gm_RemoveObjectByType. Provides a simpler
 * removal interface without filtering. */
