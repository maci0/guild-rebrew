#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <string.h>
int __cdecl __ftol(void);

typedef int(__cdecl* dispatch_fn)(unsigned char*);

extern char* g_table;
int __cdecl gm_ResolveEntityById(void** dynamic, int zero1, int zero2, int id);
int __cdecl gm_RandomMod(int range);
float __cdecl gm_RandomFloat01(void);
void __cdecl gm_AddOrAccumulateObject(int p1, int p2, int p3);
int __cdecl gm_RefreshMarketAvailability(int season);
int __cdecl gm_LookupEntityRecordById(int);
void __cdecl gm_DeallocEntity(unsigned int index, int param);
void* __cdecl gm_NextEntityQueryMatch(void);
extern float fColorScale;
extern int g_next_object_id;
extern unsigned char g_current_season;
extern float g_float_const_cc;
extern float g_float_const_a0;
extern double dScaleFactor;
extern int g_alchemy_entity_table[];
int* __cdecl ahm_LookupEntityInTable(int);
extern dispatch_fn PTR_LAB_1002c5a0[];

// SIZE 0x8
typedef struct {
	int key;
	int val;
} PAIR;

// SIZE 0x14
typedef struct {
	char hdr[8];
	int key;
	char pad[4];
	int val;
} SRC;

// SIZE 0x3c
typedef struct {
	char hdr[0xc];
	PAIR entries[6];
} TGT;

/* Resets an alchemy entity to its initial state by zeroing
 * out its operational fields via memset. */

// CFLAGS: /O2 /Gd
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);

// FUNCTION: SERVER 0x1000ca00
// ahm_ProcessEntityChain

#pragma pack(push, 1)
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
		if (PTR_LAB_1002c5a0[node->cmd](node) != 0) {
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

// FUNCTION: SERVER 0x1000CA90
// gm_GetFieldByType

int __cdecl gm_GetFieldByType(char* p, int type)
{
	unsigned int x;
	unsigned int i;

	if (type == -2) {
		x = (unsigned char) p[3];
		i = x << 4;
		i += x;
		i <<= 8;
		i += x;
		i <<= 4;
		i += x;
		return ((int*) 0x10442d00)[i * 9];
	}
	if (type == -3) {
		x = (unsigned char) p[3];
		i = x << 4;
		i += x;
		i <<= 8;
		i += x;
		i <<= 4;
		i += x;
		return ((int*) 0x10442d04)[i * 9];
	}
	if (type == -4) {
		x = (unsigned char) p[3];
		i = x << 4;
		i += x;
		i <<= 8;
		i += x;
		i <<= 4;
		i += x;
		return ((int*) 0x10442d08)[i * 9];
	}
	return type;
}
