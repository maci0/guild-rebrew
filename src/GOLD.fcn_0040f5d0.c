extern char* g_6b7e98;
// FUNCTION: GOLD 0x40f5d0

// SIZE 0x2
typedef struct {
	unsigned char kind : 5;
	unsigned char f5 : 1;
	unsigned char f6 : 1;
	unsigned char f7 : 1;
	unsigned char g0 : 1;
} Bits;

int __cdecl fcn_0041dd90(char* p);
void __cdecl fcn_004273d0(char* g, int h, const char* msg);

int __cdecl fcn_0040f5d0(char** a, int* s, unsigned char* k, unsigned char* b5, unsigned char* b6, unsigned char* b7, unsigned char* c0)
{
	char* e;

	e = *a;
	if (!fcn_0041dd90(e)) {
		fcn_004273d0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
		return 0;
	}
	*(float*) (e + 0xac) = *s * 0.01f;
	((Bits*) (e + 0xcc))->kind = *k;
	((Bits*) (e + 0xcc))->f5 = *b5;
	((Bits*) (e + 0xcc))->f6 = *b6;
	((Bits*) (e + 0xcc))->f7 = *b7;
	((Bits*) (e + 0xcc))->g0 = *c0;
	return 0;
}
