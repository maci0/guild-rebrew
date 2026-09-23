// FUNCTION: GOLDTL 0x4e90d0
// SIZE: 55

// SIZE 0x18
typedef struct {
	int a;
	int b;
	int c;
	int d;
	int e;
	int f;
} fcn_004e90d0_E;

char* __cdecl fcn_00508e40(int);

char* __cdecl fcn_004e90d0(int a1)
{
	int i;
	int a;

	for (i = 0, a = 0x9a9228; a < 0x9a9618; a += 0x18, i++) {
		if (*(unsigned char*) a == a1) {
			return fcn_00508e40(((fcn_004e90d0_E*) 0x9a9224)[i].a);
		}
	}
	return 0;
}
