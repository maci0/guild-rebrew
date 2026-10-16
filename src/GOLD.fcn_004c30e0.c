int __cdecl fcn_00422460(int, int);
int __cdecl fcn_00417710(int, int, int, int);
void __cdecl SetSoundControlValue(int, int);
void __cdecl fcn_004192b0(int, int, int, int);

/* ADDRESS: GOLD 0x004c30e0 */
void __cdecl fcn_004c30e0(void)
{
	int p;
	int s;
	int t;
	int r;

	if (*(int *)0x6f0b80 != 0)
		return;
	p = *(int *)0x6f1bc8;
	s = *(int *)(p + 0x61);
	if (s == 0)
		return;
	t = fcn_00422460(0, 0x60bd40);
	r = fcn_00417710(t, s, 0x7f, 0x45098000);
	*(int *)0x6f0b80 = r;
	if (r == 0)
		return;
	SetSoundControlValue(r, 1);
	fcn_004192b0(*(int *)0x6f0b80, 0, 0, 0);
}
