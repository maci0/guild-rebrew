


#include <stdlib.h>
#include <string.h>

// SIZE 0xc4
typedef struct {
	int list[0x20];
	int count;
	char name[0x40];
} Query;

extern int g_67a370;
#include "Develop/Units/m_alloc/m_alloc_checks.h"
void __cdecl d3_VisitSceneObjects(int a, int b, int c, void (__cdecl* cb)(void), Query* q);
void __cdecl d3_CollectMatchingSubObjects(void);

int __cdecl GetRndSubObjectHandle(int* a, char** name)
{
	Query q;

	if (*a == 0) {
		return 0;
	}
	if (!m_is_tracked((void*) *a)) {
		return 0;
	}
	memset(&q, 0, sizeof(q));
	strcpy(q.name, *name);
	d3_VisitSceneObjects(g_67a370, *a, 0x340, d3_CollectMatchingSubObjects, &q);
	if (q.count == 0) {
		return 0;
	}
	return q.list[rand() % q.count];
}
