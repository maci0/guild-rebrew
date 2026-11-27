#include <string.h>
typedef struct { unsigned char bytes[3]; } RECORD3;

/* ADDRESS: GOLDTL 0x00473360 */
char __cdecl d2_GetResourceKind(char* buf)
{
	union {
		char shape[9];
		RECORD3 record;
	} u;
	int tag;
	char kind;

	if (buf == 0)
		return 0;
	memset(u.shape, 0, 9);
	u.shape[8] = 0;
	memcpy(u.shape, buf, 8);
	u.shape[8] = 0;
	if (!memcmp(u.shape, (char*) 0x67d8bc, 9)) {
		if (*(int*) buf == 0 && *(unsigned short*) (buf + 4) > 1)
			return 5;
		tag = *(int*) buf;
		if (tag == 1)
			return 4;
		if (tag == 2)
			return 7;
		kind = tag == 3 ? 8 : 1;
		return kind;
	}
	u.record = *(RECORD3*) buf;
	kind = u.record.bytes[2] == 2 ? 17 : 0;
	return kind;
}
