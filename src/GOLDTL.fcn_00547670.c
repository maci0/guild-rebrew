// FUNCTION: GOLDTL 0x00547670
// SIZE: 253

// SIZE 0x21c
typedef struct {
	short slot;
	unsigned char type;
	char pad3;
	int id;
	char pad8[0x21c - 8];
} Entity;

extern Entity g_7f4ca0[768];
extern int g_7f4c00;
extern int g_7747b4;
extern char g_773d75;

int __cdecl gm_AccumulateTyped2(Entity*);
int __cdecl fcn_004c5150(int, int, char, int);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00535960(void);

void __cdecl fcn_00547670(void)
{
	int h;
	int n;
	int i;
	int limit;
	int v;

	h = -1;
	if (g_7f4c00 % (g_7f4c00 / 10 + 1) == 0) {
		limit = (g_7747b4 * 5 + 20) * 1600;
		n = 0;
		for (i = 0; i < 768; i++) {
			if (g_7f4ca0[i].type == 5) {
				v = gm_AccumulateTyped2(&g_7f4ca0[i]);
				if (v < limit) {
					h = fcn_004c5150(g_7f4ca0[i].id, -1, g_773d75, limit - v);
					n++;
				}
			} else if (g_7f4ca0[i].type == 4
				|| (g_7f4ca0[i].type == 2 && g_7f4c00 % 4 == (g_7f4ca0[i].id & 3))) {
				v = gm_AccumulateTyped2(&g_7f4ca0[i]);
				if (v < limit) {
					h = fcn_004c5150(g_7f4ca0[i].id, -1, g_773d75, limit - v);
					n++;
				}
			}
			if (n >= 32 && h != -1) {
				do {
					if (fcn_004c4450(h) != 0) {
						break;
					}
					fcn_00535960();
				} while (1);
				h = -1;
				n = 0;
			}
		}
	}
}
