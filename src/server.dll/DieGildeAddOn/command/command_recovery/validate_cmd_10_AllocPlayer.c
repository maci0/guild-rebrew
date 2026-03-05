// FUNCTION: SERVER 0x1000d570
// STATUS: STUB
// BLOCKER: instruction folding (lea vs mov), zero-extend pattern (xor vs mov)
// ORIGIN: GAME
// SIZE: 361
// CFLAGS: /O2 /Gd
// SYMBOL: _validate_cmd_10_AllocPlayer

/*
// BLOCKER_DELTA: 326
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 361B
 *    CFlags: 
 *    Symbol: _validate_cmd_10_AllocPlayer
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl validate_cmd_10_AllocPlayer(int param_1,char *param_2)
 * 
 * {
 *   int iVar1;
 *   uint uVar2;
 *   short *psVar3;
 *   int iVar4;
 *   
 *                     / * Command Handler 0x10. Allocates a new player character in the game world.
 *                        Assigns the next global entity ID to the payload. Calls FUN_10018850 to
 *                        create the entity, then populates string data (player name, character name)
 *                        into the static array slots. Returns 0 on success. * /
 *   *(undefined4 *)(param_1 + 0x10) = g_timestamp_0b6c;
 *   iVar1 = rand();
 *   *(int *)(param_1 + 0x45) = iVar1;
 *   crt_thread_set_alt(*(int *)(param_1 + 0x22));
 *   uVar2 = CreateEntityFromParents
 *                     (7 - (uint)(param_2 != (char *)0x0),*(int *)(param_1 + 0x14),
 *                      *(int *)(param_1 + 0x18),(uint)*(ushort *)(param_1 + 0x1c),0);
 *   uVar2 = uVar2 & 0xffff;
 *   if (uVar2 != 0xffff) {
 *     LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x2917,
 *                        s_ClientSpieler_erzeugt_1002cbbc,1);
 *     iVar1 = uVar2 * 0x21c;
 *     *(undefined4 *)(g_player_slot_0[*(byte *)(param_1 + 3)].data + 0x2641f8) =
 *          (&g_static_entity0_entity_id)[uVar2 * 0x87];
 *     strncpy();
 *     psVar3 = GetEntityTableEntry((char *)(&g_static_entity_table_358a0 + uVar2 * 0x10e));
 *     if (psVar3 != (short *)0x0) {
 *       *psVar3 = *(short *)(&g_static_entity0_lineage + iVar1);
 *       strncpy();
 *       strncpy();
 *       iVar4 = LookupEntityRecordById((&g_static_entity0_field_60)[uVar2 * 0x87]);
 *       if (iVar4 != 0) {
 *         strncpy();
 *       }
 *     }
 *     *(undefined4 *)(&g_static_entity0_field_54 + iVar1) = *(undefined4 *)(param_1 + 0x1f);
 *     (&g_static_entity0_pos_x)[iVar1] = *(undefined1 *)(param_1 + 0x24);
 *     if (param_2 != (char *)0x0) {
 *       *param_2 = '\x01';
 *       param_2[1] = '\x01';
 */

typedef unsigned int uint;
typedef unsigned short ushort;

typedef struct {
	char pad[0x26408];
	int data;
	int flags;
} player_slot;

extern int g_timestamp_0b6c;
extern player_slot g_player_slot_0[];
extern int g_static_entity0_entity_id[];
extern char g_static_entity_table_358a0[];
extern short g_static_entity0_lineage[];
extern int g_static_entity0_field_54[];
extern char g_static_entity0_pos_x[];
extern int g_static_entity0_field_60[];

extern int __cdecl rand(void);
extern void __cdecl crt_thread_set_alt(int);
extern uint __cdecl CreateEntityFromParents(int, int, int, int, int);
extern void __cdecl LogMessageInternal(const char*, uint, const char*, int);
extern short* __cdecl GetEntityTableEntry(char*);
extern int __cdecl LookupEntityRecordById(int);
extern char* __cdecl strncpy(char*, const char*, unsigned int);

extern char s_D__Develop_DieGildeAddOn_command_1002c748[];
extern char s_ClientSpieler_erzeugt_1002cbbc[];
extern char s_gm_AllocSpieler___failed_1002cbd4[];

int __cdecl validate_cmd_10_AllocPlayer(int param_1, char* param_2)
{
	int iVar1;
	uint uVar2;
	short* psVar3;
	int iVar4;

	*(int*) (param_1 + 0x10) = g_timestamp_0b6c;
	iVar1 = rand();
	*(int*) (param_1 + 0x45) = iVar1;
	crt_thread_set_alt(*(int*) (param_1 + 0x22));
	uVar2 = CreateEntityFromParents(
		7 - (uint) (param_2 != (char*) 0),
		*(int*) (param_1 + 0x14),
		*(int*) (param_1 + 0x18),
		(uint) * (ushort*) (param_1 + 0x1c),
		0
	);
	uVar2 = uVar2 & 0xffff;
	if (uVar2 != 0xffff) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x2917, s_ClientSpieler_erzeugt_1002cbbc, 1);
		*(int*) (g_player_slot_0[*(unsigned char*) (param_1 + 3)].data + 0x2641f8) =
			g_static_entity0_entity_id[uVar2 * 0x87];
		strncpy((char*) (g_static_entity0_entity_id + uVar2 * 0x87), (char*) param_1 + 0x25, 0x10);
		psVar3 = GetEntityTableEntry((char*) (g_static_entity_table_358a0 + uVar2 * 0x21c));
		if (psVar3 != (short*) 0) {
			*psVar3 = g_static_entity0_lineage[uVar2 * 0x87];
			strncpy((char*) psVar3 + 2, (char*) param_1 + 0x35, 0x10);
			strncpy(g_static_entity_table_358a0 + uVar2 * 0x21c + 0x40, (char*) param_1 + 0x35, 0x10);
			iVar4 = LookupEntityRecordById(g_static_entity0_field_60[uVar2 * 0x87]);
			if (iVar4 != 0) {
				strncpy((char*) (iVar4 + 0x40), (char*) param_1 + 0x35, 0x10);
			}
		}
		g_static_entity0_field_54[uVar2 * 0x87] = *(int*) (param_1 + 0x1f);
		g_static_entity0_pos_x[uVar2 * 0x21c] = *(char*) (param_1 + 0x24);
		if (param_2 != (char*) 0) {
			*param_2 = '\x01';
			param_2[1] = '\x01';
			*(char**) (param_2 + 6) = g_static_entity_table_358a0 + uVar2 * 0x21c;
		}
		return 0;
	}
	LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x290f, s_gm_AllocSpieler___failed_1002cbd4, 1);
	return 1;
}
