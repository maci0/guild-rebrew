#include <stdio.h>
#include "../../../Units/Error/error.h"

// SIZE 0x18
typedef struct {
	int value;
	char type;
	char pad[19];
} ENT;

#pragma pack(push, 1)
// SIZE 0x18
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
void* __cdecl gm_LookupEntityRecordById(int);
extern int DAT_101de5b4[];
extern ENT g_ents[];
extern ENT g_ents2[];
extern unsigned short DAT_10035884;
int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, int streamCtx);
void __cdecl InitBuildingTypeTable(void);

/* Validates if an entity is eligible for an office position.
 * Checks entity type, existing office holdings, and eligibility
 * requirements. Returns 0 on success, non-zero on failure. */

// STUB: SERVER 0x1000b4d0
// ExecuteOfficeAssignment

/* Game function - entity role/assignment table manager */
/* Updates a 0x18-byte record table at 0x101de5a0, clears old roles, sets new assignments */

int __cdecl ExecuteOfficeAssignment(char* cmd_payload)
{
	int iStack;
	int ent;
	int record_index;
	int old_owner;
	int record_off;

	iStack = -1;

	/* Validate associated entity if present */
	if (*(int*) (cmd_payload + 7) != -1) {
		if (gm_LookupEntityRecordById(*(int*) (cmd_payload + 7)) == 0) {
			return 0;
		}
	}

	/* Get owner entity */
	ent = 0;
	if (*(int*) (cmd_payload + 1) != -1) {
		ent = (int)gm_LookupEntityRecordById(*(int*) (cmd_payload + 1));
		if (ent == 0) {
			return 0;
		}
		iStack = *(int*) (ent + 4);
	}

	/* Search table for matching type byte */
	{
		char type;
		record_index = 0;
		type = *cmd_payload;

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
	old_owner = (int)gm_LookupEntityRecordById(*(int*) (record_off + 0x101de5a4));
	if (old_owner != 0 && *(int*) (old_owner + 4) != *(int*) (cmd_payload + 1)) {
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
	*(int*) (record_off + 0x101de5b4) = *(int*) (cmd_payload + 7);
	*(char*) (record_off + 0x101de5b0) = cmd_payload[5];
	if (cmd_payload[5] == 3) {
		*(int*) (record_off + 0x101de5ac) = 0;
	}

	return 1;
}

/* Searches for an entity with type 0x26 (specific entity class)
 * matching the given value. Used for office-related lookups. */
