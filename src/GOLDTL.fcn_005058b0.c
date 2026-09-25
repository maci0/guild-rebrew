// FUNCTION: GOLD 0x00502a60
// SIZE: 255
// FUNCTION: GOLDTL 0x005058b0
// SIZE: 255

#include <string.h>

// SIZE 0x21c
typedef struct {
	char pad0[0x80];
	unsigned char levels[5];
	char pad85[0x21c - 0x85];
} Obj;

// SIZE 0x204
typedef struct {
	int ids[64];
	int vals[64];
	int count;
} Hits;

extern int g_7746cc;
extern Obj g_7f4ca0[];
extern int g_67a370;
extern float g_664168;
extern float g_6628cc;

int __cdecl fcn_00505840(void);
void __cdecl fcn_004379a0(int h, int a, int b, int (__cdecl* cb)(void), Hits* out);
void __cdecl fcn_00442d50(int id, int on);

void __cdecl fcn_005058b0(int unused, int who, int id)
{
	int want[5];
	Hits hits;
	int t;
	int i;
	int k;

	if (g_7746cc == who) {
		for (i = 0; i < 5; i++) {
			t = (int) (g_7f4ca0[id].levels[i] * g_664168 - g_6628cc) + i * 6 + 0x17f;
			if (g_7f4ca0[id].levels[i] == 0) {
				t = 0;
			}
			want[i] = t;
		}
		memset(&hits, 0, sizeof(hits));
		fcn_004379a0(g_67a370, 0, 0xc0, fcn_00505840, &hits);
		for (k = 0; k < hits.count; k++) {
			fcn_00442d50(hits.ids[k], 0);
			for (i = 0; i < 5; i++) {
				if (hits.vals[k] == want[i]) {
					fcn_00442d50(hits.ids[k], 1);
				}
			}
		}
	}
}
