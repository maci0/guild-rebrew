#include "client_types.h"

extern pos14_7f4c00 g_current_year;
int __cdecl fcn_00500e20(int*);
void __cdecl fcn_00500c50(pos14_7f4c00*, int, int, int);

/* ADDRESS: GOLDTL 0x00566fa0 */
/* Timed action 0x3a (HE_SIM_PERSONAL) START: start = now, due = today 06:15:00. */
void __cdecl fcn_00566fa0(char* h)
{
	*(int*) (h + 0xb0) = 3;
	*(int*) (h + 0xac) = 0;
	fcn_00500e20((int*) &g_current_year);
	*(pos14_7f4c00*) (h + 0x52) = g_current_year;
	*(pos14_7f4c00*) (h + 0x44) = g_current_year;
	fcn_00500c50((pos14_7f4c00*) (h + 0x52), 6, 0xf, 0);
}



int __cdecl gm_CheckEntityType(char*);
char* __cdecl fcn_005049a0(char*);
char* __cdecl fcn_00502cd0(int, int, int, int);

int __cdecl fcn_00567030(char* h, int* out1, int* out2)
{
	int id;
	char* q;
	unsigned char k;

	id = -1;
	if (h == 0 || h[2] == 0xd || h[2] == 0xe || *(char**) (h + 0x16c) == 0 || *(char**) (h + 0x184) == 0) {
		return 0;
	}
	k = h[0x180];
	if (k == 0x3f || k == 0x40 || k == 0x48 || k == 0x3c || k == 0x49 || k == 0x44 || k == 0x62 || k == 0x61
	    || k == 0x65 || k == 0x64 || k == 0x14 || k == 0x75 || k == 0x1a || k == 0x18 || k == 0xa1) {
		return 0;
	}
	if (h[0x1b1] != 0) {
		return 0;
	}
	if (gm_CheckEntityType(*(char**) (h + 0x16c)) == 0) {
		if (*(int*) (*(char**) (h + 0x184) + 0x2c) == *(int*) (*(char**) (h + 0x16c) + 1)
		    || (q = fcn_005049a0(*(char**) (h + 0x16c))) == 0) {
			return 0;
		}
	} else {
		if (h[0x180] == 3 || h[0x180] == 8 || h[0x180] == 9) {
			q = fcn_00502cd0(*(int*) (*(char**) (h + 0x16c) + 0x5d), 1, 0, 0x37);
		} else {
			q = fcn_00502cd0(*(int*) (*(char**) (h + 0x16c) + 0x5d), 1, 0, 0xfd);
		}
		if (q == 0) {
			goto out;
		}
		if (*(int*) (q + 2) == *(int*) (*(char**) (h + 0x184) + 0x30)) {
			return 0;
		}
		if (*(short*) q == 0xfd) {
			goto out;
		}
	}
	id = *(int*) (q + 2);
out:
	*out1 = *(int*) (*(char**) (h + 0x16c) + 1);
	*out2 = id;
	return 1;
}
