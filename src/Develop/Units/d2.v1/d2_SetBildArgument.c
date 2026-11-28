#include "Develop/Units/d2.v1/d2_gui.h"

/* ADDRESS: GOLDTL 0x00472770 */
/* ADDRESS: GOLDDE 0x00465930 */
void __cdecl d2_SetBildArgument(int i, int v)
{
	*(int*) (d2_BildArgument2 + *(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[i].value_088)) * 0x160) = v;
}
