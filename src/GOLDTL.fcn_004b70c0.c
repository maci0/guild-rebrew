// FUNCTION: GOLD 0x004b6e10
// SIZE: 216
// FUNCTION: GOLDTL 0x4b70c0
// SIZE: 216

extern unsigned char g_773d75;

void* __cdecl fcn_00508e40(int);
unsigned short __cdecl fcn_0042e410(int);
int  __cdecl fcn_0050dac0(unsigned short);
void __cdecl fcn_0051af00(void*, int, int);
void __cdecl fcn_004c51a0(int, int, char, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, int);

int __cdecl fcn_004b70c0(void* a1)
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
	v = fcn_0042e410(2);
	d = (double) v + 1.0;
	n = (int) (((double) fcn_0050dac0(*(unsigned short*) p) * d) *
	    0.0125);
	fcn_0051af00(buf, *(unsigned short*) ((char*) a1 + 4) + 0x12e7, n);
	fcn_004c51a0(*(int*) a1, -1, (*(char*)&g_773d75), n);
	fcn_00545d40(*(int*) ((char*) p + 4), *(int*) ((char*) p + 4), buf,
	    (unsigned) strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
