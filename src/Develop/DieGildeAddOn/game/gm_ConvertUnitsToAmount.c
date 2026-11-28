/* ADDRESS: GOLDTL 0x0050b750 */
/* ADDRESS: GOLDDE 0x004f67c0 */
int __cdecl gm_ConvertUnitsToAmount(int value, int index)
{
	unsigned short e;

	index &= 0xff;
	e = *(unsigned short*) (0x8680b4 + index * 756);
	return *(int*) (0x6995bc + e * 4) * value;
}
