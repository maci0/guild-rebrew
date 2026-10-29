#include <string.h>

void __cdecl fcn_0051af00(char* out, int a, int b);
void __cdecl fcn_004fa5f0(void* buf, int a, int b);

/* ADDRESS: GOLDTL 0x004f8e60 */
int __cdecl fcn_004f8e60(char* a1, int* a2)
{
	char buf[0x400];

	if (a2[0] != 3 && a2[0] != 1) {
		return 1;
	}
	if (*(unsigned char*) (a1 + 0x166) != 0xe
	    && *(unsigned char*) (a1 + 0x166) != 0xa) {
		return 1;
	}
	if (a2[0] == 3) {
		if (*(unsigned char*) (a1 + 2) == 6) {
			memset(buf, 0, sizeof(buf));
			fcn_0051af00(buf, 0x1dc0, *(unsigned short*) a1);
			fcn_004fa5f0(buf, 1, 0x657c7);
			return 2;
		}
	}
	if (a2[0] == 1) {
		if (*(unsigned char*) (a1 + 2) == 6) {
			fcn_0051af00((char*) a2 + 0x14, 0x679060, 0x1dbf);
			return 2;
		}
	}
	return 2;
}
