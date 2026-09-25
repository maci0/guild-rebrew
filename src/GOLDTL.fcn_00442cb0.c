// FUNCTION: GOLD 0x447260
// SIZE: 160
// FUNCTION: GOLDTL 0x442cb0
// SIZE: 147

#include <string.h>

void __cdecl fcn_00450a00(int);

char __cdecl fcn_00442cb0(char* o, char on)
{
	char buf[0x40];

	if (on != 0) {
		if (*(int*) (o + 0x218) == 1) {
			if (o[0] == '!') {
				strcpy(buf, o + 1);
				strcpy(o, buf);
			}
			if (*(int*) (o + 0x21c) == 5) {
				fcn_00450a00(0);
			}
			*(int*) (o + 0x218) = *(int*) (o + 0x21c);
		}
	} else if (*(int*) (o + 0x218) != 1) {
		*(int*) (o + 0x21c) = *(int*) (o + 0x218);
		*(int*) (o + 0x218) = 1;
	}
	return 1;
}
