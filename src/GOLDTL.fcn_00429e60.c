// FUNCTION: GOLD 0x0042b540
// SIZE: 112
// FUNCTION: GOLDTL 0x00429e60
// SIZE: 112

#include <string.h>

// SIZE 0x4c
typedef struct {
	char name[0x4c];
} Var;

extern Var* g_6b7e9c;

Var* __cdecl fcn_00429e60(const char* name)
{
	int i;
	Var* p;

	i = 0;
	for (p = g_6b7e9c; i < 0x100; i++, p++) {
		if (strcmp(p->name, name) == 0) {
			break;
		}
	}
	if (i < 0x100) {
		return &g_6b7e9c[i];
	}
	return 0;
}
