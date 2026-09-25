// FUNCTION: GOLDTL 0x4b53c0
// SIZE: 125

typedef struct {
	int a;
	int n;
	float f;
} stat12;
// SIZE 0xc

unsigned char* __cdecl fcn_00503fe0(int, ...);
unsigned char* __cdecl fcn_00503e80(void);

void __cdecl fcn_004b53c0(unsigned short* key, int kind, stat12* out)
{
	unsigned char* e;
	int match;
	int total;

	match = 0;
	if (kind != 0)
		e = fcn_00503fe0(1, 5, kind);
	else
		e = fcn_00503fe0(1, 6);
	total = 0;
	while (e != 0) {
		if (*(unsigned short*) (e + 0x27) == *key)
			match++;
		e = fcn_00503e80();
		total++;
	}
	out->a = match;
	out->n = total;
	if (total > 0)
		out->f = (float) match / total;
	else
		out->f = 0;
}
