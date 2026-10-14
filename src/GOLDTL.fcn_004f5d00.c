


#include "client_types.h"
#pragma pack(push, 1)
typedef Rec2d_9a3800 Rec2d;
// SIZE 0x2d
#pragma pack(pop)

typedef struct
{
	int a;
	int b;
} Pair;
// SIZE 0x8

extern Rec2d_9a3800 g_9a3800[512];
extern Pair_99f800 g_99f800[0x800];

int __cdecl fcn_004f5d00(int a, int b, unsigned int st, int flag)
{
	int cnt;
	int i;
	int j;
	int id;

	cnt = 0;
	if (flag) {
		for (i = 0; i < 0x800; i++) {
			if (((Pair*)g_99f800)[i].a == a) {
				id = ((Pair*)g_99f800)[i].b;
				for (j = 0; j < 512; j++) {
					if (g_9a3800[j].id == id) {
						if (g_9a3800[j].x25 == 1 && g_9a3800[j].x16 == b) {
							g_9a3800[j].x25 = st;
							cnt++;
						}
						break;
					}
				}
			}
		}
		return cnt;
	}
	for (j = 0; j < 512; j++) {
		if (g_9a3800[j].x25 == st) {
			g_9a3800[j].x25 = 1;
			cnt++;
		}
	}
	return cnt;
}
