// FUNCTION: GOLD 0x004ecf10
// SIZE: 304
// FUNCTION: GOLDTL 0x004eed10
// SIZE: 304

/* Save counterpart of ahm_AllocAhmInfo (GOLDTL 0x4eee40). */

#include <string.h>

unsigned int __cdecl fcn_00430910(void* p, int size, int n, int file);

int __cdecl fcn_004eed10(int file, char* obj)
{
	char buf[0x3c];
	char* data;
	int i;

	data = *(char**) (obj + 0x65);
	memset(buf, 0, 0x3c);
	*(int*) buf = -1;
	if (data == 0) {
		data = buf;
	}
	if (fcn_00430910(data, 4, 1, file) <= 0)
		return 0;
	if (fcn_00430910(data + 4, 4, 1, file) <= 0)
		return 0;
	if (fcn_00430910(data + 8, 1, 1, file) <= 0)
		return 0;
	if (fcn_00430910(data + 9, 1, 1, file) <= 0)
		return 0;
	if (fcn_00430910(data + 0xa, 1, 1, file) <= 0)
		return 0;
	if (fcn_00430910(data + 0xb, 1, 1, file) <= 0)
		return 0;
	for (i = 0; i < 6; i++) {
		if (fcn_00430910(data + 0xc + i * 8, 4, 1, file) <= 0)
			return 0;
		if (fcn_00430910(data + 0x10 + i * 8, 4, 1, file) <= 0)
			return 0;
	}
	return 1;
}
