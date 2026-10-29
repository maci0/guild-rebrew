#include <windows.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"


/* ADDRESS: GOLDTL 0x0041fa00 */
int __stdcall exit_handler(int a, int b, int c)
{
	return 1;
}
