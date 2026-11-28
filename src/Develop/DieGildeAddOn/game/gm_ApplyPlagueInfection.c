


typedef struct
{
	int a;
	float b;
	int c;
} S0c;
// SIZE 0xc

extern float flt_0_0;

int __cdecl gm_GetKindRecord(int k, S0c* s);
unsigned short __cdecl gm_RandomMod(unsigned short n);
#include "Develop/DieGildeAddOn/command/client_packet_builder.h"
void __cdecl cm_AppendPacketFieldDelta(int a, int b, int c, int* v);
void __cdecl cm_RequestChangeAttribute(void);
float __cdecl gm_ApplyEntityHealthDelta(unsigned short id, int v);

/* ADDRESS: GOLDDE 0x004f3610 */
float __cdecl gm_ApplyPlagueInfection(char* p)
{
	S0c s;
	int r;
	int flags;
	int nf;

	flags = *(int*) (p + 0x2c);
	if (flags & 0xf) {
		return flt_0_0;
	}
	if (!gm_GetKindRecord(1, &s)) {
		return flt_0_0;
	}
	r = gm_RandomMod((unsigned short) s.c);
	if (r == 0) {
		return flt_0_0;
	}
	nf = ((r ^ flags) & 0xf) ^ flags;
	cm_BeginPacketFieldDelta(p, *(int*) (p + 4));
	cm_AppendPacketFieldDelta(4, 1, 0x2c, &nf);
	cm_RequestChangeAttribute();
	return gm_ApplyEntityHealthDelta(*(unsigned short*) p, -(int) (r * s.b));
}
