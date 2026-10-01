extern unsigned char g_connections[9 * 0x264264];
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
/* Named handlers let CL emit relocations for both command tables. */
typedef int (__cdecl *command_fn)(unsigned char*, int);
extern int __cdecl cm_ChkMoveCredits(int cmd, char* result);
extern int __cdecl cm_ChkSellObjekt(char* cmd);
extern int __cdecl cm_ChkChangeAttribute(int cmd, char* result);
extern int __cdecl cm_ChkChangeBits(int cmd, char* result);
extern int __cdecl cm_ChkSetGebBesitzer(char* obj);
extern int __cdecl cm_ChkOfficeCandidate(void* obj);
extern int __cdecl cm_ValidateGeneric(void* cmd, char* result);
extern int __cdecl cm_ChkElectionOrTrade(int cmd);
extern int __cdecl cm_ChkJoinLeaveElection(int* cmd);
extern int __cdecl cm_ChkCutsceneReady(char* obj);
extern int __cdecl cm_ChkCommandType(char* cmd, char* result);
extern int __cdecl cm_MarkAndReturn(int cmd, char* result);
extern int __cdecl cm_RejectCommand(void);
extern int __cdecl cm_ExAllocRaum(int cmd, char* result);
extern int __cdecl cm_ExAllocSpieler(int cmd, char* result);
extern int __cdecl cm_ExAllocClientSpieler(int cmd, char* result);
extern int __cdecl cm_ExChangePlayerIdentity(int cmd, char* result);
extern int __cdecl cm_ExFree(int cmd, char* result);
extern int __cdecl cm_ExTransferCurrency(int cmd, char* result);
extern int __cdecl cm_ExTransferCurrencyNoKill(int cmd, char* result);
extern unsigned int cm_ExSellObjekt(char* cmd, unsigned char* result);
extern int __cdecl cm_ExProdObjekt(int msg, char* result);
extern int __cdecl cm_ExMoveObjekt(int cmd, char* result);
extern int __cdecl cm_ExClearLagerslot(short* cmd, unsigned char* result);
extern int __cdecl cm_ExAllocObjekt(int cmd, char* result);
extern int __cdecl cm_ExChangeAttribute(int cmd, char* result);
extern int __cdecl cm_ExSetAttribute(int cmd, char* result);
extern int __cdecl cm_ExChangeDesire(unsigned char* cmd, unsigned char* result);
extern int __cdecl cm_ExChangeBits(int cmd, char* result);
extern int __cdecl cm_ExChangeFloat(int cmd, char* result);
extern int __cdecl cm_ExCopyEntityData(char* cmd_ptr, char* response);
extern int __cdecl cm_ChainAssignId(int cmd, char* result);
extern int __cdecl cm_ExSetSyncFlags(int cmd, char* result);
extern int __cdecl cm_ExKillSpieler(int cmd);
extern int __cdecl cm_AssignSequenceCounter(int cmd, char* result);
extern int __cdecl cm_AssignEntityId(int cmd, char* result);
extern int __cdecl cm_ExRemoveLinkedObject(int cmd, char *status_ptr);
extern int __cdecl cm_ChainRecordLookup(int cmd, char* result);
extern int __cdecl cm_ExAllocThemaPredigt(int cmd, char* result);
extern int __cdecl cm_ChainNoop(void);
extern int __cdecl cm_ExSetGebBesitzer(int cmd, char* result);
extern int __cdecl cm_ExSetWohnsitz(int cmd, char* result);
extern int __cdecl cm_ExSetGebUpgrade(int cmd, char* result);
extern int __cdecl cm_ExDestroyBuilding(int cmd, char* result);
extern int __cdecl cm_ExEmployWorker(int cmd, char* result);
extern int __cdecl cm_ExAssignOffice(void* obj);
extern int __cdecl cm_ExExecuteOffice(void* cmd, char* result);
extern int __cdecl cm_ExCreateCitizen(int cmd, char* result);
extern int __cdecl cm_ExKillTransporter(int cmd, char* result);
extern int __cdecl cm_ExCreateGeb(int cmd, char* result);
extern int __cdecl cm_ExCondWrite(void* obj, char* buf);
extern int __cdecl cm_InitDefaultResponse(int cmd, char* result);
extern int __cdecl cm_ExElectionOrTrade(int cmd, char* result);
extern int __cdecl cm_ExJoinLeaveElection(int cmd, char* result);
extern int __cdecl cm_ExCondWrite2(void* obj, char* buf);
extern int __cdecl cm_ChkEntityLookup(int cmd, char* result);
extern int __cdecl cm_ExCutsceneUpdate(int cmd, char* result);
extern int __cdecl cm_ExModifyHealth(int cmd);
extern int __cdecl cm_ExModifyStamina(int cmd);
extern int __cdecl cm_ExSimCommand(void* cmd, char* result);
extern int __cdecl cm_ExModifyStat(int* cmd);
extern int __cdecl cm_ExAllocWarEvent(int cmd, char* result);
extern int __cdecl cm_DispatchProduction(int cmd, char* result);
extern int __cdecl cm_DispatchMoveSlot(void* cmd, char* result_buf);
extern int __cdecl cm_ExAllocGraveyardWorker(int cmd, char* result);
extern int __cdecl cm_ExAllocAlchemist(int cmd, char* result);
extern int __cdecl cm_ExSimSpecialAction(int cmd, char* result);

// GLOBAL: SERVER 0x1002c3f8
command_fn g_dispatch_table[106] = {
    (command_fn) cm_ChkCommandType, (command_fn) cm_MarkAndReturn, (command_fn) cm_RejectCommand, (command_fn) cm_ChkCommandType, (command_fn) cm_MarkAndReturn, (command_fn) cm_ChkCommandType, (command_fn) cm_ChkCommandType, (command_fn) cm_ChkCommandType, (command_fn) cm_MarkAndReturn, (command_fn) cm_MarkAndReturn, (command_fn) cm_ExAllocRaum, (command_fn) cm_ExAllocSpieler, (command_fn) cm_ExAllocClientSpieler, (command_fn) cm_ExChangePlayerIdentity, (command_fn) cm_ExFree, (command_fn) cm_ExTransferCurrency,
    (command_fn) cm_ExTransferCurrencyNoKill, (command_fn) cm_ExSellObjekt, (command_fn) cm_ExProdObjekt, (command_fn) cm_ExMoveObjekt, (command_fn) cm_ExClearLagerslot, (command_fn) cm_ExAllocObjekt, (command_fn) cm_ExChangeAttribute, (command_fn) cm_ExSetAttribute, (command_fn) cm_ExChangeDesire, (command_fn) cm_ExChangeBits, (command_fn) cm_ExChangeFloat, (command_fn) cm_ExCopyEntityData, (command_fn) cm_ChainAssignId, (command_fn) cm_ChainNoop, (command_fn) cm_ChainNoop, (command_fn) cm_ChainNoop,
    (command_fn) cm_ExSetSyncFlags, (command_fn) cm_ExKillSpieler, (command_fn) cm_AssignSequenceCounter, (command_fn) cm_ChainNoop, (command_fn) cm_ChainNoop, (command_fn) cm_ChainNoop, (command_fn) cm_ChainNoop, (command_fn) cm_AssignEntityId, (command_fn) cm_ChainNoop, (command_fn) cm_ChainNoop, (command_fn) cm_ChainNoop, (command_fn) cm_ExRemoveLinkedObject, (command_fn) cm_ChainRecordLookup, (command_fn) cm_ExAllocThemaPredigt, (command_fn) cm_ChainNoop, (command_fn) cm_ChainNoop,
    (command_fn) cm_ChainNoop, (command_fn) cm_ChainNoop, (command_fn) cm_ChainNoop, (command_fn) cm_ChainNoop, (command_fn) cm_ChainNoop, (command_fn) cm_ChainNoop, (command_fn) cm_ChainNoop, (command_fn) cm_ChainNoop, (command_fn) cm_ExSetGebBesitzer, (command_fn) cm_ExSetWohnsitz, (command_fn) cm_ExSetGebUpgrade, (command_fn) cm_ExDestroyBuilding, (command_fn) cm_ChainNoop, (command_fn) cm_ExEmployWorker, (command_fn) cm_ChainNoop, (command_fn) cm_ChainNoop,
    (command_fn) cm_ChainNoop, (command_fn) cm_ChainNoop, (command_fn) cm_ChainNoop, (command_fn) cm_ChainNoop, (command_fn) cm_ExAssignOffice, (command_fn) cm_ExExecuteOffice, (command_fn) cm_ChainNoop, (command_fn) cm_ChainNoop, (command_fn) cm_ChainNoop, (command_fn) cm_ExCreateCitizen, (command_fn) cm_ExKillTransporter, (command_fn) cm_ExCondWrite, (command_fn) cm_ExCreateGeb, (command_fn) cm_ExCondWrite, (command_fn) cm_ExCondWrite, (command_fn) cm_ExCondWrite,
    (command_fn) cm_InitDefaultResponse, (command_fn) cm_InitDefaultResponse, (command_fn) cm_InitDefaultResponse, (command_fn) cm_ExElectionOrTrade, (command_fn) cm_ExJoinLeaveElection, (command_fn) cm_InitDefaultResponse, (command_fn) cm_ExCondWrite2, (command_fn) cm_ChkEntityLookup, (command_fn) cm_ChainNoop, (command_fn) cm_ExCutsceneUpdate, (command_fn) cm_ExModifyHealth, (command_fn) cm_ExModifyStamina, (command_fn) cm_ExSimCommand, (command_fn) cm_ExModifyStat, (command_fn) cm_ExAllocWarEvent, (command_fn) cm_ChainNoop,
    (command_fn) cm_DispatchProduction, (command_fn) cm_DispatchMoveSlot, (command_fn) cm_ExAllocGraveyardWorker, (command_fn) cm_ExAllocAlchemist, (command_fn) cm_ExSimSpecialAction, (command_fn) cm_ChainNoop, (command_fn) cm_ChainNoop, (command_fn) cm_ChainNoop, (command_fn) cm_ChainNoop, (command_fn) cm_ChainNoop,
};

// GLOBAL: SERVER 0x1002c5a0
dispatch_fn g_chain_handler_table[106] = {
    (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChkMoveCredits,
    (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChkSellObjekt, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChkChangeAttribute, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChkChangeBits, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop,
    (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop,
    (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChkSetGebBesitzer, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop,
    (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChkOfficeCandidate, (dispatch_fn) cm_ValidateGeneric, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop,
    (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChkElectionOrTrade, (dispatch_fn) cm_ChkJoinLeaveElection, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChkCutsceneReady, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop,
    (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop, (dispatch_fn) cm_ChainNoop,
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
		return ((int*) (int) (g_connections + 0x264200))[i * 9];
	}
	if (type == -3) {
		byte_value = (unsigned char) p[3];
		i = byte_value << 4;
		i += byte_value;
		i <<= 8;
		i += byte_value;
		i <<= 4;
		i += byte_value;
		return ((int*) (int) (g_connections + 0x264204))[i * 9];
	}
	if (type == -4) {
		byte_value = (unsigned char) p[3];
		i = byte_value << 4;
		i += byte_value;
		i <<= 8;
		i += byte_value;
		i <<= 4;
		i += byte_value;
		return ((int*) (int) (g_connections + 0x264208))[i * 9];
	}
	return type;
}

/* Resolves a field value by type from a command packet.
 * Performs entity ID resolution through the global entity
 * tables. Returns the resolved value or 0 on failure. */
