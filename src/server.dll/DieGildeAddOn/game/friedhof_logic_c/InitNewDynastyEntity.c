/* InitNewDynastyEntity - initializes a dynasty entity: sets its link flags,
 * fills the static field buffers with random height values, initializes the
 * entity's geometry/speed fields and spawn stats (5 values), then links it
 * into the season-based entity table. */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x100122e0
// SYMBOL: _InitNewDynastyEntity

#include <string.h>

extern int __cdecl rand_mod(int n);
extern int __cdecl _ftol(void);
extern int __cdecl find_entity_26(int entity_id);
extern int __cdecl find_entity_27(int entity_id);
extern int __cdecl fcn_10016cd0(int a, int b, int c);
extern unsigned char g_current_season;

int __cdecl InitNewDynastyEntity(int a, void* unused, unsigned short word_arg, void* entity)
{
	int i;
	int j;
	char* p;
	int flags;

	(void) unused;

	if (a == 0x15) {
		flags = *(int*) ((char*) entity + 0x1cc);
		flags |= 0x1000;
		*(int*) ((char*) entity + 0x1cc) = flags;
		find_entity_26(*(int*) ((char*) entity + 4));
	} else {
		flags = *(int*) ((char*) entity + 0x1cc);
		flags |= 0x2000;
		*(int*) ((char*) entity + 0x1cc) = flags;
		find_entity_27(*(int*) ((char*) entity + 4));
	}
	*(unsigned short*) ((char*) entity + 0xa) = word_arg;
	*(char*) ((char*) entity + 0xc) = 0;
	for (p = (char*) 0x100a9820; p < (char*) 0x10139820; p += 0x300) {
		for (i = 0; i < 0x300; i++) {
			p[i] = (char) (rand_mod(0x40) - 0x20);
			((char*) 0x1014d8e0)[(p - (char*) 0x100a9820) + i] = 0;
		}
	}
	*(unsigned short*) ((char*) entity + 0x50) = 0x7fff;
	*(int*) ((char*) entity + 0x7c) = 0;
	*(char*) ((char*) entity + 0x58) = 0;
	memset((char*) entity + 0x5c, 0xff, 0x20);
	*(int*) ((char*) entity + 0x170) = 0;
	*(int*) ((char*) entity + 0x16c) = 0;
	*(float*) ((char*) entity + 0x1c) = 1000.0f;
	*(float*) ((char*) entity + 0x14) = 1.0f;
	*(float*) ((char*) entity + 0x20) = 12.0f;
	*(float*) ((char*) entity + 0x10) = 330.0f;
	*(float*) ((char*) entity + 0x18) = 1000.0f;
	for (j = 0; j < 5; j++) {
		*(char*) ((char*) entity + 0x80 + j) =
			(char) (long) ((float) (rand_mod(0x2a) & 0xffff) + *(float*) 0x10025808);
	}
	*(char*) ((char*) entity + 0xd) = 9;
	fcn_10016cd0(*(int*) ((char*) entity + 4),
	             *(unsigned short*) ((char*) 0x100a8c94 + (unsigned int) g_current_season * 756),
	             1000000);
	rand_mod(2);
	*(char*) ((char*) entity + 2) = 3;
}
