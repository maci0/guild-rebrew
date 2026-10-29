#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern double g_662908;

int __cdecl fcn_004f4830(int idx, void* dst);
char* __cdecl fcn_00508e40(int a1);
int __cdecl gm_ResolveEntityById(char** out, int a2, int a3, int a4);
float __cdecl fcn_004f4ed0(unsigned short* key);
float __cdecl gm_RandomFloat01(void);
int __cdecl fcn_005c6270(char* a1, int a2);
int __cdecl fcn_004c5820(void* a1);

#pragma pack(1)
typedef struct {
	int a;
	pos14_7f4c00 pos;
	int b;
	int c;
	short d;
	char e;
	int f;
	int g;
	int h;
} msg_4f4f60;
#pragma pack()

/* ADDRESS: GOLDTL 0x004f4f60 */
int __cdecl fcn_004f4f60(int idx, int id, int a3, int a4, int a5)
{
	char rec[36];
	msg_4f4f60 msg;
	char* h1;
	char* h2;
	float f;
	char* hit;

	if (!fcn_004f4830(idx, rec)) {
		goto fail;
	}
	h1 = fcn_00508e40(a3);
	h2 = fcn_00508e40(a4);
	gm_ResolveEntityById(&hit, 0, 0, a5);
	switch ((unsigned char) *(int*) (rec + 0x14)) {
	case 1:
		if (*(int*) (rec + 0x18) != id) {
			goto fail;
		}
		break;
	case 2:
		if (*(int*) (rec + 0x18) == id) {
			goto fail;
		}
		break;
	case 6:
		if (*(int*) (rec + 0x18) > id) {
			goto fail;
		}
		break;
	case 5:
		if (*(int*) (rec + 0x18) >= id) {
			goto fail;
		}
		break;
	case 4:
		if (*(int*) (rec + 0x18) < id) {
			goto fail;
		}
		break;
	case 3:
		if (*(int*) (rec + 0x18) <= id) {
			goto fail;
		}
		break;
	case 7:
		if (*(int*) (rec + 0x18) == id || *(int*) (rec + 0x18) == 2) {
			goto fail;
		}
		break;
	default:
		goto fail;
	}
	f = fcn_004f4ed0((unsigned short*) h1);
	if (gm_RandomFloat01() < f) {
		goto fail;
	}
	if (fcn_005c6270(h1, 0x22a) != 0) {
		if (gm_RandomFloat01() > g_662908) {
			goto fail;
		}
	}
	msg.pos = g_7f4c00;
	msg.f = id;
	msg.e = rec[0];
	msg.b = a4;
	msg.c = a3;
	msg.d = *(short*) (rec + 0x10);
	msg.h = 1;
	msg.g = a5;
	return fcn_004c5820(&msg);
fail:
	return -1;
}
