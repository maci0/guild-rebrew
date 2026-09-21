// FUNCTION: GOLD 0x004ec2d0
// SIZE: 32
// fcn_004ec2d0 — a in [0,3) ? 0x6f0de0 + a*0x18 : 0.

int __cdecl fcn_004ec2d0(int a)
{
	if (a < 0 || a >= 3) {
		return 0;
	}
	return 0x6f0de0 + (a * 3) * 8;
}
