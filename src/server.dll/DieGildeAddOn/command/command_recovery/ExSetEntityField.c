// FUNCTION: SERVER 0x1000eb70
// STATUS: STUB
// BLOCKER: instruction folding (lea vs mov), stack frame choice (push vs sub esp)
// ORIGIN: GAME
// SIZE: 144
// CFLAGS: /O2 /Gd
// SYMBOL: _ExSetEntityField

/*
// BLOCKER_DELTA: 126
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 135B
 *    CFlags: 
 *    Symbol: _ExSetEntityField
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl ExSetEntityField(int param_1,char *param_2)
 * 
 * {
 *   int iVar1;
 *   int iVar2;
 *   void *pvStack_8;
 *   void *pvStack_4;
 *   
 *   iVar1 = param_1;
 *   iVar2 = get_field_by_type((char *)param_1,*(int *)(param_1 + 0x10));
 *   *(int *)(iVar1 + 0x10) = iVar2;
 *   iVar2 = ResolveEntityById(&pvStack_4,&pvStack_8,(void **)&param_1,iVar2);
 *   if (iVar2 == 0) {
 *     LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x347f,
 *                        s_cm_ExChangeFloat___Invalid_Id_1002d134,1);
 *     return 1;
 *   }
 *   if ((param_1 == 0) && (param_1 = (int)pvStack_8, pvStack_8 == (void *)0x0)) {
 *     param_1 = (int)pvStack_4;
 *   }
 *   *(float *)(param_1 + *(int *)(iVar1 + 0x14)) =
 *        *(float *)(iVar1 + 0x18) + *(float *)(param_1 + *(int *)(iVar1 + 0x14));
 *   if (param_2 != (char *)0x0) {
 *     *param_2 = '\x01';
 *   }
 *   return 0;
 * }
 */

extern int __cdecl get_field_by_type(char*, int);
extern int __cdecl ResolveEntityById(void**, void**, void**, int);
extern void __cdecl LogMessageInternal(char*, int, char*, int);

extern char s_D__Develop_DieGildeAddOn_command_1002c748[];
extern char s_cm_ExChangeFloat___Invalid_Id_1002d134[];

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wpointer-to-int-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

int __cdecl ExSetEntityField(int param_1, char* param_2)
{
	int iVar2;
	int iVar3;
	int iVar4;
	void* pvStack_8;
	void* pvStack_4;

	iVar4 = param_1;
	iVar2 = get_field_by_type((char*) iVar4, *(int*) (iVar4 + 0x10));
	*(int*) (iVar4 + 0x10) = iVar2;
	iVar2 = ResolveEntityById(&pvStack_4, &pvStack_8, (void**) &param_1, iVar2);
	if (iVar2 == 0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x347f,
			s_cm_ExChangeFloat___Invalid_Id_1002d134,
			1
		);
		return 1;
	}
	if (param_1 == 0) {
		param_1 = (int) pvStack_8;
		if (param_1 == 0) {
			param_1 = (int) pvStack_4;
		}
	}
	iVar3 = *(int*) (iVar4 + 0x14);
	*(float*) (param_1 + iVar3) = *(float*) (iVar4 + 0x18) + *(float*) (param_1 + iVar3);
	if (param_2 != (char*) 0) {
		*param_2 = '\x01';
	}
	return 0;
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif
