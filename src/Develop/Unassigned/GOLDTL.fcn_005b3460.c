
/* ADDRESS: GOLDTL 0x005b3460 */
char __cdecl d2_CollectDebugObject(int value)
{
	int count;

	count = *(int*) 0x775280;
	if (count < 0x80) {
		*(int*) (0x778b20 + count * 4) = value;
		*(int*) 0x775280 = count + 1;
		return 1;
	}
	return 0;
}
