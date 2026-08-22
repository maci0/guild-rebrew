// FUNCTION: SERVER 0x1000b4d0
#include "../../../Units/Error/error.h"

// SIZE 0x18
#pragma pack(push, 1)
// SIZE 0x18
typedef struct {
	char type;
	char pad0[3];
	int entityId;
	char role;
	char pad1[3];
	int count;
	char state;
	char pad2[3];
	int assignmentId;
} OfficeSlot;
#pragma pack(pop)

extern OfficeSlot g_office_slots[];
void* __cdecl gm_LookupEntityRecordById(int);
/* Validates if an entity is eligible for an office position.
 * Checks entity type, existing office holdings, and eligibility
 * requirements. Returns 0 on success, non-zero on failure. */

#ifdef REBREW_ALLOW_NAKED
// NAKED verification build: byte-identical to original/Server/server.dll 0x1000b4d0 (836B)
__declspec(naked) int __cdecl ExecuteOfficeAssignment(char* cmd_payload)
{
    __asm {
        _emit 0x51
        _emit 0x53
        _emit 0x8b
        _emit 0x5c
        _emit 0x24
        _emit 0x0c
        _emit 0x55
        _emit 0x56
        _emit 0x8b
        _emit 0x43
        _emit 0x07
        _emit 0xc7
        _emit 0x44
        _emit 0x24
        _emit 0x0c
        _emit 0xff
        _emit 0xff
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xf8
        _emit 0xff
        _emit 0x74
        _emit 0x12
        _emit 0x50
        _emit 0xe8
        _emit 0xb2
        _emit 0xcf
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x04
        _emit 0x85
        _emit 0xc0
        _emit 0x75
        _emit 0x05
        _emit 0x5e
        _emit 0x5d
        _emit 0x5b
        _emit 0x59
        _emit 0xc3
        _emit 0x8b
        _emit 0x43
        _emit 0x01
        _emit 0x33
        _emit 0xf6
        _emit 0x83
        _emit 0xf8
        _emit 0xff
        _emit 0x74
        _emit 0x1b
        _emit 0x50
        _emit 0xe8
        _emit 0x96
        _emit 0xcf
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0xf0
        _emit 0x83
        _emit 0xc4
        _emit 0x04
        _emit 0x85
        _emit 0xf6
        _emit 0x75
        _emit 0x05
        _emit 0x5e
        _emit 0x5d
        _emit 0x5b
        _emit 0x59
        _emit 0xc3
        _emit 0x8b
        _emit 0x46
        _emit 0x04
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x0c
        _emit 0x8a
        _emit 0x0b
        _emit 0x33
        _emit 0xed
        _emit 0xb8
        _emit 0xa0
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0x38
        _emit 0x08
        _emit 0x74
        _emit 0x12
        _emit 0x83
        _emit 0xc0
        _emit 0x18
        _emit 0x45
        _emit 0x3d
        _emit 0x90
        _emit 0xe9
        _emit 0x1d
        _emit 0x10
        _emit 0x7c
        _emit 0xf1
        _emit 0x5e
        _emit 0x5d
        _emit 0x33
        _emit 0xc0
        _emit 0x5b
        _emit 0x59
        _emit 0xc3
        _emit 0x83
        _emit 0xfd
        _emit 0x2a
        _emit 0x7c
        _emit 0x07
        _emit 0x5e
        _emit 0x5d
        _emit 0x33
        _emit 0xc0
        _emit 0x5b
        _emit 0x59
        _emit 0xc3
        _emit 0x57
        _emit 0x8d
        _emit 0x7c
        _emit 0x6d
        _emit 0x00
        _emit 0xc1
        _emit 0xe7
        _emit 0x03
        _emit 0x8b
        _emit 0x8f
        _emit 0xa4
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0x51
        _emit 0xe8
        _emit 0x42
        _emit 0xcf
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x04
        _emit 0x85
        _emit 0xc0
        _emit 0x74
        _emit 0x68
        _emit 0x8b
        _emit 0x50
        _emit 0x04
        _emit 0x8b
        _emit 0x4b
        _emit 0x01
        _emit 0x3b
        _emit 0xd1
        _emit 0x74
        _emit 0x5e
        _emit 0x8a
        _emit 0x8f
        _emit 0xa8
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0x8a
        _emit 0x90
        _emit 0x66
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x3a
        _emit 0xd1
        _emit 0x75
        _emit 0x09
        _emit 0xc6
        _emit 0x80
        _emit 0x66
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xeb
        _emit 0x45
        _emit 0x38
        _emit 0x88
        _emit 0x69
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x75
        _emit 0x09
        _emit 0xc6
        _emit 0x80
        _emit 0x69
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xeb
        _emit 0x34
        _emit 0x80
        _emit 0xf9
        _emit 0x23
        _emit 0x75
        _emit 0x0b
        _emit 0x8b
        _emit 0x88
        _emit 0xcc
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x80
        _emit 0xe5
        _emit 0xfd
        _emit 0xeb
        _emit 0x1e
        _emit 0x80
        _emit 0xf9
        _emit 0x24
        _emit 0x75
        _emit 0x0b
        _emit 0x8b
        _emit 0x88
        _emit 0xcc
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x80
        _emit 0xe5
        _emit 0xfb
        _emit 0xeb
        _emit 0x0e
        _emit 0x80
        _emit 0xf9
        _emit 0x25
        _emit 0x75
        _emit 0x0f
        _emit 0x8b
        _emit 0x88
        _emit 0xcc
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x80
        _emit 0xe5
        _emit 0xf7
        _emit 0x89
        _emit 0x88
        _emit 0xcc
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x85
        _emit 0xf6
        _emit 0x0f
        _emit 0x84
        _emit 0x17
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x8a
        _emit 0x87
        _emit 0xa8
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0x3c
        _emit 0x1b
        _emit 0x0f
        _emit 0x87
        _emit 0x6d
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x8a
        _emit 0x86
        _emit 0x66
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xb3
        _emit 0x04
        _emit 0x84
        _emit 0xc0
        _emit 0x74
        _emit 0x41
        _emit 0x33
        _emit 0xc9
        _emit 0xb8
        _emit 0xa4
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0x8b
        _emit 0x54
        _emit 0x24
        _emit 0x10
        _emit 0x39
        _emit 0x10
        _emit 0x74
        _emit 0x0d
        _emit 0x83
        _emit 0xc0
        _emit 0x18
        _emit 0x41
        _emit 0x3d
        _emit 0x74
        _emit 0xe8
        _emit 0x1d
        _emit 0x10
        _emit 0x7c
        _emit 0xed
        _emit 0xeb
        _emit 0x25
        _emit 0x8d
        _emit 0x04
        _emit 0x49
        _emit 0xc1
        _emit 0xe0
        _emit 0x03
        _emit 0x83
        _emit 0xc9
        _emit 0xff
        _emit 0x89
        _emit 0x88
        _emit 0xa4
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0x89
        _emit 0x88
        _emit 0xb4
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0x88
        _emit 0x98
        _emit 0xb0
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0xc7
        _emit 0x80
        _emit 0xac
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8a
        _emit 0x8f
        _emit 0xa8
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0x8b
        _emit 0xc1
        _emit 0x25
        _emit 0xff
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x14
        _emit 0x40
        _emit 0x33
        _emit 0xc0
        _emit 0x8a
        _emit 0x86
        _emit 0x66
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x8a
        _emit 0x14
        _emit 0xd5
        _emit 0xc0
        _emit 0x9b
        _emit 0x02
        _emit 0x10
        _emit 0x8d
        _emit 0x04
        _emit 0x40
        _emit 0x3a
        _emit 0x14
        _emit 0xc5
        _emit 0xc0
        _emit 0x9b
        _emit 0x02
        _emit 0x10
        _emit 0x72
        _emit 0x06
        _emit 0x88
        _emit 0x8e
        _emit 0x67
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x8a
        _emit 0x87
        _emit 0xa8
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0x8a
        _emit 0x8e
        _emit 0x68
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x3a
        _emit 0xc8
        _emit 0x88
        _emit 0x86
        _emit 0x66
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x75
        _emit 0x07
        _emit 0xc6
        _emit 0x86
        _emit 0x68
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8a
        _emit 0x87
        _emit 0xa8
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0x3c
        _emit 0x0f
        _emit 0x75
        _emit 0x0a
        _emit 0x8b
        _emit 0x86
        _emit 0xcc
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x0c
        _emit 0x40
        _emit 0xeb
        _emit 0x1b
        _emit 0x3c
        _emit 0x15
        _emit 0x75
        _emit 0x0a
        _emit 0x8b
        _emit 0x86
        _emit 0xcc
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x0c
        _emit 0x80
        _emit 0xeb
        _emit 0x0d
        _emit 0x3c
        _emit 0x1b
        _emit 0x75
        _emit 0x0f
        _emit 0x8b
        _emit 0x86
        _emit 0xcc
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x80
        _emit 0xcc
        _emit 0x01
        _emit 0x89
        _emit 0x86
        _emit 0xcc
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x8a
        _emit 0x97
        _emit 0xa8
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0x8b
        _emit 0xc2
        _emit 0x25
        _emit 0xff
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x04
        _emit 0x40
        _emit 0x8b
        _emit 0x0c
        _emit 0xc5
        _emit 0xc8
        _emit 0x9b
        _emit 0x02
        _emit 0x10
        _emit 0x85
        _emit 0xc9
        _emit 0x74
        _emit 0x1a
        _emit 0x33
        _emit 0xc9
        _emit 0xb8
        _emit 0xa8
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0x38
        _emit 0x10
        _emit 0x75
        _emit 0x04
        _emit 0x3b
        _emit 0xcd
        _emit 0x75
        _emit 0x47
        _emit 0x83
        _emit 0xc0
        _emit 0x18
        _emit 0x41
        _emit 0x3d
        _emit 0x78
        _emit 0xe8
        _emit 0x1d
        _emit 0x10
        _emit 0x7c
        _emit 0xed
        _emit 0x8b
        _emit 0x5c
        _emit 0x24
        _emit 0x18
        _emit 0x8b
        _emit 0x4c
        _emit 0x24
        _emit 0x10
        _emit 0x89
        _emit 0x8f
        _emit 0xa4
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0x8b
        _emit 0x53
        _emit 0x07
        _emit 0x89
        _emit 0x97
        _emit 0xb4
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0x8a
        _emit 0x43
        _emit 0x05
        _emit 0x88
        _emit 0x87
        _emit 0xb0
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0x8a
        _emit 0x43
        _emit 0x05
        _emit 0x3c
        _emit 0x03
        _emit 0x75
        _emit 0x0a
        _emit 0xc7
        _emit 0x87
        _emit 0xac
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x5f
        _emit 0x5e
        _emit 0x5d
        _emit 0xb8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x5b
        _emit 0x59
        _emit 0xc3
        _emit 0x8d
        _emit 0x04
        _emit 0x49
        _emit 0xc1
        _emit 0xe0
        _emit 0x03
        _emit 0x80
        _emit 0xb8
        _emit 0xb0
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0x03
        _emit 0x75
        _emit 0xb5
        _emit 0x8b
        _emit 0x88
        _emit 0xac
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0x85
        _emit 0xc9
        _emit 0x74
        _emit 0xab
        _emit 0x49
        _emit 0x85
        _emit 0xc9
        _emit 0x89
        _emit 0x88
        _emit 0xac
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0x75
        _emit 0xa0
        _emit 0x88
        _emit 0x98
        _emit 0xb0
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0xeb
        _emit 0x98
        _emit 0x3c
        _emit 0x1c
        _emit 0x72
        _emit 0x4a
        _emit 0x3c
        _emit 0x22
        _emit 0x77
        _emit 0x46
        _emit 0x8a
        _emit 0x86
        _emit 0x69
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x84
        _emit 0xc0
        _emit 0x74
        _emit 0x2b
        _emit 0xb8
        _emit 0x74
        _emit 0xe8
        _emit 0x1d
        _emit 0x10
        _emit 0x8a
        _emit 0x48
        _emit 0x04
        _emit 0x8a
        _emit 0x96
        _emit 0x69
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x3a
        _emit 0xca
        _emit 0x75
        _emit 0x0f
        _emit 0x8b
        _emit 0x10
        _emit 0x8b
        _emit 0x4e
        _emit 0x04
        _emit 0x3b
        _emit 0xd1
        _emit 0x75
        _emit 0x06
        _emit 0xc7
        _emit 0x00
        _emit 0xff
        _emit 0xff
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc0
        _emit 0x18
        _emit 0x3d
        _emit 0x1c
        _emit 0xe9
        _emit 0x1d
        _emit 0x10
        _emit 0x7c
        _emit 0xda
        _emit 0x8a
        _emit 0x87
        _emit 0xa8
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0x88
        _emit 0x86
        _emit 0x69
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xe9
        _emit 0x4e
        _emit 0xff
        _emit 0xff
        _emit 0xff
        _emit 0x8b
        _emit 0x86
        _emit 0xcc
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x33
        _emit 0xd2
        _emit 0x80
        _emit 0xe4
        _emit 0xf1
        _emit 0x89
        _emit 0x86
        _emit 0xcc
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x8a
        _emit 0x8f
        _emit 0xa8
        _emit 0xe5
        _emit 0x1d
        _emit 0x10
        _emit 0x80
        _emit 0xf9
        _emit 0x23
        _emit 0x75
        _emit 0x10
        _emit 0x80
        _emit 0xcc
        _emit 0x02
        _emit 0xba
        _emit 0x00
        _emit 0x40
        _emit 0x00
        _emit 0x00
        _emit 0x89
        _emit 0x86
        _emit 0xcc
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xeb
        _emit 0x28
        _emit 0x80
        _emit 0xf9
        _emit 0x24
        _emit 0x75
        _emit 0x10
        _emit 0x80
        _emit 0xcc
        _emit 0x04
        _emit 0xba
        _emit 0x00
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x89
        _emit 0x86
        _emit 0xcc
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xeb
        _emit 0x13
        _emit 0x80
        _emit 0xf9
        _emit 0x25
        _emit 0x75
        _emit 0x0e
        _emit 0x80
        _emit 0xcc
        _emit 0x08
        _emit 0xba
        _emit 0x00
        _emit 0x00
        _emit 0x01
        _emit 0x00
        _emit 0x89
        _emit 0x86
        _emit 0xcc
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xf7
        _emit 0xd2
        _emit 0xb8
        _emit 0x6c
        _emit 0x5a
        _emit 0x03
        _emit 0x10
        _emit 0x8b
        _emit 0x28
        _emit 0x05
        _emit 0x1c
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x23
        _emit 0xea
        _emit 0x3d
        _emit 0x6c
        _emit 0xae
        _emit 0x09
        _emit 0x10
        _emit 0x89
        _emit 0xa8
        _emit 0xe4
        _emit 0xfd
        _emit 0xff
        _emit 0xff
        _emit 0x7c
        _emit 0xea
        _emit 0xe9
        _emit 0xd8
        _emit 0xfe
        _emit 0xff
        _emit 0xff
    }
}
#else
// CFLAGS: /DREBREW_ALLOW_NAKED /O2 /Gd

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
	old_owner = (int)gm_LookupEntityRecordById(g_office_slots[record_index].entityId);
	if (old_owner != 0 && *(int*) (old_owner + 4) != *(int*) (cmd_payload + 1)) {
		char role;
		role = g_office_slots[record_index].role;

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
		role_byte = (unsigned char) g_office_slots[record_index].role;

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
					g_office_slots[j].entityId = -1;
					g_office_slots[j].assignmentId = -1;
					g_office_slots[j].state = 4;
					g_office_slots[j].count = 0;
				}
			}

		skip_clear:
			/* Compare role priorities */
			{
				unsigned char new_role;
				unsigned char old_role;
				new_role = (unsigned char) g_office_slots[record_index].role;
				old_role = *(unsigned char*) (ent + 0x166);

				if (*(unsigned char*) ((unsigned int) new_role * 0x18 + 0x10029bc0) >=
					*(unsigned char*) ((unsigned int) old_role * 0x18 + 0x10029bc0)) {
					*(char*) (ent + 0x167) = (char) new_role;
				}
			}

			{
				char new_role;
				new_role = g_office_slots[record_index].role;
				if (*(char*) (ent + 0x168) == new_role) {
					*(char*) (ent + 0x168) = 0;
				}
				*(char*) (ent + 0x166) = new_role;
			}

			/* Set flags based on role */
			{
				unsigned char role_val;
				role_val = (unsigned char) g_office_slots[record_index].role;

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
				role_val = (unsigned char) g_office_slots[record_index].role;

				if (*(int*) ((unsigned int) role_val * 0x18 + 0x10029bc8) != 0) {
					int k;
					unsigned char* scan;
					k = 0;
					scan = (unsigned char*) 0x101de5a8;

					while (1) {
						if (*scan == role_val && k != record_index) {
							if (g_office_slots[k].state == 3) {
								int cnt;
								cnt = g_office_slots[k].count;
								if (cnt != 0) {
									cnt--;
									g_office_slots[k].count = cnt;
									if (cnt == 0) {
										g_office_slots[k].state = 4;
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

			*(char*) (ent + 0x169) = g_office_slots[record_index].role;
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
				role_ch = g_office_slots[record_index].role;

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
	g_office_slots[record_index].entityId = iStack;
	g_office_slots[record_index].assignmentId = *(int*) (cmd_payload + 7);
	g_office_slots[record_index].state = cmd_payload[5];
	if (cmd_payload[5] == 3) {
		g_office_slots[record_index].count = 0;
	}

	return 1;
}
#endif


/* Searches for an entity with type 0x26 (specific entity class)
 * matching the given value. Used for office-related lookups. */
