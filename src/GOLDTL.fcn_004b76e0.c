// FUNCTION: GOLDTL 0x4b76e0
// SIZE: 282

void* __cdecl fcn_00508e40(int);
unsigned short __cdecl fcn_0042e410(int);
int  __cdecl fcn_0050dac0(unsigned short);
int  __cdecl fcn_005c6270(void*, int);
int  __cdecl fcn_00507b00(int);
void __cdecl fcn_0051af00(void*, int, int);
void __cdecl fcn_004c51a0(int, int, char, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, int);

int __cdecl fcn_004b76e0(void* a1)
{
	char buf[0x100];
	double d;
	int v;
	void* p;
	int n;

	p = fcn_00508e40(*(int*) a1);
	if (p == 0) {
		return 1;
	}
	if (*(char*) ((char*) p + 0x166) == 0 && *(char*) ((char*) p + 0x169) == 0) {
		return 0x400;
	}
	if (fcn_005c6270(p, 0x290) != 0) {
		return 0x400;
	}
	v = fcn_0042e410(4);
	d = (double) v + *(double*) 0x6629c8;
	n = (int) (((double) fcn_0050dac0(*(unsigned short*) p) * d) *
	    *(double*) 0x6640e8);
	fcn_0051af00(buf, *(unsigned short*) ((char*) a1 + 4) + 0x12e7, n);
	fcn_004c51a0(-1, *(int*) a1, *(char*) 0x773d75, n);
	fcn_00545d40(*(int*) ((char*) p + 4), *(int*) ((char*) p + 4), buf,
	    (unsigned) strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
