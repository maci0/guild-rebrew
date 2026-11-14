#include <string.h>
#include "client_data.h"

typedef struct { int v[6]; } Blk4e7d40;

void __cdecl fcn_004c4eb0(char* s);
void __cdecl fcn_004c4ef0(char* s);
int __cdecl fcn_004c6360(void* info);

typedef struct
{
	int owner; unsigned char sel;
	unsigned char alt;
	unsigned char id;
	char pad3;
	int data[6];
} Info4e7d40;
/* SIZE 0x20 */

extern char g_68da68[];

/* ADDRESS: GOLDTL 0x004e7d40 */
int __cdecl fcn_004e7d40(char* a0, int a1)
{
	Info4e7d40 info;
	int i;
	int first;
	int flag;
	int res;

	if (*(unsigned char*) (a0 + 0x168) != 0) {
		return -1;
	}
	for (i = 0; i < 0x1e; i++) {
		if (g_9a9220[i].type == a1) {
			break;
		}
	}
	if (i >= 0x1e) {
		return -1;
	}
	info.id = (unsigned char) a1;
	*(Blk4e7d40*) info.data = *(Blk4e7d40*) (g_68da68 + g_9a9220[i].type * 0x18);
	info.sel = 0xff;
	info.alt = 0xff;
	if (info.data[4] != 0) {
		first = 0;
		flag = 0;
		if (g_9a9220[i].x4 == -1 && g_9a9220[i].x10 == 3 && g_9a9220[i].xc < 4) {
			info.sel = g_9a9220[i].id;
			first = 1;
			info.owner = *(int*) (a0 + 4);
			flag = 1;
		}
		for (i++; i < 0x1e; i++) {
			if (g_9a9220[i].type == a1) {
				break;
			}
		}
		if (i < 0x1e && g_9a9220[i].x4 == -1 && g_9a9220[i].x10 == 3 && g_9a9220[i].xc < 4) {
			if (first) {
				info.alt = g_9a9220[i].id;
			} else {
				info.sel = g_9a9220[i].id;
				info.owner = *(int*) (a0 + 4);
				fcn_004c4eb0((char*) 0x67eef4);
				res = fcn_004c6360(&info);
				fcn_004c4ef0((char*) 0x67eef4);
				return res;
			}
		}
		if (flag) {
			fcn_004c4eb0((char*) 0x67eef4);
			res = fcn_004c6360(&info);
			fcn_004c4ef0((char*) 0x67eef4);
			return res;
		}
	}
	if (g_9a9220[i].x4 != -1) {
		return -1;
	}
	if (g_9a9220[i].x10 != 3) {
		return -1;
	}
	if (g_9a9220[i].xc >= 4) {
		return -1;
	}
	info.owner = *(int*) (a0 + 4);
	info.sel = g_9a9220[i].id;
	fcn_004c4eb0((char*) 0x67eef4);
	res = fcn_004c6360(&info);
	fcn_004c4ef0((char*) 0x67eef4);
	return res;
}
