int __cdecl fcn_00470820(int a, int b, int c);
void __cdecl fcn_00471d80(int r, int n);

// FUNCTION: GOLDTL 0x471130
int __cdecl fcn_00471130(short a, short b, int c)
{
	int r;

	r = fcn_00470820(a, b, c);
	if (r != -1) {
		fcn_00471d80(r, 3);
	}
	return r;
}
