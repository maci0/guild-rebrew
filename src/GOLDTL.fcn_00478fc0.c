#pragma pack(push, 1)
// SIZE 0x2a
typedef struct {
	char p0[6];
	unsigned short h;
	char p8[4];
	unsigned char kind;
	char pd[0x19];
	int x26;
} Spr;
#pragma pack(pop)

// SIZE 0x20
typedef struct {
	char p0[0x10];
	int x10;
	char p14[8];
	int bits;
} Surf;

extern int g_100ef80;
extern int g_67d964;
extern int g_7725f8;
extern int g_67d96c;
extern int g_100f1bc;

void __cdecl fcn_00478fa0(int, int, Surf*, Spr*);
void __cdecl fcn_004774e0(int, int, int, Spr*);
void __cdecl fcn_0047a320(int, int, int, Spr*);
void __cdecl fcn_00477500(int, int, int, Spr*);
void __cdecl fcn_004774f0(int, int, int, Spr*);

// FUNCTION: GOLD 0x47bd60
// FUNCTION: GOLDTL 0x00478fc0

int __cdecl fcn_00478fc0(int x, int y, Surf* s, Spr* spr)
{
	int saved;
	int right;
	int h;

	if (g_100ef80 == 0) {
		if (spr->x26 != -1) {
			h = spr->h;
			if (x <= g_67d964) {
				if (h + x >= g_7725f8) {
					right = h + x;
					saved = g_67d96c;
					g_67d96c = s->x10;
					switch (spr->kind) {
					case 0:
						if (g_100f1bc == 0) {
							fcn_00477500(x, y, s->bits, spr);
						} else {
							fcn_004774f0(x, y, s->bits, spr);
						}
						return 1;
					case 1:
						if (x < g_7725f8) {
							fcn_004774e0(x, y, s->bits, spr);
						} else if (right > g_67d964) {
							fcn_004774e0(x, y, s->bits, spr);
						} else {
							fcn_0047a320(x, y, s->bits, spr);
						}
						return 1;
					case 2:
						return 1;
					}
					g_67d96c = saved;
				}
			}
		} else {
			switch (spr->kind) {
			case 0:
				return 0;
			case 2:
				return 1;
			case 1:
				fcn_00478fa0(x, y, s, spr);
				return 1;
			}
		}
	}
	return 0;
}
