// FUNCTION: GOLD 0x0040c1d0
// SIZE: 60
// fcn_0040c1d0 — p=fcn_004287b0(a+0x90); if(p){ fcn_00429ab0(p,1,a[0x180]); p[0x104]=a[0x17c]; }.

int __cdecl fcn_004287b0(void*);
int __cdecl fcn_00429ab0(void*, int, int);

void __cdecl fcn_0040c1d0(char* a)
{
	char* p;
	p = (char*) fcn_004287b0(a + 0x90);
	if (p != 0) {
		fcn_00429ab0(p, 1, *(int*) (a + 0x180));
		*(int*) (p + 0x104) = *(int*) (a + 0x17c);
	}
}
