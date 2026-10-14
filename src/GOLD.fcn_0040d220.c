
// fcn_0040d220 — if(!*a){ log(0x5f2304); return 0; } return fcn_005de800(a+8, *b) != 0.

int __cdecl fcn_004273d0(int, int, int);
int __cdecl fcn_005de800(void*, int);

int __cdecl fcn_0040d220(void* a, void* b)
{
	int e;
	e = *(int*) a;
	if (e == 0) {
		fcn_004273d0(*(int*) 0x6332b8, *(int*) (*(int*) 0x6332b8 + 0x118), 0x5f2304);
		return 0;
	}
	return fcn_005de800((char*) e + 8, *(int*) b) != 0;
}
