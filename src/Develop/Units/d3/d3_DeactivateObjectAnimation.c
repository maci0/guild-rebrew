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
/* SIZE 0x7c */

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00435810 */
void __cdecl d3_DeactivateObjectAnimation(char* base, char* name)
{
	char* p;
	char* s;
	int k;

	if (base == 0) {
		return;
	}
	p = base + 0x90;
	for (k = 3; k != 0; k--, p += 0x7c) {
		s = *(char**) (p - 0xc);
		if (s != 0 && strcmp(name, s) == 0) {
			*p &= 0xfd;
		}
	}
}
#else
/* ADDRESS: GOLDTL 0x004355d0 */
void __cdecl d3_DeactivateObjectAnimation(char* a, const char* name)
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
#endif
