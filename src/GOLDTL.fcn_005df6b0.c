// FUNCTION: GOLD 0x005d3180
// SIZE: 386
// FUNCTION: GOLDTL 0x005df6b0
// SIZE: 386

void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

// SIZE 0x50
typedef struct {
	int a;
	int size;
	int c;
	int d;
	int kind;
	int pad[14];
	int id;
} Req;

extern __int64 g_666018;
extern int g_66601c;
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;

void __cdecl fcn_0051af00(char*, int, ...);
char* __cdecl fcn_005cd440(Req*, char*, int, int);
char* __cdecl fcn_00508e40(int);
void __cdecl fcn_004c5530(char*);
char* __cdecl fcn_005c6220(int, int*);
void __cdecl fcn_005dbe90(char*);

int __cdecl fcn_005df6b0(char* e, char* a2)
{
	int out;
	Req req;
	char msg[0xf8];
	char text[0x100];
	char buf[0x200];
	char line[0x400];
	char* r;
	char* p;

	if (e[2] == 6) {
		memset(&req, 0, sizeof(req));
		memset(&req.pad[2], -1, 0x20);
		fcn_0051af00(text, 0x9c);
		req.c = (*(int*)&g_666018);
		req.a = 1;
		req.size = 0x400;
		req.kind = 6;
		req.d = g_66601c;
		r = fcn_005cd440(&req, text, 0, 0);
	}
	else {
		r = fcn_00508e40(*(int*) (a2 + 4));
	}
	if (r == 0) {
		return 0;
	}
	*(int*) (msg + 8) = *(int*) (r + 4);
	msg[4] = (char) 0xa3;
	*(int*) (msg + 0xc) = -1;
	*(int*) (msg + 0x28) = (*(int*)&g_7f4c00);
	*(int*) (msg + 0x2c) = (*(int*)&g_7f4c04);
	*(int*) (msg + 0x30) = g_7f4c08;
	*(short*) (msg + 0x34) = g_7f4c0c;
	msg[0x36] = 1;
	fcn_004c5530(msg);
	if (e[2] == 6) {
		p = fcn_005c6220(**(unsigned short**) a2, &out);
		fcn_0051af00(buf, *(unsigned short*) (p + 0x18) + 1, *(unsigned short*) r);
		fcn_0051af00(line, 0xfe8, buf);
		fcn_005dbe90(line);
	}
	*(int*) (a2 + 0x10) = 1;
	return 1;
}
