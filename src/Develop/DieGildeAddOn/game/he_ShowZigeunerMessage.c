


#include <string.h>

int __cdecl gm_ApplyRandomDisease(char*, int*, int*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, char*);

void __cdecl he_ShowZigeunerMessage(char* a, char* b)
{
	int v0;
	int v1;
	char tag[100];
	char buf1[0x400];
	char buf2[0x400];
	int id;

	if (gm_ApplyRandomDisease(b, &v0, &v1) != 0) {
		if (b == a) {
			id = 0x41dd;
			memcpy(tag, "_NACHRICHTEN_ZIGEUNER_02", 25);
		} else {
			id = 0x41dc;
			memcpy(tag, "_NACHRICHTEN_ZIGEUNER_01", 25);
		}
		io_FormatTextBuffer(buf1, 0x41de, v0 + 0x1632);
		io_FormatTextBuffer(buf2, id, buf1);
		he_PostEntityMessage(*(int*) (b + 4), -1, buf2, 1, 0x5fb, tag);
	}
}
