

// SIZE 0xc
typedef struct {
	int a;
	int b;
	int c;
} T41b1c0;

extern T41b1c0 g_662b68[];

T41b1c0* __cdecl fcn_0041b1c0(int index)
{
	if (index >= 0x14 && index <= 0x1f) {
		return &g_662b68[index - 0x14];
	}
	return 0;
}
