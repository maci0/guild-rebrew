#include "Develop/DieGildeAddOn/game/ch_motion.h"
// FUNCTION: GOLD 0x004c9c10
// FUNCTION: GOLDTL 0x4ca7c0

extern char g_68b0d8[];

int __cdecl fcn_0064d41a(char*, char*, ...);
char* __cdecl fcn_004032b0(char*);
void __cdecl fcn_00406120(char*);
void __cdecl fcn_0040c120(char*, int, int);

int __cdecl fcn_004ca7c0(char* x, char* out)
{
	char buf[0x80];
	char* o;

	fcn_0064d41a(buf, g_68b0d8, *(int*) (x + 0x10));
	o = fcn_004032b0(buf);
	if (o == 0)
		return 2;
	fcn_00406120(o);
	if (out != 0) {
		out[0] = 2;
		out[1] = 0;
		*(int*) (out + 6) = 0;
	}
	return 0;
}
