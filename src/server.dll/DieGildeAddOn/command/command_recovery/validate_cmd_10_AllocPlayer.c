/* BLOCKER_DELTA: 326
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
typedef unsigned char uchar;

extern int g_timestamp_0b6c;
extern char g_player_slot_0[];
extern char g_static_entity_table_358a0[];

extern int __cdecl rand(void);
extern void __cdecl crt_thread_set_alt(int);
extern uint __cdecl CreateEntityFromParents(uint, int, int, ushort, int, uint, uint, uint);
extern void __cdecl LogMessageInternal(const char*, uint, const char*, int);
extern short* __cdecl GetEntityTableEntry(char*);
extern int __cdecl LookupEntityRecordById(int);
extern char* __cdecl strncpy(char*, const char*, unsigned int);

extern char s_D__Develop_DieGildeAddOn_command_1002c748[];
extern char s_ClientSpieler_erzeugt_1002cbbc[];
extern char s_gm_AllocSpieler___failed_1002cbd4[];

/* FUNCTION: SERVER 0x1000d570 */
/* STATUS: STUB */
/* ORIGIN: GAME */
/* SIZE: 361 */
/* CFLAGS: /O2 /Gd */
/* SYMBOL: _validate_cmd_10_AllocPlayer */
int __cdecl validate_cmd_10_AllocPlayer(int param_1, char* param_2)
{
	int iVar1;
	uint uVar2;
	short* psVar3;
	int iVar4;
	char* entity_base;

	*(int*) (param_1 + 0x10) = g_timestamp_0b6c;
	iVar1 = rand();
	*(int*) (param_1 + 0x45) = iVar1;
	crt_thread_set_alt(*(int*) (param_1 + 0x22));
	uVar2 = CreateEntityFromParents(
		7 - (uint)(param_2 != (char*)0x0),
		*(int*) (param_1 + 0x14),
		*(int*) (param_1 + 0x18),
		*(ushort*) (param_1 + 0x1c),
		0,
		(uint)*(uchar*) (param_1 + 0x1e),
		0,
		(uint)*(uchar*) (param_1 + 0x23)
	);
	uVar2 = uVar2 & 0xffff;
	if (uVar2 == 0xffff) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x290f, s_gm_AllocSpieler___failed_1002cbd4, 1);
		return 1;
	}
	LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x2917, s_ClientSpieler_erzeugt_1002cbbc, 1);
	*(int*) (g_player_slot_0 + (uint)*(uchar*) (param_1 + 3) * 0x264264 + 0x2641f8) =
		*(int*) (g_static_entity_table_358a0 + uVar2 * 0x21c + 4);
	strncpy(g_static_entity_table_358a0 + uVar2 * 0x21c + 0x30, (char*) param_1 + 0x25, 0x10);
	entity_base = g_static_entity_table_358a0 + uVar2 * 0x21c;
	psVar3 = GetEntityTableEntry(entity_base);
	if (psVar3 != (short*) 0) {
		*psVar3 = *(short*) (g_static_entity_table_358a0 + uVar2 * 0x21c + 0x50);
		strncpy((char*) psVar3 + 2, (char*) param_1 + 0x35, 0x10);
		strncpy(g_static_entity_table_358a0 + uVar2 * 0x21c + 0x40, (char*) param_1 + 0x35, 0x10);
		iVar4 = LookupEntityRecordById(*(int*) (g_static_entity_table_358a0 + uVar2 * 0x21c + 0x60));
		if (iVar4 != 0) {
			strncpy((char*) (iVar4 + 0x40), (char*) param_1 + 0x35, 0x10);
		}
	}
	*(int*) (g_static_entity_table_358a0 + uVar2 * 0x21c + 0x54) = *(int*) (param_1 + 0x1f);
	*(char*) (g_static_entity_table_358a0 + uVar2 * 0x21c + 0x0c) = *(char*) (param_1 + 0x24);
	if (param_2 != (char*) 0) {
		*param_2 = '\x01';
		param_2[1] = '\x01';
		*(char**) (param_2 + 6) = entity_base;
	}
	return 0;
}
