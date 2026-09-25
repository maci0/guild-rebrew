#include <string.h>

typedef struct Ent7c {
	int f0;
	int f4;
	char pad8[0x5c];
	char* name;
	int f68;
	int f6c;
	unsigned char b0 : 1;
	unsigned char b1 : 1;
	char pad71[0xb];
} Ent7c;

// FUNCTION: GOLDTL 0x4355d0
// SIZE: 95
void __cdecl fcn_004355d0(char* a, const char* name)
{
	int i;
	Ent7c* e;

	if (a != 0) {
		e = (Ent7c*) (a + 0x32c);
		for (i = 3; i != 0; i--) {
			if (e->name != 0 && strcmp(name, e->name) == 0) {
				e->b1 = 0;
			}
			e++;
		}
	}
}
