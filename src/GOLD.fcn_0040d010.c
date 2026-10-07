// FUNCTION: GOLD 0x0040d010
// fcn_0040d010 — if(!*a){ log(0x4273d0,..,0x5f227c); return 0; } fcn_00449690(a[0x34],0x140,0,*b); return ...

int __cdecl fcn_004273d0(int, int, int);
int __cdecl fcn_00449690(int, int, int, int);

int __cdecl fcn_0040d010(void* a, void* b)
{
	int e;
	int r;
	e = *(int*) a;
	if (e == 0) {
		fcn_004273d0(*(int*) 0x6332b8, *(int*) (*(int*) 0x6332b8 + 0x118), 0x5f227c);
		return 0;
	}
	r = fcn_00449690(*(int*) (e + 0x34), 0x140, 0, *(int*) b);
	return r;
}
