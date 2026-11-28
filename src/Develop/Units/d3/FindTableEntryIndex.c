
int __cdecl FindTableEntryIndex(int value, int* p)
{
	int i;

	for (i = 0; i < 0x40; i++, p += 3) {
		if (value == *p) {
			return i;
		}
		if (*p == 0x28) {
			break;
		}
	}
	return 0x27;
}
