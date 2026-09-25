#include <string.h>

typedef struct {
	short v[7];
} stamp14;
// SIZE 0xe

extern stamp14 g_7f4c00;
extern char* g_773da8;

int __cdecl fcn_004e8a80(int, void*);
void __cdecl fcn_004e8240(int, int, int, int, int);
int __cdecl fcn_0064eeec(char*);
void __cdecl fcn_004c5530(void*);

struct slot_4b11a0 {
	int kind;
	int id;
	int pad[4];
};
// SIZE 0x18

// FUNCTION: GOLDTL 0x4b11a0
// SIZE: 370

int __cdecl fcn_004b11a0(int a1, int a2, char* arg)
{
	struct slot_4b11a0 s;
	char m[0xf8];

	if (*arg != '-')
		return 0;
	if (fcn_004e8a80(0x1e, &s) != 0 && s.id != -1)
		fcn_004e8240(s.kind, 0, 0, 4, 0xff);
	if (fcn_004e8a80(0x1f, &s) != 0 && s.id != -1)
		fcn_004e8240(s.kind, 0, 0, 4, 0xff);
	if (fcn_004e8a80(0x20, &s) != 0 && s.id != -1)
		fcn_004e8240(s.kind, 0, 0, 4, 0xff);
	if (fcn_004e8a80(0x21, &s) != 0 && s.id != -1)
		fcn_004e8240(s.kind, 0, 0, 4, 0xff);
	fcn_0064eeec(arg + 1);
	memset(m, 0, sizeof(m));
	m[4] = (char) 0x80;
	*(int*) (m + 8) = *(int*) (g_773da8 + 4);
	*(int*) (m + 0xc) = -1;
	m[0x36] = 2;
	*(int*) (m + 0x58) = 4;
	*(stamp14*) (m + 0x28) = g_7f4c00;
	*(short*) (m + 0x2c) = 8;
	*(int*) (m + 0x2e) = 0;
	fcn_004c5530(m);
	return 1;
}
