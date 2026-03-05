// FUNCTION: SERVER 0x1000e8d0
// STATUS: STUB
// BLOCKER: instruction folding (lea vs mov), loop rotation / branch layout, stack frame choice (push vs sub esp), zero-extend pattern (xor vs mov)
// ORIGIN: GAME
// SIZE: 240
// CFLAGS: /O2 /Gd
// SYMBOL: _ExWriteEntityFields

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

/*
// BLOCKER_DELTA: 225
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 239B
 *    CFlags: 
 *    Symbol: _ExWriteEntityFields
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl ExWriteEntityFields(int param_1,char *param_2)
 * 
 * {
 *   char cVar1;
 *   undefined2 uVar2;
 *   undefined4 uVar3;
 *   int iVar4;
 *   int iVar5;
 *   ushort *puVar6;
 *   char *pcVar7;
 *   char *pcVar8;
 *   uint uVar9;
 *   void *pvStack_8;
 *   void *pvStack_4;
 *   
 *   iVar4 = param_1;
 *   iVar5 = get_field_by_type((char *)param_1,*(int *)(param_1 + 0x10));
 *   *(int *)(iVar4 + 0x10) = iVar5;
 *   iVar5 = ResolveEntityById((void **)&param_1,&pvStack_8,&pvStack_4,iVar5);
 *   if (iVar5 == 0) {
 *     LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x32ed,
 *                        s_cm_ExSetAttribute___Invalid_Id_1002d0d4,1);
 *     return 1;
 *   }
 *   if ((param_1 == 0) && (param_1 = (int)pvStack_8, pvStack_8 == (void *)0x0)) {
 *     param_1 = (int)pvStack_4;
 *   }
 *   uVar9 = 0;
 *   pcVar7 = (char *)(iVar4 + 0x15);
 *   if (*(char *)(iVar4 + 0x14) != '\0') {
 *     do {
 *       cVar1 = *pcVar7;
 *       iVar5 = (int)pcVar7[1];
 *       puVar6 = (ushort *)(pcVar7 + 2);
 *       pcVar7 = pcVar7 + 4;
 *       pcVar8 = (char *)((uint)*puVar6 + param_1);
 *       if (cVar1 == '\x01') {
 *         for (; iVar5 != 0; iVar5 = iVar5 + -1) {
 *           *pcVar8 = *pcVar7;
 *           pcVar8 = pcVar8 + 1;
 *           pcVar7 = pcVar7 + 1;
 *         }
 */

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

extern int __cdecl get_field_by_type(char*, int);
extern int __cdecl ResolveEntityById(void**, void**, void**, int);
extern void __cdecl LogMessageInternal(const char*, uint, const char*, int);

extern char s_D__Develop_DieGildeAddOn_command_1002c748[];
extern char s_cm_ExSetAttribute___Invalid_Id_1002d0d4[];

int __cdecl ExWriteEntityFields(int param_1, char* param_2)
{
	char cVar1;
	short uVar2;
	int uVar3;
	int iVar4;
	int iVar5;
	ushort* puVar6;
	char* pcVar7;
	char* pcVar8;
	uint uVar9;
	void* pvStack_8;
	void* pvStack_4;

	iVar4 = param_1;
	iVar5 = get_field_by_type((char*) param_1, *(int*) (param_1 + 0x10));
	*(int*) (iVar4 + 0x10) = iVar5;
	iVar5 = ResolveEntityById((void**) &param_1, &pvStack_8, &pvStack_4, iVar5);
	if (iVar5 == 0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x32ed,
			s_cm_ExSetAttribute___Invalid_Id_1002d0d4,
			1
		);
		return 1;
	}
	if ((param_1 == 0) && (param_1 = (int) pvStack_8, pvStack_8 == (void*) 0)) {
		param_1 = (int) pvStack_4;
	}
	uVar9 = 0;
	pcVar7 = (char*) (iVar4 + 0x15);
	if (*(char*) (iVar4 + 0x14) != '\0') {
		do {
			cVar1 = *pcVar7;
			iVar5 = (int) pcVar7[1];
			puVar6 = (ushort*) (pcVar7 + 2);
			pcVar7 = pcVar7 + 4;
			pcVar8 = (char*) ((uint) *puVar6 + param_1);
			if (cVar1 == '\x01') {
				for (; iVar5 != 0; iVar5 = iVar5 + -1) {
					*pcVar8 = *pcVar7;
					pcVar8 = pcVar8 + 1;
					pcVar7 = pcVar7 + 1;
				}
			}
			else if (cVar1 == '\x02') {
				for (; iVar5 != 0; iVar5 = iVar5 + -1) {
					uVar2 = *(short*) pcVar7;
					pcVar7 = pcVar7 + 2;
					*(short*) pcVar8 = uVar2;
					pcVar8 = pcVar8 + 2;
				}
			}
			else if (cVar1 == '\x04') {
				for (; iVar5 != 0; iVar5 = iVar5 + -1) {
					uVar3 = *(int*) pcVar7;
					pcVar7 = pcVar7 + 4;
					*(int*) pcVar8 = uVar3;
					pcVar8 = pcVar8 + 4;
				}
			}
			uVar9 = uVar9 + 1;
		} while (uVar9 < *(uchar*) (iVar4 + 0x14));
	}
	if (param_2 != (char*) 0) {
		*param_2 = '\x01';
	}
	return 0;
}
