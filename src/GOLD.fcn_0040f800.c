// FUNCTION: GOLD 0x40f800
// SIZE: 79

// SIZE 0x2
typedef struct {
	unsigned char kind : 5;
	unsigned char f5 : 1;
	unsigned char f6 : 1;
	unsigned char f7 : 1;
	unsigned char g0 : 1;
} Bits;

extern char* g_6b7e98;
int __cdecl fcn_0041dd90(char* p);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl fcn_0040f800(char** a, unsigned char* v)
{
	char* e;

	e = *a;
	if (!fcn_0041dd90(e)) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
		return 0;
	}
	((Bits*) (e + 0xcc))->g0 = *v;
	return 0;
}
