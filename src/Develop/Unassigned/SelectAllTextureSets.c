#include <string.h>

// SIZE 0xcc
struct query_40f4b0 {
	char name[0x40];
	char found[0x80];
	int count;
	int result;
	char flag;
};

extern char str_empty[];
extern int d3_ActiveScene;

int __cdecl d3_SelectMatchingTextureSet();
void __cdecl d3_VisitSceneObjects(char*, int, int, int (__cdecl*)(), struct query_40f4b0*);

/* ADDRESS: GOLDTL 0x0040f4b0 */
int __cdecl SelectAllTextureSets(char** args, char* pflag)
{
	struct query_40f4b0 q;

	strcpy(q.name, *args);
	q.found[0] = (*(char*)str_empty);
	q.count = 0;
	q.result = 0;
	q.flag = *pflag;
	if (q.name[0] != 0) {
		d3_VisitSceneObjects(((char*)d3_ActiveScene), 0, 0xc0, d3_SelectMatchingTextureSet, &q);
	}
	return 0;
}
