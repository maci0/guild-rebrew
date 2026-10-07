// FUNCTION: GOLDTL 0x4e9500

typedef struct {
	int x0;
	int x1;
	int x2;
	int x3;
	int x4;
	int x5;
} fcn_004e9500_rec;
// SIZE 0x18

void __cdecl fcn_004e9500(int count, fcn_004e9500_rec* p)
{
	int i;

	if (count <= 0) {
		return;
	}
	for (i = 0; i < count; i++) {
		p[i] = ((fcn_004e9500_rec*) 0x9a9220)[*(unsigned char*) &p[i]];
	}
}
