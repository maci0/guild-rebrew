


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
	char pad5c[0x40];
	unsigned char flags;
	char pad9d[0x5b];
};

char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl cm_SendRawEntityPacket(struct msg*, int, char*);

int __cdecl he_PostEntityMessage(int id, int arg, char* text1, unsigned char flags, int value, char* text2)
{
	struct msg m;
	char text[0x1fa0];
	char* e;
	int len;
	int result;

	e = gm_LookupEntityRecordById(id);
	if (e != 0 && (e[2] == 6 || e[2] == 7)) {
		memset(&m, 0, sizeof(m));
		m.id = id;
		m.arg = arg;
		m.kind = 0x11;
		m.code = 9;
		m.value = value;
		m.flags = flags;
		strcpy(text, text1);
		len = strlen(text1) + 1;
		if (text2 != 0 && *text2 != 0) {
			memcpy(text + len, text2, strlen(text2) + 1);
			m.flags = flags | 0x10;
			result = cm_SendRawEntityPacket(&m, len + strlen(text2) + 1, text);
		} else {
			result = cm_SendRawEntityPacket(&m, len, text1);
		}
		return result;
	}
	return -1;
}
