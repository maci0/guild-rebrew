

#include <string.h>

// SIZE 0x4
typedef struct Col {
	unsigned char a;
	unsigned char b;
	unsigned char c0 : 1;
	unsigned char c1 : 1;
	unsigned char c2 : 6;
	unsigned char d;
} Col;

// SIZE 0x14
typedef struct Tex {
	int h;
	int* owner;
	int x8;
	unsigned int id;
	char flag;
} Tex;

extern int g_6b89b8;
extern char g_6b89bd;
extern char g_67bcb0[];

void __cdecl fcn_0045bfb0(int);
int __cdecl fcn_0045d0d0(char*, unsigned int, int, int, Col, int, int, char);

int __cdecl fcn_00456590(Tex* t, int* owner, char flag, unsigned int id, int x8)
{
	Col c;

	t->x8 = x8;
	owner[3] = (int) t;
	if (t->id > 0 && t->owner != 0) {
		*t->owner = 0;
	}
	t->owner = owner;
	if (t->id != id || t->flag != flag) {
		if (t->h != 0) {
			fcn_0045bfb0(t->h);
		}
		memset(&c, 0, sizeof(c));
		c.c1 = 1;
		t->id = id;
		t->flag = flag;
		c.a = 0x7f;
		t->h = fcn_0045d0d0(g_67bcb0, id, g_6b89b8, g_6b89bd != 0, c, 0, 0, flag);
	}
	return t->h;
}
