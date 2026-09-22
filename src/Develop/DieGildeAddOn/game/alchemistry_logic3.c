#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <string.h>

typedef int(__cdecl* dispatch_fn)(unsigned char*);

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

/* Resolves a field value by type from a command packet.
 * Performs entity ID resolution through the global entity
 * tables. Returns the resolved value or 0 on failure. */
