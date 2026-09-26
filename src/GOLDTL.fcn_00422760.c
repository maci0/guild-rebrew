extern int g_6b7d7c;

// SIZE 0x30
typedef struct {
	int a;
	int key;
	char pad[0x28];
} T422760;

#include "client_types.h"
// GLOBAL: GOLD 0x1460a20
extern Voice_14cbbe0 g_14cbbe0;
extern char* g_6b7e88;
// GLOBAL: GOLD 0x6332ac
extern int g_6b7e8c;

// FUNCTION: GOLD 0x004262f0
// SIZE: 96
// FUNCTION: GOLDTL 0x422760
// SIZE: 96

T422760* __cdecl fcn_00422760(int key, int* idx)
{
	T422760* r = 0;
	T422760* t;
	int i;
	int n;

	if (g_6b7d7c == 0) {
		return &(*(T422760*)&g_14cbbe0);
	}
	t = ((T422760*)g_6b7e88);
	if (t != 0) {
		n = g_6b7e8c;
		for (i = *idx; i < n; i++) {
			if (t[i].key == key) {
				*idx = i;
				r = &t[i];
				break;
			}
		}
	}
	return r;
}
