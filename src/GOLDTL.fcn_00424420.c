#include <string.h>

int __cdecl fcn_00423a50(unsigned int a0);
int __cdecl fcn_004239e0(void);
char* __cdecl fcn_0041db70(unsigned int size, char* file);
int __cdecl fcn_00423920(unsigned int a0);
char* __cdecl strncpy(char* dst, const char* src, unsigned int n);

/* ADDRESS: GOLDTL 0x00424420 */
unsigned int __cdecl fcn_00424420(unsigned int a0)
{
	char* v2;
	char* v3;
	unsigned int v4;

	if (*(char**) 0x6b7d68 == 0) {
		return 0xffffffff;
	}
	v2 = (char*) fcn_00423a50(a0);
	if (v2 != 0) {
		return 0xffffffff;
	}
	v2 = (char*) fcn_004239e0();
	v3 = fcn_0041db70(0x108, (char*) 0x679000);
	v4 = a0;
	if (v2 != 0) {
		*(char**) (v2 + 0x104) = v3;
		if (v3 != 0) {
			memset(v3, 0, 0x108);
			strncpy(*(char**) (v2 + 0x104), (char*) a0, 0x100);
			v4 = fcn_00423920(v4);
			*(unsigned int*) (*(char**) (v2 + 0x104) + 0x100) = v4;
			*(int*) (*(char**) 0x6b7d68 + 0x34) = *(int*) (*(char**) 0x6b7d68 + 0x34) + *(int*) (*(char**) (v2 + 0x104) + 0x100);
			*(int*) 0x6b7d6c = *(int*) 0x6b7d6c + 1;
			return 0;
		}
	} else {
		*(char**) (*(char**) 0x6b7d68 + 0x38) = v3;
		v3 = *(char**) (*(char**) 0x6b7d68 + 0x38);
		if (v3 != 0) {
			memset(v3, 0, 0x108);
			strncpy(*(char**) (*(char**) 0x6b7d68 + 0x38), (char*) a0, 0x100);
			v4 = fcn_00423920(v4);
			*(unsigned int*) (*(char**) (*(char**) 0x6b7d68 + 0x38) + 0x100) = v4;
			*(int*) (*(char**) 0x6b7d68 + 0x34) = *(int*) (*(char**) 0x6b7d68 + 0x34) + *(int*) (*(char**) (*(char**) 0x6b7d68 + 0x38) + 0x100);
			*(int*) 0x6b7d6c = *(int*) 0x6b7d6c + 1;
			return 0;
		}
	}
	return 0xffffffff;
}
