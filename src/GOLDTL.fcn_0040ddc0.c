// FUNCTION: GOLD 0x0040ce90
// FUNCTION: GOLDTL 0x0040ddc0

extern char* g_6b7e98;
extern float g_6628dc;
void __cdecl fcn_00455350(char* src, char* pos, float* out);
float __cdecl fcn_00444700(int h, float* pos);
char* __cdecl fcn_0040c120(char* e, int kind, ...);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl fcn_0040ddc0(char** a, char** b)
{
	float pos[4];
	float f;

	if (*a == 0 || *b == 0) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
		return 1;
	}
	fcn_00455350(*b, *b + 0x4c, pos);
	f = fcn_00444700(*(int*) (*a + 0x34), pos) * g_6628dc;
	fcn_0040c120(*a, 7, (int) f, 0);
	return 0;
}
