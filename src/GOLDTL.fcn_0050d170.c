// FUNCTION: GOLD 0x00509d60
// SIZE: 129
// FUNCTION: GOLDTL 0x0050d170
// SIZE: 129

extern unsigned char* g_868050;
extern char* g_99ec10;

float __cdecl fcn_0050b980(int k, int n);

int __cdecl fcn_0050d170(int k)
{
	unsigned char* t;
	int total;
	int i;
	unsigned short w;
	int rec;

	t = g_868050 + k * 0x24d;
	total = *(int*) (t + 0x249) * 0xf00;
	for (i = 0; i < 0x40; i++) {
		w = ((unsigned short*) (t + 0x23))[i];
		if (w == 0) {
			break;
		}
		rec = (*(int*)&g_99ec10) + (w & 0x7fff) * 0x40 + (w & 0x7fff);
		if (w & 0x8000) {
			total = (int) (fcn_0050b980(*(unsigned char*) rec, 100) + total);
		}
	}
	return total;
}
