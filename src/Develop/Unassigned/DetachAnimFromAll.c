#include <string.h>

// SIZE 0xcc
struct query_40f400 {
	char name[0x40];
	char found[0x80];
	int count;
	int result;
	char flag;
};

extern int d3_ActiveScene;

int __cdecl d3_RemoveAnimationIfNameContains();
void __cdecl d3_VisitSceneObjects(char*, int, int, int (__cdecl*)(), struct query_40f400*);


/* Script command: runs the name query callback over every object of the
 * current room. */
/* ADDRESS: GOLDTL 0x0040f400 */
int __cdecl DetachAnimFromAll(char** args)
{
	struct query_40f400 q;

	strcpy(q.name, *args);
	strcpy(q.found, "");
	q.count = 0;
	q.result = 0;
	if (q.name[0] != 0) {
		d3_VisitSceneObjects(((char*)d3_ActiveScene), 0, 0xc0, d3_RemoveAnimationIfNameContains, &q);
	}
	return 0;
}
