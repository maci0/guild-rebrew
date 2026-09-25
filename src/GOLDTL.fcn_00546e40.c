void __cdecl fcn_00546e40(int a1, int a2, char* a3, int a4, void* a5);

#pragma pack(2)
// SIZE 0xe
struct pos14_546e40 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

// SIZE 0xa4
struct s_7d2020 {
	int f0;
	char f4;
	char pad[3];
	int f8;
	int fc;
	int f10;
	struct pos14_546e40 pos;
	char name[0x80];
};

extern struct s_7d2020 g_7d2020[256];

// FUNCTION: GOLDTL 0x546e40
// SIZE: 131

#include <string.h>

void __cdecl fcn_00546e40(int a1, int a2, char* a3, int a4, void* a5)
{
	int i;
	struct s_7d2020* t;

	for (i = 0; i < 256; i++) {
		if (g_7d2020[i].f0 == 0) {
			break;
		}
	}
	if (i < 256) {
		t = &g_7d2020[i];
		t->f0 = a1;
		t->fc = a2;
		t->f10 = a4;
		t->f8 = 1;
		t->f4 = 2;
		strncpy(t->name, a3, 0x7f);
		t->pos = *(struct pos14_546e40*) a5;
	}
}
