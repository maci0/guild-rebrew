// FUNCTION: GOLD 0x573a20
// FUNCTION: GOLDTL 0x57bf60

#include <string.h>

int __cdecl fcn_00508280(char*, int*, int*);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);

void __cdecl fcn_0057bf60(char* a, char* b)
{
	int v0;
	int v1;
	char tag[100];
	char buf1[0x400];
	char buf2[0x400];
	int id;

	if (fcn_00508280(b, &v0, &v1) != 0) {
		if (b == a) {
			id = 0x41dd;
			memcpy(tag, "_NACHRICHTEN_ZIGEUNER_02", 25);
		} else {
			id = 0x41dc;
			memcpy(tag, "_NACHRICHTEN_ZIGEUNER_01", 25);
		}
		fcn_0051af00(buf1, 0x41de, v0 + 0x1632);
		fcn_0051af00(buf2, id, buf1);
		fcn_00545d40(*(int*) (b + 4), -1, buf2, 1, 0x5fb, tag);
	}
}
