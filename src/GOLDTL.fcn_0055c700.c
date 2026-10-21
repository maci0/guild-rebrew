#include "he_tables.h"

void __cdecl fcn_00500bb0(Pos14*, int, int, int);

struct s_55c700 {
	char pad0[0x44];
	Pos14 src;
	Pos14 dst;
};

/* ADDRESS: GOLDTL 0x0055c700 */
void __cdecl fcn_0055c700(struct s_55c700* s)
{
	s->dst = s->src;
	fcn_00500bb0(&s->dst, 0, 0xf, 0);
}
