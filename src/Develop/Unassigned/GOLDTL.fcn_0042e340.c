

void __cdecl ch_ValidateActorPtrs(int);

void __cdecl ch_ValidateQueueTable(void)
{
	int o;
	char* base;

	base = *(char**) 0x6b5c20;
	for (o = 0; o < 0xc5440; o += 0x194) {
		if (*(unsigned char*) (base + o + 9) != 0) {
			ch_ValidateActorPtrs(*(int*) (base + o + 0x14));
			base = *(char**) 0x6b5c20;
		}
	}
}
