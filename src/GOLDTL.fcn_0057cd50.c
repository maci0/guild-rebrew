


#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

char* __cdecl fcn_00508e40(int);
void __cdecl fcn_00546190(char*);
void __cdecl fcn_00508cf0(int, int*);

void __cdecl fcn_0057cd50(char* u)
{
	short kinds[4];
	int pick[4];
	char* h;
	int i;

	kinds[0] = 7;
	kinds[1] = 0x16;
	kinds[2] = 0xf;
	kinds[3] = 0xa;
	for (i = 0; i < 4; i++) {
		h = fcn_00508e40(*(int*) (u + 0x8c + i * 4));
		if (h != 0 && *(char**) (h + 0x16c) != 0 && *(int*) (*(char**) (h + 0x16c) + 1) == *(int*) (u + 0x10)) {
			*(pos14_7f4c00*) (u + 0x44) = g_7f4c00;
			*(pos14_7f4c00*) (u + 0x52) = g_7f4c00;
			fcn_00508cf0(4, pick);
			*(short*) (u + 0xce) = 0;
			*(short*) (u + 0xc0) = kinds[pick[0]];
			*(short*) (u + 0xc2) = kinds[pick[1]];
			*(short*) (u + 0xc4) = kinds[pick[2]];
			*(short*) (u + 0xc6) = kinds[pick[3]];
			*(short*) (u + 0xcc) = 0;
			*(short*) (u + 0xca) = 0;
			*(short*) (u + 0xc8) = 0;
			*(int*) (u + 0xac) = 0;
			*(int*) (u + 0xb0) = 0xf0;
			*(int*) (u + 0xb4) = 0xf0;
			*(int*) (u + 0xbc) = 0;
			*(int*) (u + 0xd0) = -1;
			*(int*) (u + 0x70) = 0;
			return;
		}
	}
	fcn_00546190(u);
}
