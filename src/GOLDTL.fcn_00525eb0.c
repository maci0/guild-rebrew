void __cdecl fcn_00525e90(void);
/* ADDRESS: GOLDTL 0x007e2760 */
extern char g_7e2760[];
/* ADDRESS: GOLDTL 0x009ba1c0 */
extern char g_9ba1c0[];


#include <string.h>

#include "client_timer.h"

void __cdecl fcn_00525eb0(void)
{
	fcn_0042de90(fcn_00525e90, 0x47);
	memset(g_7e2760, 0, 0x300);
	memset(g_9ba1c0, 0, 0x100);
}
