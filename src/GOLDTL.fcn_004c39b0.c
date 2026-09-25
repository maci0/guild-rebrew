extern int g_772d30;
extern char* g_773d78;
extern char g_68a9a8[];

int __cdecl fcn_00422460(int, char*);
int __cdecl fcn_00418c80(int, int, int, float);
void __cdecl vfs_WriteUint32LE(int stream, unsigned int value);
void __cdecl fcn_004192b0(int, int, int, int);

// FUNCTION: GOLDTL 0x4c39b0
// SIZE: 91

void __cdecl fcn_004c39b0(void)
{
	int h;
	int t;

	if (g_772d30 == 0) {
		h = *(int*) (g_773d78 + 0x61);
		if (h != 0) {
			t = fcn_00422460(0, g_68a9a8);
			g_772d30 = fcn_00418c80(t, h, 0x7f, 2200.0f);
			if (g_772d30 != 0) {
				vfs_WriteUint32LE(g_772d30, 1);
				fcn_004192b0(g_772d30, 0, 0, 0);
			}
		}
	}
}
