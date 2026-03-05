// FUNCTION: SERVER 0x1000e9c0
// STATUS: STUB
// BLOCKER: jump condition swap
// ORIGIN: GAME
// SIZE: 214
// CFLAGS: /O2 /Gd
// SYMBOL: _ExChangeDesire
// BLOCKER_DELTA: 208

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

extern int __cdecl get_field_by_type(char*, int);
extern int __cdecl ResolveEntityById(void**, void**, void**, int);
extern void __cdecl LogMessageInternal(char*, int, char*, int);

extern double _g_stat_min_d;
extern double _g_stat_max_d;
extern char s_D__Develop_DieGildeAddOn_command_1002c748[];
extern char s_cm_ExChangeDesire___Invalid_Id_1002d0f4[];

/*
 * Ghidra decompilation reference:
 * /+ WARNING: Globals starting with '_' overlap smaller symbols at the same address * / * / * [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 214B
 *    CFlags: 
 *    Symbol: _ExChangeDesire
 *    Files: DieGildeAddOn/command/command.c * /
 * 
 * int __cdecl ExChangeDesire(uchar *param_1)
 * 
 * {
 *   float fVar1;
 *   uchar *puVar2;
 *   int iVar3;
 *   float *pfVar4;
 *   byte *pbVar5;
 *   uint uVar6;
 *   undefined1 *in_stack_00000008;
 *   
 *   puVar2 = param_1;
 *   iVar3 = get_field_by_type((char *)param_1,*(int *)(param_1 + 0x10));
 *   *(int *)(puVar2 + 0x10) = iVar3;
 *   iVar3 = ResolveEntityById((void **)0x0,(void **)0x0,&param_1,iVar3);
 *   if (iVar3 != 0) {
 *     uVar6 = 0;
 *     pbVar5 = puVar2 + 0x15;
 *     if (puVar2[0x14] != '\0') {
 *       do {
 *         pfVar4 = (float *)(pbVar5 + 1);
 *         iVar3 = ((uint)*pbVar5 * 3 + 0x24) * 4;
 *         pbVar5 = pbVar5 + 5;
 *         *(float *)(param_1 + iVar3) = *pfVar4 + *(float *)(param_1 + iVar3);
 *         if ((*(float *)(param_1 + iVar3) < (float)_g_stat_min_d) ||
 *            (*(float *)(param_1 + iVar3) < (float)_g_stat_max_d)) {
 *           if ((float)_g_stat_min_d <= *(float *)(param_1 + iVar3)) {
 *             fVar1 = *(float *)(param_1 + iVar3);
 *           }
 *           else {
 *             fVar1 = (float)_g_stat_min_d;
 *           }
 *         }
 *         else {
 *           fVar1 = (float)_g_stat_max_d;
 *         }
 *         *(float *)(param_1 + iVar3) = fVar1;
 *         uVar6 = uVar6 + 1;
 *       } while (uVar6 < puVar2[0x14]);
 *     }
 *     if (in_stack_00000008 != (undefined1 *)0x0) {
 */

int __cdecl ExChangeDesire(uchar* param_1, uchar* param_2)
{
	float fVar1;
	uchar* puVar2;
	int iVar3;
	float* pfVar4;
	uchar* pbVar5;
	uint uVar6;

	puVar2 = param_1;
	iVar3 = get_field_by_type((char*) param_1, *(int*) (param_1 + 0x10));
	*(int*) (puVar2 + 0x10) = iVar3;
	iVar3 = ResolveEntityById((void**) 0x0, (void**) 0x0, (void**) &param_1, iVar3);
	if (iVar3 == 0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x33af,
			s_cm_ExChangeDesire___Invalid_Id_1002d0f4,
			1
		);
		return 1;
	}

	uVar6 = 0;
	pbVar5 = puVar2 + 0x15;
	if (puVar2[0x14] != '\0') {
		do {
			pfVar4 = (float*) (pbVar5 + 1);
			iVar3 = (((uint) *pbVar5 * 3) + 0x24) * 4;
			pbVar5 = pbVar5 + 5;
			*(float*) (param_1 + iVar3) = *pfVar4 + *(float*) (param_1 + iVar3);
			if (*(float*) (param_1 + iVar3) < (float) _g_stat_min_d) {
				fVar1 = (float) _g_stat_min_d;
			}
			else if (*(float*) (param_1 + iVar3) < (float) _g_stat_max_d) {
				fVar1 = *(float*) (param_1 + iVar3);
			}
			else {
				fVar1 = (float) _g_stat_max_d;
			}
			*(float*) (param_1 + iVar3) = fVar1;
			uVar6 = uVar6 + 1;
		} while (uVar6 < puVar2[0x14]);
	}

	if (param_2 != (uchar*) 0x0) {
		*param_2 = '\x01';
	}
	return 0;
}
