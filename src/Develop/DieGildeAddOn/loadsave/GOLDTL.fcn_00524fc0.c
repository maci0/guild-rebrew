#include <string.h>
#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern int g_6a23ac;

int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
void __cdecl fcn_00500bb0(void*, int, int, int);

/* Reads the 0x114-byte slot records of the table at g_9a9660 from a save
 * stream. Records written by version 0x1003f and later carry a timestamp;
 * older ones reuse g_7f4c00. */
/* ADDRESS: GOLDTL 0x00524fc0 */
int __cdecl fcn_00524fc0(void* fp)
{
	char buf[0x1000];
	char* p;
	int count;
	int i;

	if (!ls_ReadVfsDataChecked(&count, 4, 1, fp)) {
		return 0;
	}
	i = 0;
	if (count <= 0) {
		return 1;
	}
	p = (char*) 0x9a9674;
	for (; i < count; i++, p += 0x114) {
		if (!ls_ReadVfsDataChecked(p - 0x14, 4, 1, fp)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(p - 0xc, 1, 1, fp)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(p, 4, 1, fp)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(p + 0x12, 1, 1, fp)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(p + 0x1c, 1, 1, fp)) {
			return 0;
		}
		if (g_6a23ac >= 0x10059) {
			if (!ls_ReadVfsDataChecked(p + 0x20, 4, 0x10, fp)) {
				return 0;
			}
		} else {
			if (!ls_ReadVfsDataChecked(buf, 0x40, 0x10, fp)) {
				return 0;
			}
			memcpy(p + 0x20, buf, 0x40);
		}
		if (!ls_ReadVfsDataChecked(p + 0x60, 1, 1, fp)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(p + 0x68, 0x98, 1, fp)) {
			return 0;
		}
		if (g_6a23ac >= 0x1003f) {
			if (!ls_ReadVfsDataChecked(p + 4, 0xe, 1, fp)) {
				return 0;
			}
		} else {
			*(pos14_7f4c00*) (p + 4) = g_7f4c00;
			fcn_00500bb0(p + 4, i + 1, 0, 0);
		}
		if (g_6a23ac >= 0x10040) {
			if (!ls_ReadVfsDataChecked(p - 8, 4, 1, fp)) {
				return 0;
			}
		} else {
			*(int*) (p - 8) = -1;
		}
	}
	return 1;
}
