#include "client_types.h"

#pragma pack(push, 1)
typedef struct node99_load {
	char used;
	char pad[0x90];
	int prev;
	int next;
} node99_load;
#pragma pack(pop)
/* SIZE 0x99 */

int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);

/* Loads the 0x99-byte node pool at 0x9bade0 and the parallel cell table at
 * 0xfb5760 from a save stream, turning the stored link indices back into
 * absolute addresses. */
/* ADDRESS: GOLDTL 0x005252d0 */
int __cdecl fcn_005252d0(void* fp)
{
	char* r;
	int n;
	int i;

	for (r = (char*) 0x9bae71; (int) r < (int) 0xaece71; r += 0x99) {
		if (!ls_ReadVfsDataChecked(r - 0x91, 0x99, 1, fp)) {
			return 0;
		}
		if (*(int*) r == -1) {
			*(int*) r = 0;
		} else {
			*(int*) r = (int) &((node99_load*) 0x9bade0)[*(int*) r];
		}
		if (*(int*) (r + 4) == -1) {
			*(int*) (r + 4) = 0;
		} else {
			*(int*) (r + 4) = (int) &((node99_load*) 0x9bade0)[*(int*) (r + 4)];
		}
	}
	if (!ls_ReadVfsDataChecked(&n, 4, 1, fp)) {
		return 0;
	}
	if (n == -1) {
		*(char**) 0xaed324 = 0;
	} else {
		*(char**) 0xaed324 = (char*) &((node99_load*) 0x9bade0)[n];
	}
	if (!ls_ReadVfsDataChecked(&n, 4, 1, fp)) {
		return 0;
	}
	if (n == -1) {
		*(char**) 0xaed200 = 0;
	} else {
		*(char**) 0xaed200 = (char*) &((node99_load*) 0x9bade0)[n];
	}
	n = (*(int*) 0x6a23ac < 0x1003c) ? 0x2000 : 0x8000;
	for (r = (char*) 0xfb5760; r < (char*) 0x1005760; r += 0xa) {
		*(int*) (r + 6) = 0;
		*(int*) (r + 2) = -1;
		*(char*) r = 1;
	}
	if (n > 0) {
		for (i = 0; i < n; i++) {
			r = (char*) 0xaed740 + i * 0x99;
			if (!ls_ReadVfsDataChecked(r, 0x99, 1, fp)) {
				return 0;
			}
			if (*(int*) (r + 0x91) == -1) {
				*(int*) (r + 0x91) = 0;
			} else {
				*(int*) (r + 0x91) = (int) &((node99_load*) 0xaed740)[*(int*) (r + 0x91)];
			}
			if (*(int*) (r + 0x95) == -1) {
				*(int*) (r + 0x95) = 0;
			} else {
				*(int*) (r + 0x95) = (int) &((node99_load*) 0xaed740)[*(int*) (r + 0x95)];
			}
		}
	}
	if (!ls_ReadVfsDataChecked(&n, 4, 1, fp)) {
		return 0;
	}
	if (n == -1) {
		*(int*) 0x1005760 = 0;
	} else {
		*(int*) 0x1005760 = (int) &((node99_load*) 0xaed740)[n];
	}
	if (!ls_ReadVfsDataChecked((void*) 0x1005768, 4, 1, fp)) {
		return 0;
	}
	n = (*(int*) 0x6a23ac < 0x1003c) ? 0x2000 : 0x8000;
	if (n > 0) {
		for (i = 0; i < n; i++) {
			if (!ls_ReadVfsDataChecked((void*) (0xfb5760 + i * 0xa), 0xa, 1, fp)) {
				return 0;
			}
		}
	}
	if (!ls_ReadVfsDataChecked((void*) 0x100581c, 4, 1, fp)) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked((void*) 0xaed204, 4, 1, fp)) {
		return 0;
	}
	*(int*) 0x68a9d0 = 0;
	if (!ls_ReadVfsDataChecked((void*) 0x68a9d0, 4, 1, fp)) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked((void*) 0x68a9d4, 4, 1, fp)) {
		return 0;
	}
	return ls_ReadVfsDataChecked((void*) 0x68a9d8, 4, 1, fp) != 0;
}
