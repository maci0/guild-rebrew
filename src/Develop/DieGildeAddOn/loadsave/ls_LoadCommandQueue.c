#include "client_types.h"
#include "client_queued_packet.h"

#pragma pack(push, 1)
typedef struct CMD_QUEUE_NODE_99 {
	char used;
	char pad[0x90];
	int prev;
	int next;
} CMD_QUEUE_NODE_99;
#pragma pack(pop)
/* SIZE 0x99 */
extern char g_9bade0[];
extern COMMAND_STATUS_SLOT g_fb5760[0x8000];
extern char* cm_CommandQueueHead;
extern char* g_aed200;
extern int ls_SaveVersion;
extern int g_1005760;
extern int g_1005768;
extern unsigned int g_100581c;
extern unsigned int g_aed204;

int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);

/* Loads the 0x99-byte node pool at 0x9bade0 and the parallel cell table at
 * 0xfb5760 from a save stream, turning the stored link indices back into
 * absolute addresses. */
/* ADDRESS: GOLDTL 0x005252d0 */
int __cdecl ls_LoadCommandQueue(void* fp)
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
			*(int*) r = (int) &((CMD_QUEUE_NODE_99*) g_9bade0)[*(int*) r];
		}
		if (*(int*) (r + 4) == -1) {
			*(int*) (r + 4) = 0;
		} else {
			*(int*) (r + 4) = (int) &((CMD_QUEUE_NODE_99*) g_9bade0)[*(int*) (r + 4)];
		}
	}
	if (!ls_ReadVfsDataChecked(&n, 4, 1, fp)) {
read_failed: return 0;
	}
	if (n == -1) {
		cm_CommandQueueHead = 0;
	} else {
		cm_CommandQueueHead = (char*) &((CMD_QUEUE_NODE_99*) g_9bade0)[n];
	}
	i = 0;
	if (!ls_ReadVfsDataChecked(&n, 4, 1, fp)) {
		return 0;
	}
	if (n == -1) {
		g_aed200 = 0;
	} else {
		g_aed200 = (char*) &((CMD_QUEUE_NODE_99*) g_9bade0)[n];
	}
	n = (ls_SaveVersion >= 0x1003c) ? 0x8000 : 0x2000;
	for (r = (char*) g_fb5760 + 2; (int) r < (int) g_fb5760 + 0x50002; r += 0xa) {
		*(int*) (r + 4) = 0;
		*(int*) r = -1;
		*(char*) (r - 2) = 1;
	}
	if (n > 0) {
		for (; i < n; i++) {
			if (!ls_ReadVfsDataChecked(&g_aed740[i], 0x99, 1, fp)) {
				return 0;
			}
			if ((int) g_aed740[i].prev == -1) {
				g_aed740[i].prev = 0;
			} else {
				g_aed740[i].prev = &g_aed740[(int) g_aed740[i].prev];
			}
			if ((int) g_aed740[i].next == -1) {
				g_aed740[i].next = 0;
			} else {
				g_aed740[i].next = &g_aed740[(int) g_aed740[i].next];
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
	n = (ls_SaveVersion >= 0x1003c) ? 0x8000 : 0x2000;
	if (n > 0) {
		for (r = (char*) g_fb5760; i < n; i++, r += 0xa) {
			if (!ls_ReadVfsDataChecked(r, 0xa, 1, fp)) {
				return 0;
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
