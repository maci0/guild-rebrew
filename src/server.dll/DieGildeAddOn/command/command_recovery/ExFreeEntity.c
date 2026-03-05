// FUNCTION: SERVER 0x1000d730
// STATUS: STUB
// BLOCKER: instruction folding (lea vs mov), stack frame choice (push vs sub esp), zero-extend pattern (xor vs mov)
// ORIGIN: GAME
// SIZE: 192
// CFLAGS: /O2 /Gd
// SYMBOL: _ExFreeEntity

/*
// BLOCKER_DELTA: 172
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 180B
 *    CFlags: 
 *    Symbol: _ExFreeEntity
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl ExFreeEntity(int param_1,char *param_2)
 * 
 * {
 *   uint uVar1;
 *   int iVar2;
 *   char *msg;
 *   void *pvStack_8;
 *   ushort *puStack_4;
 *   
 *   iVar2 = param_1;
 *   uVar1 = get_field_by_type((char *)param_1,(uint)*(ushort *)(param_1 + 0x10));
 *   *(short *)(iVar2 + 0x10) = (short)uVar1;
 *   iVar2 = ResolveEntityById((void **)&param_1,&pvStack_8,&puStack_4,uVar1 & 0xffff);
 *   if (iVar2 == 0) {
 *     msg = s_Invalid_Id_for_cmdt_FREE_in_cm_E_1002cc5c;
 *     uVar1 = 0x2a09;
 * LAB_1000d7ab:
 *     LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,uVar1,msg,1);
 *     return 1;
 *   }
 *   if (param_1 == 0) {
 *     if (pvStack_8 != (void *)0x0) {
 *       msg = s_cm_ExFree____Can_t_free_Objects_1002cc3c;
 *       uVar1 = 0x2a21;
 *       goto LAB_1000d7ab;
 *     }
 *     DeallocEntity((uint)*puStack_4,1);
 *   }
 *   else {
 *     iVar2 = CleanupBuildingEntity((uchar *)param_1);
 *     if (iVar2 != 0) {
 *       return 1;
 *     }
 *   }
 *   if (param_2 != (char *)0x0) {
 *     *param_2 = '\x01';
 *   }
 *   return 0;
 * }
*/

typedef unsigned char uchar;

extern int __cdecl get_field_by_type(char*, unsigned int);
extern int __cdecl ResolveEntityById(void**, void**, void**, int);
extern int __cdecl CleanupBuildingEntity(uchar*);
extern void __cdecl DeallocEntity(unsigned int, int);
extern void __cdecl LogMessageInternal(char*, unsigned int, char*, int);

extern char s_D__Develop_DieGildeAddOn_command_1002c748[];
extern char s_Invalid_Id_for_cmdt_FREE_in_cm_E_1002cc5c[];
extern char s_cm_ExFree____Can_t_free_Objects_1002cc3c[];

int __cdecl ExFreeEntity(int param_1, char* param_2)
{
	unsigned int field;
	void* local_8;
	unsigned short* local_4;

	field = (unsigned int) get_field_by_type((char*) param_1, (unsigned int) *(unsigned short*) (param_1 + 0x10));
	*(unsigned short*) (param_1 + 0x10) = (unsigned short) field;
	if (ResolveEntityById((void**) &param_1, &local_8, (void**) &local_4, (int) (field & 0xffff)) == 0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x2a09,
			s_Invalid_Id_for_cmdt_FREE_in_cm_E_1002cc5c,
			1
		);
		return 1;
	}

	if (param_1 != 0) {
		if (CleanupBuildingEntity((uchar*) param_1) != 0) {
			return 1;
		}
	}
	else {
		if (local_8 != (void*) 0x0) {
			LogMessageInternal(
				s_D__Develop_DieGildeAddOn_command_1002c748,
				0x2a21,
				s_cm_ExFree____Can_t_free_Objects_1002cc3c,
				1
			);
			return 1;
		}
		DeallocEntity((unsigned int) *local_4, 1);
	}

	if (param_2 != (char*) 0x0) {
		*param_2 = '\x01';
	}
	return 0;
}
