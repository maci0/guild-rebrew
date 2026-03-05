// FUNCTION: SERVER 0x1000e7d0
// STATUS: STUB
// BLOCKER: loop rotation / branch layout, zero-extend pattern (xor vs mov)
// ORIGIN: GAME
// SIZE: 242
// CFLAGS: /O2 /Gd
// SYMBOL: _ExAccumulateEntityFields
// BLOCKER_DELTA: 209

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

/*
// BLOCKER_DELTA: 210
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 242B
 *    CFlags: 
 *    Symbol: _ExAccumulateEntityFields
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl ExAccumulateEntityFields(int param_1,char *param_2)
 * 
 * {
 *   char cVar1;
 *   int iVar2;
 *   int iVar3;
 *   int iVar4;
 *   ushort *puVar5;
 *   int *piVar6;
 *   int *piVar7;
 *   uint uVar8;
 *   void *pvStack_8;
 *   void *pvStack_4;
 *   
 *   iVar2 = param_1;
 *   iVar3 = get_field_by_type((char *)param_1,*(int *)(param_1 + 0x10));
 *   iVar4 = ResolveEntityById((void **)&param_1,&pvStack_8,&pvStack_4,iVar3);
 *   if (iVar4 == 0) {
 *     LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x31f7,
 *                        s_cm_ExChangeAttribute___Invalid_I_1002d0b0,1);
 *     return 1;
 *   }
 *   *(int *)(iVar2 + 0x10) = iVar3;
 *   if ((param_1 == 0) && (param_1 = (int)pvStack_8, pvStack_8 == (void *)0x0)) {
 *     param_1 = (int)pvStack_4;
 *   }
 *   uVar8 = 0;
 *   piVar6 = (int *)(iVar2 + 0x15);
 *   if (*(char *)(iVar2 + 0x14) != '\0') {
 *     do {
 *       cVar1 = (char)*piVar6;
 *       iVar3 = (int)*(char *)((int)piVar6 + 1);
 *       puVar5 = (ushort *)((int)piVar6 + 2);
 *       piVar6 = piVar6 + 1;
 *       piVar7 = (int *)((uint)*puVar5 + param_1);
 *       if (cVar1 == '\x01') {
 *         for (; iVar3 != 0; iVar3 = iVar3 + -1) {
 *           *(char *)piVar7 = (char)*piVar7 + (char)*piVar6;
 *           piVar6 = (int *)((int)piVar6 + 1);
 *           piVar7 = (int *)((int)piVar7 + 1);
 *         }
 *       }
 */

typedef unsigned int uint;
typedef unsigned short ushort;

extern int __cdecl get_field_by_type(char*, int);
extern int __cdecl ResolveEntityById(void**, void**, void**, int);
extern void __cdecl LogMessageInternal(const char*, uint, const char*, int);

extern char s_D__Develop_DieGildeAddOn_command_1002c748[];
extern char s_cm_ExChangeAttribute___Invalid_I_1002d0b0[];

int __cdecl ExAccumulateEntityFields(int param_1, char *param_2)
{
	char cVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	ushort *puVar5;
	int *piVar6;
	int *piVar7;
	uint uVar8;
	void *pvStack_8;
	void *pvStack_4;

	iVar2 = param_1;
	iVar3 = get_field_by_type((char *)param_1, *(int *)(param_1 + 0x10));
	iVar4 = ResolveEntityById((void **)&param_1, &pvStack_8, &pvStack_4, iVar3);
	if (iVar4 == 0) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x31f7,
			s_cm_ExChangeAttribute___Invalid_I_1002d0b0, 1);
		return 1;
	}
	*(int *)(iVar2 + 0x10) = iVar3;
	if ((param_1 == 0) && (param_1 = (int)pvStack_8, pvStack_8 == (void *)0x0)) {
		param_1 = (int)pvStack_4;
	}
	uVar8 = 0;
	piVar6 = (int *)(iVar2 + 0x15);
	if (*(char *)(iVar2 + 0x14) != '\0') {
		do {
			cVar1 = (char)*piVar6;
			iVar3 = (int)*(char *)((int)piVar6 + 1);
			puVar5 = (ushort *)((int)piVar6 + 2);
			piVar6 = piVar6 + 1;
			piVar7 = (int *)((uint)*puVar5 + param_1);
			if (cVar1 == '\x04') {
				for (; iVar3 != 0; iVar3 = iVar3 + -1) {
					*piVar7 = *piVar7 + *(int *)piVar6;
					piVar6 = (int *)((int)piVar6 + 4);
					piVar7 = piVar7 + 1;
				}
			} else if (cVar1 == '\x02') {
				for (; iVar3 != 0; iVar3 = iVar3 + -1) {
					*(ushort *)piVar7 = (ushort)(*(ushort *)piVar7 + *(ushort *)piVar6);
					piVar6 = (int *)((int)piVar6 + 2);
					piVar7 = (int *)((int)piVar7 + 2);
				}
			} else if (cVar1 == '\x01') {
				for (; iVar3 != 0; iVar3 = iVar3 + -1) {
					*(char *)piVar7 = (char)*(char *)piVar7 + (char)*(char *)piVar6;
					piVar6 = (int *)((int)piVar6 + 1);
					piVar7 = (int *)((int)piVar7 + 1);
				}
			}
			uVar8 = uVar8 + 1;
		} while (uVar8 < (uint)*(unsigned char *)(iVar2 + 0x14));
	}
	if (param_2 != (char *)0) {
		*param_2 = '\x01';
	}
	return 0;
}
