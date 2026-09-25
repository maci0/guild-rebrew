// FUNCTION: GOLD 0x0058f720
// SIZE: 83
// FUNCTION: GOLDTL 0x597ff0
// SIZE: 83

#include <string.h>

// SIZE 0x50
typedef struct {
	char name[0x20];
	int ids[12];
} Entry;

extern Entry g_6a9bf8[15];

int __cdecl fcn_00597ff0(int key, char* out)
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
