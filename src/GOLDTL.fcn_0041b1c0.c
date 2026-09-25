// FUNCTION: GOLDTL 0x41b1c0
// SIZE: 29

// SIZE 0xc
typedef struct {
	int a;
	int b;
	int c;
} T41b1c0;

extern T41b1c0 g_662b68[];

T41b1c0* __cdecl fcn_0041b1c0(int a1)
{
	if (a1 >= 0x14 && a1 <= 0x1f) {
		return &g_662b68[a1 - 0x14];
	}
	return 0;
}
