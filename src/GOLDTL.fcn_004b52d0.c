// FUNCTION: GOLD 0x004b5160
// SIZE: 140
// FUNCTION: GOLDTL 0x4b52d0
// SIZE: 140

#pragma pack(2)
typedef struct {
	int t;
	unsigned short type;
	unsigned int f6;
	unsigned int f10;
} stamp14;
// SIZE 0xe
#pragma pack()

typedef struct {
	int f0;
	int f4;
	stamp14 st;
} holder;
// SIZE 0x18

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

void __cdecl sim_SetSyncParams(stamp14*, unsigned char, unsigned char, unsigned char);
int __cdecl fcn_00500d20(stamp14*, stamp14*);

int __cdecl fcn_004b52d0(holder* p, int flag, int limit)
{
	if (flag != 0) {
		if (p->st.t == 0 && p->st.type == 0 && p->st.f6 == 0 && p->st.f10 == 0) {
			p->st.t = (*(stamp14*)&g_7f4c00).t;
			sim_SetSyncParams(&p->st, (unsigned char) (*(stamp14*)&g_7f4c00).type, (unsigned char) (*(stamp14*)&g_7f4c00).f6,
			    (unsigned char) (*(stamp14*)&g_7f4c00).f10);
		}
		return fcn_00500d20(&p->st, &(*(stamp14*)&g_7f4c00)) >= limit;
	}
	p->st.t = 0;
	sim_SetSyncParams(&p->st, 0, 0, 0);
	return 0;
}
