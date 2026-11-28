


#include <string.h>
#include "Develop/DieGildeAddOn/game/client_placement.h"

// SIZE 0x50
typedef struct {
	char name[0x20];
	int ids[12];
} Entry;

extern Entry g_6a9bf8[15];

/* ADDRESS: GOLDDE 0x0057d7a0 */
int __cdecl lc_GetBauplatzPrefix(int key, char* out)
{
	int i;
	int j;
	int* p;

	for (i = 0; i < 15; i++) {
		for (j = 0, p = g_6a9bf8[i].ids; j < 12; j++, p++) {
			if (*p == key) {
				strcpy(out, g_6a9bf8[i].name);
				return 1;
			}
		}
	}
	return 0;
}
