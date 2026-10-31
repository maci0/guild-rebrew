#include "g_6abb08.h"
extern Offer g_6abb08[];

/* ADDRESS: GOLD 0x005ba7b0 */
/* ADDRESS: GOLDTL 0x005c6220 */
char* __cdecl fcn_005c6220(int key, int* out)
{
	int n;
	int v;

	v = *(int*) g_6abb08;
	n = 0;
	while (v != 0) {
		if (v == key) {
			if (out != 0) {
				*out = n;
			}
			return (char*) g_6abb08 + n * 0x1c;
		}
		n++;
		v = *(int*) ((char*) g_6abb08 + n * 0x1c);
	}
	return 0;
}
