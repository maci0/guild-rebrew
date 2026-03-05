// FUNCTION: SERVER 0x100100a0
// STATUS: MATCHING
// BLOCKER: three-fcom float clamp pattern with shared return paths - compiler generates different branch layout and fcom count
// ORIGIN: GAME
// SIZE: 159
// CFLAGS: /O2 /Gd
// SYMBOL: _ModifyEntityStat

/*
 * Ghidra decompilation reference:
 * /+ WARNING: Globals starting with '_' overlap smaller symbols at the same address * / * / * [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 159B
 *    CFlags: 
 *    Symbol: _ModifyEntityStat
 *    Files: DieGildeAddOn/command/command.c * /
 * 
 * int __cdecl ModifyEntityStat(int *param_1)
 * 
 * {
 *   int iVar1;
 *   float fVar2;
 *   int iVar3;
 *   long lVar4;
 *   
 *   iVar3 = LookupEntityRecordById(param_1[4]);
 *   if (((iVar3 == 0) || (iVar1 = param_1[5], iVar1 < 0)) || (4 < iVar1)) {
 *     return 1;
 *   }
 *   fVar2 = (float)(int)(param_1[6] + (uint)*(byte *)(iVar1 + 0x80 + iVar3));
 *   if (((_g_stat_max <= fVar2) || (_g_stat_min < fVar2)) && (_g_stat_max <= fVar2)) {
 *     lVar4 = _ftol();
 *     *(char *)(iVar1 + 0x80 + iVar3) = (char)lVar4;
 *     return 0;
 *   }
 *   lVar4 = _ftol();
 *   *(char *)(iVar1 + 0x80 + iVar3) = (char)lVar4;
 *   return 0;
 * }
 */

extern int __cdecl LookupEntityRecordById(int);
extern float _g_stat_max;
extern float _g_stat_min;

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wpointer-to-int-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

int __cdecl ModifyEntityStat(int* param_1)
{
	int iVar1;
	int iVar3;
	float fVar2;

	iVar3 = LookupEntityRecordById(param_1[4]);
	if ((iVar3 == 0) || ((iVar1 = param_1[5], iVar1 < 0) || (4 < iVar1))) {
		return 1;
	}
	fVar2 = (float) (int) (param_1[6] + (unsigned int) *(unsigned char*) (iVar1 + 0x80 + iVar3));
	if (fVar2 >= _g_stat_max) {
		*(char*) (iVar1 + 0x80 + iVar3) = (char) (long) _g_stat_max;
		return 0;
	}
	if (fVar2 <= _g_stat_min) {
		fVar2 = _g_stat_min;
	}
	*(char*) (iVar1 + 0x80 + iVar3) = (char) (long) fVar2;
	return 0;
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif
