// FUNCTION: GOLD 0x005de784
// fcn_005de784 — LCG: state = state*0x343fd + 0x269ec3; return (state>>0x10) & 0x7fff.

int __cdecl fcn_005de784(void)
{
	int s;
	s = *(int*) 0x62e108;
	s = s * 0x343fd + 0x269ec3;
	*(int*) 0x62e108 = s;
	return (s >> 0x10) & 0x7fff;
}
