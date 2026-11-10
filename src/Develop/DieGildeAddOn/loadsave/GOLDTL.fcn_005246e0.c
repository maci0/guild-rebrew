#include "Develop/DieGildeAddOn/loadsave/loadsave.h"
#include "client_types.h"

extern Sample_99ec20 g_99ec20[16];
extern Cell_99ef80 g_99ef80[9][8];

/* ADDRESS: GOLDTL 0x005246e0 */
unsigned int __cdecl fcn_005246e0(unsigned int stream)
{
	int i;
	int j;
	int value;

	value = 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5e0, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5e4, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5e8, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5ec, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5f0, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5f4, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5f8, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5fc, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f600, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f604, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99ec14, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f590, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f594, 2, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f596, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f59a, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x773d4c, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x773d50, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5a0, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5a4, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5a8, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5ac, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5b0, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5b4, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5b8, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5bc, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f5c0, 4, 1, (void*) stream))
		return 0;
	for (i = 0; i < 16; i++) {
		if (!ls_ReadVfsDataChecked(&g_99ec20[i].a, 4, 1, (void*) stream))
			return 0;
		if (!ls_ReadVfsDataChecked(&g_99ec20[i].b, 4, 1, (void*) stream))
			return 0;
		if (!ls_ReadVfsDataChecked(&g_99ec20[i].c, 4, 1, (void*) stream))
			return 0;
		if (!ls_ReadVfsDataChecked(&g_99ec20[i].d, 4, 1, (void*) stream))
			return 0;
		if (!ls_ReadVfsDataChecked(&g_99ec20[i].e, 4, 1, (void*) stream))
			return 0;
	}
	if (!ls_ReadVfsDataChecked((void*) 0x99f6a0, 0x44, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f6e4, 0x44, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f728, 0x44, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f76c, 0x44, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) 0x99f7b0, 0x44, 1, (void*) stream))
		return 0;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (!ls_ReadVfsDataChecked(&g_99ef80[i][j].demand, 2, 1, (void*) stream))
				return 0;
			if (!ls_ReadVfsDataChecked(&g_99ef80[i][j].supply, 2, 1, (void*) stream))
				return 0;
			if (!ls_ReadVfsDataChecked(&g_99ef80[i][j].pad4[0], 1, 1, (void*) stream))
				return 0;
			if (!ls_ReadVfsDataChecked(&g_99ef80[i][j].pad4[4], 4, 1, (void*) stream))
				return 0;
		}
	}
	return 1;
}
