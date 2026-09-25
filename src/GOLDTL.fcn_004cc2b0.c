// FUNCTION: GOLDTL 0x4cc2b0
// SIZE: 131

typedef struct {
	unsigned short id;
	char pad2[0xe];
	int f10;
	int f14;
	int f18;
	int f1c;
	float f20;
	float f24;
	float f28;
	float f2c;
	int f30;
	int f34;
	float f38;
	char pad3c[0x44];
} slot80;
// SIZE 0x80

slot80* __cdecl fcn_005027d0(int, int);

int __cdecl fcn_004cc2b0(char* x, char* out)
{
	slot80* s;

	s = fcn_005027d0(*(unsigned char*) (x + 0x10), *(unsigned short*) (x + 0x11));
	if (s == 0)
		return 1;
	s->f10 += *(int*) (x + 0x13);
	s->f14 += *(int*) (x + 0x17);
	s->f18 += *(int*) (x + 0x1b);
	s->f20 += *(float*) (x + 0x1f);
	s->f24 += *(float*) (x + 0x23);
	s->f2c += *(float*) (x + 0x27);
	s->f38 += *(float*) (x + 0x2b);
	if (out != 0) {
		out[0] = 1;
		out[1] = 0;
		*(int*) (out + 6) = 0;
	}
	return 0;
}
