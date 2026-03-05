// FUNCTION: SERVER 0x1000eaa0
// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 208
// CFLAGS: /O2 /Gd
// SYMBOL: _ExSetEntityBitmask
// BLOCKER: param_1 reuse pattern (ResolveEntityById writes through &param_1), switch dec chain offset (case 1 needs leading dec), register allocation (and edx,ecx vs and ecx,edx in case bodies)

#ifdef __clang__
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 208B
 *    CFlags: 
 *    Symbol: _ExSetEntityBitmask
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl ExSetEntityBitmask(int param_1,char *param_2)
 * 
 * {
 *   int iVar1;
 *   int iVar2;
 *   uint *puVar3;
 *   byte bVar4;
 *   uint uVar5;
 *   void *pvStack_8;
 *   void *pvStack_4;
 *   
 *   iVar1 = param_1;
 *   iVar2 = get_field_by_type((char *)param_1,*(int *)(param_1 + 0x10));
 *   *(int *)(iVar1 + 0x10) = iVar2;
 *   iVar2 = ResolveEntityById((void **)&param_1,&pvStack_8,&pvStack_4,iVar2);
 *   if (iVar2 == 0) {
 *     LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x340d,
 *                        s_cm_ExChangeBits___Invalid_Id_1002d114,1);
 *     return 1;
 *   }
 *   if ((param_1 == 0) && (param_1 = (int)pvStack_8, pvStack_8 == (void *)0x0)) {
 *     param_1 = (int)pvStack_4;
 *   }
 *   puVar3 = (uint *)(param_1 + *(int *)(iVar1 + 0x14));
 *   iVar2 = *(int *)(iVar1 + 0x18);
 *   if (iVar2 == 1) {
 *     bVar4 = (byte)*puVar3 & ~*(byte *)(iVar1 + 0x20);
 *     *(byte *)puVar3 = bVar4;
 *     *(byte *)puVar3 = *(byte *)(iVar1 + 0x1c) | bVar4;
 *   }
 *   else if (iVar2 == 2) {
 *     *(ushort *)puVar3 = (ushort)*puVar3 & ~*(ushort *)(iVar1 + 0x20);
 *     *(ushort *)puVar3 = *(ushort *)(iVar1 + 0x1c) | (ushort)*puVar3;
 *   }
 *   else if (iVar2 == 4) {
 *     uVar5 = *puVar3 & ~*(uint *)(iVar1 + 0x20);
 *     *puVar3 = uVar5;
 *     *puVar3 = *(uint *)(iVar1 + 0x1c) | uVar5;
 *   }
 *   if (param_2 != (char *)0x0) {
 *     *param_2 = '\x01';
 *   }
 */

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

extern int __cdecl get_field_by_type(char*, int);
extern int __cdecl ResolveEntityById(void**, void**, void**, int);
extern void __cdecl LogMessageInternal(const char*, uint, const char*, int);

extern char s_D__Develop_DieGildeAddOn_command_1002c748[];
extern char s_cm_ExChangeBits___Invalid_Id_1002d114[];

int __cdecl ExSetEntityBitmask(int param_1, char* param_2)
{
	int entity_id;
	int ok;
	void* primary;
	void* secondary;
	void* tertiary;
	uint* p;
	int size;
	uchar bVal;
	uint uVal;

	entity_id = get_field_by_type((char*) param_1, *(int*) (param_1 + 0x10));
	*(int*) (param_1 + 0x10) = entity_id;

	ok = ResolveEntityById(&primary, &secondary, &tertiary, entity_id);
	if (ok == 0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x340d,
			s_cm_ExChangeBits___Invalid_Id_1002d114,
			1
		);
		return 1;
	}

	if (primary == (void*) 0) {
		primary = secondary;
		if (primary == (void*) 0) {
			primary = tertiary;
		}
	}

	p = (uint*) ((int) primary + *(int*) (param_1 + 0x14));
	size = *(int*) (param_1 + 0x18);

	switch (size) {
	case 1:
		bVal = *(uchar*) p & ~*(uchar*) (param_1 + 0x20);
		*(uchar*) p = bVal;
		*(uchar*) p = *(uchar*) (param_1 + 0x1c) | bVal;
		break;
	case 2:
		*(ushort*) p = *(ushort*) p & ~*(ushort*) (param_1 + 0x20);
		*(ushort*) p = *(ushort*) (param_1 + 0x1c) | *(ushort*) p;
		break;
	case 4:
		uVal = *p & ~*(uint*) (param_1 + 0x20);
		*p = uVal;
		*p = *(uint*) (param_1 + 0x1c) | uVal;
		break;
	}

	if (param_2 != (char*) 0) {
		*param_2 = '\x01';
	}

	return 0;
}
