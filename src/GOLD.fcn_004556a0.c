
// fcn_004556a0 — while([0xfb98f4] != 0xfb9280) fcn_00455750([0xfb98f4]).

int __cdecl fcn_00455750(int);

void __cdecl fcn_004556a0(void)
{
	int v;

	v = *(int*) 0xfb98f4;
	if (v != 0xfb9280) {
		do {
			fcn_00455750(v);
			v = *(int*) 0xfb98f4;
		} while (v != 0xfb9280);
	}
}
