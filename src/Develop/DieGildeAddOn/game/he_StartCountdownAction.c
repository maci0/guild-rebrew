#include "Develop/client_types.h"

int __cdecl cm_SendSetHE(char, unsigned char*);

/* ADDRESS: GOLDTL 0x0055a820 */
/* ADDRESS: GOLDDE 0x00540b10 */
void __cdecl he_StartCountdownAction(unsigned char* e)
{
    if ((e[0x78] & 4) == 0) {
        *(pos14_7f4c00*) (e + 0x52) = *(pos14_7f4c00*) (e + 0x44);
        *(int*) (e + 0x84) = cm_SendSetHE(0, e);
    }
}
