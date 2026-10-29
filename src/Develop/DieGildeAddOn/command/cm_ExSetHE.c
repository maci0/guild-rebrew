#include <stdio.h>
#include <string.h>

#pragma pack(push, 1)
typedef struct Hdr14 {
	int x0;
	int x4;
	int x8;
	short xc;
} Hdr14;
#pragma pack(pop)
// SIZE 0xe

char* __cdecl fcn_005463a0(int, int, int);

/* Serializes one entity (cmd+0x14..cmd+0x3e) into the fresh record returned by
 * fcn_005463a0 and copies the 0xa0-byte message template into it. Native extent
 * is 244 bytes (ret at 0x004c9433); the stored 101-byte size is a stale split. */
/* ADDRESS: GOLDTL 0x004c9340 */
int __cdecl cm_ExSetHE(char* cmd, char* result)
{
	char buf[0x100];
	char* p;

	if (result != 0) {
		result[0] = 2;
		result[1] = 4;
		*(int*) (result + 6) = 0;
	}
	p = fcn_005463a0(1, 1, *(int*) (cmd + 0x10));
	if (p == 0) {
		sprintf(buf, "cm_ExSetHE(): He not found. id:%i name:%s",
		        *(int*) (cmd + 0x10), cmd + 0x3f);
		return 1;
	}
	*(Hdr14*) (p + 0x44) = *(Hdr14*) (cmd + 0x14);
	*(Hdr14*) (p + 0x52) = *(Hdr14*) (cmd + 0x22);
	*(Hdr14*) (p + 0x60) = *(Hdr14*) (cmd + 0x30);
	*(int*) (p + 0x70) = (int) *(signed char*) (cmd + 0x3e);
	memcpy(p + 0xac, (void*) 0xaed340, 0xa0);
	if (result != 0) {
		result[0] = 1;
		result[1] = 4;
		*(char**) (result + 6) = p;
	}
	return 0;
}
