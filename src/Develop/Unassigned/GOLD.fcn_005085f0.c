/* ADDRESS: GOLD 0x005085f0 */
int __cdecl fcn_005085f0(int amount, unsigned char kind)
{
	unsigned int index;
	unsigned short slot;

	index = kind;
	index = index * 0x2f4;
	slot = *(unsigned short*) (0x7e3f94 + index);
	return *(int*) (0x61a88c + slot * 4) * amount;
}
