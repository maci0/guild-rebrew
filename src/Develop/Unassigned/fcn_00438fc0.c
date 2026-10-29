void __cdecl fcn_00437bc0(void);
void __cdecl fcn_00438af0(int a);

/* ADDRESS: GOLDTL 0x00438fc0 */
void __cdecl fcn_00438fc0(float v)
{
	register float t;

	if (!(v > *(double*) 0x662950)) {
		return;
	}
	if (v == *(float*) 0x10432a4) {
		return;
	}
	t = *(float*) 0x1042a18;
	*(float*) 0x10432a4 = v;
	t *= v;
	*(float*) 0x1042584 = t * *(float*) 0x662a94;
	fcn_00437bc0();
	fcn_00438af0(0);
}
