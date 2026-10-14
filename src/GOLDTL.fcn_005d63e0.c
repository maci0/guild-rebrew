

#include <string.h>

// SIZE 0xf8
#include "client_types.h"
struct msg {
	int f0;
	char b4;
	char pad5[3];
	int f8;
	int fc;
	char pad10[0x18];
	pos14_7f4c00 pos;
	char b36;
	char pad37[0x21];
	int f58;
	int f5c;
	char pad60[0x98];
};

// SIZE 0x50
typedef struct {
	int a;
	int size;
	__int64 cd;
	int kind;
	int pad[15];
} Req;

extern pos14_7f4c00 g_7f4c00;
extern __int64 g_666018;

unsigned char* __cdecl fcn_00508e40(int);
void __cdecl fcn_004c6ae0(int, int);
void __cdecl fcn_004c5530(struct msg*);
void __cdecl fcn_0051af00(char*, int, ...);
int __cdecl fcn_005cd440(Req*, char*, int, void*);
void __cdecl fcn_005d61d0(void);

/* The message struct is local to the branch that sends it: with it at function
   scope the header stores before the e+4 load issue ahead of the push. */
int __cdecl fcn_005d63e0(unsigned char* obj, char* arg)
{
	Req req;
	char text[0x40];
	unsigned char* e;
	int result;

	result = 0;
	if (obj[2] != 6 && obj[2] != 7) {
		e = fcn_00508e40(*(int*) (arg + 0x214));
		if (e == 0) {
			return 0x60;
		}
		{
			struct msg m;

			fcn_004c6ae0(*(int*) (obj + 4), -2);
			memset(&m, 0, sizeof(m));
			m.b4 = 0x4b;
			m.f8 = *(int*) (obj + 4);
			m.fc = *(int*) (obj + 4);
			m.pos = g_7f4c00;
			m.b36 = 2;
			m.f5c = *(int*) (e + 4);
			m.f58 = *(int*) (obj + 4);
			fcn_004c5530(&m);
			return 0x10;
		}
	}
	memset(&req, 0, sizeof(req));
	req.size = 0x400;
	req.kind = 6;
	req.cd = g_666018;
	fcn_0051af00(text, 0x1d61);
	if (fcn_005cd440(&req, text, 0, fcn_005d61d0)) {
		result = 1;
	}
	return result;
}
