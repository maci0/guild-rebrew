#include <string.h>
typedef int(__cdecl* dispatch_fn)(unsigned char*);

extern float g_color_scale;
extern double g_dbl_const_6d0; /* 0x100256d0 */
extern dispatch_fn g_chain_handler_table[];

// SIZE 0x8
typedef struct {
	int key;
	int val;
} PAIR;

// SIZE 0x14
// SIZE 0x3c
typedef struct {
	char hdr[0xc];
	PAIR entries[6];
} TGT;

/* Resets an alchemy entity to its initial state by zeroing
 * out its operational fields via memset. */

// FUNCTION: SERVER 0x1000c710
// ahm_GetCommandPayloadSize

/* RELOC 752/752.  The switch-byte/index register pair (dl/ecx in the target,
 * cl/edx before this fix) is decided by which case-0x16 statement reads
 * cmd_payload first: assigning `cursor` from the `*cmd_payload == 0x16`
 * test before reading `cmd_payload[0x14]` into `count` pins the byte in dl.
 * The reverse order scores 742/752, and hoisting `total_size = 0x15` above
 * both scores 508/752. */
int ahm_GetCommandPayloadSize(unsigned char* cmd_payload)

{
	int count;
	unsigned char* cursor;
	int total_size;
	int entry_size;

	// switch table (103 cases) at 0x1000c864
	switch ((unsigned char) *cmd_payload) {
	case 0x3:
	case 0x13:
	case 0x1a:
	case 0x25:
	case 0x2b:
	case 0x34:
	case 0x36:
	case 0x38:
	case 0x47:
	case 0x52:
	case 0x54:
	case 0x5b:
	case 0x5d:
		return 0x1c;
	case 0x4:
		return 0x11;
	case 0x8:
	case 0x1c:
	case 0x28:
	case 0x31:
	case 0x3b:
	case 0x42:
	case 0x43:
	case 0x4a:
	case 0x4d:
	case 0x57:
	case 0x58:
	case 0x69:
		return 0x14;
	case 0xa:
		return 0x50;
	case 0xb:
		return 0x2a;
	case 0xc:
		return 0x49;
	case 0xf:
	case 0x2c:
		return 0x21;
	case 0x11:
	case 0x3d:
		return 0x27;
	case 0x12:
	case 0x1e:
		return 0x1e;
	case 0x14:
		return 0x16;
	case 0x15:
		return 0x39;
	case 0x16:
	case 0x17:
		cursor = (*cmd_payload == 0x16) ? (cmd_payload + 0x15) : (cmd_payload + 0x15);
		count = cmd_payload[0x14];
		total_size = 0x15;
		while (count > 0) {
			entry_size = cursor[1] * *cursor + 4;
			total_size = total_size + entry_size;
			cursor = cursor + entry_size;
			count = count - 1;
		}
		return total_size;
	case 0x18:
		return cmd_payload[0x14] * 5 + 0x15;
	case 0x19:
	case 0x53:
		return 0x24;
	case 0x1b:
	case 0x64:
		return 0x28;
	case 0x1d:
		return 0x5f;
	case 0x20:
		return ((cmd_payload[0x10] != 0xe ? -1 : 0) & 0x7c) + 0x11;
	case 0x22:
		return 0x3d;
	case 0xd:
	case 0x21:
	case 0x23:
	case 0x24:
	case 0x26:
	case 0x27:
	case 0x29:
	case 0x2a:
	case 0x33:
	case 0x39:
	case 0x3a:
	case 0x5a:
	case 0x66:
	case 0x68:
		return 0x18;
	case 0x2d:
	case 0x45:
		return 0x1f;
	case 0x2e:
	case 0x3c:
		return 0x20;
	case 0x2f:
	case 0x30:
		return 0x3c;
	case 0x35:
		return 0x5d;
	case 0x37:
		return 0x45;
	case 0x32:
	case 0x3e:
	case 0x4f:
	case 0x5e:
	case 0x63:
		return 0x34;
	case 0x40:
	case 0x60:
		return 0x2f;
	case 0x41:
		return 0x4a;
	case 0x44:
		return 0x17;
	case 0x46:
		return 0x19;
	case 0x48:
		return 0x15;
	case 0x49:
		return 0x36;
	case 0x4b:
	case 0x67:
		return 0x90;
	case 0x4c:
		return 0x35;
	case 0x4e:
		return 0x40;
	case 0x50:
	case 0x51:
		return 0x44;
	case 0x55:
		return 0x61;
	case 0x56:
		return 0x38;
	case 0x5c:
		return 0x1a;
	case 0x61:
	case 0x62:
		return 0x29;
	case 0x5f:
		return 0x80;
	default:
		return 0x91;
	}
	return total_size;
}