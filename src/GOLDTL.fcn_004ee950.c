// FUNCTION: GOLDTL 0x004ee950
// SIZE: 111

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

int __cdecl ahm_CheckFlag(char* p);
int __cdecl fcn_004ec950(char* p, int id);
int __cdecl fcn_004c6d30(Msg18* m);

int __cdecl fcn_004ee950(char* p, int id)
{
	Msg18 m;

	if (!ahm_CheckFlag(p)) {
		return -1;
	}
	if (!fcn_004ec950(p, id)) {
		return -1;
	}
	memset(&m, 0, sizeof(m));
	m.tag = 0x61736452;
	m.id = *(int*) (p + 4);
	m.x8 = id;
	return fcn_004c6d30(&m);
}
