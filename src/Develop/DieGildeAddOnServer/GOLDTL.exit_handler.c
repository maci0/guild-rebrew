#include <windows.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

// FUNCTION: GOLDTL 0x41fa00

int __stdcall exit_handler(int a, int b, int c)
{
	return 1;
}
