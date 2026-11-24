#include <string.h>
typedef struct { unsigned char bytes[3]; } RECORD3;

/* ADDRESS: GOLDTL 0x00473360 */
char __cdecl fcn_00473360(char* p)
{
	union {
		char shape[9];
		RECORD3 record;
	} u;
	int a;
	char r;

	if (p == 0)
		return 0;
	memset(u.shape, 0, 9);
	u.shape[8] = 0;
	memcpy(u.shape, p, 8);
	u.shape[8] = 0;
	if (!memcmp(u.shape, (char*) 0x67d8bc, 9)) {
		if (*(int*) p == 0 && *(unsigned short*) (p + 4) > 1)
			return 5;
		a = *(int*) p;
		if (a == 1)
			return 4;
		if (a == 2)
			return 7;
		r = a == 3 ? 8 : 1;
		return r;
	}
	u.record = *(RECORD3*) p;
	r = u.record.bytes[2] == 2 ? 17 : 0;
	return r;
}
