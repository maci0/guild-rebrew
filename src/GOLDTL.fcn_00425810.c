// FUNCTION: GOLDTL 0x425810
// SIZE: 59

void __cdecl fcn_00424040(int);
void __cdecl fcn_004245b0(int);
void __cdecl fcn_0041ddd0(int);

int __cdecl fcn_00425810(void)
{
	int r = 0;

	if (*(int*) 0x6b7d68 != r) {
		fcn_00424040(r);
		fcn_004245b0(r);
		fcn_0041ddd0(*(int*) 0x6b7d68);
		*(int*) 0x6b7d68 = r;
		*(int*) 0x6b7d6c = r;
	} else {
		r = -1;
	}
	return r;
}
