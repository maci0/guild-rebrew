// FUNCTION: GOLD 0x004e5210
// SIZE: 139
// FUNCTION: GOLDTL 0x4e6bd0
// SIZE: 139

extern int* g_772f40;
extern char g_9b0e20[];

unsigned char* __cdecl fcn_004e6a30(int);

int __cdecl fcn_004e6bd0(int a, int b)
{
	unsigned char* s;
	int i;

	s = fcn_004e6a30(a);
	if (s == 0)
		return 0;
	for (i = 0; i < s[0x30]; i++) {
		if (*(int*) (s + 0x34 + i * 4) == b) {
			*(int*) (s + 0x34 + i * 4) = -1;
			break;
		}
	}
	if (g_772f40 != 0 && *g_772f40 == a) {
		for (i = 0; i < 16; i++) {
			if (*(int*) (g_9b0e20 + i * 0x35c + 0x10) == b) {
				*(int*) (g_9b0e20 + i * 0x35c + 0x10) = -1;
				break;
			}
		}
	}
	return 1;
}
