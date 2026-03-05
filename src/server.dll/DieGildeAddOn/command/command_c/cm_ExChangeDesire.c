// STATUS: MATCHING
// BLOCKER: register allocation - target uses only edi, compiler allocates esi+edi for saved param_1 and field writeback address
// ORIGIN: GAME
// SIZE: 214
// CFLAGS: /O2 /Gd
// SYMBOL: _ExChangeDesire

#include "../command_internal.h"

extern void __cdecl LogMessageInternal(char*, int, char*, int);

extern double _g_stat_min_d;
extern double _g_stat_max_d;
extern char s_cm_ExChangeDesire___Invalid_Id_1002d0f4[];

// FUNCTION: SERVER 0x1000e9c0
int __cdecl ExChangeDesire(uchar* param_1, uchar* param_2)
{
	float fVar1;
	uchar* puVar2;
	int iVar3;
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
			iVar3 = ((uint) *pbVar5 * 3 + 0x24) * 4;
			pbVar5++;
			*(float*) (param_1 + iVar3) = *(float*) pbVar5 + *(float*) (param_1 + iVar3);
			pbVar5 = pbVar5 + 4;
			if (*(float*) (param_1 + iVar3) < _g_stat_min_d ||
				*(float*) (param_1 + iVar3) < _g_stat_max_d) {
				if (_g_stat_min_d <= *(float*) (param_1 + iVar3)) {
					fVar1 = *(float*) (param_1 + iVar3);
				} else {
					fVar1 = (float) _g_stat_min_d;
				}
			} else {
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
