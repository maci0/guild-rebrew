


#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern char g_6a59fc[];

void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl he_PostEntityMessage(int, int, char*, unsigned char, int, char*);
int __cdecl fcn_004c5620(int, char*);

void __cdecl he_StartAction0x4b(char* u)
{
	char text[0x400];
	char* a;
	char* b;

	*(int*) (u + 0x84) = -1;
	if (u[0x78] & 4) {
		return;
	}
	*(pos14_7f4c00*) (u + 0x52) = gm_GameTime;
	gm_AddTime((pos14_7f4c00*) (u + 0x52), 0x18, 0, 0);
	if (u[0x78] & 2) {
		b = gm_LookupEntityRecordById(*(int*) (u + 0xb0));
		a = gm_LookupEntityRecordById(*(int*) (u + 0xac));
		if (a == 0 || b == 0) {
			*(pos14_7f4c00*) (u + 0x52) = gm_GameTime;
			fcn_004c5620(-1, u);
			return;
		}
		if (b[2] == 6 || b[2] == 7) {
			io_FormatTextBuffer(text, 0x1d64, *(unsigned short*) a, (pos14_7f4c00*) (u + 0x52), *(unsigned short*) a);
			he_PostEntityMessage(*(int*) (b + 4), -1, text, 0, 0x5fb, g_6a59fc);
		}
	}
	fcn_004c5620(0, u);
}
