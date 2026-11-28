void __cdecl he_SendZigeunerMsg9f(char*, char*);

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

// SIZE 0xf8
struct msg {
	int f0;
	char b4;
	char pad[3];
	int f8;
	int fc;
	char pad2[0x18];
	pos14_7f4c00 pos;
	char b36;
	char pad3[0x21];
	char b58;
	char pad4[3];
	char b5c;
	char pad5[0x9b];
};




#include <string.h>

void __cdecl cm_SendCopyEntityData(struct msg*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, char*);

void __cdecl he_SendZigeunerMsg9f(char* a, char* b)
{
	struct msg m;
	char tag[100];
	char buf1[0x400];
	char buf2[0x400];
	int id;

	memset(&m, 0, sizeof(m));
	m.b4 = (char) 0x9f;
	m.f8 = *(int*) (b + 4);
	m.fc = -1;
	m.pos = gm_GameTime;
	m.b36 = 1;
	cm_SendCopyEntityData(&m);
	if (b == a) {
		id = 0x41dd;
		memcpy(tag, "_NACHRICHTEN_ZIGEUNER_02", 25);
	} else {
		id = 0x41dc;
		memcpy(tag, "_NACHRICHTEN_ZIGEUNER_01", 25);
	}
	io_FormatTextBuffer(buf1, 0x41e3);
	io_FormatTextBuffer(buf2, id, buf1);
	he_PostEntityMessage(*(int*) (b + 4), -1, buf2, 1, 0x5fb, tag);
}
