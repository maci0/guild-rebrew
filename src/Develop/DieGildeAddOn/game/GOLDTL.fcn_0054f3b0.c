void __cdecl fcn_004c5620(int, char*);

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;




void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);

void __cdecl fcn_0054f3b0(char* o, char* a, char* b)
{
	char buf[0x400];

	fcn_004c5420(*(int*) (a + 4), 0x1c8, 4, 0x400, 0);
	fcn_004c5420(*(int*) (b + 4), 0x1c8, 4, 0x400, 0);
	if (a[2] == 6 || a[2] == 7) {
		io_FormatTextBuffer(buf, 0x1d83, *(unsigned short*) b, o + 0x52, *(unsigned short*) b);
		fcn_00545d40(*(int*) (a + 4), *(int*) (a + 4), buf, 0, 0x5fa,
		             "_DUELL_INTRO_EVENT_DUELLANTEN_HS_00");
	}
	if (b[2] == 6 || b[2] == 7) {
		io_FormatTextBuffer(buf, 0x1d82, *(unsigned short*) a, o + 0x52, *(unsigned short*) a);
		fcn_00545d40(*(int*) (b + 4), -1, buf, 0, 0x5fb, "_DUELL_INTRO_EVENT_DUELLANTEN_HS_00");
	}
	fcn_004c5620(2, o);
}
