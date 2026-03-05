/* Ghidra decompilation reference:
 */

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

extern int g_timestamp_0b6c;
extern char g_player_slot_0[];

extern int __cdecl rand(void);
extern void __cdecl crt_thread_set_alt(int);
extern ushort __cdecl CreateEntityFromParents(uint, int, int, ushort, int, uint, uint, uint);
extern void __cdecl LogMessageInternal(const char*, uint, const char*, int);
extern short* __cdecl GetEntityTableEntry(char*);
extern int __cdecl LookupEntityRecordById(int);
extern char* __cdecl strncpy(char*, const char*, unsigned int);

extern char s_D__Develop_DieGildeAddOn_command_1002c748[];
extern char s_ClientSpieler_erzeugt_1002cbbc[];
extern char s_gm_AllocSpieler___failed_1002cbd4[];

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 361
// CFLAGS: /O2 /Gd
// BLOCKER: Register allocation/instruction scheduling difference in CreateEntityFromParents argument setup; target evaluates param_2 boolean first (neg/sbb in eax) then pushes args in different register order. Same-size, semantically equivalent.
// SYMBOL: _validate_cmd_10_AllocPlayer
// FUNCTION: SERVER 0x1000d570
int __cdecl validate_cmd_10_AllocPlayer(int param_1, char* param_2)
{
	ushort sVar1;
	uint uVar2;
	int iVar1;
	int iVar4;
	short* psVar3;
	char* entity_base;

	*(int*) (param_1 + 0x10) = g_timestamp_0b6c;
	iVar1 = rand();
	*(int*) (param_1 + 0x45) = iVar1;
	crt_thread_set_alt(*(int*) (param_1 + 0x22));
	sVar1 = (ushort) CreateEntityFromParents(
		param_2 ? 6 : 7,
		*(int*) (param_1 + 0x14),
		*(int*) (param_1 + 0x18),
		*(ushort*) (param_1 + 0x1c),
		0,
		(uint)*(uchar*) (param_1 + 0x1e),
		0,
		(uint)*(uchar*) (param_1 + 0x23)
	);
	uVar2 = sVar1;
	if (uVar2 == 0xffff) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x290f, s_gm_AllocSpieler___failed_1002cbd4, 1);
		return 1;
	}
	LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x2917, s_ClientSpieler_erzeugt_1002cbbc, 1);
	iVar1 = uVar2 * 0x21c;
	*(int*) (g_player_slot_0 + (uint)*(uchar*) (param_1 + 3) * 0x264264 + 0x2641f8) =
		*(int*) (iVar1 + 0x100358a4);
	strncpy((char*) (iVar1 + 0x100358d0), (char*) param_1 + 0x25, 0x10);
	entity_base = (char*) (iVar1 + 0x100358a0);
	psVar3 = GetEntityTableEntry(entity_base);
	if (psVar3 != (short*) 0) {
		*psVar3 = *(short*) (iVar1 + 0x100358f0);
		strncpy((char*) psVar3 + 2, (char*) param_1 + 0x35, 0x10);
		strncpy((char*) (iVar1 + 0x100358e0), (char*) param_1 + 0x35, 0x10);
		iVar4 = LookupEntityRecordById(*(int*) (iVar1 + 0x10035900));
		if (iVar4 != 0) {
			strncpy((char*) (iVar4 + 0x40), (char*) param_1 + 0x35, 0x10);
		}
	}
	*(int*) (iVar1 + 0x100358f4) = *(int*) (param_1 + 0x1f);
	*(char*) (iVar1 + 0x100358ac) = *(char*) (param_1 + 0x24);
	if (param_2 != (char*) 0) {
		*param_2 = '\x01';
		param_2[1] = '\x01';
		*(char**) (param_2 + 6) = entity_base;
	}
	return 0;
}
