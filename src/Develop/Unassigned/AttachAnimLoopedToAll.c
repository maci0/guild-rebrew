


#include <string.h>

// SIZE 0xcc
typedef struct {
	char name[0x40];
	char name2[0x80];
	int a;
	int b;
	int found;
} Query;

extern int g_67a370;
void __cdecl d3_VisitSceneObjects(int a, int b, int c, void (__cdecl* cb)(void), Query* q);
void __cdecl d3_AttachMatchingAnimation(void);

int __cdecl AttachAnimLoopedToAll(char** name, char** name2, int* a, int* b)
{
	Query q;

	strcpy(q.name, *name);
	strcpy(q.name2, *name2);
	q.a = *a;
	q.b = *b;
	if (q.name[0] != 0) {
		d3_VisitSceneObjects(g_67a370, 0, 0x40, d3_AttachMatchingAnimation, &q);
	}
	return 0;
}
