#include <string.h>

typedef struct Picks {
	char* item[0x20];
	int count;
} Picks;
// SIZE 0x84

extern int g_67a370;

void __cdecl fcn_004379a0(char*, int, int, void*, Picks*);
int __cdecl fcn_00406ee0(char*, Picks*);
int __cdecl fcn_00404e40(unsigned short);

// FUNCTION: GOLDTL 0x00407330
// SIZE: 96

/* Fills p through the fcn_00406ee0 scene callback and returns a random
 * entry, or 0 when p.count is 0. The inventory entry also holds a second
 * function at 0x407390 (632 bytes). */
char* __cdecl fcn_00407330(void)
{
	Picks p;

	memset(&p, 0, sizeof(p));
	fcn_004379a0(((char*)g_67a370), 0, 0x100, (void*) fcn_00406ee0, &p);
	if (p.count == 0) {
		return 0;
	}
	return p.item[(unsigned short) fcn_00404e40((unsigned short) p.count)];
}
