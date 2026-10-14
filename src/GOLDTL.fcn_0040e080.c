


#include <string.h>

// SIZE 0x4
typedef struct {
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
} Bytes4;

extern char* g_6b7e98;
void __cdecl fcn_0043a3f0(int a, int b, Bytes4 c);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl fcn_0040e080(char** a, unsigned char* v)
{
	Bytes4 col;
	int o;

	if (*a == 0) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
		return 1;
	}
	o = *(int*) (*a + 0x34);
	memset(&col, 0, sizeof(col));
	col.c &= 0xfe;
	col.a = *v;
	fcn_0043a3f0(o, *(int*) (o + 0x1cc), col);
	if (*(int*) (*a + 0x124) != 0) {
		o = **(int**) (*a + 0x124);
		fcn_0043a3f0(o, *(int*) (o + 0x1cc), col);
	}
	return 0;
}
