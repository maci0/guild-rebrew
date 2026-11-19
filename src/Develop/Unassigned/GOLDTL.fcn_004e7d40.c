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
int __cdecl fcn_004e7d40(char* entityRecord, int officeKind)
{
	Info4e7d40 info;
	int i;
	int first;
	int flag;
	int res;

	if (*(unsigned char*) (entityRecord + 0x168) != 0) {
		return -1;
	}
	for (i = 0; i < 0x1e; i++) {
		if (amt_OfficeSlots[i].type == officeKind) {
			break;
		}
	}
	if (i >= 0x1e) {
		return -1;
	}
	info.id = (unsigned char) officeKind;
	*(Blk4e7d40*) info.data = *(Blk4e7d40*) (g_68da68 + amt_OfficeSlots[i].type * 0x18);
	info.sel = 0xff;
	info.alt = 0xff;
	if (info.data[4] != 0) {
		first = 0;
		flag = 0;
		if (amt_OfficeSlots[i].x4 == -1 && amt_OfficeSlots[i].x10 == 3 && amt_OfficeSlots[i].xc < 4) {
			info.owner = *(int*) (entityRecord + 4);
			info.sel = amt_OfficeSlots[i].id;
			first = 1;
			flag = 1;
		}
		for (i++; i < 0x1e; i++) {
			if (amt_OfficeSlots[i].type == officeKind) {
				break;
			}
		}
		if (i < 0x1e && amt_OfficeSlots[i].x4 == -1 && amt_OfficeSlots[i].x10 == 3 && amt_OfficeSlots[i].xc < 4) {
			if (first) {
				info.alt = amt_OfficeSlots[i].id;
			} else {
				info.sel = amt_OfficeSlots[i].id;
				info.owner = *(int*) (entityRecord + 4);
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
	if (amt_OfficeSlots[i].x4 != -1) {
		return -1;
	}
	if (amt_OfficeSlots[i].x10 != 3) {
		return -1;
	}
	if (amt_OfficeSlots[i].xc >= 4) {
		return -1;
	}
	info.sel = amt_OfficeSlots[i].id;
	info.owner = *(int*) (entityRecord + 4);
	fcn_004c4eb0((char*) 0x67eef4);
	res = fcn_004c6360(&info);
	fcn_004c4ef0((char*) 0x67eef4);
	return res;
}
