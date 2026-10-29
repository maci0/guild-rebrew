#include "client_types.h"

#pragma pack(push, 1)
typedef struct node99_save {
	char used;
	char pad[0x90];
	unsigned int prev;
	unsigned int next;
} node99_save;
#pragma pack(pop)
/* SIZE 0x99 */

unsigned int __cdecl vfs_fwrite(void* buf, int size, int count, char* stream);

/* Writes the 0x99-byte node pools at 0x9bade0 and 0xaed740 into a save stream,
 * turning each linked-list pointer back into its pool index. */
/* ADDRESS: GOLDTL 0x00521530 */
int __cdecl fcn_00521530(void* fp)
{
	int index;
	node99_save buf;
	char* r;
	char* cell;

	for (r = (char*) 0x9bae71; (int) r < (int) 0xaece71; r += 0x99) {
		buf = *(node99_save*) (r - 0x91);
		buf.prev = *(unsigned int*) r ? (*(unsigned int*) r - 0x9bade0) / 0x99 : 0xffffffff;
		index = *(unsigned int*) (r + 4) ? (*(unsigned int*) (r + 4) - 0x9bade0) / 0x99 : 0xffffffff;
		buf.next = index;
		if (vfs_fwrite(&buf, 0x99, 1, fp) <= 0) {
			return 0;
		}
	}
	if (*(unsigned int*) 0xaed324) {
		index = (*(unsigned int*) 0xaed324 - 0x9bade0) / 0x99;
	} else {
		index = 0xffffffff;
	}
	if (vfs_fwrite(&index, 4, 1, fp) <= 0) {
		return 0;
	}
	if (*(unsigned int*) 0xaed200) {
		index = (*(unsigned int*) 0xaed200 - 0x9bade0) / 0x99;
	} else {
		index = 0xffffffff;
	}
	if (vfs_fwrite(&index, 4, 1, fp) <= 0) {
		return 0;
	}
	for (r = (char*) 0xaed7d1; (int) r < (int) 0xfb57d1; r += 0x99) {
		buf = *(node99_save*) (r - 0x91);
		buf.prev = *(unsigned int*) r ? (*(unsigned int*) r - 0xaed740) / 0x99 : 0xffffffff;
		index = *(unsigned int*) (r + 4) ? (*(unsigned int*) (r + 4) - 0xaed740) / 0x99 : 0xffffffff;
		buf.next = index;
		if (vfs_fwrite(&buf, 0x99, 1, fp) <= 0) {
			return 0;
		}
	}
	if (*(unsigned int*) 0x1005760) {
		index = (*(unsigned int*) 0x1005760 - 0xaed740) / 0x99;
	} else {
		index = 0xffffffff;
	}
	if (vfs_fwrite(&index, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x1005768, 4, 1, fp) <= 0) {
		return 0;
	}
	for (cell = (char*) 0xfb5760; (int) cell < (int) 0x1005760; cell += 0xa) {
		if (vfs_fwrite(cell, 0xa, 1, fp) <= 0) {
			return 0;
		}
	}
	if (vfs_fwrite((void*) 0x100581c, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0xaed204, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x68a9d0, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x68a9d4, 4, 1, fp) <= 0) {
		return 0;
	}
	return vfs_fwrite((void*) 0x68a9d8, 4, 1, fp) != 0;
}
