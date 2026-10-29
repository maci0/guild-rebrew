char* __cdecl fcn_00508e40(int);
int __cdecl fcn_0064eeec(char*);
#include "client_packet_builder.h"
void __cdecl fcn_004c4670(int, int, int, char*);
void __cdecl fcn_004c5360(void);


/* ADDRESS: GOLDTL 0x004b0a20 */
int __cdecl fcn_004b0a20(int* a1, int a2, char* a3)
{
	char c = 0;
	char* e;

	if (*a3 != '-')
		return 0;
	c = (char) fcn_0064eeec(a3 + 1);
	if (a1 == 0 || a2 >= 8)
		return 0;
	e = fcn_00508e40(a1[a2 * 2 + 1]);
	if (e == 0)
		return 0;
	fcn_004c4510(e, *(int*) (e + 4));
	fcn_004c4670(1, 1, 0x1b1, &c);
	fcn_004c5360();
	return 1;
}
