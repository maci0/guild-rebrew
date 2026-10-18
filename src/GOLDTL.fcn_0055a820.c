#include "client_types.h"

int __cdecl fcn_004c5620(char, unsigned char*);

/* ADDRESS: GOLD 0x00552730 */
/* ADDRESS: GOLDTL 0x0055a820 */
void __cdecl fcn_0055a820(unsigned char* e)
{
    if ((e[0x78] & 4) == 0) {
        *(pos14_7f4c00*) (e + 0x52) = *(pos14_7f4c00*) (e + 0x44);
        *(int*) (e + 0x84) = fcn_004c5620(0, e);
    }
}
