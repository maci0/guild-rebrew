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
extern char g_9bade0[];
extern node99_load g_aed740[0x8000];
extern cell10_fb5760 g_fb5760[0x8000];
extern char* g_aed324;
extern char* g_aed200;
extern int g_6a23ac;
extern int g_1005760;
extern int g_1005768;
extern unsigned int g_100581c;
extern unsigned int g_aed204;

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

	for (r = g_9bade0 + 0x91; (int) r < (int) g_9bade0 + 0x132091; r += 0x99) {
		if (!ls_ReadVfsDataChecked(r - 0x91, 0x99, 1, fp)) {
			goto read_failed;
		}
		if (*(int*) r == -1) {
			*(int*) r = 0;
		} else {
			*(int*) r = (int) &((node99_load*) g_9bade0)[*(int*) r];
		}
		if (*(int*) (r + 4) == -1) {
			*(int*) (r + 4) = 0;
		} else {
			*(int*) (r + 4) = (int) &((node99_load*) g_9bade0)[*(int*) (r + 4)];
		}
	}
	if (!ls_ReadVfsDataChecked(&n, 4, 1, fp)) {
read_failed: return 0;
	}
	i = 0;
	if (n == -1) {
		g_aed324 = 0;
	} else {
		g_aed324 = (char*) &((node99_load*) g_9bade0)[n];
	}
	if (!ls_ReadVfsDataChecked(&n, 4, 1, fp)) {
		return 0;
	}
	if (n == -1) {
		g_aed200 = 0;
	} else {
		g_aed200 = (char*) &((node99_load*) g_9bade0)[n];
	}
	n = (g_6a23ac >= 0x1003c) ? 0x8000 : 0x2000;
	for (r = (char*) g_fb5760 + 2; (int) r < (int) g_fb5760 + 0x50002; r += 0xa) {
		*(int*) (r + 4) = 0;
		*(int*) r = -1;
		*(char*) (r - 2) = 1;
	}
	if (n > 0) {
		for (r = (char*) g_aed740 + 0x91; i < n; i++, r += 0x99) {
			if (!ls_ReadVfsDataChecked(r - 0x91, 0x99, 1, fp)) {
				goto read_failed;
			}
			if (*(int*) r == -1) {
				*(int*) r = 0;
			} else {
				*(int*) r = (int) &(g_aed740)[*(int*) r];
			}
			if (*(int*) (r + 4) == -1) {
				*(int*) (r + 4) = 0;
			} else {
				*(int*) (r + 4) = (int) &(g_aed740)[*(int*) (r + 4)];
			}
		}
	}
	i = 0;
	if (!ls_ReadVfsDataChecked(&n, 4, 1, fp)) {
		return 0;
	}
	if (n == -1) {
		g_1005760 = 0;
	} else {
		g_1005760 = (int) &(g_aed740)[n];
	}
	if (!ls_ReadVfsDataChecked(&g_1005768, 4, 1, fp)) {
		return 0;
	}
	n = (g_6a23ac >= 0x1003c) ? 0x8000 : 0x2000;
	if (n > 0) {
		for (r = (char*) g_fb5760; i < n; i++, r += 0xa) {
			if (!ls_ReadVfsDataChecked(r, 0xa, 1, fp)) {
				goto read_failed;
			}
		}
	}
	if (!ls_ReadVfsDataChecked(&g_100581c, 4, 1, fp)) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked(&g_aed204, 4, 1, fp)) {
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
