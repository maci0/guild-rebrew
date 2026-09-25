// FUNCTION: GOLD 0x00499a80
// SIZE: 240
// FUNCTION: GOLDTL 0x4994c0
// SIZE: 240

#include <string.h>

extern float g_10092c0[16];
extern char g_67eac4[];

char* __cdecl gm_SearchTable67(int id);
void __cdecl fcn_004c4eb0(char* s);
void __cdecl fcn_004c4ef0(char* s);
void __cdecl fcn_004c5530(char* msg);

int __cdecl fcn_004994c0(char* e, char* cmd)
{
	char msg[0xf8];
	char* t;
	char* o;

	if (*cmd != 4) {
		return 0;
	}
	t = gm_SearchTable67(*(int*) (cmd + 4));
	if (t == 0) {
		return 0;
	}
	memset(msg, 0, sizeof(msg));
	msg[4] = 0x19;
	*(int*) (msg + 8) = *(int*) (e + 4);
	o = *(char**) (e + 0x170);
	if (o != 0) {
		*(int*) (msg + 0xc) = *(int*) (o + 1);
	} else {
		*(int*) (msg + 0xc) = -1;
	}
	msg[0x36] = 1;
	*(int*) (msg + 0x58) = *(int*) (t + 1);
	*(int*) (msg + 0x7c) = *(int*) (cmd + 0x10);
	fcn_004c4eb0(g_67eac4);
	fcn_004c5530(msg);
	fcn_004c4ef0(g_67eac4);
	g_10092c0[8] = g_10092c0[0] * *(float*) (cmd + 0x14);
	g_10092c0[10] = g_10092c0[2] * *(float*) (cmd + 0x14);
	g_10092c0[12] = g_10092c0[4] * *(float*) (cmd + 0x14);
	g_10092c0[14] = g_10092c0[6] * *(float*) (cmd + 0x14);
	return 0x17;
}
