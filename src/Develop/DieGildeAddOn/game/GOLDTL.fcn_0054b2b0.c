


#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

int __cdecl cm_GetCommandStatus(int);
char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl fcn_00545d40(int, int, char*, unsigned char, int, char*);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
int __cdecl fcn_004c5620(int, char*);
void __cdecl he_FreeAction(char*);

void __cdecl he_HandleAction0x2e(char* u)
{
	char text[0x100];
	char* a;
	char* b;

	if (*(int*) (u + 0x70) != -1 && *(int*) (u + 0x70) != -2) {
		if (u[0x78] & 4) {
			return;
		}
		if (*(int*) (u + 0x84) != -1 && cm_GetCommandStatus(*(int*) (u + 0x84)) == 0) {
			return;
		}
		*(int*) (u + 0x84) = -1;
		a = gm_LookupEntityRecordById(*(int*) (u + 0xac));
		b = gm_LookupEntityRecordById(*(int*) (u + 0xb0));
		if (b == 0 || a == 0) {
			*(pos14_7f4c00*) (u + 0x52) = gm_GameTime;
			*(int*) (u + 0x84) = fcn_004c5620(-1, u);
			return;
		}
		if (*(int*) (u + 0x70) != 0) {
			return;
		}
		if (u[0x78] & 2) {
			io_FormatTextBuffer(text, 0x175d, *(unsigned short*) a);
			fcn_00545d40(*(int*) (b + 4), -1, text, 0, 0x5fa, 0);
		}
		*(pos14_7f4c00*) (u + 0x52) = gm_GameTime;
		gm_AddTime((pos14_7f4c00*) (u + 0x52), 0, 1, 0);
		*(int*) (u + 0x84) = fcn_004c5620(-1, u);
	} else {
		he_FreeAction(u);
	}
}
