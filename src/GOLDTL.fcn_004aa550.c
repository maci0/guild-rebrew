#include <stdio.h>
#include <string.h>

char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl fcn_005462a0(void);
int __cdecl fcn_00508e40(int);
int __cdecl fcn_004fa5b0(int, void*, void*);

/* ADDRESS: GOLDTL 0x004aa550 */
int __cdecl fcn_004aa550(unsigned short* a0, char* a1, char* a2)
{
	char text[0x40];
	char msg[0x220];
	char text2[0x100];
	char* e;
	int r;

	if (*a1 != 0x10) {
		return 0;
	}
	memset(msg, 0, sizeof(msg));
	*(int*) (msg + 0x21c) = 0;
	if ((*(int*) ((char*) a0 + 0x1c8) & 0x100) && *(int*) (a1 + 8) == 4) {
		e = fcn_005463a0(1, 0, 0x45);
		while (e != 0) {
			if (*(int*) (e + 0xac) == *(int*) ((char*) a0 + 4)) {
				*(int*) (msg + 0x21c) = fcn_00508e40(*(int*) (e + 0xb0));
				break;
			}
			e = fcn_005462a0();
		}
		if (e == 0) {
			return 0;
		}
	}
	*(int*) msg = *(int*) (a1 + 8);
	switch (*(int*) (a1 + 4)) {
	case 0:
		sprintf(text, (char*) 0x67fb1c);
		break;
	case 3:
		sprintf(text, (char*) 0x67fb04);
		break;
	case 4:
		sprintf(text, (char*) 0x67faf4);
		break;
	case 7:
		sprintf(text, (char*) 0x67fadc);
		break;
	case 8:
		sprintf(text, (char*) 0x67fac8);
		break;
	default:
		return 0;
	}
	*(int*) (msg + 0x214) = *(int*) (a2 + 4);
	sprintf(text2, (char*) 0x67fab0, a0 + 0x18, (int) *a0, text);
	r = fcn_004fa5b0(*(int*) (a1 + 4), a0, msg);
	return (r & 0x60) == 0;
}
