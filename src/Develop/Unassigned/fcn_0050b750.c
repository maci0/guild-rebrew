/* ADDRESS: GOLDTL 0x0050b750 */
int __cdecl fcn_0050b750(int value, int index)
{
	unsigned short e;

	index &= 0xff;
	e = *(unsigned short*) (0x8680b4 + index * 756);
	return *(int*) (0x6995bc + e * 4) * value;
}
