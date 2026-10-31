#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;

char* __cdecl gm_LookupEntityRecordById(int id);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl he_fn_Handlung(void);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);
int __cdecl fcn_004c6040(int, int, int, int);
int __cdecl fcn_004c5620(int, char*);

/* ADDRESS: GOLDTL 0x0054aa70 */
void __cdecl fcn_0054aa70(char* u)
{
	char* r1;
	char buf[0x100];
	char* r2;
	char* p;
	pos14_7f4c00* stamp;

	r1 = gm_LookupEntityRecordById(*(int*) (u + 0xb0));
	r2 = gm_LookupEntityRecordById(*(int*) (u + 0xac));
	stamp = (pos14_7f4c00*) (u + 0xc5);
	*stamp = g_7f4c00;
	fcn_00500bb0(stamp, 0x18, 0, 0);
	*(short*) (u + 0xc9) = 0xa;
	*(int*) (u + 0xcb) = 0;
	*(pos14_7f4c00*) (u + 0x52) = g_7f4c00;
	if ((u[0x78] & 2) == 0) {
		return;
	}
	for (p = fcn_005463a0(1, 0, 0x2c); p != 0; p = he_fn_Handlung()) {
		if (*(int*) (p + 4) == *(int*) (u + 4)) {
			continue;
		}
		if (*(char*) (p + 0xc4) != *(char*) (u + 0xc4)) {
			continue;
		}
		if (*(int*) (p + 0xac) == *(int*) (u + 0xac)) {
			io_FormatTextBuffer(buf, 0x1bbe, *(unsigned short*) r2, *(unsigned short*) r1);
			fcn_00545d40(*(int*) (r2 + 4), *(int*) (r2 + 4), buf, 0, 0x5f5, 0);
			*(pos14_7f4c00*) (u + 0x52) = g_7f4c00;
			*(int*) (u + 0x84) = fcn_004c5620(-1, u);
			return;
		}
		if (*(int*) (u + 0xc5) > *(int*) (p + 0xc5)) {
			continue;
		}
		*stamp = *(pos14_7f4c00*) (p + 0xc5);
		fcn_00500bb0(stamp, 0x18, 0, 0);
		*(short*) (u + 0xc9) = 0xa;
		*(int*) (u + 0xcb) = 0;
	}
	*(int*) (u + 0xd4) = fcn_004c6040(*(int*) (u + 0xac), *(int*) (u + 0xb0), *(int*) (u + 4), 1);
	*(int*) (u + 0x84) = fcn_004c5620(0, u);
}
