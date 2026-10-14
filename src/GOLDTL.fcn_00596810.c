


typedef struct {
	int kind;
	char pad4[0x10];
} Lane;
// SIZE 0x14

typedef struct {
	int id;
	char pad4[0xc];
	int ent;
	char pad14[0x2c - 0x14];
	int f2c;
	int field;
	int value;
} Watch;
// SIZE 0x38

typedef struct {
	char pad0[0x20];
	int type;
	char pad24[0x2f4 - 0x24];
} Ent;
// SIZE 0x2f4

#include "client_types.h"

extern Lane g_778d4c[4];
extern Slot_778da0 g_778da0[16];
extern char* g_1015ea0;

unsigned short* __cdecl fcn_00502cd0(int, int, int, ...);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl gm_GetMsgField(char*, unsigned short*);
int __cdecl fcn_0050dfd0(char*, int);
int __cdecl fcn_00471f80(int);

int __cdecl fcn_00596810(char* msg, char* src)
{
	int tbl[17][4];
	unsigned short* p;
	unsigned short* q;
	int key;
	int i;
	int id;
	int result;

	tbl[0][0] = 2;
	tbl[0][1] = 0;
	tbl[0][2] = 0;
	tbl[0][3] = 0;
	tbl[1][0] = 2;
	tbl[1][1] = 0;
	tbl[1][2] = 0;
	tbl[1][3] = 0;
	tbl[2][0] = 2;
	tbl[2][1] = 0;
	tbl[2][2] = 0;
	tbl[2][3] = 0;
	tbl[3][0] = 3;
	tbl[3][1] = 0;
	tbl[3][2] = 0;
	tbl[3][3] = 0;
	tbl[4][0] = 4;
	tbl[4][1] = 0;
	tbl[4][2] = 0;
	tbl[4][3] = 0;
	tbl[5][0] = 3;
	tbl[5][1] = 2;
	tbl[5][2] = 0;
	tbl[5][3] = 0;
	tbl[6][0] = 4;
	tbl[6][1] = 2;
	tbl[6][2] = 0;
	tbl[6][3] = 0;
	tbl[7][0] = 4;
	tbl[7][1] = 3;
	tbl[7][2] = 0;
	tbl[7][3] = 0;
	tbl[8][0] = 4;
	tbl[8][1] = 4;
	tbl[8][2] = 0;
	tbl[8][3] = 0;
	tbl[9][0] = 4;
	tbl[9][1] = 3;
	tbl[9][2] = 2;
	tbl[9][3] = 0;
	tbl[10][0] = 4;
	tbl[10][1] = 3;
	tbl[10][2] = 3;
	tbl[10][3] = 0;
	tbl[11][0] = 4;
	tbl[11][1] = 4;
	tbl[11][2] = 3;
	tbl[11][3] = 0;
	tbl[12][0] = 4;
	tbl[12][1] = 4;
	tbl[12][2] = 4;
	tbl[12][3] = 0;
	tbl[13][0] = 4;
	tbl[13][1] = 4;
	tbl[13][2] = 3;
	tbl[13][3] = 2;
	tbl[14][0] = 4;
	tbl[14][1] = 4;
	tbl[14][2] = 3;
	tbl[14][3] = 3;
	tbl[15][0] = 4;
	tbl[15][1] = 4;
	tbl[15][2] = 4;
	tbl[15][3] = 3;
	tbl[16][0] = 4;
	tbl[16][1] = 4;
	tbl[16][2] = 4;
	tbl[16][3] = 4;
	for (i = 0; i < 4; i++) {
		g_778d4c[i].kind = tbl[(unsigned char) msg[0x1c]][i];
	}
	p = fcn_00502cd0(*(int*) (src + 0x14), 1, 5);
	while (p != 0) {
		for (i = 0, key = *p; i < 16; i++) {
			if (((Watch*) g_778da0)[i].id == key) {
				break;
			}
		}
		if (i >= 16) {
			for (i = 0; i < 16; i++) {
				if (((Watch*) g_778da0)[i].id == 0) {
					break;
				}
			}
			if (i < 16) {
				((Watch*) g_778da0)[i].id = key;
				((Watch*) g_778da0)[i].f2c = 0;
				((Watch*) g_778da0)[i].field = 0;
				((Watch*) g_778da0)[i].value = 0;
			}
		} else {
			((Watch*) g_778da0)[i].field = 0;
		}
		p = gm_NextEntityQueryMatch();
	}
	for (i = 0; i < 16; i++) {
		q = fcn_00502cd0(*(int*) (msg + 0x14), 1, 0, ((Watch*) g_778da0)[i].id);
		if (q != 0) {
			((Watch*) g_778da0)[i].field = gm_GetMsgField(msg, q);
			((Watch*) g_778da0)[i].value = fcn_0050dfd0(msg, *q);
		}
	}
	result = 0;
	for (i = 0; result == 0 && i < 16; i++) {
		id = ((Watch*) g_778da0)[i].ent;
		if (id != -1 && ((Ent*) g_1015ea0)[id].type == 0x41 && fcn_00471f80(id) != 0) {
			result = 1;
		}
	}
	return result;
}
