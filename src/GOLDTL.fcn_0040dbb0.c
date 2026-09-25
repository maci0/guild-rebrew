// FUNCTION: GOLDTL 0x0040dbb0
// SIZE: 240

extern char* g_14d0020[];
extern char* g_67a370;
extern int g_6791c8;
extern char* g_6b7e98;
void __cdecl fcn_00455350(char* src, char* pos, float* out);
int __cdecl fcn_00451840(char* a, float* b, float range);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

char* __cdecl fcn_0040dbb0(char** a, int* range)
{
	float pos[4];
	char* result;
	char* e;
	char* t;
	int i;

	result = 0;
	if (*a == 0) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
		return 0;
	}
	i = 0;
	fcn_00455350(*a, *a + 0x4c, pos);
	for (; i < 0x300; i++) {
		e = g_14d0020[i];
		if (e != 0 && *(char**) (e + 0x88) == g_67a370 && *(int*) (e + 0x2c) == g_6791c8) {
			if (fcn_00451840(*(char**) (e + 0x34) + 0x4c, pos, (float) *range)) {
				result = g_14d0020[i];
				break;
			}
			t = *(char**) (g_14d0020[i] + 0x128);
			if (t != 0 && t[9] == 0x2d && fcn_00451840(t + 0x134, pos, (float) *range)) {
				result = g_14d0020[i];
				break;
			}
		}
	}
	return result;
}
