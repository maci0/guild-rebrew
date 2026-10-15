


#include <string.h>

// SIZE 0xf8
struct msg {
	char pad0[4];
	unsigned char kind;
	char pad5[3];
	int id;
	int arg;
	char pad10[0x26];
	unsigned char code;
	char pad37[0x21];
	int value;
	int x;
	int y;
	char pad64[4];
	char name[0x30];
	char pad98[4];
	unsigned char flags;
	char pad9d[0x5b];
};

#include "Develop/Units/Error/error_message.h"
int __cdecl fcn_004c5580(struct msg*, int, char*);

int __cdecl fcn_00545e80(int id, int arg, char* text1, unsigned char flags, int value, int x, int y, char* name, char* text2)
{
	struct msg m;
	char text[0x1fa0];
	int len;

	memset(&m, 0, sizeof(m));
	m.kind = 0x11;
	m.id = id;
	m.arg = arg;
	m.code = 9;
	if (name != 0) {
		if (strlen(name) + 1 > 0x30) {
			fcn_0041d9e0("he_MessageBoxQuickjump(): contactname is too long!");
		} else {
			strcpy(m.name, name);
		}
	}
	m.value = value;
	m.x = x;
	m.flags = flags | 2;
	m.y = y;
	strcpy(text, text1);
	len = strlen(text1) + 1;
	if (text2 != 0 && *text2 != 0) {
		memcpy(text + len, text2, strlen(text2) + 1);
		m.flags |= 0x10;
		return fcn_004c5580(&m, len + strlen(text2) + 1, text);
	}
	return fcn_004c5580(&m, len, text1);
}
