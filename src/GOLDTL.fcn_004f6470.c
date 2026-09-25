// FUNCTION: GOLD 0x004f4080
// SIZE: 162
// FUNCTION: GOLDTL 0x004f6470
// SIZE: 162

#include <string.h>

#pragma pack(push, 1)
typedef struct
{
	int id;
	char p4[0xe];
	int x12;
	int x16;
	char p1a[2];
	unsigned char x1c;
	char p1d[8];
	unsigned int x25;
	char p29[4];
} Rec2d;
// SIZE 0x2d
#pragma pack(pop)

typedef struct
{
	int a;
	int b;
} Pair;
// SIZE 0x8

extern Rec2d g_9a3800[512];
extern Pair g_99f800[0x800];
extern char g_7f4ca0[];

void* __cdecl fcn_00508e40(int id);
int __cdecl fcn_004f5810(int b);

int __cdecl fcn_004f6470(int id, int* out, unsigned short k)
{
	char* e;
	int cnt;
	int i;
	int s;

	cnt = 0;
	if (fcn_00508e40(id) == 0) {
		return 0;
	}
	e = g_7f4ca0 + k * 0x21c;
	if (e == 0) {
		return 0;
	}
	memset(out, 0xff, 0x20 * 4);
	for (i = 0; i < 0x800; i++) {
		if (g_99f800[i].a == *(int*) (e + 4)) {
			s = fcn_004f5810(g_99f800[i].b);
			if (s != -1 && g_9a3800[s].x16 == id) {
				out[cnt] = g_9a3800[s].id;
				cnt++;
				if (cnt > 0x20) {
					break;
				}
			}
		}
	}
	return cnt;
}
