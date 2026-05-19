#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <string.h>

#pragma intrinsic(memset, strcpy)

int __cdecl gv_CheckSlotActive(char*, int);
extern char* DAT_100a8c30;
extern int g_slot_count_cat0[]; /* 0x1002577c */
extern int g_slot_count_cat1[]; /* 0x1002578c */
extern int g_slot_count_cat2[]; /* 0x1002579c */
extern int g_slot_count_cat3[]; /* 0x100257ac */
int __cdecl cm_GetBuildingStatCount(unsigned char*);
char* __cdecl gv_FindSlotEntryFiltered(char*, unsigned char*, char*, int(__cdecl*)(char*, char*), int);
int __cdecl gm_RandomMod(int);
extern unsigned int __ftol(void);
extern int g_entity_type_table;
extern int g_1002575c[];
extern int g_1002576c[];
extern char g_1002d444;
extern char g_1002d45c;
extern char g_1002d474;
int AllocGraveyardField(int);
void gv_Free3Fields(char*);
int __cdecl gm_ResolveEntityById(void** out_slot, void** out_person, void** out_building, int entity_id);
int __cdecl gv_GetSlotEntry(int, int, unsigned char);
int __cdecl gm_SubObjektNoKill(int, int, int);
void* __cdecl gm_AddOrAccumulateObject(int, int, int);
void __cdecl game_free(void*);
extern int DAT_1003546c;
extern short DAT_100358a0;
int SpawnGraveyardEntities(unsigned char*, int);
extern int g_entity_table_end;
extern char* g_action_table_base;
extern char g_slot_table[];
double __cdecl gm_RandomFloat01(void);
extern int DAT_10030b6c;
extern int DAT_10035434;
extern unsigned char DAT_10035439;
extern float DAT_10025680;
extern float DAT_100257c4;
extern float DAT_100257c8;

/* Checks if a production slot in a building is active.
 * Returns non-zero if the slot at the given index has
 * an assigned worker or active production. */

// FUNCTION: SERVER 0x10010530
// gv_CheckSlotActive
int __cdecl gv_CheckSlotActive(char* obj, int idx)
{
	if (idx == 0) {
		if (*(int*) (obj + 8) && *(obj + 0x18)) {
			return 1;
		}
		return 0;
	}
	if (idx == 1) {
		if (*(int*) (obj + 0xc) && *(obj + 0x19)) {
			return 1;
		}
		return 0;
	}
	if (idx == 2) {
		if (*(int*) (obj + 0x10) && *(obj + 0x1a)) {
			return 1;
		}
		return 0;
	}
	if (idx == 3) {
		if (*(int*) (obj + 0x14) && *(obj + 0x1b)) {
			return 1;
		}
		return 0;
	}
	return 1;
}

/* Gets a reference to a slot entry in a building's production
 * table. Returns the slot pointer at the specified index and
 * sub-type. */

// FUNCTION: SERVER 0x100105b0
// gv_GetSlotEntry

__declspec(naked) int __cdecl gv_GetSlotEntry(int param_1, int param_2, unsigned char param_3)
{
	(void) param_1;
	(void) param_2;
	(void) param_3;
	__asm {
		push esi
		mov esi, dword ptr [esp + 8]
		mov eax, dword ptr [esi + 4]
		cmp eax, 1
		jl near L_ret0
		cmp eax, 3
		jg near L_ret0
		mov eax, dword ptr [esp + 0xc]
		test eax, eax
		jne L_cat1
		push eax
		push esi
		call gv_CheckSlotActive
		add esp, 8
		test eax, eax
		je near L_ret0
		mov ecx, dword ptr [esi + 4]
		mov eax, dword ptr [esp + 0x10]
		cmp ecx, 1
		jne L_chk2_cat0
		cmp al, 8
		jae near L_ret0
	L_chk2_cat0:
		cmp ecx, 2
		jne L_chk3_cat0
		cmp al, 0xc
		jae near L_ret0
	L_chk3_cat0:
		cmp ecx, 3
		jne L_emit_cat0
		cmp al, 0x10
		jae near L_ret0
	L_emit_cat0:
		mov ecx, dword ptr [esi + 8]
		and eax, 0xff
		pop esi
		lea eax, [eax + eax*4]
		lea eax, [ecx + eax*4]
		ret
	L_cat1:
		cmp eax, 1
		jne L_cat2
		push eax
		push esi
		call gv_CheckSlotActive
		add esp, 8
		test eax, eax
		je near L_ret0
		mov ecx, dword ptr [esi + 4]
		mov eax, dword ptr [esp + 0x10]
		cmp ecx, 1
		jne L_chk2_cat1
		cmp al, 4
		jae near L_ret0
	L_chk2_cat1:
		cmp ecx, 2
		jne L_chk3_cat1
		cmp al, 6
		jae near L_ret0
	L_chk3_cat1:
		cmp ecx, 3
		jne L_emit_cat1
		cmp al, 8
		jae near L_ret0
	L_emit_cat1:
		and eax, 0xff
		lea edx, [eax + eax*4]
		mov eax, dword ptr [esi + 0xc]
		pop esi
		lea eax, [eax + edx*4]
		ret
	L_cat2:
		cmp eax, 2
		jne L_cat3
		push eax
		push esi
		call gv_CheckSlotActive
		add esp, 8
		test eax, eax
		je L_ret0
		mov ecx, dword ptr [esi + 4]
		cmp ecx, 1
		je L_ret0
		mov eax, dword ptr [esp + 0x10]
		cmp ecx, 2
		jne L_chk3_cat2
		cmp al, 2
		jae L_ret0
	L_chk3_cat2:
		cmp ecx, 3
		jne L_emit_cat2
		cmp al, 4
		jae L_ret0
	L_emit_cat2:
		mov edx, dword ptr [esi + 0x10]
		and eax, 0xff
		pop esi
		lea ecx, [eax + eax*4]
		lea eax, [edx + ecx*4]
		ret
	L_cat3:
		cmp eax, 3
		jne L_ret0
		push eax
		push esi
		call gv_CheckSlotActive
		add esp, 8
		test eax, eax
		je L_ret0
		mov eax, dword ptr [esi + 4]
		cmp eax, 1
		je L_ret0
		cmp eax, 2
		je L_ret0
		cmp eax, 3
		mov eax, dword ptr [esp + 0x10]
		jne L_emit_cat3
		cmp al, 2
		jae L_ret0
	L_emit_cat3:
		mov ecx, dword ptr [esi + 0x14]
		and eax, 0xff
		pop esi
		lea eax, [eax + eax*4]
		lea eax, [ecx + eax*4]
		ret
	L_ret0:
		xor eax, eax
		pop esi
		ret
	}
}

/* Finds a slot entry in a building with optional type filtering.
 * Searches production slots for one matching the given criteria
 * and returns a pointer to it. */

// FUNCTION: SERVER 0x10010710
// gv_FindSlotEntryFiltered

char* __cdecl gv_FindSlotEntryFiltered(char* ctx, unsigned char* obj, char* start, int(__cdecl* callback)(char*, char*), int category)
{
	unsigned int type_idx;
	char* sub_obj;
	char* entry;
	int count;
	char* base;
	char* end;

	type_idx = (unsigned int) *obj;
	entry = DAT_100a8c30 + type_idx * 0x24d;
	sub_obj = *(char**) (obj + 0x65);

	if (category != 0xFF) {
		if (!gv_CheckSlotActive(sub_obj, category)) {
			return 0;
		}
	}

	if (category == 0) {
		count = g_slot_count_cat0[(unsigned char) entry[0x247]];
		end = *(char**) (sub_obj + 8) + count * 0x14;
	}
	else if (category == 1) {
		count = g_slot_count_cat1[(unsigned char) entry[0x247]];
		end = *(char**) (sub_obj + 0xc) + count * 0x14;
	}
	else if (category == 2) {
		count = g_slot_count_cat2[(unsigned char) entry[0x247]];
		end = *(char**) (sub_obj + 0x10) + count * 0x14;
	}
	else if (category == 3) {
		count = g_slot_count_cat3[(unsigned char) entry[0x247]];
		end = *(char**) (sub_obj + 0x14) + count * 0x14;
	}
	else if (category == 0xFF) {
		count = cm_GetBuildingStatCount(obj);
		end = *(char**) (sub_obj + 0x1c) + count * 0x14;
	}
	else {
		return 0;
	}

	if (start == 0) {
		if (category == 0) {
			base = *(char**) (sub_obj + 8);
		}
		else if (category == 1) {
			base = *(char**) (sub_obj + 0xc);
		}
		else if (category == 2) {
			base = *(char**) (sub_obj + 0x10);
		}
		else if (category == 3) {
			base = *(char**) (sub_obj + 0x14);
		}
		else {
			base = *(char**) (sub_obj + 0x1c);
		}
	}
	else {
		base = start + 0x14;
	}

	if ((unsigned int) base >= (unsigned int) end) {
		return 0;
	}

	do {
		if (callback == 0) {
			return base;
		}
		if (callback(ctx, base)) {
			return base;
		}
		base += 0x14;
	} while ((unsigned int) base < (unsigned int) end);

	return 0;
}

/* Spawns graveyard entities (workers, resources) for a building.
 * Initializes the graveyard's active entities based on its
 * current upgrade level and capacity. */

// FUNCTION: SERVER 0x10010850
// SpawnGraveyardEntities

/* Auto-generated Ghidra decompilation */

int SpawnGraveyardEntities(unsigned char* param_1, int param_2)
{
	unsigned char building_tier;
	unsigned int new_entity_id;
	short current_game_tick;
	unsigned char rand_skill_byte;
	int slot_entry_ptr;
	unsigned int rand_stat_val;
	int spawn_count;
	int skill_index;
	char* entity_type_entry;
	char entity_class_byte;

	rand_stat_val = *param_1;
	entity_type_entry = *(char**) 0x100a8c30 + rand_stat_val + rand_stat_val * 0x24c;
	entity_class_byte = *entity_type_entry;

	if (entity_class_byte == '\x1d') {
		building_tier = *(unsigned char*) (entity_type_entry + 0x247);
		if (building_tier != 0 && building_tier < 4) {
			spawn_count = 0;
			if (0 < param_2) {
				do {
					slot_entry_ptr = (int) gv_FindSlotEntryFiltered(
						(char*) 0,
						param_1,
						(char*) 0,
						(int(__cdecl*)(char*, char*)) 0x10010700,
						0
					);
					if (slot_entry_ptr == 0) {
						return spawn_count;
					}
					*(*(unsigned int**) (slot_entry_ptr + 0x10)) = *(unsigned int*) 0x10030b6c;
					*(unsigned int*) 0x10030b6c = *(unsigned int*) 0x10030b6c + 1;
					new_entity_id = *(*(unsigned int**) (slot_entry_ptr + 0x10));
					*(unsigned int*) (slot_entry_ptr + 8) = 0x7fff;
					*(unsigned int*) (slot_entry_ptr + 4) = new_entity_id;
					current_game_tick = *(short*) 0x10035880;
					*(unsigned int*) (slot_entry_ptr + 0xc) = 0xff;
					*(unsigned int*) (slot_entry_ptr + 10) = current_game_tick + 5;
					skill_index = 0;
					do {
						gm_RandomMod(8);
						rand_skill_byte = __ftol();
						skill_index = skill_index + 1;
						*(*(char**) (slot_entry_ptr + 0x10) + 0x23 + skill_index) = rand_skill_byte;
					} while (skill_index < 5);
					rand_stat_val = gm_RandomMod(9);
					*(*(char**) (slot_entry_ptr + 0x10) + 0x2c) = (rand_stat_val & 0xffff) + 1;
					rand_stat_val = gm_RandomMod(2);
					*(*(char**) (slot_entry_ptr + 0x10) + 0x30) = (rand_stat_val & 0xffff) + 1;
					rand_stat_val = gm_RandomMod(0x5e);
					*(*(char**) (slot_entry_ptr + 0x10) + 0x34) = (rand_stat_val & 0xffff) + 1;
					rand_stat_val = gm_RandomMod(4);
					*(*(char**) (slot_entry_ptr + 0x10) + 0x40) =
						(*(short*) 0x10035880 - (rand_stat_val & 0xffff)) + -1;
					rand_stat_val = gm_RandomMod(2);
					*(*(char**) (slot_entry_ptr + 0x10) + 0x38) = rand_stat_val & 0xffff;
					gm_RandomMod(0x10);
					gm_RandomMod(0x10);
					gm_RandomMod(0x10);
					spawn_count = spawn_count + 1;
				} while (spawn_count < param_2);
			}
			return spawn_count;
		}
	}
	return 0;
}

/* Allocates a single graveyard production field. Sets up the
 * field's entity type, worker assignment, and production timer. */

// FUNCTION: SERVER 0x100109d0
// AllocGraveyardField

int __cdecl AllocGraveyardField(int param_1)
{
	unsigned int btype;
	char* type_entry;
	unsigned char tier;
	char* result;
	char* slot_1c;
	char* slot_20;
	int slot_1c_size;
	int slot_20_size;
	int i;
	char* eax_ptr;
	char* ecx_ptr;

	btype = *(unsigned char*) param_1;
	type_entry = (char*) (g_entity_type_table + btype + btype * 0x24c);
	if (*type_entry != '\x1d') {
		return 0;
	}
	tier = *(unsigned char*) (type_entry + 0x247);
	if (tier < 1 || tier > 3) {
		return 0;
	}

	result = (char*) m_AllocTracked(0x24, &g_1002d474);
	if (result == (char*) 0) {
		return 0;
	}

	/* zero-fill the 0x24-byte struct (9 dwords) */
	{
		int* fill = (int*) result;
		for (i = 9; i != 0; i--) {
			*fill = 0;
			fill = fill + 1;
		}
	}

	*(int*) result = *(int*) (param_1 + 1);
	*(int*) (result + 4) = (unsigned int) *(unsigned char*) (type_entry + 0x247);

	/* allocate slot_1c: g_1002575c[tier] * 0x14 bytes */
	slot_1c_size = g_1002575c[*(unsigned char*) (type_entry + 0x247)] * 0x14;
	slot_1c = (char*) m_AllocTracked(slot_1c_size, &g_1002d45c);
	*(int*) (result + 0x1c) = (int) slot_1c;
	if (slot_1c == (char*) 0) {
		goto cleanup;
	}

	/* zero-fill slot_1c */
	{
		int total = g_1002575c[*(unsigned char*) (type_entry + 0x247)] * 0x14;
		int dwords = total >> 2;
		int rem = total & 3;
		int* dp = (int*) slot_1c;
		char* bp;
		for (i = dwords; i != 0; i--) {
			*dp = 0;
			dp = dp + 1;
		}
		bp = (char*) dp;
		for (i = rem; i != 0; i--) {
			*bp = 0;
			bp = bp + 1;
		}
	}

	/* allocate slot_20: g_1002576c[tier] * 0x44 bytes */
	slot_20_size = g_1002576c[*(unsigned char*) (type_entry + 0x247)] * 0x44;
	slot_20 = (char*) m_AllocTracked(slot_20_size, &g_1002d444);
	*(int*) (result + 0x20) = (int) slot_20;
	if (slot_20 == (char*) 0) {
		goto cleanup;
	}

	/* zero-fill slot_20 */
	{
		int total = g_1002576c[*(unsigned char*) (type_entry + 0x247)] * 0x44;
		int dwords = total >> 2;
		int rem = total & 3;
		int* dp = (int*) slot_20;
		char* bp;
		for (i = dwords; i != 0; i--) {
			*dp = 0;
			dp = dp + 1;
		}
		bp = (char*) dp;
		for (i = rem; i != 0; i--) {
			*bp = 0;
			bp = bp + 1;
		}
	}

	/* init slot_20 entries: set first dword of each 0x44-byte entry to -1 */
	if (g_1002576c[*(unsigned char*) (type_entry + 0x247)] > 0) {
		int offset = 0;
		i = 0;
		do {
			*(int*) (*(int*) (result + 0x20) + offset) = -1;
			i = i + 1;
			offset = offset + 0x44;
		} while (i < g_1002576c[*(unsigned char*) (type_entry + 0x247)]);
	}

	/* set up struct fields and category pointers */
	eax_ptr = (char*) *(int*) (result + 0x1c);
	ecx_ptr = (char*) *(int*) (result + 0x20);
	*(int*) (result + 8) = (int) eax_ptr;
	*(char*) (result + 0x18) = 1;
	*(char*) (result + 0x19) = 0;
	*(char*) (result + 0x1a) = 0;
	*(char*) (result + 0x1b) = 0;

	if (*(int*) (result + 4) == 1) {
		/* Tier 1: 8 category-0 slots (stride 0x44), 4 category-1 slots (stride 0x88) */
		*(int*) (result + 0x10) = 0;
		*(int*) (result + 0x0c) = (int) (eax_ptr + 0xa0);
		*(int*) (result + 0x14) = 0;
		for (i = 8; i != 0; i--) {
			*(int*) eax_ptr = 0;
			*(int*) (eax_ptr + 0x10) = (int) ecx_ptr;
			*(int*) (eax_ptr + 4) = -1;
			*(unsigned short*) (eax_ptr + 8) = 0xffff;
			ecx_ptr = ecx_ptr + 0x44;
			eax_ptr = eax_ptr + 0x14;
		}
		for (i = 4; i != 0; i--) {
			*(int*) eax_ptr = 1;
			*(int*) (eax_ptr + 0x10) = (int) ecx_ptr;
			*(int*) (eax_ptr + 4) = -1;
			*(unsigned short*) (eax_ptr + 8) = 0xffff;
			ecx_ptr = ecx_ptr + 0x88;
			eax_ptr = eax_ptr + 0x14;
		}
		*(int*) (param_1 + 0x65) = (int) result;
		return (int) result;
	}

	if (*(int*) (result + 4) == 2) {
		/* Tier 2: 12 cat-0 (0x44), 6 cat-1 (0x88), 2 cat-2 (0x110) */
		*(int*) (result + 0x14) = 0;
		*(int*) (result + 0x0c) = (int) (eax_ptr + 0xf0);
		*(int*) (result + 0x10) = (int) (eax_ptr + 0x168);
		for (i = 0xc; i != 0; i--) {
			*(int*) eax_ptr = 0;
			*(int*) (eax_ptr + 0x10) = (int) ecx_ptr;
			*(int*) (eax_ptr + 4) = -1;
			*(unsigned short*) (eax_ptr + 8) = 0xffff;
			ecx_ptr = ecx_ptr + 0x44;
			eax_ptr = eax_ptr + 0x14;
		}
		for (i = 6; i != 0; i--) {
			*(int*) eax_ptr = 1;
			*(int*) (eax_ptr + 0x10) = (int) ecx_ptr;
			*(int*) (eax_ptr + 4) = -1;
			*(unsigned short*) (eax_ptr + 8) = 0xffff;
			ecx_ptr = ecx_ptr + 0x88;
			eax_ptr = eax_ptr + 0x14;
		}
		for (i = 2; i != 0; i--) {
			*(int*) eax_ptr = 2;
			*(int*) (eax_ptr + 0x10) = (int) ecx_ptr;
			*(int*) (eax_ptr + 4) = -1;
			*(unsigned short*) (eax_ptr + 8) = 0xffff;
			ecx_ptr = ecx_ptr + 0x110;
			eax_ptr = eax_ptr + 0x14;
		}
		*(int*) (param_1 + 0x65) = (int) result;
		return (int) result;
	}

	/* Tier 3: 16 cat-0 (0x44), 8 cat-1 (0x88), 4 cat-2 (0x110), 2 cat-3 (0x220) */
	*(int*) (result + 0x0c) = (int) (eax_ptr + 0x140);
	*(int*) (result + 0x10) = (int) (eax_ptr + 0x1e0);
	*(int*) (result + 0x14) = (int) (eax_ptr + 0x230);
	for (i = 0x10; i != 0; i--) {
		*(int*) eax_ptr = 0;
		*(int*) (eax_ptr + 0x10) = (int) ecx_ptr;
		*(int*) (eax_ptr + 4) = -1;
		*(unsigned short*) (eax_ptr + 8) = 0xffff;
		ecx_ptr = ecx_ptr + 0x44;
		eax_ptr = eax_ptr + 0x14;
	}
	for (i = 8; i != 0; i--) {
		*(int*) eax_ptr = 1;
		*(int*) (eax_ptr + 0x10) = (int) ecx_ptr;
		*(int*) (eax_ptr + 4) = -1;
		*(unsigned short*) (eax_ptr + 8) = 0xffff;
		ecx_ptr = ecx_ptr + 0x88;
		eax_ptr = eax_ptr + 0x14;
	}
	for (i = 4; i != 0; i--) {
		*(int*) eax_ptr = 2;
		*(int*) (eax_ptr + 0x10) = (int) ecx_ptr;
		*(int*) (eax_ptr + 4) = -1;
		*(unsigned short*) (eax_ptr + 8) = 0xffff;
		ecx_ptr = ecx_ptr + 0x110;
		eax_ptr = eax_ptr + 0x14;
	}
	for (i = 2; i != 0; i--) {
		*(int*) eax_ptr = 3;
		*(int*) (eax_ptr + 0x10) = (int) ecx_ptr;
		*(int*) (eax_ptr + 4) = -1;
		*(unsigned short*) (eax_ptr + 8) = 0xffff;
		ecx_ptr = ecx_ptr + 0x220;
		eax_ptr = eax_ptr + 0x14;
	}
	*(int*) (param_1 + 0x65) = (int) result;
	return (int) result;

cleanup:
	if (*(int*) (result + 0x1c) != 0) {
		m_FreeTracked((void*) *(int*) (result + 0x1c));
		*(int*) (result + 0x1c) = 0;
	}
	if (*(int*) (result + 0x20) != 0) {
		m_FreeTracked((void*) *(int*) (result + 0x20));
		*(int*) (result + 0x20) = 0;
	}
	m_FreeTracked(result);
	return 0;
}

/* Upgrades a graveyard field to the next tier. Increases
 * production capacity and unlocks new product types. */

// FUNCTION: SERVER 0x10010d10
// UpgradeGraveyardField

/* Auto-generated Ghidra decompilation */

unsigned int UpgradeGraveyardField(unsigned char* param_1)
{
	int old_field_ptr;
	int new_field_ptr;
	unsigned int entity_type_idx;
	int loop_byte_offset;
	int slot_copy_counter;
	int slot0_count;
	int slot1_count;
	unsigned int* src_slot_dword_ptr;
	unsigned int* dst_slot_dword_ptr;
	int slot2_count;

	entity_type_idx = *param_1;
	old_field_ptr = *(int*) (param_1 + 0x65);
	loop_byte_offset = *(int*) 0x100a8c30 + entity_type_idx + entity_type_idx * 0x24c;
	if ((((*(char*) (*(int*) 0x100a8c30 + entity_type_idx + entity_type_idx * 0x24c) == '\x1d') &&
		  (old_field_ptr != 0)) &&
		 (*(int*) (old_field_ptr + 4) < 3)) &&
		(*(char*) (loop_byte_offset + 0x247) - *(int*) (old_field_ptr + 4) == 1)) {
		param_1[0x65] = 0;
		param_1[0x66] = 0;
		param_1[0x67] = 0;
		param_1[0x68] = 0;
		new_field_ptr = AllocGraveyardField((int) param_1);
		if (new_field_ptr != 0) {
			if (*(char*) (loop_byte_offset + 0x247) == '\x02') {
				slot2_count = 0;
				slot0_count = 8;
				slot1_count = 4;
				src_slot_dword_ptr = *(unsigned int**) (*(int*) (old_field_ptr + 8) + 0x10);
				dst_slot_dword_ptr = *(unsigned int**) (*(int*) (new_field_ptr + 8) + 0x10);
				for (loop_byte_offset = 0x88; loop_byte_offset != 0; loop_byte_offset = loop_byte_offset + -1) {
					*dst_slot_dword_ptr = *src_slot_dword_ptr;
					src_slot_dword_ptr = src_slot_dword_ptr + 1;
					dst_slot_dword_ptr = dst_slot_dword_ptr + 1;
				}
				loop_byte_offset = *(int*) (new_field_ptr + 0xc);
				src_slot_dword_ptr = *(unsigned int**) (*(int*) (old_field_ptr + 0xc) + 0x10);
			}
			else {
				slot2_count = 2;
				src_slot_dword_ptr = *(unsigned int**) (*(int*) (old_field_ptr + 8) + 0x10);
				dst_slot_dword_ptr = *(unsigned int**) (*(int*) (new_field_ptr + 8) + 0x10);
				for (loop_byte_offset = 0xcc; loop_byte_offset != 0; loop_byte_offset = loop_byte_offset + -1) {
					*dst_slot_dword_ptr = *src_slot_dword_ptr;
					src_slot_dword_ptr = src_slot_dword_ptr + 1;
					dst_slot_dword_ptr = dst_slot_dword_ptr + 1;
				}
				slot0_count = 0xc;
				src_slot_dword_ptr = *(unsigned int**) (*(int*) (old_field_ptr + 0xc) + 0x10);
				dst_slot_dword_ptr = *(unsigned int**) (*(int*) (new_field_ptr + 0xc) + 0x10);
				for (loop_byte_offset = 0xcc; loop_byte_offset != 0; loop_byte_offset = loop_byte_offset + -1) {
					*dst_slot_dword_ptr = *src_slot_dword_ptr;
					src_slot_dword_ptr = src_slot_dword_ptr + 1;
					dst_slot_dword_ptr = dst_slot_dword_ptr + 1;
				}
				loop_byte_offset = *(int*) (new_field_ptr + 0x10);
				slot1_count = 6;
				src_slot_dword_ptr = *(unsigned int**) (*(int*) (old_field_ptr + 0x10) + 0x10);
			}
			dst_slot_dword_ptr = *(unsigned int**) (loop_byte_offset + 0x10);
			for (slot_copy_counter = 0x88; slot_copy_counter != 0; slot_copy_counter = slot_copy_counter + -1) {
				*dst_slot_dword_ptr = *src_slot_dword_ptr;
				src_slot_dword_ptr = src_slot_dword_ptr + 1;
				dst_slot_dword_ptr = dst_slot_dword_ptr + 1;
			}
			if ((*(int*) (old_field_ptr + 8) != 0) && (slot0_count != 0)) {
				loop_byte_offset = 0;
				do {
					*(int*) (*(int*) (new_field_ptr + 8) + loop_byte_offset) =
						*(int*) (loop_byte_offset + *(int*) (old_field_ptr + 8));
					*(int*) (*(int*) (new_field_ptr + 8) + 4 + loop_byte_offset) =
						*(int*) (loop_byte_offset + 4 + *(int*) (old_field_ptr + 8));
					*(int*) (*(int*) (new_field_ptr + 8) + 8 + loop_byte_offset) =
						*(int*) (loop_byte_offset + 8 + *(int*) (old_field_ptr + 8));
					*(short*) (*(int*) (new_field_ptr + 8) + 10 + loop_byte_offset) =
						*(short*) (loop_byte_offset + 10 + *(int*) (old_field_ptr + 8));
					*(char*) (*(int*) (new_field_ptr + 8) + 0xc + loop_byte_offset) =
						*(char*) (loop_byte_offset + 0xc + *(int*) (old_field_ptr + 8));
					loop_byte_offset = loop_byte_offset + 0x14;
					slot0_count = slot0_count + -1;
				} while (slot0_count != 0);
			}
			if ((*(int*) (old_field_ptr + 0xc) != 0) && (slot1_count != 0)) {
				loop_byte_offset = 0;
				do {
					*(int*) (loop_byte_offset + *(int*) (new_field_ptr + 0xc)) =
						*(int*) (loop_byte_offset + *(int*) (old_field_ptr + 0xc));
					*(int*) (loop_byte_offset + 4 + *(int*) (new_field_ptr + 0xc)) =
						*(int*) (loop_byte_offset + 4 + *(int*) (old_field_ptr + 0xc));
					*(int*) (loop_byte_offset + 8 + *(int*) (new_field_ptr + 0xc)) =
						*(int*) (loop_byte_offset + 8 + *(int*) (old_field_ptr + 0xc));
					*(short*) (loop_byte_offset + 10 + *(int*) (new_field_ptr + 0xc)) =
						*(short*) (loop_byte_offset + 10 + *(int*) (old_field_ptr + 0xc));
					*(char*) (loop_byte_offset + 0xc + *(int*) (new_field_ptr + 0xc)) =
						*(char*) (loop_byte_offset + 0xc + *(int*) (old_field_ptr + 0xc));
					loop_byte_offset = loop_byte_offset + 0x14;
					slot1_count = slot1_count + -1;
				} while (slot1_count != 0);
			}
			if ((*(int*) (old_field_ptr + 0x10) != 0) && (slot2_count != 0)) {
				loop_byte_offset = 0;
				do {
					*(int*) (loop_byte_offset + *(int*) (new_field_ptr + 0x10)) =
						*(int*) (loop_byte_offset + *(int*) (old_field_ptr + 0x10));
					*(int*) (loop_byte_offset + 4 + *(int*) (new_field_ptr + 0x10)) =
						*(int*) (loop_byte_offset + 4 + *(int*) (old_field_ptr + 0x10));
					*(int*) (loop_byte_offset + 8 + *(int*) (new_field_ptr + 0x10)) =
						*(int*) (loop_byte_offset + 8 + *(int*) (old_field_ptr + 0x10));
					*(short*) (loop_byte_offset + 10 + *(int*) (new_field_ptr + 0x10)) =
						*(short*) (loop_byte_offset + 10 + *(int*) (old_field_ptr + 0x10));
					*(char*) (loop_byte_offset + 0xc + *(int*) (new_field_ptr + 0x10)) =
						*(char*) (loop_byte_offset + 0xc + *(int*) (old_field_ptr + 0x10));
					loop_byte_offset = loop_byte_offset + 0x14;
					slot2_count = slot2_count + -1;
				} while (slot2_count != 0);
			}
			*(int*) (new_field_ptr + 0x18) = *(int*) (old_field_ptr + 0x18);
			*(char*) (new_field_ptr + 0x19) = *(char*) (old_field_ptr + 0x19);
			*(char*) (new_field_ptr + 0x1a) = *(char*) (old_field_ptr + 0x1a);
			*(char*) (new_field_ptr + 0x1b) = *(char*) (old_field_ptr + 0x1b);
			gv_Free3Fields((char*) old_field_ptr);
			return *(unsigned int*) (param_1 + 0x65);
		}
		*(unsigned int*) (param_1 + 0x65) = old_field_ptr;
	}
	return 0;
}

/* Frees 3 consecutive production fields in a building.
 * Deallocates the field entities and clears their slots. */

// FUNCTION: SERVER 0x10010F50
// gv_Free3Fields

void __cdecl gv_Free3Fields(char* p)
{
	if (!p) {
		return;
	}
	if (*(int*) (p + 0x1c)) {
		game_free(*(void**) (p + 0x1c));
		*(int*) (p + 0x1c) = 0;
	}
	if (*(int*) (p + 0x20)) {
		game_free(*(void**) (p + 0x20));
		*(int*) (p + 0x20) = 0;
	}
	game_free(p);
}

/* Assigns a product type to a production slot. Validates the
 * slot is empty, sets the product ID, and initializes the
 * production timer. */

// FUNCTION: SERVER 0x10010fa0
// AssignProductionSlot

/* Auto-generated Ghidra decompilation */

unsigned int AssignProductionSlot(int param_1)
{
	char str_scan_char;
	int worker_slot_capacity;
	int slot_category_check;
	int assignment_loop_idx;
	int* candidate_record_ptr;
	unsigned int strlen_counter;
	unsigned int copy_dword_count;
	int* best_slot_record_ptr;
	int* slot_worker_array_ptr;
	char* name_scan_ptr;
	char* name_scan_end_ptr;
	unsigned char* building_entity_ptr;

	worker_slot_capacity = param_1;
	gm_ResolveEntityById(&building_entity_ptr, 0, 0, *(unsigned int*) (param_1 + 8));
	if (((building_entity_ptr == 0) || (*(unsigned short*) (building_entity_ptr + 0x27) == 0xffff)) ||
		(*(unsigned short*) (building_entity_ptr + 0x27) * 0x21c + *(unsigned int*) 0x100358a0 ==
		 *(unsigned int*) 0x1003546c)) {
		return 0xffffffff;
	}
	if (*(*(char**) 0x100a8c30 + *building_entity_ptr * 0x24d) != '\x1d') {
		return 0xfffffffe;
	}
	assignment_loop_idx = *(unsigned int*) (building_entity_ptr + 0x65);
	if (assignment_loop_idx == 0) {
		return 0xfffffffd;
	}
	slot_category_check = gv_CheckSlotActive((char*) assignment_loop_idx, *(int*) (worker_slot_capacity + 0xc));
	if (slot_category_check == 0) {
		return 0xfffffffc;
	}
	gm_ResolveEntityById((void**) 0, (void**) 0, (void**) &param_1, *(unsigned int*) (worker_slot_capacity + 4));
	if (param_1 == 0) {
		return 0xfffffffa;
	}
	assignment_loop_idx = gv_GetSlotEntry(
		assignment_loop_idx,
		*(int*) (worker_slot_capacity + 0xc),
		(unsigned char) *(int*) (worker_slot_capacity + 0x10)
	);
	if ((assignment_loop_idx == 0) ||
		(*(unsigned int*) (assignment_loop_idx + 8) != *(unsigned int*) (param_1 + 0x50))) {
		return 0xfffffff9;
	}
	slot_worker_array_ptr = *(int**) (assignment_loop_idx + 0x10);
	assignment_loop_idx = 0;
	worker_slot_capacity = *(int*) (*(int*) (worker_slot_capacity + 0xc) * 4 + 0x1002574c);
	candidate_record_ptr = slot_worker_array_ptr;
	best_slot_record_ptr = slot_worker_array_ptr;
	if (0 < worker_slot_capacity) {
		do {
			if (*best_slot_record_ptr == -1) {
				break;
			}
			if (*candidate_record_ptr == -1) {
				best_slot_record_ptr = slot_worker_array_ptr + assignment_loop_idx * 0x11;
				break;
			}
			if (candidate_record_ptr[0x10] < best_slot_record_ptr[0x10]) {
				best_slot_record_ptr = candidate_record_ptr;
			}
			assignment_loop_idx = assignment_loop_idx + 1;
			candidate_record_ptr = candidate_record_ptr + 0x11;
		} while (assignment_loop_idx < worker_slot_capacity);
	}
	*best_slot_record_ptr = *(unsigned int*) (param_1 + 4);
	strlen_counter = 0xffffffff;
	name_scan_ptr = (char*) (param_1 + 0x30);
	do {
		name_scan_end_ptr = name_scan_ptr;
		if (strlen_counter == 0) {
			break;
		}
		strlen_counter = strlen_counter - 1;
		name_scan_end_ptr = name_scan_ptr + 1;
		str_scan_char = *name_scan_ptr;
		name_scan_ptr = name_scan_end_ptr;
	} while (str_scan_char != '\0');
	strlen_counter = ~strlen_counter;
	candidate_record_ptr = (int*) (name_scan_end_ptr + -(int) strlen_counter);
	slot_worker_array_ptr = best_slot_record_ptr;
	for (copy_dword_count = strlen_counter >> 2;
		 slot_worker_array_ptr = slot_worker_array_ptr + 1, copy_dword_count != 0;
		 copy_dword_count = copy_dword_count - 1) {
		*slot_worker_array_ptr = *candidate_record_ptr;
		candidate_record_ptr = candidate_record_ptr + 1;
	}
	for (strlen_counter = strlen_counter & 3; strlen_counter != 0; strlen_counter = strlen_counter - 1) {
		*slot_worker_array_ptr = *candidate_record_ptr;
		candidate_record_ptr = candidate_record_ptr + 1;
		slot_worker_array_ptr = slot_worker_array_ptr + 1;
	}
	strlen_counter = 0xffffffff;
	name_scan_ptr = (char*) (param_1 + 0x40);
	do {
		name_scan_end_ptr = name_scan_ptr;
		if (strlen_counter == 0) {
			break;
		}
		strlen_counter = strlen_counter - 1;
		name_scan_end_ptr = name_scan_ptr + 1;
		str_scan_char = *name_scan_ptr;
		name_scan_ptr = name_scan_end_ptr;
	} while (str_scan_char != '\0');
	strlen_counter = ~strlen_counter;
	slot_worker_array_ptr = (int*) (name_scan_end_ptr + -(int) strlen_counter);
	candidate_record_ptr = best_slot_record_ptr + 5;
	for (copy_dword_count = strlen_counter >> 2; copy_dword_count != 0; copy_dword_count = copy_dword_count - 1) {
		*candidate_record_ptr = *slot_worker_array_ptr;
		slot_worker_array_ptr = slot_worker_array_ptr + 1;
		candidate_record_ptr = candidate_record_ptr + 1;
	}
	for (strlen_counter = strlen_counter & 3; strlen_counter != 0; strlen_counter = strlen_counter - 1) {
		*candidate_record_ptr = *slot_worker_array_ptr;
		slot_worker_array_ptr = slot_worker_array_ptr + 1;
		candidate_record_ptr = candidate_record_ptr + 1;
	}
	best_slot_record_ptr[9] = *(unsigned int*) (param_1 + 0x80);
	*(best_slot_record_ptr + 10) = *(unsigned int*) (param_1 + 0x84);
	best_slot_record_ptr[0xb] = *(unsigned int*) (param_1 + 0x167);
	best_slot_record_ptr[0xc] = *(unsigned int*) (param_1 + 0xd);
	best_slot_record_ptr[0xd] = *(unsigned int*) (param_1 + 0x164);
	best_slot_record_ptr[0xe] = *(unsigned int*) (param_1 + 9);
	best_slot_record_ptr[0x10] = *(unsigned int*) 0x10035880;
	best_slot_record_ptr[0xf] = *(unsigned int*) (param_1 + 0x18c);
	return 0;
}

/* Hires a worker for a production slot. Links the worker
 * entity to the building's production slot and starts the
 * production cycle. */

// FUNCTION: SERVER 0x100111b0
// HireProductionWorker

/* Auto-generated Ghidra decompilation */

unsigned int HireProductionWorker(int param_1)
{
	int cmd_ptr_saved;
	int slot_or_active_check;
	unsigned int rand_coin_amount;
	short hire_deadline_tick;
	int worker_record_count;
	int worker_record_offset;
	unsigned char* building_entity_ptr;

	cmd_ptr_saved = param_1;
	gm_ResolveEntityById(&building_entity_ptr, 0, 0, *(unsigned int*) (param_1 + 8));
	if (((building_entity_ptr == 0) || (*(unsigned short*) (building_entity_ptr + 0x27) == 0xffff)) ||
		(*(unsigned short*) (building_entity_ptr + 0x27) * 0x21c + *(unsigned int*) 0x100358a0 ==
		 *(unsigned int*) 0x1003546c)) {
		return 0xffffffff;
	}
	if (*(*(char**) 0x100a8c30 + *building_entity_ptr * 0x24d) != '\x1d') {
		return 0xfffffffe;
	}
	if (*(unsigned int*) (building_entity_ptr + 0x65) == 0) {
		return 0xfffffffd;
	}
	slot_or_active_check =
		gv_CheckSlotActive((char*) *(unsigned int*) (building_entity_ptr + 0x65), *(int*) (cmd_ptr_saved + 0xc));
	if (slot_or_active_check == 0) {
		return 0xfffffffc;
	}
	gm_ResolveEntityById((void**) 0, (void**) 0, (void**) &param_1, *(unsigned int*) (cmd_ptr_saved + 4));
	if (param_1 == 0) {
		return 0xfffffffa;
	}
	slot_or_active_check = *(int*) (cmd_ptr_saved + 0xc);
	if ((-1 < slot_or_active_check) && (slot_or_active_check < 4)) {
		slot_or_active_check = (int) gv_FindSlotEntryFiltered(
			(char*) param_1,
			building_entity_ptr,
			(char*) 0,
			(int(__cdecl*)(char*, char*)) 0x10010700,
			slot_or_active_check
		);
		if (slot_or_active_check == 0) {
			return 0xfffffff9;
		}
		*(unsigned int*) (slot_or_active_check + 4) = *(unsigned int*) (param_1 + 4);
		*(unsigned int*) (slot_or_active_check + 8) = *(unsigned int*) (param_1 + 0x50);
		hire_deadline_tick = *(short*) (cmd_ptr_saved + 0x11) + *(short*) 0x10035880;
		*(unsigned char*) (slot_or_active_check + 0xc) = 0xff;
		*(short*) (slot_or_active_check + 10) = hire_deadline_tick;
		worker_record_count = 0;
		if (0 < *(int*) (*(int*) (cmd_ptr_saved + 0xc) * 4 + 0x1002574c)) {
			worker_record_offset = 0;
			do {
				worker_record_count = worker_record_count + 1;
				*(unsigned int*) (*(int*) (slot_or_active_check + 0x10) + worker_record_offset) = 0xffffffff;
				worker_record_offset = worker_record_offset + 0x44;
			} while (worker_record_count < *(int*) (*(int*) (cmd_ptr_saved + 0xc) * 4 + 0x1002574c));
		}
		if (0 < *(int*) (cmd_ptr_saved + 0x13)) {
			gm_SubObjektNoKill(
				*(unsigned int*) (param_1 + 4),
				*(unsigned int*) (*(unsigned int*) 0x10035439 * 0x2f4 + 0x100a8c94),
				*(unsigned int*) (cmd_ptr_saved + 0x13)
			);
			rand_coin_amount = __ftol();
			gm_AddOrAccumulateObject(
				*(unsigned int*) (*(unsigned short*) (building_entity_ptr + 0x27) * 0x21c + 0x100358a4),
				*(unsigned int*) (*(unsigned int*) 0x10035439 * 0x2f4 + 0x100a8c94),
				rand_coin_amount
			);
		}
		return 0;
	}
	return 0xfffffffb;
}

/* Extends the production time for an active slot. Adds
 * additional time to the production timer, adjusting for
 * worker skill and building efficiency. */

// FUNCTION: SERVER 0x100113b0
// ExtendProductionTime

/* Auto-generated Ghidra decompilation */

unsigned int ExtendProductionTime(unsigned int* param_1)
{
	unsigned int* cmd_ptr_saved;
	int slot_active_result;
	int slot_entry_ptr;
	unsigned int rand_coin_amount;
	unsigned char* building_entity_ptr;

	cmd_ptr_saved = param_1;
	gm_ResolveEntityById(&building_entity_ptr, 0, 0, *(param_1 + 8));
	if (((building_entity_ptr == 0) || (*(unsigned short*) (building_entity_ptr + 0x27) == 0xffff)) ||
		((*(unsigned short*) (building_entity_ptr + 0x27) * 0x21c + *(unsigned int*) 0x100358a0) ==
		 *(unsigned int*) 0x1003546c)) {
		return 0xffffffff;
	}
	if (*(*(char**) 0x100a8c30 + *building_entity_ptr * 0x24d) != '\x1d') {
		return 0xfffffffe;
	}
	slot_entry_ptr = *(unsigned int*) (building_entity_ptr + 0x65);
	if (slot_entry_ptr == 0) {
		return 0xfffffffd;
	}
	slot_active_result = gv_CheckSlotActive((char*) slot_entry_ptr, *(cmd_ptr_saved + 0xc));
	if (slot_active_result == 0) {
		return 0xfffffffc;
	}
	gm_ResolveEntityById((void**) 0, (void**) 0, (void**) &param_1, *(cmd_ptr_saved + 4));
	if (param_1 == 0) {
		return 0xfffffffa;
	}
	slot_entry_ptr = gv_GetSlotEntry(slot_entry_ptr, *(cmd_ptr_saved + 0xc), (unsigned char) *(cmd_ptr_saved + 0x10));
	if (slot_entry_ptr == 0) {
		return 0xfffffff9;
	}
	*(unsigned int*) (slot_entry_ptr + 10) = *(unsigned int*) (slot_entry_ptr + 10) + *(cmd_ptr_saved + 0x11);
	if (0 < (int) *(cmd_ptr_saved + 0x13)) {
		gm_SubObjektNoKill(
			*(param_1 + 4),
			*(*(unsigned int**) 0x100a8c94 + *(unsigned int*) 0x10035439 * 0x2f4),
			*(cmd_ptr_saved + 0x13)
		);
		rand_coin_amount = __ftol();
		gm_AddOrAccumulateObject(
			*(*(unsigned int**) 0x100358a4 + *(unsigned short*) (building_entity_ptr + 0x27) * 0x21c),
			*(*(unsigned int**) 0x100a8c94 + *(unsigned int*) 0x10035439 * 0x2f4),
			rand_coin_amount
		);
	}
	return 0;
}

/* Replaces the worker assigned to a production slot.
 * Unlinks the old worker and assigns a new one while
 * maintaining production state. */

// FUNCTION: SERVER 0x10011540
// gv_ReplaceProductionWorker


int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);

__declspec(naked) int __cdecl gv_ReplaceProductionWorker(unsigned char* param_1)
{
	(void) param_1;
	__asm {
		push ecx
		push ebx
		push ebp
		push esi
		mov esi, dword ptr [esp + 0x14]
		push edi
		lea ecx, [esp + 0x18]
		mov eax, dword ptr [esi + 8]
		or ebx, 0xffffffff
		push eax
		push 0
		push 0
		push ecx
		mov ebp, 0xffff
		call gm_ResolveEntityById
		mov edx, dword ptr [esp + 0x28]
		add esp, 0x10
		test edx, edx
		je L_ret_neg1
		mov ax, word ptr [edx + 0x27]
		cmp ax, bp
		je L_ret_neg1
		and eax, ebp
		lea eax, [eax + eax*2]
		lea eax, [eax + eax*4]
		lea eax, [eax + eax*8]
		lea ecx, [eax*4 + 0x100358a0]
		_emit 0xa1
		_emit 0x6c
		_emit 0x54
		_emit 0x03
		_emit 0x10
		cmp ecx, eax
		je L_ret_neg1
		xor ecx, ecx
		_emit 0x8b
		_emit 0x3d
		_emit 0x30
		_emit 0x8c
		_emit 0x0a
		_emit 0x10
		mov cl, byte ptr [edx]
		add edi, ecx
		lea eax, [ecx + ecx*2]
		shl eax, 4
		add eax, ecx
		lea eax, [eax + eax*2]
		cmp byte ptr [edi + eax*4], 0x1d
		je L_action_ok
		pop edi
		pop esi
		pop ebp
		mov eax, 0xfffffffe
		pop ebx
		pop ecx
		ret
	L_action_ok:
		mov edi, dword ptr [edx + 0x65]
		test edi, edi
		jne L_have_slot
		pop edi
		pop esi
		pop ebp
		mov eax, 0xfffffffd
		pop ebx
		pop ecx
		ret
	L_have_slot:
		mov ecx, dword ptr [esi + 0xc]
		push ecx
		push edi
		call gv_CheckSlotActive
		add esp, 8
		test eax, eax
		jne L_slot_active
		pop edi
		pop esi
		pop ebp
		mov eax, 0xfffffffc
		pop ebx
		pop ecx
		ret
	L_slot_active:
		mov eax, dword ptr [esi + 4]
		cmp eax, -1
		je L_no_new_worker
		lea edx, [esp + 0x10]
		push eax
		push edx
		push 0
		push 0
		call gm_ResolveEntityById
		mov eax, dword ptr [esp + 0x20]
		add esp, 0x10
		test eax, eax
		jne L_worker_ok
		pop edi
		pop esi
		pop ebp
		mov eax, 0xfffffffa
		pop ebx
		pop ecx
		ret
	L_worker_ok:
		mov ebx, dword ptr [esi + 4]
		mov bp, word ptr [eax + 0x50]
	L_no_new_worker:
		mov al, byte ptr [esi + 0x10]
		mov ecx, dword ptr [esi + 0xc]
		push eax
		push ecx
		push edi
		call gv_GetSlotEntry
		add esp, 0xc
		test eax, eax
		jne L_have_entry
		pop edi
		pop esi
		pop ebp
		mov eax, 0xfffffff9
		pop ebx
		pop ecx
		ret
	L_have_entry:
		pop edi
		mov word ptr [eax + 8], bp
		pop esi
		mov dword ptr [eax + 4], ebx
		pop ebp
		xor eax, eax
		pop ebx
		pop ecx
		ret
	L_ret_neg1:
		pop edi
		pop esi
		pop ebp
		or eax, 0xffffffff
		pop ebx
		pop ecx
		ret
	}
}

/* Activates a graveyard section (tier/wing). Unlocks
 * additional production slots and enables new capabilities
 * for the graveyard building. */

// FUNCTION: SERVER 0x10011660
// ActivateGraveyardSection

// DATA: SERVER 0x1003546c
extern int g_entity_table_end;

// DATA: SERVER 0x100a8c30
extern char* g_action_table_base;

// DATA: SERVER 0x100358a0
extern char g_slot_table[];

int __cdecl ActivateGraveyardSection(unsigned char* param_1)
{
	void* entity;
	void* target_entity;

	gm_ResolveEntityById((void**) &entity, (void**) 0, (void**) 0, *(int*) (param_1 + 8));
	if (entity != 0) {
		if (*(unsigned short*) ((char*) entity + 0x27) != 0xFFFF) {
			unsigned int slot_val;
			unsigned char type_byte;
			void* field;
			int action_type;

			slot_val = (unsigned int) *(unsigned short*) ((char*) entity + 0x27);
			if ((int) &g_slot_table[slot_val * 540] != g_entity_table_end) {
				type_byte = *(unsigned char*) entity;
				if (g_action_table_base[(int) type_byte * 589] != 0x1d) {
					return -2;
				}

				field = *(void**) ((char*) entity + 0x65);
				if (field == 0) {
					return -3;
				}

				gm_ResolveEntityById((void**) 0, (void**) 0, (void**) &target_entity, *(int*) (param_1 + 4));
				if (target_entity == 0) {
					return -6;
				}

				action_type = *(int*) (param_1 + 0xc);
				if (action_type == 3) {
					if (*(int*) ((char*) field + 0x14) == 0) {
						goto fail;
					}
					if (*(int*) ((char*) field + 4) < 3) {
						goto fail;
					}
					*(unsigned char*) ((char*) field + 0x1b) = 1;
					*(unsigned char*) ((char*) field + 0x1a) = 1;
					*(unsigned char*) ((char*) field + 0x19) = 1;
					return 0;
				}
				if (action_type == 2) {
					if (*(int*) ((char*) field + 0x10) == 0) {
						goto fail;
					}
					if (*(int*) ((char*) field + 4) < 2) {
						goto fail;
					}
					*(unsigned char*) ((char*) field + 0x1a) = 1;
					*(unsigned char*) ((char*) field + 0x19) = 1;
					return 0;
				}
				if (action_type == 1) {
					if (*(int*) ((char*) field + 0xc) == 0) {
						goto fail;
					}
					*(unsigned char*) ((char*) field + 0x19) = 1;
					return 0;
				}
				return -8;

			fail:
				return -7;
			}
		}
	}
	return -1;
}


/* Updates production progress for active slots. Decrements
 * timers, checks for completion, and triggers product output
 * when the production cycle finishes. */

// FUNCTION: SERVER 0x10011790
// gv_UpdateProductionProgress


int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);

int __cdecl gv_UpdateProductionProgress(unsigned char* param_1)
{
	unsigned char* cmd_ptr_saved;
	int slot_active_result;
	int slot_entry_ptr;
	unsigned int new_progress_value;

	cmd_ptr_saved = param_1;
	gm_ResolveEntityById((void**) &param_1, (void**) 0, (void**) 0, *(int*) (param_1 + 8));
	if (((param_1 == (unsigned char*) 0) || (*(unsigned short*) (param_1 + 0x27) == 0xffff)) ||
		((char*) &DAT_100358a0 + (unsigned int) *(unsigned short*) (param_1 + 0x27) * 0x10e == (char*) DAT_1003546c)) {
		return -1;
	}
	if (*(char*) (DAT_100a8c30 + (unsigned int) *param_1 * 0x24d) != 0x1d) {
		return -2;
	}
	slot_entry_ptr = *(int*) (param_1 + 0x65);
	if (slot_entry_ptr == 0) {
		return -3;
	}
	slot_active_result = gv_CheckSlotActive((char*) slot_entry_ptr, *(int*) (cmd_ptr_saved + 0xc));
	if (slot_active_result == 0) {
		return -4;
	}
	slot_entry_ptr = gv_GetSlotEntry(slot_entry_ptr, *(int*) (cmd_ptr_saved + 0xc), cmd_ptr_saved[0x10]);
	if (slot_entry_ptr == 0) {
		return -7;
	}
	new_progress_value = *(int*) (cmd_ptr_saved + 0x13) + (unsigned int) *(unsigned char*) (slot_entry_ptr + 0xc);
	new_progress_value = new_progress_value & ((int) new_progress_value <= 0) - 1;
	if ((int) new_progress_value >= 0xff) {
		new_progress_value = 0xff;
	}
	*(char*) (slot_entry_ptr + 0xc) = (char) new_progress_value;
	return 0;
}

/* Validates that an entity action is permitted. Checks
 * entity state, slot availability, and production rules
 * before allowing the action to proceed. */

// FUNCTION: SERVER 0x10011890
// gv_ValidateEntityAction

int __cdecl gv_ValidateEntityAction(unsigned char* param_1)
{
	void* entity;
	unsigned int slot_val;
	unsigned char type_byte;
	int result;

	gm_ResolveEntityById((void**) &entity, (void**) 0, (void**) 0, *(int*) (param_1 + 8));
	if (entity != 0) {
		if (*(unsigned short*) ((char*) entity + 0x27) != 0xFFFF) {
			slot_val = (unsigned int) *(unsigned short*) ((char*) entity + 0x27);
			if ((int) &g_slot_table[slot_val * 540] != g_entity_table_end) {
				type_byte = *(unsigned char*) entity;
				if (g_action_table_base[(int) type_byte * 589] != 0x1d) {
					return -2;
				}
				if (*(int*) ((char*) entity + 0x65) == 0) {
					return -3;
				}
				result = SpawnGraveyardEntities(entity, *(int*) (param_1 + 0x13));
				if (result > 0) {
					return 0;
				}
				return -4;
			}
		}
	}
	return -1;
}

/* Moves a slot entry within a building's production table.
 * Relocates a product or worker from one slot position to
 * another, updating internal links. */

// FUNCTION: SERVER 0x10011940
// gv_MoveSlotEntry

unsigned int gv_MoveSlotEntry(int param_1)
{
	int* src_worker_array_ptr;
	int cmd_ptr_saved;
	int field_or_slot_ptr;
	unsigned char* building_entity_ptr;
	int src_worker_array_end;
	int dst_slot_entry_ptr;

	cmd_ptr_saved = param_1;
	gm_ResolveEntityById((void**) 0, (void**) 0, (void**) &param_1, *(int*) cmd_ptr_saved);
	if (param_1 == 0) {
		return 0xfffffffa;
	}
	gm_ResolveEntityById((void**) &building_entity_ptr, (void**) 0, (void**) 0, *(int*) (cmd_ptr_saved + 4));
	if (((building_entity_ptr == 0) || (*(unsigned short*) (building_entity_ptr + 0x27) == 0xffff)) ||
		(*(unsigned short*) (building_entity_ptr + 0x27) * 0x21c + *(unsigned int*) 0x100358a0 ==
		 *(unsigned int*) 0x1003546c)) {
		return 0xffffffff;
	}
	if (*(*(char**) 0x100a8c30 + *building_entity_ptr * 0x24d) != '\x1d') {
		return 0xfffffffe;
	}
	field_or_slot_ptr = *(int*) (building_entity_ptr + 0x65);
	if (field_or_slot_ptr == 0) {
		return 0xfffffffd;
	}
	field_or_slot_ptr = gv_CheckSlotActive((char*) field_or_slot_ptr, *(int*) (cmd_ptr_saved + 8));
	if (field_or_slot_ptr == 0) {
		return 0xfffffffc;
	}
	field_or_slot_ptr = gv_GetSlotEntry(
		*(int*) (building_entity_ptr + 0x65),
		*(int*) (cmd_ptr_saved + 8),
		(unsigned char) *(unsigned char*) (cmd_ptr_saved + 0xc)
	);
	if ((field_or_slot_ptr != 0) &&
		(*(unsigned short*) (field_or_slot_ptr + 8) == *(unsigned short*) (param_1 + 0x50))) {
		int saved_src_slot_entry_ptr;

		src_worker_array_ptr = *(int**) (field_or_slot_ptr + 0x10);
		src_worker_array_end = *(int*) (*(int*) (cmd_ptr_saved + 8) * 4 + 0x1002574c);
		saved_src_slot_entry_ptr = field_or_slot_ptr;
		dst_slot_entry_ptr = (int) gv_FindSlotEntryFiltered(
			(char*) param_1,
			(unsigned char*) building_entity_ptr,
			(char*) 0,
			(int(__cdecl*)(char*, char*)) 0x10010700,
			*(int*) (cmd_ptr_saved + 0xd)
		);
		if (dst_slot_entry_ptr != 0) {
			int* piVar5;
			int* piVar7;
			int* piVar8;
			int word_copy_count;
			piVar5 = *(int**) (dst_slot_entry_ptr + 0x10);
			piVar8 = piVar5 + *(int*) (*(int*) (cmd_ptr_saved + 0xd) * 4 + 0x1002574c) * 0x11;
			src_worker_array_end = (int) (src_worker_array_ptr + src_worker_array_end * 0x11);
			for (; piVar5 < piVar8; piVar5 = piVar5 + 0x11) {
				if (*piVar5 == -1) {
					while (1) {
						if ((int*) src_worker_array_end <= src_worker_array_ptr) {
							goto code_r0x10011b0d;
						}
						if (*src_worker_array_ptr != -1) {
							break;
						}
						src_worker_array_ptr = src_worker_array_ptr + 0x11;
					}
					{
						int* pSrc = src_worker_array_ptr;
						int* pDst = piVar5;
						for (word_copy_count = 0x11; word_copy_count != 0; word_copy_count = word_copy_count + -1) {
							*pDst = *pSrc;
							pSrc = pSrc + 1;
							pDst = pDst + 1;
						}
					}
					piVar7 = src_worker_array_ptr;
					for (word_copy_count = 0x11; word_copy_count != 0; word_copy_count = word_copy_count + -1) {
						*piVar7 = 0;
						piVar7 = piVar7 + 1;
					}
					*src_worker_array_ptr = -1;
					field_or_slot_ptr = saved_src_slot_entry_ptr;
					if ((int*) src_worker_array_end <= src_worker_array_ptr) {
						break;
					}
				}
			}
		code_r0x10011b0d:
			*(int*) (dst_slot_entry_ptr + 4) = *(int*) (field_or_slot_ptr + 4);
			*(int*) (field_or_slot_ptr + 4) = 0xffffffff;
			*(unsigned short*) (dst_slot_entry_ptr + 8) = *(unsigned short*) (field_or_slot_ptr + 8);
			*(unsigned short*) (field_or_slot_ptr + 8) = 0xffff;
			*(unsigned short*) (dst_slot_entry_ptr + 0xa) = (unsigned short) (*(unsigned short*) 0x10035880 + 0xa);
			*(unsigned char*) (dst_slot_entry_ptr + 0xc) = 0xff;
			*(unsigned short*) (field_or_slot_ptr + 0xa) = 0xff;
			*(int*) (cmd_ptr_saved + 0x15) = *(int*) 0x10030b6c;
			if (0 < *(int*) (cmd_ptr_saved + 0x11)) {
				unsigned int scaled_amount;
				gm_SubObjektNoKill(
					*(unsigned int*) (param_1 + 4),
					*(unsigned int*) ((unsigned char*) 0x100a8c94 + *(unsigned int*) 0x10035439 * 0x2f4),
					*(unsigned int*) (cmd_ptr_saved + 0x11)
				);
				scaled_amount = (unsigned int) ((int) *(int*) (cmd_ptr_saved + 0x11) *
												((float*) 0x1002572c)[*(int*) (cmd_ptr_saved + 0xd)]);
				gm_AddOrAccumulateObject(
					*(unsigned int*) ((unsigned char*) 0x100358a4 +
									  *(unsigned short*) (building_entity_ptr + 0x27) * 0x21c),
					*(unsigned int*) ((unsigned char*) 0x100a8c94 + *(unsigned int*) 0x10035439 * 0x2f4),
					scaled_amount
				);
			}
			return 0;
		}
	}
	return 0xfffffff9;
}

/* Allocates a graveyard worker entity. Creates the worker,
 * assigns to a building, and initializes work schedule. */

// FUNCTION: SERVER 0x10011bf0
// gv_ExAllocGraveyardWorker

unsigned int __cdecl gv_ExAllocGraveyardWorker(int param_1)
{
	unsigned short* new_entity_slot_ptr;
	unsigned short entity_slot_index;
	char rand_relationship_val;
	int entity_slot_byte_offset;
	int* matched_production_record;
	short* slot_scan_ptr;
	char* entity_type_scan_ptr;
	int* production_record_walker;
	int clear_loop_counter;
	int search_loop_idx;
	int slot_scan_idx_or_capacity;
	unsigned int* relationship_array_ptr;
	unsigned short* slot_clear_ptr;
	double random_float;
	int relationship_loop_idx;
	unsigned char* building_entity_ptr;
	int production_slot_entry_ptr;

	if (*(int*) (param_1 + 0x15) != 0x1b && *(int*) (param_1 + 0x15) != 0x1c) {
		return 0xfffffffa;
	}
	search_loop_idx = 0;
	gm_ResolveEntityById(&building_entity_ptr, 0, 0, *(unsigned int*) (param_1 + 8));
	if (building_entity_ptr == 0 || *(unsigned short*) (building_entity_ptr + 0x27) == 0xffff ||
		*(unsigned short*) (building_entity_ptr + 0x27) * 0x21c + (int) &DAT_100358a0 == DAT_1003546c) {
		return 0xffffffff;
	}
	if (*(char*) (DAT_100a8c30 + (unsigned int) *building_entity_ptr * 0x24d) != '\x1d') {
		return 0xfffffffe;
	}
	slot_scan_idx_or_capacity = *(int*) (building_entity_ptr + 0x65);
	if (slot_scan_idx_or_capacity == 0) {
		return 0xfffffffd;
	}
	entity_slot_byte_offset = gv_CheckSlotActive((char*) slot_scan_idx_or_capacity, *(int*) (param_1 + 0xc));
	if (entity_slot_byte_offset == 0) {
		return 0xfffffffc;
	}
	production_slot_entry_ptr =
		gv_GetSlotEntry(slot_scan_idx_or_capacity, *(int*) (param_1 + 0xc), *(unsigned char*) (param_1 + 0x10));
	if (production_slot_entry_ptr == 0) {
		return 0xffff;
	}
	entity_slot_byte_offset = 0;
	slot_scan_idx_or_capacity = *(int*) (*(int*) (param_1 + 0xc) * 4 + 0x1002574c);
	if (0 < slot_scan_idx_or_capacity) {
		production_record_walker = *(int**) (production_slot_entry_ptr + 0x10);
		do {
			matched_production_record = production_record_walker;
			if (*matched_production_record == *(int*) (param_1 + 0x11)) {
				break;
			}
			entity_slot_byte_offset = entity_slot_byte_offset + 1;
			production_record_walker = matched_production_record + 0x11;
		} while (entity_slot_byte_offset < slot_scan_idx_or_capacity);
		if (matched_production_record != 0 && *matched_production_record == *(int*) (param_1 + 0x11)) {
			slot_scan_idx_or_capacity = 0;
			slot_scan_ptr = (short*) &DAT_100358a0;
			do {
				if (*slot_scan_ptr == -1) {
					break;
				}
				slot_scan_ptr = slot_scan_ptr + 0x10e;
				slot_scan_idx_or_capacity = slot_scan_idx_or_capacity + 1;
			} while (slot_scan_ptr < (short*) 0x1009aca0);
			if (slot_scan_idx_or_capacity == 0x300) {
				slot_scan_idx_or_capacity = 0;
				entity_type_scan_ptr = (char*) 0x100358a2;
				do {
					if (*entity_type_scan_ptr == '\x0f') {
						break;
					}
					entity_type_scan_ptr = entity_type_scan_ptr + 0x21c;
					slot_scan_idx_or_capacity = slot_scan_idx_or_capacity + 1;
				} while (entity_type_scan_ptr < (char*) 0x1009aca2);
				if (slot_scan_idx_or_capacity == 0x300) {
					LogMessageInternal(
						"D:\\Develop\\DieGildeAddOn\\game\\friedhof_logic.c",
						0x6ef,
						"gv_ExAllocGraveyardWorker: array overflow...",
						1
					);
					return 0xffff;
				}
			}
			entity_slot_byte_offset = slot_scan_idx_or_capacity * 0x21c;
			if (*(char*) (entity_slot_byte_offset + 0x100358a2) == '\x0f') {
				DAT_10035434 = DAT_10035434 - 1;
			}
			new_entity_slot_ptr = (unsigned short*) (entity_slot_byte_offset + (int) &DAT_100358a0);
			slot_clear_ptr = new_entity_slot_ptr;
			for (clear_loop_counter = 0x87; clear_loop_counter != 0; clear_loop_counter = clear_loop_counter - 1) {
				slot_clear_ptr[0] = 0;
				slot_clear_ptr[1] = 0;
				slot_clear_ptr = slot_clear_ptr + 2;
			}
			*new_entity_slot_ptr = 0xffff;
			*(int*) (entity_slot_byte_offset + 0x100358a4) = (int) 0xffffffff;
			relationship_array_ptr = (unsigned int*) (entity_slot_byte_offset + 0x100358fc);
			for (clear_loop_counter = 8; clear_loop_counter != 0; clear_loop_counter = clear_loop_counter - 1) {
				*relationship_array_ptr = 0xffffffff;
				relationship_array_ptr = relationship_array_ptr + 1;
			}
			*(unsigned char**) (entity_slot_byte_offset + 0x10035a10) = building_entity_ptr;
			*(unsigned char**) (entity_slot_byte_offset + 0x10035a0c) = building_entity_ptr;
			DAT_10035434 = DAT_10035434 + 1;
			*(int*) (entity_slot_byte_offset + 0x100358a4) = DAT_10030b6c;
			DAT_10030b6c = DAT_10030b6c + 1;
			*new_entity_slot_ptr = (unsigned short) slot_scan_idx_or_capacity;
			*(char*) (entity_slot_byte_offset + 0x100358a2) = 0x14;
			*(int*) (entity_slot_byte_offset + 0x10035a90) = 0;
			*(int*) (entity_slot_byte_offset + 0x10035ab0) = (int) 0xffffffff;
			*(char*) (entity_slot_byte_offset + 0x10035ab5) = 0;
			*(char*) (entity_slot_byte_offset + 0x10035ab6) = 0;
			*(char*) (entity_slot_byte_offset + 0x10035ab7) = 0;
			*(char*) (entity_slot_byte_offset + 0x10035ab8) = 1;
			*(int*) (entity_slot_byte_offset + 0x10035a84) = 0x3f800000;
			*(short*) (entity_slot_byte_offset + 0x100358a8) = 100;
			*(short*) (entity_slot_byte_offset + 0x100358aa) = 0x10;
			*(char*) (entity_slot_byte_offset + 0x10035a04) = 0;
			*(char*) (entity_slot_byte_offset + 0x10035a06) = 0;
			*(char*) (entity_slot_byte_offset + 0x10035a05) = *(char*) (param_1 + 0x15);
			*(int*) (entity_slot_byte_offset + 0x10035a94) = 0;
			*(int*) (entity_slot_byte_offset + 0x10035a30) = 4;
			*(int*) (entity_slot_byte_offset + 0x10035a34) = 0;
			*(char*) (entity_slot_byte_offset + 0x100358ad) = 1;
			*(int*) (entity_slot_byte_offset + 0x10035a2c) = (int) 0xffffffff;
			*(int*) (entity_slot_byte_offset + 0x10035aac) = (int) 0xffffffff;
			*(short*) (entity_slot_byte_offset + 0x100358f0) = 0x7fff;
			slot_scan_idx_or_capacity = 0;
			do {
				*(char*) (slot_scan_idx_or_capacity + 0x80 + (int) new_entity_slot_ptr) =
					*((char*) matched_production_record + slot_scan_idx_or_capacity + 0x24) >> 1;
				slot_scan_idx_or_capacity = slot_scan_idx_or_capacity + 1;
			} while (slot_scan_idx_or_capacity < 5);
			*(char*) (entity_slot_byte_offset + 0x100358a9) = *((char*) matched_production_record + 0x38);
			strcpy((char*) (entity_slot_byte_offset + 0x100358d0), (char*) matched_production_record + 4);
			strcpy((char*) (entity_slot_byte_offset + 0x100358e0), (char*) matched_production_record + 0x14);
			*(int*) (entity_slot_byte_offset + 0x100358b0) = 0;
			random_float = gm_RandomFloat01();
			*(int*) (entity_slot_byte_offset + 0x100358b8) = 0;
			*(int*) (entity_slot_byte_offset + 0x100358bc) = 0x447a0000;
			*(int*) (entity_slot_byte_offset + 0x100358c0) = 0;
			*(int*) (entity_slot_byte_offset + 0x100358c4) = 0;
			*(int*) (entity_slot_byte_offset + 0x100358c8) = 0;
			*(int*) (entity_slot_byte_offset + 0x100358cc) = 0;
			relationship_loop_idx = 0;
			slot_scan_idx_or_capacity = 0;
			*(float*) (entity_slot_byte_offset + 0x100358b4) =
				DAT_10025680 / (float) (random_float * (double) DAT_100257c8 + (double) DAT_100257c4);
			do {
				entity_slot_index = *new_entity_slot_ptr;
				rand_relationship_val = (char) gm_RandomMod(0x40);
				*(char*) (entity_slot_index + slot_scan_idx_or_capacity + 0x1014d8e0) = 0;
				*(char*) (entity_slot_index + slot_scan_idx_or_capacity + 0x100a9820) = rand_relationship_val - 0x20;
				entity_slot_byte_offset = *new_entity_slot_ptr * 0x300 + relationship_loop_idx;
				rand_relationship_val = (char) gm_RandomMod(0x40);
				slot_scan_idx_or_capacity = slot_scan_idx_or_capacity + 0x300;
				relationship_loop_idx = relationship_loop_idx + 1;
				*(char*) (entity_slot_byte_offset + 0x100a9820) = rand_relationship_val - 0x20;
				*(char*) (entity_slot_byte_offset + 0x1014d8e0) = 0;
			} while (slot_scan_idx_or_capacity < 0x90000);
			if (*matched_production_record == *(int*) (production_slot_entry_ptr + 4)) {
				slot_scan_idx_or_capacity = *(int*) (*(int*) (param_1 + 0xc) * 4 + 0x1002574c);
				if (0 < slot_scan_idx_or_capacity) {
					search_loop_idx = 0;
					production_record_walker = *(int**) (production_slot_entry_ptr + 0x10);
					do {
						if (*production_record_walker != -1 &&
							*production_record_walker != *matched_production_record) {
							*(int*) (production_slot_entry_ptr + 4) = *production_record_walker;
							goto code_r0x10011fcd;
						}
						search_loop_idx = search_loop_idx + 1;
						production_record_walker = production_record_walker + 0x11;
					} while (search_loop_idx < slot_scan_idx_or_capacity);
				}
				*(int*) (production_slot_entry_ptr + 4) = (int) 0xffffffff;
				*(short*) (production_slot_entry_ptr + 8) = (short) 0xffff;
			}
		code_r0x10011fcd:
			production_record_walker = matched_production_record;
			for (search_loop_idx = 0x11; search_loop_idx != 0; search_loop_idx = search_loop_idx - 1) {
				*production_record_walker = 0;
				production_record_walker = production_record_walker + 1;
			}
			*matched_production_record = -1;
			return (unsigned int) *new_entity_slot_ptr;
		}
	}
	return 0xffff;
}
