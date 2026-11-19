


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// SIZE 0x108
struct list {
	int handle;
	char* e[0x40];
	int count;
};

#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_67a370;

void __cdecl fcn_004432d0(int, int);
int __cdecl fcn_00445600(int, int, int, char*);
void __cdecl d3_VisitSceneObjects(int, int, int, void*, struct list*);
char __cdecl d3_CollectObjectCallback(int v, int* list);

int __cdecl fcn_00574150(char* a)
{
	int best;
	int saved;
	char tmp[0x10];
	int vals[8];
	struct list l;
	char name[0x80];
	char buf[0x80];
	char* p;
	int i;
	int n;

	best = 0;
	saved = d3_CurrentContextIndex;
	fcn_004432d0(0, 1);
	sprintf(buf, "he_%i", *(int*) (a + 4));
	l.handle = fcn_00445600(0, 0x1c0, 0, buf);
	l.count = 0;
	d3_VisitSceneObjects(g_67a370, l.handle, 0x2c0, d3_CollectObjectCallback, &l);
	for (i = 1; i < l.count; i++) {
		n = 0;
		*(int*) (l.e[i] + 0x224) = 0;
		strcpy(name, l.e[i]);
		p = strrchr(name, '_');
		if (p == 0) {
			continue;
		}
		while (p != 0 && n < 2) {
			strncpy(tmp, p + 1, 2);
			tmp[2] = 0;
			if (isdigit(tmp[0])) {
				vals[n] = atoi(tmp);
				n++;
			}
			*p = 0;
			p = strrchr(p, '_');
		}
		if (n != 0 && vals[0] > best) {
			best = vals[0];
		}
	}
	fcn_004432d0(saved, 1);
	return best;
}
