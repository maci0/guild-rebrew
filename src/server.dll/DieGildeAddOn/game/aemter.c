#include <stdio.h>

typedef struct {
	int value;
	char type;
	char pad[19];
} ENT;

#pragma pack(push, 1)
typedef struct {
	char key;
	char pad[3];
	int entityId;
	char field8;
	char rest[15];
} SlotEntry;
#pragma pack(pop)

extern SlotEntry DAT_101de5a0[];
extern int DAT_101de5a4;
extern char DAT_101de5a8;
extern int DAT_101de5ac;
extern char DAT_101de5b0;
extern void* __cdecl LookupEntityRecordById(int);
extern int DAT_101de5b4[];
extern ENT g_ents[];
extern ENT g_ents2[];
extern unsigned short DAT_10035884;
extern void __cdecl LogMessageInternal(char* file, unsigned int line, char* msg, int level);
extern int __cdecl ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, int streamCtx);
extern void __cdecl InitBuildingTypeTable(void);

// STATUS: MATCHING
// BLOCKER: comparison direction swap, jump condition swap, zero-extend pattern (xor vs mov)
// ORIGIN: GAME
// SIZE: 205
// SYMBOL: _LookupEntityRecordById
// BLOCKER_DELTA: 196
// FUNCTION: SERVER 0x1000b1c0
// ValidateOfficeCandidate
// PROTOTYPE: int __cdecl ValidateOfficeCandidate(int * param_1)

void* __cdecl LookupEntityRecordById(int entityId);

int __cdecl ValidateOfficeCandidate(int* param_1)
{
	void* entity_rec;
	char* slot_ptr;
	int slot_index;
	int dep_slot_index;

	entity_rec = LookupEntityRecordById(*param_1);
	if ((entity_rec != (void*) 0) && (*(char*) ((int) entity_rec + 0x168) == '\0')) {
		slot_index = 0;
		slot_ptr = (char*)&DAT_101de5a0;
		do {
			if (*slot_ptr == (char) param_1[1]) {
				if (0x1d < slot_index) {
					return 0;
				}
				if ((&DAT_101de5a4)[slot_index * 6] != -1) {
					return 0;
				}
				if ((&DAT_101de5b0)[slot_index * 0x18] != '\x03') {
					return 0;
				}
				if (3 < (int) (&DAT_101de5ac)[slot_index * 6]) {
					return 0;
				}
				if (*(char*) ((int) param_1 + 6) != (&DAT_101de5a8)[slot_index * 0x18]) {
					return 0;
				}
				if (*(char*) ((int) param_1 + 5) != -1) {
					dep_slot_index = 0;
					slot_ptr = (char*)&DAT_101de5a0;
					while (*slot_ptr != *(char*) ((int) param_1 + 5)) {
						slot_ptr = slot_ptr + 0x18;
						dep_slot_index = dep_slot_index + 1;
						if (0x101de86f < (int) slot_ptr) {
							return 0;
						}
					}
					if (0x1d < dep_slot_index) {
						return 0;
					}
					if ((&DAT_101de5a8)[slot_index * 0x18] != (&DAT_101de5a8)[dep_slot_index * 0x18]) {
						return 0;
					}
					if ((&DAT_101de5a4)[dep_slot_index * 6] != -1) {
						return 0;
					}
					if ((&DAT_101de5b0)[dep_slot_index * 0x18] != '\x03') {
						return 0;
					}
					if (3 < (int) (&DAT_101de5ac)[dep_slot_index * 6]) {
						return 0;
					}
				}
				return 1;
			}
			slot_ptr = slot_ptr + 0x18;
			slot_index = slot_index + 1;
		} while ((int) slot_ptr < 0x101de870);
	}
	return 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, instruction folding (lea vs mov), jump condition swap, zero-extend pattern (xor vs mov)
// SIZE: 425
// SYMBOL: _LookupEntityRecordById
// FUNCTION: SERVER 0x1000b290
// ValidateAndAssignOffice

/* Auto-generated Ghidra decompilation */
// BLOCKER_DELTA: 400
// PROTOTYPE: uint __stdcall ValidateAndAssignOffice(uint * param_1)

unsigned int ValidateAndAssignOffice(unsigned int* param_1)
{
	unsigned char requested_role;
	unsigned char slot_role;
	short* entity_rec;
	char* slot_ptr;
	int copy_count;
	int slot_index;
	int dep_slot_offset;
	unsigned int* role_def_src;
	unsigned int* role_def_dst;
	unsigned int role_def_buf[4];
	int dep_slot_status = 0;

	entity_rec = LookupEntityRecordById(*param_1);
	if (((entity_rec != 0) && (*entity_rec != -1)) && (*(char*) (entity_rec + 0xb4) == '\0')) {
		slot_index = 0;
		slot_ptr = (char*) 0x101de5a0;
		do {
			if (*slot_ptr == *(char*) (param_1 + 1)) {
				if (0x1d < slot_index) {
					return 0;
				}
				requested_role = *(unsigned char*) (param_1 + 6);
				slot_index = slot_index * 0x18;
				slot_role = *(unsigned char*) (slot_index + 0x101de5a8);
				if (requested_role != slot_role) {
					return 0;
				}
				if (*(int*) (param_1 + 5) == -1) {
					if (*(int*) (slot_index + 0x101de5a4) != -1) {
						return 0;
					}
					if (*(char*) (slot_index + 0x101de5b0) != '\x03') {
						return 0;
					}
					if (3 < *(int*) (slot_index + 0x101de5ac)) {
						return 0;
					}
					*(unsigned char*) (entity_rec + 0xb4) = requested_role;
					*(int*) (slot_index + 0x101de5ac) = *(int*) (slot_index + 0x101de5ac) + 1;
					return 1;
				}
				dep_slot_offset = 0;
				slot_ptr = (char*) 0x101de5a0;
				while (*slot_ptr != *(char*) (param_1 + 5)) {
					slot_ptr = slot_ptr + 0x18;
					dep_slot_offset = dep_slot_offset + 1;
					if ((char*) 0x101de86f < slot_ptr) {
						return 0;
					}
				}
				if (0x1d < dep_slot_offset) {
					return 0;
				}
				dep_slot_offset = dep_slot_offset * 0x18;
				if (slot_role != *(unsigned char*) (dep_slot_offset + 0x101de5a8)) {
					return 0;
				}
				role_def_src = (unsigned int*) (slot_role * 0x18 + 0x10029bb8);
				role_def_dst = role_def_buf;
				for (copy_count = 6; copy_count != 0; copy_count = copy_count + -1) {
					*role_def_dst = *role_def_src;
					role_def_src = role_def_src + 1;
					role_def_dst = role_def_dst + 1;
				}
				if (role_def_buf[0] != requested_role) {
					return 0;
				}
				if (dep_slot_status == 0) {
					return 0;
				}
				if (*(int*) (slot_index + 0x101de5a4) != -1) {
					return 0;
				}
				if (*(char*) (slot_index + 0x101de5b0) != '\x03') {
					return 0;
				}
				if (3 < *(int*) (slot_index + 0x101de5ac)) {
					return 0;
				}
				if (*(int*) (dep_slot_offset + 0x101de5a4) != -1) {
					return 0;
				}
				if (3 < *(int*) (dep_slot_offset + 0x101de5ac)) {
					return 0;
				}
				*(unsigned char*) (entity_rec + 0xb4) = requested_role;
				*(int*) (slot_index + 0x101de5ac) = *(int*) (slot_index + 0x101de5ac) + 1;
				*(int*) (dep_slot_offset + 0x101de5ac) = *(int*) (dep_slot_offset + 0x101de5ac) + 1;
				return 1;
			}
			slot_ptr = slot_ptr + 0x18;
			slot_index = slot_index + 1;
		} while (slot_ptr < (char*) 0x101de870);
	}
	return 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 133
// SYMBOL: _LookupEntityRecordById
// FUNCTION: SERVER 0x1000b440
// ValidateCommand
// PROTOTYPE: int __cdecl ValidateCommand(char * param_1)

int __cdecl ValidateCommand(char* param_1)
{
	char* slot_ptr;
	void* entity_rec;
	int slot_index;

	if (param_1[6] != -1) {
		slot_index = 0;
		slot_ptr = (char*) DAT_101de5a0;
		while (*slot_ptr != *param_1) {
			slot_ptr = slot_ptr + 0x18;
			slot_index = slot_index + 1;
			if ((int) slot_ptr >= (int) 0x101de990) {
				return 0;
			}
		}
		if (slot_index >= 0x2a) {
			return 0;
		}
		if ((&DAT_101de5b0)[slot_index * 0x18] != 1) {
			return 0;
		}
		if (DAT_101de5b4[slot_index * 6] != -1) {
			return 0;
		}
		if (*(int*) (param_1 + 7) != -1) {
			entity_rec = LookupEntityRecordById(*(int*) (param_1 + 7));
			if (entity_rec == (void*) 0) {
				return 0;
			}
		}
		if (*(int*) (param_1 + 1) != -1) {
			entity_rec = LookupEntityRecordById(*(int*) (param_1 + 1));
			if (entity_rec == (void*) 0) {
				return 0;
			}
		}
	}
	return 1;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: jump condition swap
// BLOCKER_DELTA: 119
// ANALYSIS: Iterates through a fixed validation table at g_office_table looking for a matching command_type. Once found, verifies conditions including checking if entity_ids in the payload actually map to existing objects using LookupEntityRecordById. Returns 1 if valid, 0 if invalid.
// BLOCKER: comparison direction swap, instruction folding (lea vs mov), jump condition swap, loop rotation / branch layout, stack frame choice (push vs sub esp), zero-extend pattern (xor vs mov)
// SIZE: 836
// SYMBOL: _LookupEntityRecordById
// FUNCTION: SERVER 0x1000b4d0
// ExecuteOfficeAssignment

/* Game function - entity role/assignment table manager */
/* Updates a 0x18-byte record table at 0x101de5a0, clears old roles, sets new assignments */
// BLOCKER_DELTA: 800
// PROTOTYPE: int __stdcall ExecuteOfficeAssignment(char * param_1)

int __cdecl ExecuteOfficeAssignment(char* param_1)
{
	int iStack;
	int ent;
	int record_index;
	int old_owner;
	int record_off;

	iStack = -1;

	/* Validate associated entity if present */
	if (*(int*) (param_1 + 7) != -1) {
		if (LookupEntityRecordById(*(int*) (param_1 + 7)) == 0) {
			return 0;
		}
	}

	/* Get owner entity */
	ent = 0;
	if (*(int*) (param_1 + 1) != -1) {
		ent = (int)LookupEntityRecordById(*(int*) (param_1 + 1));
		if (ent == 0) {
			return 0;
		}
		iStack = *(int*) (ent + 4);
	}

	/* Search table for matching type byte */
	{
		char type;
		record_index = 0;
		type = *param_1;

		{
			char* ptr;
			ptr = (char*) 0x101de5a0;
			while (*ptr != type) {
				ptr += 0x18;
				record_index++;
				if (ptr >= (char*) 0x101de990) {
					return 0;
				}
			}
		}
	}

	if (record_index >= 0x2a) {
		return 0;
	}

	record_off = record_index * 0x18;

	/* Lookup existing owner and clear old role references */
	old_owner = (int)LookupEntityRecordById(*(int*) (record_off + 0x101de5a4));
	if (old_owner != 0 && *(int*) (old_owner + 4) != *(int*) (param_1 + 1)) {
		char role;
		role = *(char*) (record_off + 0x101de5a8);

		if (*(char*) (old_owner + 0x166) == role) {
			*(char*) (old_owner + 0x166) = 0;
		}
		else if (*(char*) (old_owner + 0x169) == role) {
			*(char*) (old_owner + 0x169) = 0;
		}
		else {
			int flags;
			if (role == 0x23) {
				flags = *(int*) (old_owner + 0x1cc);
				flags &= 0xfffffdff;
			}
			else if (role == 0x24) {
				flags = *(int*) (old_owner + 0x1cc);
				flags &= 0xfffffbff;
			}
			else if (role == 0x25) {
				flags = *(int*) (old_owner + 0x1cc);
				flags &= 0xfffff7ff;
			}
			else {
				goto after_old_clear;
			}
			*(int*) (old_owner + 0x1cc) = flags;
		}
	}

after_old_clear:
	if (ent == 0) {
		goto final_store;
	}

	{
		unsigned char role_byte;
		role_byte = *(unsigned char*) (record_off + 0x101de5a8);

		if (role_byte <= 0x1b) {
			/* Small role path */
			if (*(char*) (ent + 0x166) != 0) {
				/* Search for existing assignment with same owner */
				int j;
				int* scan;
				j = 0;
				scan = (int*) 0x101de5a4;

				while (*scan != iStack) {
					scan = (int*) ((char*) scan + 0x18);
					j++;
					if (scan >= (int*) 0x101de874) {
						goto skip_clear;
					}
				}

				{
					int off;
					off = j * 0x18;
					*(int*) (off + 0x101de5a4) = -1;
					*(int*) (off + 0x101de5b4) = -1;
					*(char*) (off + 0x101de5b0) = 4;
					*(int*) (off + 0x101de5ac) = 0;
				}
			}

		skip_clear:
			/* Compare role priorities */
			{
				unsigned char new_role;
				unsigned char old_role;
				new_role = *(unsigned char*) (record_off + 0x101de5a8);
				old_role = *(unsigned char*) (ent + 0x166);

				if (*(unsigned char*) ((unsigned int) new_role * 0x18 + 0x10029bc0) >=
					*(unsigned char*) ((unsigned int) old_role * 0x18 + 0x10029bc0)) {
					*(char*) (ent + 0x167) = (char) new_role;
				}
			}

			{
				char new_role;
				new_role = *(char*) (record_off + 0x101de5a8);
				if (*(char*) (ent + 0x168) == new_role) {
					*(char*) (ent + 0x168) = 0;
				}
				*(char*) (ent + 0x166) = new_role;
			}

			/* Set flags based on role */
			{
				unsigned char role_val;
				role_val = *(unsigned char*) (record_off + 0x101de5a8);

				if (role_val == 0x0f) {
					*(int*) (ent + 0x1cc) = *(int*) (ent + 0x1cc) | 0x40;
				}
				else if (role_val == 0x15) {
					*(int*) (ent + 0x1cc) = *(int*) (ent + 0x1cc) | 0x80;
				}
				else if (role_val == 0x1b) {
					*(int*) (ent + 0x1cc) = *(int*) (ent + 0x1cc) | 0x100;
				}
			}

			/* Check role's count property */
			{
				unsigned char role_val;
				role_val = *(unsigned char*) (record_off + 0x101de5a8);

				if (*(int*) ((unsigned int) role_val * 0x18 + 0x10029bc8) != 0) {
					int k;
					unsigned char* scan;
					k = 0;
					scan = (unsigned char*) 0x101de5a8;

					while (1) {
						if (*scan == role_val && k != record_index) {
							int off;
							off = k * 0x18;

							if (*(char*) (off + 0x101de5b0) == 3) {
								int cnt;
								cnt = *(int*) (off + 0x101de5ac);
								if (cnt != 0) {
									cnt--;
									*(int*) (off + 0x101de5ac) = cnt;
									if (cnt == 0) {
										*(char*) (off + 0x101de5b0) = 4;
									}
								}
							}
							break;
						}
						scan += 0x18;
						k++;
						if (scan >= (unsigned char*) 0x101de878) {
							break;
						}
					}
				}
			}

			goto final_store;
		}

		if (role_byte >= 0x1c && role_byte <= 0x22) {
			/* Medium role path (0x1c-0x22) */
			if (*(char*) (ent + 0x169) != 0) {
				int* scan;
				scan = (int*) 0x101de874;
				do {
					if (*(char*) ((char*) scan + 4) == *(char*) (ent + 0x169) && *scan == *(int*) (ent + 4)) {
						*scan = -1;
					}
					scan = (int*) ((char*) scan + 0x18);
				} while (scan < (int*) 0x101de91c);
			}

			*(char*) (ent + 0x169) = *(char*) (record_off + 0x101de5a8);
			goto final_store;
		}

		/* High role path (> 0x22) */
		{
			int flags;
			unsigned int mask;

			mask = 0;
			flags = *(int*) (ent + 0x1cc);
			flags &= 0xfffff1ff;
			*(int*) (ent + 0x1cc) = flags;

			{
				char role_ch;
				role_ch = *(char*) (record_off + 0x101de5a8);

				if (role_ch == 0x23) {
					mask = 0x4000;
					*(int*) (ent + 0x1cc) = flags | 0x200;
				}
				else if (role_ch == 0x24) {
					mask = 0x8000;
					*(int*) (ent + 0x1cc) = flags | 0x400;
				}
				else if (role_ch == 0x25) {
					mask = 0x10000;
					*(int*) (ent + 0x1cc) = flags | 0x800;
				}
			}

			{
				unsigned int* scan;
				unsigned int neg_mask;
				neg_mask = ~mask;
				scan = (unsigned int*) 0x10035a6c;
				do {
					*scan = *scan & neg_mask;
					scan = (unsigned int*) ((char*) scan + 0x21c);
				} while (scan < (unsigned int*) 0x1009ae6c);
			}
		}
	}

final_store:
	*(int*) (record_off + 0x101de5a4) = iStack;
	*(int*) (record_off + 0x101de5b4) = *(int*) (param_1 + 7);
	*(char*) (record_off + 0x101de5b0) = param_1[5];
	if (param_1[5] == 3) {
		*(int*) (record_off + 0x101de5ac) = 0;
	}

	return 1;
}

// ORIGIN: GAME
// STATUS: RELOC
// SIZE: 42
// SYMBOL: _LookupEntityRecordById
// FUNCTION: SERVER 0x1000B820
// find_entity_26
// PROTOTYPE: void __cdecl find_entity_26(int val)

void __cdecl find_entity_26(int val)
{
	unsigned int i;
	for (i = 0x29; i != 0; i--) {
		if (g_ents[i].type == 0x26) {
			g_ents[i].value = val;
			return;
		}
	}
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 42
// SYMBOL: _LookupEntityRecordById
// FUNCTION: SERVER 0x1000B850
// find_entity_27
// PROTOTYPE: void __cdecl find_entity_27(int val)

void __cdecl find_entity_27(int val)
{
	unsigned int i;
	for (i = 0x29; i != 0; i--) {
		if (g_ents2[i].type == 0x27) {
			g_ents2[i].value = val;
			return;
		}
	}
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, instruction folding (lea vs mov), jump condition swap
// SIZE: 263
// SYMBOL: _LookupEntityRecordById
// BLOCKER_DELTA: 205
// FUNCTION: SERVER 0x1000b880
// SwapOfficeHolders
// PROTOTYPE: int __cdecl SwapOfficeHolders(int * param_1)

int __cdecl SwapOfficeHolders(int* param_1)
{
	int saved_entity_id;
	void* requester_rec;
	SlotEntry* slot_scan;
	void* entity_rec_a;
	void* entity_rec_b;
	int slot_index_a;
	int slot_index_b;

	requester_rec = LookupEntityRecordById(*param_1);
	if (requester_rec == (void*) 0) {
		return 0;
	}
	if (*(int*) ((int) requester_rec + 0x194) < *(int*) ((int) param_1 + 6)) {
		return 0;
	}
	slot_index_a = 0;
	slot_scan = DAT_101de5a0;
	while (slot_scan->key != (char) param_1[1]) {
		slot_scan = slot_scan + 1;
		slot_index_a = slot_index_a + 1;
		if ((int) slot_scan > 0x101de86f) {
			return 0;
		}
	}
	if (slot_scan == (SlotEntry*) 0) {
		return 0;
	}
	entity_rec_a = LookupEntityRecordById(DAT_101de5a0[slot_index_a].entityId);
	if (entity_rec_a == (void*) 0) {
		return 0;
	}
	slot_index_b = 0;
	slot_scan = DAT_101de5a0;
	while (slot_scan->key != *(char*) ((int) param_1 + 5)) {
		slot_scan = slot_scan + 1;
		slot_index_b = slot_index_b + 1;
		if ((int) slot_scan > 0x101de86f) {
			return 0;
		}
	}
	if (slot_scan == (SlotEntry*) 0) {
		return 0;
	}
	entity_rec_b = LookupEntityRecordById(DAT_101de5a0[slot_index_b].entityId);
	if (entity_rec_b == (void*) 0) {
		return 0;
	}
	*(char*) ((int) entity_rec_a + 0x166) = DAT_101de5a0[slot_index_b].field8;
	*(char*) ((int) entity_rec_b + 0x166) = DAT_101de5a0[slot_index_a].field8;
	saved_entity_id = DAT_101de5a0[slot_index_a].entityId;
	DAT_101de5a0[slot_index_a].entityId = DAT_101de5a0[slot_index_b].entityId;
	DAT_101de5a0[slot_index_b].entityId = saved_entity_id;
	*(int*) ((int) requester_rec + 0x194) = *(int*) ((int) requester_rec + 0x194) - *(int*) ((int) param_1 + 6);
	return 1;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, zero-extend pattern (xor vs mov)
// SIZE: 157
// SYMBOL: _LookupEntityRecordById
// BLOCKER_DELTA: 146
// FUNCTION: SERVER 0x1000b990
// ClearEntityLinks
// PROTOTYPE: int __stdcall ClearEntityLinks(int param_1)

int __cdecl ClearEntityLinks(int param_1)
{
	int result;
	int* p;

	result = 0;
	p = (int*) 0x101de5b4;
	do {
		if (p[-4] == *(int*) (param_1 + 4)) {
			p[-4] = -1;
			*p = -1;
			*(char*) (p + -1) = (char) ((DAT_10035884 > 0xb) + 3);
			p[-2] = 0;
			result = 1;
		}
		else if (*p == *(int*) (param_1 + 4)) {
			*p = -1;
			*(char*) (p + -1) = 1;
		}
		p = p + 6;
	} while ((int) p < 0x101de9a4);
	if (*(char*) (param_1 + 0x168) != 0) {
		p = (int*) 0x101de5ac;
		do {
			if ((char) p[-1] == *(char*) (param_1 + 0x168) && *p > 0) {
				result = 1;
				*p = *p - 1;
			}
			p = p + 6;
		} while ((int) p < 0x101de99c);
	}
	*(char*) (param_1 + 0x166) = 0;
	*(char*) (param_1 + 0x169) = 0;
	*(char*) (param_1 + 0x168) = 0;
	return result;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 179
// SYMBOL: _LookupEntityRecordById
// BLOCKER_DELTA: 178
// ANALYSIS: Iterates through the command execution tracker table at g_office_secondary_id_base to detach or update a specific entity's links and pending sequence numbers. Used when an entity changes state abruptly or is being removed.
// FUNCTION: SERVER 0x1000ba30
// UpdateEntityLinks
// PROTOTYPE: void __cdecl UpdateEntityLinks(int param_1, int param_2)

void __cdecl UpdateEntityLinks(int param_1, int param_2)
{
	unsigned short player_count;
	int* slot_scan;

	player_count = DAT_10035884;
	slot_scan = (int*) 0x101de5b4;
	do {
		if (slot_scan[-4] == *(int*) (param_1 + 4) && param_2 != 0) {
			slot_scan[-4] = -1;
			*slot_scan = -1;
			*(char*) (slot_scan + -1) = (char) ((player_count > 0xb) + 3);
			slot_scan[-2] = 0;
		}
		else if (*slot_scan == *(int*) (param_1 + 4)) {
			*slot_scan = -1;
			*(char*) (slot_scan + -1) = 1;
		}
		slot_scan = slot_scan + 6;
	} while ((int) slot_scan < 0x101de9a4);
	if (*(char*) (param_1 + 0x168) != '\0') {
		slot_scan = (int*) 0x101de5ac;
		do {
			if ((char) slot_scan[-1] == *(char*) (param_1 + 0x168) && *slot_scan > 0) {
				*slot_scan = *slot_scan - 1;
			}
			slot_scan = slot_scan + 6;
		} while ((int) slot_scan < 0x101de99c);
	}
	if (param_2 != 0) {
		*(char*) (param_1 + 0x166) = 0;
		*(char*) (param_1 + 0x169) = 0;
	}
	*(char*) (param_1 + 0x168) = 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: instruction folding (lea vs mov)
// SIZE: 606
// SYMBOL: _LookupEntityRecordById
// BLOCKER_DELTA: 407
// GHIDRA: LoadOfficeData
// FUNCTION: SERVER 0x1000baf0
// amt_fio_LoadAemter

/* GLOBAL: SERVER 0x101de5a4 */
extern char g_aemter_table[];

unsigned int __cdecl amt_fio_LoadAemter(int param_1, int param_2)
{
	unsigned int num_entries;
	unsigned int i;
	char* ptr;
	unsigned int stored_count;
	char buf[256];

	num_entries = (((unsigned int) (param_2 < 0x10051) - 1) & 5) + 0x25;

	InitBuildingTypeTable();

	if (param_1 == 0) {
		return 0;
	}

	if (ReadVfsDataChecked(&stored_count, 4, 1, param_1) == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\game\\aemter.c",
			0xe73,
			"amt_fio_LoadAemter(): Can\'t load count",
			1
		);
		return 0;
	}

	if (stored_count != num_entries) {
		sprintf(buf, "amt_fio_LoadAemter(): wrong count %d (expected %d)", stored_count, 0x2a);
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe7c, buf, 1);
		return 0;
	}

	i = 0;
	if (num_entries > 0) {
		ptr = g_aemter_table;
		do {
			if (ReadVfsDataChecked(ptr - 4, 1, 1, param_1) == 0) {
				goto err_id;
			}
			if (ReadVfsDataChecked(ptr, 4, 1, param_1) == 0) {
				goto err_playerid;
			}
			if (ReadVfsDataChecked(ptr + 4, 1, 1, param_1) == 0) {
				goto err_amt;
			}
			if (ReadVfsDataChecked(ptr + 8, 4, 1, param_1) == 0) {
				goto err_pcount;
			}
			if (ReadVfsDataChecked(ptr + 0xc, 1, 1, param_1) == 0) {
				goto err_status;
			}
			if (ReadVfsDataChecked(ptr + 0x10, 4, 1, param_1) == 0) {
				goto err_last;
			}
			i++;
			ptr += 0x18;
		} while (i < num_entries);
	}

	return 1;

err_id:
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe82, "amt_fio_LoadAemter(): Can\'t load id", 1);
	return 0;
err_playerid:
	LogMessageInternal(
		"D:\\Develop\\DieGildeAddOn\\game\\aemter.c",
		0xe83,
		"amt_fio_LoadAemter(): Can\'t load mplayerid",
		1
	);
	return 0;
err_amt:
	LogMessageInternal(
		"D:\\Develop\\DieGildeAddOn\\game\\aemter.c",
		0xe84,
		"amt_fio_LoadAemter(): Can\'t load mamt",
		1
	);
	return 0;
err_pcount:
	LogMessageInternal(
		"D:\\Develop\\DieGildeAddOn\\game\\aemter.c",
		0xe85,
		"amt_fio_LoadAemter(): Can\'t load pcount",
		1
	);
	return 0;
err_status:
	LogMessageInternal(
		"D:\\Develop\\DieGildeAddOn\\game\\aemter.c",
		0xe86,
		"amt_fio_LoadAemter(): Can\'t load status",
		1
	);
	return 0;
err_last:
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe87, "amt_fio_LoadAemter(): Can\'t load ???", 1);
	return 0;
}
