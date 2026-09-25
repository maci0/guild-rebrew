#include <string.h>

// SIZE 0xcc
struct query_40f400 {
	char name[0x40];
	char found[0x80];
	int count;
	int result;
	char flag;
};

extern char* g_67a370;

int __cdecl fcn_0040f3d0();
void __cdecl fcn_004379a0(char*, int, int, int (__cdecl*)(), struct query_40f400*);

// FUNCTION: GOLD 0x0040e4f0
// SIZE: 111
// FUNCTION: GOLDTL 0x40f400
// SIZE: 111

/* Script command: runs the name query callback over every object of the
 * current room. */
int __cdecl fcn_0040f400(char** args)
{
	struct query_40f400 q;

	strcpy(q.name, *args);
	strcpy(q.found, "");
	q.count = 0;
	q.result = 0;
	if (q.name[0] != 0) {
		fcn_004379a0(g_67a370, 0, 0xc0, fcn_0040f3d0, &q);
	}
	return 0;
}
