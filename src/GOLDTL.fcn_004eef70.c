// FUNCTION: GOLD 0x004ed170
// SIZE: 112
// FUNCTION: GOLDTL 0x004eef70
// SIZE: 112

extern char g_68e020[];
extern double g_662a20;

unsigned short __cdecl fcn_0042e410(unsigned short n);

char* __cdecl fcn_004eef70(void)
{
	unsigned int idx;
	int counter;
	unsigned int off;
	float* cursor;
	int n;

	idx = fcn_0042e410(0x20);
	counter = 0x20;
	while (counter != 0) {
		if (g_68e020[0xf2 + idx * 244] == 0) {
			goto found;
		}
		counter--;
		idx = (idx + 1) & 0x1f;
	}
	return 0;
found:
	off = idx * 244;
	cursor = (float*) (g_68e020 + 0x30 + off);
	n = 0xe;
	do {
		*cursor = (float) (cursor[-1] * g_662a20);
		cursor += 3;
		n--;
	} while (n != 0);
	g_68e020[0xf2 + off] = 1;
	return g_68e020 + off;
}
