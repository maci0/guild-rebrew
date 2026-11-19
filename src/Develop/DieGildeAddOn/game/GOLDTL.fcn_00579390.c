#include "client_data.h"



extern unsigned char g_773d75;

void __cdecl fcn_004c51a0(int, int, char, int);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl io_FormatTextBuffer(void*, int, int, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, int);

extern void __cdecl fcn_00500bb0(char*, int, int, int);

/* Timed action 0x8B (grave debt) START: due is now; late in the day (hour >= 0x17) the
 * action is rescheduled to 0xc with the longer delay, otherwise the short one. */
/* ADDRESS: GOLDTL 0x00579320 */
void __cdecl fcn_00579320(char* a0)
{
	*(pos14_7f4c00*) (a0 + 0x52) = gm_GameTime;
	if (*(unsigned short*) (a0 + 0x56) >= 0x17) {
		fcn_00500bb0(a0 + 0x52, 0x18, 0, 0);
		*(unsigned short*) (a0 + 0x56) = 0xc;
		*(int*) (a0 + 0x70) = 0;
		return;
	}
	fcn_00500bb0(a0 + 0x52, 6, 0, 0);
	*(int*) (a0 + 0x70) = 0;
}

void __cdecl fcn_00579390(void* a1, void* a2)
{
	char buf[0x400];

	fcn_004c51a0(*(int*) a1, *(int*) ((char*) a2 + 4),
	    g_773d75, *(int*) ((char*) a1 + 0xc));
	fcn_004c5420(*(int*) ((char*) a2 + 4), 0x1cc, 4, 1, 0);
	io_FormatTextBuffer(buf, 0x40fe, *(unsigned short*) a2, *(int*) ((char*) a1 + 0xc));
	fcn_00545d40(*(int*) a1, -1, buf, 1, 0x5f4, 0);
}
