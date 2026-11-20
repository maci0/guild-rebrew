#include <stdio.h>
#include <string.h>

char* __cdecl he_StartHandlungSearch(int, int, int);
char* __cdecl he_fn_Handlung(void);
int __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_004fa5b0(int, void*, void*);

/* ADDRESS: GOLDTL 0x004aa550 */
int __cdecl ai_DispatchPrivilege(unsigned short* a0, char* request, char* a2)
{
	char text[0x40];
	char msg[0x220];
	char text2[0x100];
	char* e;
	int r;
	char* format;

	if (*request != 0x10) {
		return 0;
	}
	memset(msg, 0, sizeof(msg));
	*(int*) (msg + 0x21c) = 0;
	if ((*(int*) ((char*) a0 + 0x1c8) & 0x100) && *(int*) (request + 8) == 4) {
		e = he_StartHandlungSearch(1, 0, 0x45);
		while (e != 0) {
			if (*(int*) (e + 0xac) == *(int*) ((char*) a0 + 4)) {
				*(int*) (msg + 0x21c) = gm_LookupEntityRecordById(*(int*) (e + 0xb0));
				break;
			}
			e = he_fn_Handlung();
		}
		if (e == 0) {
			return 0;
		}
	}
	*(int*) msg = *(int*) (request + 8);
	switch (*(int*) (request + 4)) {
	case 0:
		format = (char*) 0x67fb1c;
		break;
	case 3:
		format = (char*) 0x67fb04;
		break;
	case 4:
		format = (char*) 0x67faf4;
		break;
	case 7:
		format = (char*) 0x67fadc;
		break;
	case 8:
		format = (char*) 0x67fac8;
		break;
	default:
		return 0;
	}
	sprintf(text, format);
	*(int*) (msg + 0x214) = *(int*) (a2 + 4);
	sprintf(text2, (char*) 0x67fab0, a0 + 0x18, (int) *a0, text);
	r = fcn_004fa5b0(*(int*) (request + 4), a0, msg);
	return (r & 0x60) == 0;
}
