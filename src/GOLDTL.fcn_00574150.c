


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

extern int g_6b8010;
extern int g_67a370;

void __cdecl fcn_004432d0(int, int);
int __cdecl fcn_00445600(int, int, int, char*);
void __cdecl fcn_004379a0(int, int, int, void*, struct list*);
char __cdecl fcn_00573de0(int v, int* list);

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
	saved = g_6b8010;
	fcn_004432d0(0, 1);
	sprintf(buf, "he_%i", *(int*) (a + 4));
	l.handle = fcn_00445600(0, 0x1c0, 0, buf);
	l.count = 0;
	fcn_004379a0(g_67a370, l.handle, 0x2c0, fcn_00573de0, &l);
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
