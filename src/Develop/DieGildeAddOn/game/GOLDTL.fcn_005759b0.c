


#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

char* __cdecl gm_LookupEntityRecordById(int);
int* __cdecl fcn_004ecc20(char*);
int __cdecl fcn_004ecd20(char*, int*);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl fcn_00529160(char*, int, int, char*);
void __cdecl fcn_004c35f0(void);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_005759b0(char* u)
{
	char* h;
	int* p;
	int r;

	h = gm_LookupEntityRecordById(*(int*) (u + 0xac));
	if (h != 0) {
		p = fcn_004ecc20(h);
		if (p != 0) {
			*(int*) (u + 0xb0) = *p;
			r = fcn_004ecd20(h, p);
			*(int*) (u + 0xb4) = r;
			*(int*) (u + 0xb8) = r;
			*(pos14_7f4c00*) (u + 0xbc) = g_7f4c00;
			*(pos14_7f4c00*) (u + 0x52) = g_7f4c00;
			fcn_00500bb0((pos14_7f4c00*) (u + 0x52), 0, 5, 0);
			*(int*) (u + 0x70) = 0;
			fcn_00529160(*(char**) (h + 0x16c), fcn_00502cd0(*(int*) (*(char**) (h + 0x16c) + 0x5d), 2, 6, 0, 0x24b),
			    *(unsigned short*) h, u);
			fcn_004c35f0();
			return;
		}
	}
	fcn_00546190(u);
}
