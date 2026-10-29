
// fcn_0040d080 — if(!*a){ log(0x5f22b0); return 1; } *b ? (a[0x8d]|=2) : (a[0x8d]&=~2); return 1.

int __cdecl fcn_004273d0(int, int, int);

int __cdecl fcn_0040d080(void* a, void* b)
{
	if (*(int*) a == 0) {
		fcn_004273d0(*(int*) 0x6332b8, *(int*) (*(int*) 0x6332b8 + 0x118), 0x5f22b0);
		return 1;
	}
	if (*(int*) b != 0) {
		((unsigned char*) a)[0x8d] |= 2;
	} else {
		((unsigned char*) a)[0x8d] &= 0xfd;
	}
	return 1;
}
