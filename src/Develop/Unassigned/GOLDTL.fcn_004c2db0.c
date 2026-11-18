
/* ADDRESS: GOLDTL 0x004c2db0 */
int __cdecl fcn_004c2db0(unsigned value, int mode)
{
	if (mode == 1) {
		return (value & 1) - 2;
	}
	return (int) (value % 3) - 5;
}
