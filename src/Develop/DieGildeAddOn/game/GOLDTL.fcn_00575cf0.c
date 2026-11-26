


#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern float g_6628a8;

char* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl fcn_004ecbe0(int);
float __cdecl fcn_004ecd50(char*, char*, int*);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl fcn_00529160(char*, int, int, char*);
void __cdecl fcn_004c35f0(void);
void __cdecl he_FreeAction(char*);

void __cdecl fcn_00575cf0(char* u)
{
	char* h;
	char* p;

	h = gm_LookupEntityRecordById(*(int*) (u + 0xac));
	if (h != 0) {
		p = fcn_004ecbe0(*(int*) (u + 0xb0));
		if (p != 0) {
			*(float*) (u + 0xb4) = fcn_004ecd50(h, p, (int*) (u + 0xbc));
			if (!(*(float*) (u + 0xb4) <= g_6628a8)) {
				*(int*) (u + 0xb8) = *(int*) (u + 0xbc);
				*(pos14_7f4c00*) (u + 0xc0) = gm_GameTime;
				*(pos14_7f4c00*) (u + 0x52) = gm_GameTime;
				gm_AddTime((pos14_7f4c00*) (u + 0x52), 0, 5, 0);
				*(int*) (u + 0x70) = 0;
				fcn_00529160(*(char**) (h + 0x16c),
				    fcn_00502cd0(*(int*) (*(char**) (h + 0x16c) + 0x5d), 2, 6, 0, 0x24b), *(unsigned short*) h, u);
				fcn_004c35f0();
				return;
			}
		}
	}
	he_FreeAction(u);
}
