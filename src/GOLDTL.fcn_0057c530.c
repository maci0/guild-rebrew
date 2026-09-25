void __cdecl fcn_0057c530(char*, char*);

#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

extern struct pos14 g_7f4c00;

// SIZE 0xf8
struct msg {
	int f0;
	char b4;
	char pad[3];
	int f8;
	int fc;
	char pad2[0x18];
	struct pos14 pos;
	char b36;
	char pad3[0x21];
	char b58;
	char pad4[3];
	char b5c;
	char pad5[0x9b];
};

// FUNCTION: GOLD 0x00573ff0
// SIZE: 245
// FUNCTION: GOLDTL 0x57c530
// SIZE: 245

#include <string.h>

void __cdecl fcn_004c5530(struct msg*);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);

void __cdecl fcn_0057c530(char* a, char* b)
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
	m.pos = g_7f4c00;
	m.b36 = 1;
	fcn_004c5530(&m);
	if (b == a) {
		id = 0x41dd;
		memcpy(tag, "_NACHRICHTEN_ZIGEUNER_02", 25);
	} else {
		id = 0x41dc;
		memcpy(tag, "_NACHRICHTEN_ZIGEUNER_01", 25);
	}
	fcn_0051af00(buf1, 0x41e3);
	fcn_0051af00(buf2, id, buf1);
	fcn_00545d40(*(int*) (b + 4), -1, buf2, 1, 0x5fb, tag);
}
