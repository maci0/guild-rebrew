// SIZE 0x6
typedef struct {
	int who;
	unsigned short op;
} fcn_004bbbd0_msg;

typedef int(__cdecl* fcn_004bbbd0_handler)(fcn_004bbbd0_msg*);

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern fcn_004bbbd0_handler g_6811b8[];

char* __cdecl gm_LookupEntityRecordById(int);


/* ADDRESS: GOLDTL 0x004bbbd0 */
int __cdecl fcn_004bbbd0(fcn_004bbbd0_msg* m)
{
	char* p;

	if ((*(int*)&g_7f4c00) < 8)
		return 0;
	if (m == 0)
		return -1;
	p = gm_LookupEntityRecordById(m->who);
	if (p == 0 || *(unsigned char*) (p + 0x1b1) > 0)
		return 0x400;
	if (m->op < 0x45)
		return g_6811b8[m->op](m);
	return -2;
}
