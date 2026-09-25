// FUNCTION: GOLDTL 0x00591d00
// SIZE: 151
// FUNCTION: GOLD 0x005897a0
// SIZE: 160

// SIZE 0xc
typedef struct {
	int a;
	int b;
	int c;
} Slot;

extern Slot g_779d00[];
extern char g_14cf950;
extern char g_14cf72a;
extern char g_6b5c60[];

void __cdecl fcn_00591c80(void);
int __cdecl gm_SearchTable67(int);
char* __cdecl gm_FindRecordById(int);
void __cdecl fcn_00526920(int, int, char*);

void __cdecl fcn_00591d00(void)
{
	int i;
	int x;
	char* r;

	if (g_14cf950 != 0 && g_14cf72a == 0) {
		for (i = 0; i < 11; i++) {
			if ((char) g_779d00[i].a == g_14cf950 && g_14cf72a == 0) {
				fcn_00591c80();
				if (g_779d00[i].b != -1) {
					x = gm_SearchTable67(g_779d00[i].b);
					r = gm_FindRecordById(g_779d00[i].c);
					if (r != 0) {
						fcn_00526920(x, *(int*) (r + 2), g_6b5c60);
						return;
					}
					fcn_00526920(x, -1, g_6b5c60);
					return;
				}
			}
		}
	}
}
