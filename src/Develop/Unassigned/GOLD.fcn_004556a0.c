
// fcn_004556a0 — while([0xfb98f4] != 0xfb9280) fcn_00455750([0xfb98f4]).

int __cdecl d3_DestroyEffect(int);

void __cdecl d3_DestroyAllEffects(void)
{
	int v;

	v = *(int*) 0xfb98f4;
	if (v != 0xfb9280) {
		do {
			d3_DestroyEffect(v);
			v = *(int*) 0xfb98f4;
		} while (v != 0xfb9280);
	}
}
