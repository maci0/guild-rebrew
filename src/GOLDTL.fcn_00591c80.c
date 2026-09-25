// FUNCTION: GOLD 0x00589720
// SIZE: 113
// FUNCTION: GOLDTL 0x00591c80
// SIZE: 113

// SIZE 0xc
typedef struct {
	int a;
	int b;
	int c;
} Slot;

extern Slot g_779d00[];
extern unsigned short g_774970;

int __cdecl gm_SearchTable67(int);
int __cdecl gm_FindRecordById(int);
char __cdecl fcn_00506380(int, int, int, int);
void __cdecl fcn_00591c30(Slot*);

void __cdecl fcn_00591c80(void)
{
	int i;
	int x;
	int r;

	for (i = 0; i < 11; i++) {
		if (g_779d00[i].b != -1) {
			x = gm_SearchTable67(g_779d00[i].b);
			if (x == 0) {
				fcn_00591c30(&g_779d00[i]);
			}
			else {
				r = gm_FindRecordById(g_779d00[i].c);
				if (r == 0 && g_779d00[i].c != -1) {
					fcn_00591c30(&g_779d00[i]);
				}
				else if (!(fcn_00506380(g_774970, x, r, 0) & 1)) {
					fcn_00591c30(&g_779d00[i]);
				}
			}
		}
	}
}
