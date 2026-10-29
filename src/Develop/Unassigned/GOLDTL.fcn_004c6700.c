

#include <string.h>

int __cdecl fcn_004c4330(char*);

int __cdecl fcn_004c6700(char* e)
{
	char tmp[2][2];
	char buf[0x9c];
	char* q;
	int pos;
	int end;
	int i;

	tmp[0][0] = 0;
	tmp[0][1] = 0;
	tmp[1][0] = 0;
	tmp[1][1] = 0;
	q = *(char**) (e + 0x128);
	pos = *(int*) (q + 0xf8);
	end = *(int*) (q + 0xf0);
	for (i = 0; pos + i < end && i < 2; i++) {
		tmp[i][0] = (*(char**) (q + 0xf4))[(pos + i) * 2];
		tmp[i][1] = (*(char**) (q + 0xf4))[(pos + i) * 2 + 1];
	}
	buf[0] = 0x4f;
	strcpy(buf + 0x10, *(char**) (e + 0x34));
	*(int*) (buf + 0x28) = pos;
	*(int*) (buf + 0x2c) = end;
	*(short*) (buf + 0x30) = *(short*) tmp[0];
	*(short*) (buf + 0x32) = *(short*) tmp[1];
	return fcn_004c4330(buf);
}
