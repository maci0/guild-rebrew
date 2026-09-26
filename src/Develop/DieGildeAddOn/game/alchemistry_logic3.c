#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <string.h>

typedef int(__cdecl* dispatch_fn)(unsigned char*);

/* The command TU's data opens with the game speed pair and the command
 * dispatch table (read by cm_ExSetSyncFlags, ServerMainThread and
 * cm_ProcessCommandQueue), ahead of the chain handler table. */
// GLOBAL: SERVER 0x1002c3f0
int g_game_speed_value = 770;
// GLOBAL: SERVER 0x1002c3f4
int g_game_speed_index = 2;
// GLOBAL: SERVER 0x1002c3f8
int(__cdecl* g_dispatch_table[106])(unsigned char* pkt, int param) = {
    0x1000d2e0, 0x1000d330, 0x1000d340, 0x1000d2e0, 0x1000d330, 0x1000d2e0, 0x1000d2e0, 0x1000d2e0, 0x1000d330, 0x1000d330, 0x1000d350, 0x1000d460, 0x1000d570, 0x1000d6e0, 0x1000d730, 0x1000d7f0,
    0x1000d8a0, 0x1000d930, 0x1000e140, 0x1000e530, 0x1000e690, 0x1000e750, 0x1000e7d0, 0x1000e8d0, 0x1000e9c0, 0x1000eaa0, 0x1000eb70, 0x1000ec00, 0x1000ef90, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0,
    0x1000efb0, 0x1000f030, 0x1000f080, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f0a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f0d0, 0x1000f1a0, 0x1000f2f0, 0x1000f3a0, 0x1000f3a0,
    0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3b0, 0x1000f480, 0x1000f590, 0x1000f680, 0x1000f3a0, 0x1000f730, 0x1000f3a0, 0x1000f3a0,
    0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f940, 0x1000f960, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f980, 0x1000fad0, 0x1000fbd0, 0x1000fb30, 0x1000fbd0, 0x1000fbd0, 0x1000fbd0,
    0x1000fbf0, 0x1000fbf0, 0x1000fbf0, 0x1000fc10, 0x1000fd50, 0x1000fbf0, 0x1000ff10, 0x1000ff30, 0x1000f3a0, 0x1000ff60, 0x1000ffc0, 0x10010010, 0x10010080, 0x100100a0, 0x10010140, 0x1000f3a0,
    0x10010260, 0x100102f0, 0x10010310, 0x10010350, 0x10010390, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0,
};

// GLOBAL: SERVER 0x1002c5a0
dispatch_fn g_chain_handler_table[106] = {
    0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000cb20,
    0x1000f3a0, 0x1000cbd0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000cde0, 0x1000f3a0, 0x1000f3a0, 0x1000cf30, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0,
    0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0,
    0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000cfe0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0,
    0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000d020, 0x1000d040, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0,
    0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000d060, 0x1000d110, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000d260, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0,
    0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0, 0x1000f3a0,
};

/* Resets an alchemy entity to its initial state by zeroing
 * out its operational fields via memset. */
// FUNCTION: GOLDTL 0x499a50
// SIZE: 128

// FUNCTION: GOLD 0x004c43c0
// SIZE: 130
// FUNCTION: GOLDTL 0x4c4d30
// SIZE: 130
// FUNCTION: SERVER 0x1000ca00

// ahm_ProcessEntityChain

#pragma pack(push, 1)
// SIZE 0x99
typedef struct ChainNode {
	unsigned char cmd;      /* +0x00 */
	char pad[0x94];
	struct ChainNode* next; /* +0x95 (unaligned) */
} ChainNode;
#pragma pack(pop)

int __cdecl ahm_ProcessEntityChain(char* cmd_payload)
{
	ChainNode* node;
	ChainNode* n;
	int ok;

	ok = 1;
	node = ((ChainNode*) cmd_payload)->next;
	while (ok != 0) {
		if (node->cmd == 6) {
			goto check_result;
		}
		if (g_chain_handler_table[node->cmd](node) != 0) {
			ok = 0;
		}
		node = node->next;
	}
	goto error;
check_result:
	if (ok == 0) {
		goto error;
	}
	/* success: mark head and chain terminator as processed */
	n = (ChainNode*) cmd_payload;
	n->cmd = 1;
	while (n->cmd != 6) {
		n = n->next;
	}
	n->cmd = 1;
	return 1;

error:
	/* failure: mark every node in the chain */
	n = (ChainNode*) cmd_payload;
	while (n->cmd != 6) {
		n->cmd = 2;
		n = n->next;
	}
	n->cmd = 2;
	return 1;
}
// FUNCTION: SERVER 0x1000CA90
// gm_GetFieldByType

int __cdecl gm_GetFieldByType(char* p, int type)
{
	unsigned int byte_value;
	unsigned int i;

	if (type == -2) {
		byte_value = (unsigned char) p[3];
		i = byte_value << 4;
		i += byte_value;
		i <<= 8;
		i += byte_value;
		i <<= 4;
		i += byte_value;
		return ((int*) 0x10442d00)[i * 9];
	}
	if (type == -3) {
		byte_value = (unsigned char) p[3];
		i = byte_value << 4;
		i += byte_value;
		i <<= 8;
		i += byte_value;
		i <<= 4;
		i += byte_value;
		return ((int*) 0x10442d04)[i * 9];
	}
	if (type == -4) {
		byte_value = (unsigned char) p[3];
		i = byte_value << 4;
		i += byte_value;
		i <<= 8;
		i += byte_value;
		i <<= 4;
		i += byte_value;
		return ((int*) 0x10442d08)[i * 9];
	}
	return type;
}

/* Resolves a field value by type from a command packet.
 * Performs entity ID resolution through the global entity
 * tables. Returns the resolved value or 0 on failure. */
