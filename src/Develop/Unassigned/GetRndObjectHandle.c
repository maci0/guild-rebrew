


#include <stdlib.h>
#include <string.h>

// SIZE 0xc4
typedef struct {
	int list[0x20];
	int count;
	char name[0x40];
} Query;

extern int d3_ActiveScene;
void __cdecl d3_VisitSceneObjects(int a, int b, int c, void (__cdecl* cb)(void), Query* q);
void __cdecl d3_CollectMatchingSubObjects(void);

int __cdecl GetRndObjectHandle(char** name)
{
	Query q;

	memset(&q, 0, sizeof(q));
	strcpy(q.name, *name);
	d3_VisitSceneObjects(d3_ActiveScene, 0, 0x140, d3_CollectMatchingSubObjects, &q);
	if (q.count == 0) {
		return 0;
	}
	return q.list[rand() % q.count];
}
