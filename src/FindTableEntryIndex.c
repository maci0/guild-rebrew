
int __cdecl FindTableEntryIndex(int a1, int* p)
{
	int i;

	for (i = 0; i < 0x40; i++, p += 3) {
		if (a1 == *p) {
			return i;
		}
		if (*p == 0x28) {
			break;
		}
	}
	return 0x27;
}
