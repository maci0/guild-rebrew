// FUNCTION: GOLD 0x42ec00
// SIZE: 32

int __cdecl fcn_005de784(void);

int __cdecl fcn_0042ec00(unsigned short si)
{
	if (si != 0) {
		return fcn_005de784() % (si & 0xffff);
	}
	return 0;
}
