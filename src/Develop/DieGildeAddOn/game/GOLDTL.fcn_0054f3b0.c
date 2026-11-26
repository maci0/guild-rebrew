void __cdecl fcn_004c5620(int, char*);

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;




void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, char*);

void __cdecl he_AcceptDuell(char* o, char* a, char* b)
{
	char buf[0x400];

	cm_RequestChangeBits(*(int*) (a + 4), 0x1c8, 4, 0x400, 0);
	cm_RequestChangeBits(*(int*) (b + 4), 0x1c8, 4, 0x400, 0);
	if (a[2] == 6 || a[2] == 7) {
		io_FormatTextBuffer(buf, 0x1d83, *(unsigned short*) b, o + 0x52, *(unsigned short*) b);
		he_PostEntityMessage(*(int*) (a + 4), *(int*) (a + 4), buf, 0, 0x5fa,
		             "_DUELL_INTRO_EVENT_DUELLANTEN_HS_00");
	}
	if (b[2] == 6 || b[2] == 7) {
		io_FormatTextBuffer(buf, 0x1d82, *(unsigned short*) a, o + 0x52, *(unsigned short*) a);
		he_PostEntityMessage(*(int*) (b + 4), -1, buf, 0, 0x5fb, "_DUELL_INTRO_EVENT_DUELLANTEN_HS_00");
	}
	fcn_004c5620(2, o);
}
