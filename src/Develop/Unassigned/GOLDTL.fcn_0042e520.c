/* ADDRESS: GOLDTL 0x006b7fe8 */
/* ADDRESS: GOLD 0x00633408 */
extern char g_6b7fe8;



#include <string.h>

/* ADDRESS: GOLD 0x0042ecf0 */
int __cdecl fcn_0042e520(int a)
{
	if (g_6b7fe8 != 0) {
		return a;
	}
	return (int) _strupr((char*) a);
}
