// FUNCTION: SERVER 0x1000cbd0
// STATUS: STUB
// BLOCKER: comparison direction swap, instruction folding (lea vs mov), jump condition swap, zero-extend pattern (xor vs mov)
// ORIGIN: GAME
// SIZE: 517
// CFLAGS: /O2 /Gd
// SYMBOL: _CheckSellObject

/*
// BLOCKER_DELTA: 500
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 517B
 *    CFlags: 
 *    Symbol: _CheckSellObject
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl CheckSellObject(char *cmd)
 * 
 * {
 *   short sVar1;
 *   int iVar2;
 *   int *piVar3;
 *   ushort *puVar4;
 *   undefined4 extraout_EDX;
 *   undefined4 extraout_EDX_00;
 *   undefined4 extraout_EDX_01;
 *   undefined4 uVar5;
 *   uint line;
 *   char *pcVar6;
 *   short *local_c;
 *   void *local_8;
 *   void *local_4;
 *   
 *   pcVar6 = cmd;
 *   if (*(int *)(cmd + 0x14) != -1) {
 *     iVar2 = get_field_by_type(cmd,*(int *)(cmd + 0x14));
 *     *(int *)(pcVar6 + 0x14) = iVar2;
 *     iVar2 = ResolveEntityById(&local_8,&cmd,&local_c,iVar2);
 *     if (iVar2 == 0) {
 *       pcVar6 = s_cm_ChkSellObjekt___Invalid__quel_1002c8dc;
 *       line = 0x236b;
 *       goto LAB_1000cdb7;
 *     }
 *     if (local_8 == (void *)0x0) {
 *       if (cmd == (char *)0x0) {
 *         piVar3 = (int *)(local_c + 0xbc);
 *       }
 *       else {
 *         piVar3 = (int *)(cmd + 0x14);
 *       }
 *     }
 *     else {
 *       piVar3 = (int *)((int)local_8 + 0x5d);
 *     }
 *     puVar4 = StartEntityQuery(*piVar3,1,0,(uint)*(ushort *)(pcVar6 + 0x18));
 *     if (puVar4 == (ushort *)0x0) {
 *       pcVar6 = s_cm_ChkSellObjekt___No_Objekts_at_1002c8b4;
 *       line = 0x2383;
 */

typedef unsigned int uint;
typedef unsigned short ushort;

extern char g_static_entity_table_358a0[];

extern int __cdecl get_field_by_type(char*, int);
extern int __cdecl ResolveEntityById(void**, void**, void**, int);
extern void* __cdecl StartEntityQuery(int, int, int, uint);
extern int __cdecl CheckInventoryCapacity(char*, uint, int);
extern int __cdecl gm_KannObjektHergestellt(int, uint, int);
extern short* __cdecl ResolveParentEntity(short*);
extern void __cdecl LogMessageInternal(const char*, uint, const char*, int);

extern char s_D__Develop_DieGildeAddOn_command_1002c748[];
extern char s_cm_ChkSellObjekt___Invalid__quel_1002c8dc[];
extern char s_cm_ChkSellObjekt___No_Objekts_at_1002c8b4[];
extern char s_cm_ChkSellObjekt___Not_enough_Ob_1002c884[];
extern char s_cm_ChkSellObjekt___Invalid__ziel_1002c854[];
extern char s_cm_ChkSellObjekt___Inventory_vol_1002c810[];
extern char s_cm_ChkSellObjekt___Lager_voll_1002c834[];

int __cdecl CheckSellObject(char* cmd)
{
	short sVar1;
	int iVar2;
	int* piVar3;
	ushort* puVar4;
	uint line;
	char* pcVar6;
	short* local_c;
	void* local_8;
	void* local_4;

	pcVar6 = cmd;
	if (*(int*) (cmd + 0x14) != -1) {
		iVar2 = get_field_by_type(cmd, *(int*) (cmd + 0x14));
		*(int*) (pcVar6 + 0x14) = iVar2;
		iVar2 = ResolveEntityById(&local_8, (void**) &cmd, (void**) &local_c, iVar2);
		if (iVar2 == 0) {
			pcVar6 = s_cm_ChkSellObjekt___Invalid__quel_1002c8dc;
			line = 0x236b;
			goto LAB_1000cdb7;
		}
		if (local_8 == (void*) 0) {
			if (cmd == (char*) 0) {
				piVar3 = (int*) (local_c + 0xbc);
			}
			else {
				piVar3 = (int*) (cmd + 0x14);
			}
		}
		else {
			piVar3 = (int*) ((int) local_8 + 0x5d);
		}
		puVar4 = (ushort*) StartEntityQuery(*piVar3, 1, 0, (uint) * (ushort*) (pcVar6 + 0x18));
		if (puVar4 == (ushort*) 0) {
			pcVar6 = s_cm_ChkSellObjekt___No_Objekts_at_1002c8b4;
			line = 0x2383;
			goto LAB_1000cdb7;
		}
		if (*(int*) (puVar4 + 7) < *(int*) (pcVar6 + 0x1f)) {
			pcVar6 = s_cm_ChkSellObjekt___Not_enough_Ob_1002c884;
			line = 0x238f;
			goto LAB_1000cdb7;
		}
	}
	if (*(int*) (pcVar6 + 0x10) != -1) {
		iVar2 = get_field_by_type(pcVar6, *(int*) (pcVar6 + 0x10));
		*(int*) (pcVar6 + 0x10) = iVar2;
		iVar2 = ResolveEntityById(&local_4, (void**) &cmd, (void**) &local_c, iVar2);
		if (iVar2 == 0) {
			pcVar6 = s_cm_ChkSellObjekt___Invalid__ziel_1002c854;
			line = 0x23ab;
			goto LAB_1000cdb7;
		}
		if (local_4 == (void*) 0) {
			if (cmd == (char*) 0) {
				iVar2 = CheckInventoryCapacity(
					(char*) local_c,
					(uint) * (ushort*) (pcVar6 + 0x18),
					*(int*) (pcVar6 + 0x1f)
				);
				if (iVar2 < *(int*) (pcVar6 + 0x1f)) {
					pcVar6 = s_cm_ChkSellObjekt___Inventory_vol_1002c810;
					line = 0x23e3;
					goto LAB_1000cdb7;
				}
			}
			else {
				sVar1 = *(short*) cmd;
				if ((((sVar1 == 0x2a) || (sVar1 == 0x116)) || (sVar1 == 0x1dd)) &&
					((iVar2 = gm_KannObjektHergestellt(
						  (int) cmd,
						  (uint) * (ushort*) (pcVar6 + 0x18),
						  *(int*) (pcVar6 + 0x1f)
					  ),
					  iVar2 < *(int*) (pcVar6 + 0x1f)))) {
					pcVar6 = s_cm_ChkSellObjekt___Lager_voll_1002c834;
					line = 0x23cd;
					goto LAB_1000cdb7;
				}
				local_c = ResolveParentEntity((short*) cmd);
			}
		}
		else {
			if (*(ushort*) ((int) local_4 + 0x27) == 0xffff) {
				local_c = (short*) 0;
			}
			else {
				local_c = (short*) (g_static_entity_table_358a0 + (uint) * (ushort*) ((int) local_4 + 0x27) * 0x21c);
			}
		}
	}
	return 0;
LAB_1000cdb7:
	LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, line, pcVar6, 1);
	return 1;
}
