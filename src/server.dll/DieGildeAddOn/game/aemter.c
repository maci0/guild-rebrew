#include <stdio.h>

typedef struct {

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

	int value;
	char type;
	char pad[19];
} ENT;

#pragma pack(push, 1)
	char key;
	char pad[3];
	int entityId;
	char field8;
	char rest[15];
} SlotEntry;
#pragma pack(pop)

// STATUS: MATCHING
// BLOCKER: comparison direction swap, jump condition swap, zero-extend pattern (xor vs mov)
// ORIGIN: GAME
// SIZE: 205
// SYMBOL: _ValidateOfficeCandidate
// BLOCKER_DELTA: 196
// FUNCTION: SERVER 0x1000b1c0
// ValidateOfficeCandidate

void* __cdecl LookupEntityRecordById(int entityId);

int __cdecl ValidateOfficeCandidate(int* param_1)
{
	void* pvVar1;
	char* pcVar2;
	int iVar3;
	int iVar4;

	pvVar1 = LookupEntityRecordById(*param_1);
	if ((pvVar1 != (void*) 0) && (*(char*) ((int) pvVar1 + 0x168) == '\0')) {
		iVar3 = 0;
		pcVar2 = &DAT_101de5a0;
		do {
			if (*pcVar2 == (char) param_1[1]) {
				if (0x1d < iVar3) {
					return 0;
				}
				if ((&DAT_101de5a4)[iVar3 * 6] != -1) {
					return 0;
				}
				if ((&DAT_101de5b0)[iVar3 * 0x18] != '\x03') {
					return 0;
				}
				if (3 < (int) (&DAT_101de5ac)[iVar3 * 6]) {
					return 0;
				}
				if (*(char*) ((int) param_1 + 6) != (&DAT_101de5a8)[iVar3 * 0x18]) {
					return 0;
				}
				if (*(char*) ((int) param_1 + 5) != -1) {
					iVar4 = 0;
					pcVar2 = &DAT_101de5a0;
					while (*pcVar2 != *(char*) ((int) param_1 + 5)) {
						pcVar2 = pcVar2 + 0x18;
						iVar4 = iVar4 + 1;
						if (0x101de86f < (int) pcVar2) {
							return 0;
						}
					}
					if (0x1d < iVar4) {
						return 0;
					}
					if ((&DAT_101de5a8)[iVar3 * 0x18] != (&DAT_101de5a8)[iVar4 * 0x18]) {
						return 0;
					}
					if ((&DAT_101de5a4)[iVar4 * 6] != -1) {
						return 0;
					}
					if ((&DAT_101de5b0)[iVar4 * 0x18] != '\x03') {
						return 0;
					}
					if (3 < (int) (&DAT_101de5ac)[iVar4 * 6]) {
						return 0;
					}
				}
				return 1;
			}
			pcVar2 = pcVar2 + 0x18;
			iVar3 = iVar3 + 1;
		} while ((int) pcVar2 < 0x101de870);
	}
	return 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, instruction folding (lea vs mov), jump condition swap, zero-extend pattern (xor vs mov)
// SIZE: 425
// SYMBOL: _ValidateAndAssignOffice
// FUNCTION: SERVER 0x1000b290
// ValidateAndAssignOffice

/* Auto-generated Ghidra decompilation */
// BLOCKER_DELTA: 400

unsigned int ValidateAndAssignOffice(unsigned int* param_1)
{
	unsigned char uVar1;
	unsigned char uVar2;
	short* piVar3;
	char* pcVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	unsigned int* puVar8;
	unsigned int* puVar9;
	unsigned int auStack_18[4];
	int iStack_8;

	piVar3 = LookupEntityRecordById(*param_1);
	if (((piVar3 != 0) && (*piVar3 != -1)) && (*(char*) (piVar3 + 0xb4) == '\0')) {
		iVar6 = 0;
		pcVar4 = (char*) 0x101de5a0;
		do {
			if (*pcVar4 == *(char*) (param_1 + 1)) {
				if (0x1d < iVar6) {
					return 0;
				}
				uVar1 = *(unsigned char*) (param_1 + 6);
				iVar6 = iVar6 * 0x18;
				uVar2 = *(unsigned char*) (iVar6 + 0x101de5a8);
				if (uVar1 != uVar2) {
					return 0;
				}
				if (*(int*) (param_1 + 5) == -1) {
					if (*(int*) (iVar6 + 0x101de5a4) != -1) {
						return 0;
					}
					if (*(char*) (iVar6 + 0x101de5b0) != '\x03') {
						return 0;
					}
					if (3 < *(int*) (iVar6 + 0x101de5ac)) {
						return 0;
					}
					*(unsigned char*) (piVar3 + 0xb4) = uVar1;
					*(int*) (iVar6 + 0x101de5ac) = *(int*) (iVar6 + 0x101de5ac) + 1;
					return 1;
				}
				iVar7 = 0;
				pcVar4 = (char*) 0x101de5a0;
				while (*pcVar4 != *(char*) (param_1 + 5)) {
					pcVar4 = pcVar4 + 0x18;
					iVar7 = iVar7 + 1;
					if ((char*) 0x101de86f < pcVar4) {
						return 0;
					}
				}
				if (0x1d < iVar7) {
					return 0;
				}
				iVar7 = iVar7 * 0x18;
				if (uVar2 != *(unsigned char*) (iVar7 + 0x101de5a8)) {
					return 0;
				}
				puVar8 = (unsigned int*) (uVar2 * 0x18 + 0x10029bb8);
				puVar9 = auStack_18;
				for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
					*puVar9 = *puVar8;
					puVar8 = puVar8 + 1;
					puVar9 = puVar9 + 1;
				}
				if (auStack_18[0] != uVar1) {
					return 0;
				}
				if (iStack_8 == 0) {
					return 0;
				}
				if (*(int*) (iVar6 + 0x101de5a4) != -1) {
					return 0;
				}
				if (*(char*) (iVar6 + 0x101de5b0) != '\x03') {
					return 0;
				}
				if (3 < *(int*) (iVar6 + 0x101de5ac)) {
					return 0;
				}
				if (*(int*) (iVar7 + 0x101de5a4) != -1) {
					return 0;
				}
				if (3 < *(int*) (iVar7 + 0x101de5ac)) {
					return 0;
				}
				*(unsigned char*) (piVar3 + 0xb4) = uVar1;
				*(int*) (iVar6 + 0x101de5ac) = *(int*) (iVar6 + 0x101de5ac) + 1;
				*(int*) (iVar7 + 0x101de5ac) = *(int*) (iVar7 + 0x101de5ac) + 1;
				return 1;
			}
			pcVar4 = pcVar4 + 0x18;
			iVar6 = iVar6 + 1;
		} while (pcVar4 < (char*) 0x101de870);
	}
	return 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 133
// SYMBOL: _ValidateCommand
// FUNCTION: SERVER 0x1000b440
// ValidateCommand

int __cdecl ValidateCommand(char* param_1)
{
	char* pcVar1;
	void* pvVar2;
	int iVar3;

	if (param_1[6] != -1) {
		iVar3 = 0;
		pcVar1 = (char*) DAT_101de5a0;
		while (*pcVar1 != *param_1) {
			pcVar1 = pcVar1 + 0x18;
			iVar3 = iVar3 + 1;
			if ((int) pcVar1 >= (int) 0x101de990) {
				return 0;
			}
		}
		if (iVar3 >= 0x2a) {
			return 0;
		}
		if ((&DAT_101de5b0)[iVar3 * 0x18] != 1) {
			return 0;
		}
		if (DAT_101de5b4[iVar3 * 6] != -1) {
			return 0;
		}
		if (*(int*) (param_1 + 7) != -1) {
			pvVar2 = LookupEntityRecordById(*(int*) (param_1 + 7));
			if (pvVar2 == (void*) 0) {
				return 0;
			}
		}
		if (*(int*) (param_1 + 1) != -1) {
			pvVar2 = LookupEntityRecordById(*(int*) (param_1 + 1));
			if (pvVar2 == (void*) 0) {
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
// SYMBOL: _ExecuteOfficeAssignment
// FUNCTION: SERVER 0x1000b4d0
// ExecuteOfficeAssignment

/* Game function - entity role/assignment table manager */
/* Updates a 0x18-byte record table at 0x101de5a0, clears old roles, sets new assignments */
// BLOCKER_DELTA: 800

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
		ent = LookupEntityRecordById(*(int*) (param_1 + 1));
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
	old_owner = LookupEntityRecordById(*(int*) (record_off + 0x101de5a4));
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
// SYMBOL: _find_entity_26
// FUNCTION: SERVER 0x1000B820
// find_entity_26

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
// SYMBOL: _find_entity_27
// FUNCTION: SERVER 0x1000B850
// find_entity_27

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
// SYMBOL: _SwapOfficeHolders
// BLOCKER_DELTA: 205
// FUNCTION: SERVER 0x1000b880
// SwapOfficeHolders

int __cdecl SwapOfficeHolders(int* param_1)
{
	int uVar1;
	void* pvVar2;
	SlotEntry* pcVar3;
	void* pvVar4;
	void* pvVar5;
	int iVar6;
	int iVar7;

	pvVar2 = LookupEntityRecordById(*param_1);
	if (pvVar2 == (void*) 0) {
		return 0;
	}
	if (*(int*) ((int) pvVar2 + 0x194) < *(int*) ((int) param_1 + 6)) {
		return 0;
	}
	iVar6 = 0;
	pcVar3 = DAT_101de5a0;
	while (pcVar3->key != (char) param_1[1]) {
		pcVar3 = pcVar3 + 1;
		iVar6 = iVar6 + 1;
		if ((int) pcVar3 > 0x101de86f) {
			return 0;
		}
	}
	if (pcVar3 == (SlotEntry*) 0) {
		return 0;
	}
	pvVar4 = LookupEntityRecordById(DAT_101de5a0[iVar6].entityId);
	if (pvVar4 == (void*) 0) {
		return 0;
	}
	iVar7 = 0;
	pcVar3 = DAT_101de5a0;
	while (pcVar3->key != *(char*) ((int) param_1 + 5)) {
		pcVar3 = pcVar3 + 1;
		iVar7 = iVar7 + 1;
		if ((int) pcVar3 > 0x101de86f) {
			return 0;
		}
	}
	if (pcVar3 == (SlotEntry*) 0) {
		return 0;
	}
	pvVar5 = LookupEntityRecordById(DAT_101de5a0[iVar7].entityId);
	if (pvVar5 == (void*) 0) {
		return 0;
	}
	*(char*) ((int) pvVar4 + 0x166) = DAT_101de5a0[iVar7].field8;
	*(char*) ((int) pvVar5 + 0x166) = DAT_101de5a0[iVar6].field8;
	uVar1 = DAT_101de5a0[iVar6].entityId;
	DAT_101de5a0[iVar6].entityId = DAT_101de5a0[iVar7].entityId;
	DAT_101de5a0[iVar7].entityId = uVar1;
	*(int*) ((int) pvVar2 + 0x194) = *(int*) ((int) pvVar2 + 0x194) - *(int*) ((int) param_1 + 6);
	return 1;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, zero-extend pattern (xor vs mov)
// SIZE: 157
// SYMBOL: _ClearEntityLinks
// BLOCKER_DELTA: 146
// FUNCTION: SERVER 0x1000b990
// ClearEntityLinks

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
// SYMBOL: _UpdateEntityLinks
// BLOCKER_DELTA: 178
// ANALYSIS: Iterates through the command execution tracker table at g_office_secondary_id_base to detach or update a specific entity's links and pending sequence numbers. Used when an entity changes state abruptly or is being removed.
// FUNCTION: SERVER 0x1000ba30
// UpdateEntityLinks

void __cdecl UpdateEntityLinks(int param_1, int param_2)
{
	unsigned short uVar1;
	int* piVar2;

	uVar1 = DAT_10035884;
	piVar2 = (int*) 0x101de5b4;
	do {
		if (piVar2[-4] == *(int*) (param_1 + 4) && param_2 != 0) {
			piVar2[-4] = -1;
			*piVar2 = -1;
			*(char*) (piVar2 + -1) = (char) ((uVar1 > 0xb) + 3);
			piVar2[-2] = 0;
		}
		else if (*piVar2 == *(int*) (param_1 + 4)) {
			*piVar2 = -1;
			*(char*) (piVar2 + -1) = 1;
		}
		piVar2 = piVar2 + 6;
	} while ((int) piVar2 < 0x101de9a4);
	if (*(char*) (param_1 + 0x168) != '\0') {
		piVar2 = (int*) 0x101de5ac;
		do {
			if ((char) piVar2[-1] == *(char*) (param_1 + 0x168) && *piVar2 > 0) {
				*piVar2 = *piVar2 - 1;
			}
			piVar2 = piVar2 + 6;
		} while ((int) piVar2 < 0x101de99c);
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
// SYMBOL: _amt_fio_LoadAemter
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
