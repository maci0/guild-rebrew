#include <string.h>
#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern int g_6a23ac;
extern char g_9a9660[];

int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
void __cdecl fcn_00500bb0(void*, int, int, int);

typedef struct slot_114 {
	char pad0[0x14];
	int field14;
	char pad18[0xe];
	char pad26[1];
	char pad27[0x9];
	char field30;
	char pad31[3];
	int field34[0x10];
	char field74;
	char pad75[0x7];
	char field7c[0x98];
} slot_114;

/* Reads the 0x114-byte slot records of the table at g_9a9660 from a save
 * stream. Records written by version 0x1003f and later carry a timestamp;
 * older ones reuse g_7f4c00. */
/* ADDRESS: GOLDTL 0x00524fc0 */
int __cdecl fcn_00524fc0(void* fp)
{
	char buf[0x1000];
	slot_114* p;
	int count;
	int i;
	int k;

	if (!ls_ReadVfsDataChecked(&count, 4, 1, fp)) {
		return 0;
	}
	i = 0;
	if (count <= 0) {
		return 1;
	}
	p = (slot_114*) g_9a9660;
	for (; i < count; i++, p++) {
		if (!ls_ReadVfsDataChecked(&p->pad0[0], 4, 1, fp)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&p->pad0[8], 1, 1, fp)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&p->field14, 4, 1, fp)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&p->pad26[0], 1, 1, fp)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&p->field30, 1, 1, fp)) {
			return 0;
		}
		if (g_6a23ac >= 0x10059) {
			if (!ls_ReadVfsDataChecked(&p->field34[0], 4, 0x10, fp)) {
				return 0;
			}
		} else {
			if (!ls_ReadVfsDataChecked(buf, 0x40, 0x10, fp)) {
				return 0;
			}
			for (k = 0; k < 16; k++) {
				p->field34[k] = ((int*) buf)[k];
			}
		}
		if (!ls_ReadVfsDataChecked(&p->field74, 1, 1, fp)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&p->field7c[0], 0x98, 1, fp)) {
			return 0;
		}
		if (g_6a23ac >= 0x1003f) {
			if (!ls_ReadVfsDataChecked(&p->pad18[0], 0xe, 1, fp)) {
				return 0;
			}
		} else {
			*(pos14_7f4c00*) (&p->pad18[0]) = g_7f4c00;
			fcn_00500bb0(&p->pad18[0], i + 1, 0, 0);
		}
		if (g_6a23ac >= 0x10040) {
			if (!ls_ReadVfsDataChecked(&p->pad0[0xc], 4, 1, fp)) {
				return 0;
			}
		} else {
			*(int*) (&p->pad0[0xc]) = -1;
		}
	}
	return 1;
}
