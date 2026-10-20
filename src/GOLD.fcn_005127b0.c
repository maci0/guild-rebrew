#include <string.h>

/* ADDRESS: GOLD 0x005127b0 */
void __cdecl fcn_005127b0(char* e)
{
	if (strstr(e, "gate")) {
		e[0x211] &= 0xfe;
		*(int*) (e + 0x224) = 1;
	} else {
		*(int*) (e + 0x224) = 0;
	}
}
