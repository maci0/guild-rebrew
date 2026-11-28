


#include <string.h>

#include "Develop/Units/d3/client_lighting.h"

/* ADDRESS: GOLDDE 0x0043b100 */
char __cdecl d3_SetSubObjectVisibleCallback(char* o, char on)
{
	char buf[0x40];

	if (on != 0) {
		if (*(int*) (o + 0x218) == 1) {
			if (o[0] == '!') {
				strcpy(buf, o + 1);
				strcpy(o, buf);
			}
			if (*(int*) (o + 0x21c) == 5) {
				UpdateSceneLighting(0);
			}
			*(int*) (o + 0x218) = *(int*) (o + 0x21c);
		}
	} else if (*(int*) (o + 0x218) != 1) {
		*(int*) (o + 0x21c) = *(int*) (o + 0x218);
		*(int*) (o + 0x218) = 1;
	}
	return 1;
}
