// FUNCTION: GOLD 0x004ecaa0
// SIZE: 138
// FUNCTION: GOLDTL 0x004ee830
// SIZE: 138

#include <string.h>

typedef struct
{
	int tag;
	int id;
	int x8;
	int xc;
	int x10;
	int x14;
} Msg18;
// SIZE 0x18

int __cdecl ahm_CheckFlag(char* p);
int __cdecl fcn_004ec9a0(char* p);
int* __cdecl fcn_004ecbe0(int id);
int __cdecl fcn_004c6d30(Msg18* m);

int __cdecl fcn_004ee830(char* p, int id)
{
	Msg18 m;
	int* q;

	if (!ahm_CheckFlag(p)) {
		return -1;
	}
	if (!fcn_004ec9a0(p)) {
		return -1;
	}
	q = fcn_004ecbe0(id);
	if (q == 0) {
		return -1;
	}
	memset(&m, 0, sizeof(m));
	m.tag = 0x61616452;
	m.id = *(int*) (p + 4);
	m.x8 = q[0];
	m.x10 = q[2];
	return fcn_004c6d30(&m);
}
