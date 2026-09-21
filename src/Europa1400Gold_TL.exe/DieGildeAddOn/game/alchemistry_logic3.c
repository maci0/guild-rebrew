#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <string.h>

typedef int(__cdecl* dispatch_fn)(unsigned char*);

// FUNCTION: GOLDTL 0x499a50
// SIZE: 128
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
