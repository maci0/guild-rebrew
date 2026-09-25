// FUNCTION: GOLDTL 0x00420690
// SIZE: 112

// SIZE 0x128
typedef struct {
	char name[0x100];
	int handle;
	unsigned char active;
	unsigned char b105;
	unsigned char b106;
	unsigned char b107;
	int f108;
	int f10c;
	char pad110[0x128 - 0x110];
} Chan;

extern Chan g_6b71b0[10];

Chan* __cdecl fcn_00420690(void)
{
	int i;

	for (i = 0; i < 10; i++) {
		if (g_6b71b0[i].active == 0 && g_6b71b0[i].handle == 0 && g_6b71b0[i].f10c == 0) {
			return &g_6b71b0[i];
		}
	}
	for (i = 0; i < 10; i++) {
		if (g_6b71b0[i].active == 0 && g_6b71b0[i].handle == 0) {
			return &g_6b71b0[i];
		}
	}
	return 0;
}
