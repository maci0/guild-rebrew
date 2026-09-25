// FUNCTION: GOLDTL 0x4b5440
// SIZE: 149

typedef struct {
	int a;
	int n;
	float f;
} stat12;
// SIZE 0xc

unsigned char* __cdecl fcn_00503fe0(int, ...);
unsigned char* __cdecl fcn_00503e80(void);

extern char g_7f4ca4[];

void __cdecl fcn_004b5440(int kind, stat12* out)
{
	unsigned char* e;
	int match;
	int total;
	unsigned short k;
	char t;

	match = 0;
	if (kind != 0)
		e = fcn_00503fe0(1, 5, kind);
	else
		e = fcn_00503fe0(1, 6);
	total = 0;
	while (e != 0) {
		k = *(unsigned short*) (e + 0x27);
		if (k != 0xffff) {
			t = g_7f4ca4[k * 0x21c - 2];
			if (t == 6 || t == 7)
				match++;
		}
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
