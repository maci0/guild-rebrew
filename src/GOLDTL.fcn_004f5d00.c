// FUNCTION: GOLD 0x004f3910
// SIZE: 148
// FUNCTION: GOLDTL 0x004f5d00
// SIZE: 148

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

int __cdecl fcn_004f5d00(int a, int b, unsigned int st, int flag)
{
	int cnt;
	int i;
	int j;
	int id;

	cnt = 0;
	if (flag) {
		for (i = 0; i < 0x800; i++) {
			if (g_99f800[i].a == a) {
				id = g_99f800[i].b;
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
