// FUNCTION: GOLDTL 0x456b80

void __cdecl fcn_00456b10(char*);

void __cdecl fcn_00456b80(char* o)
{
	int i;

	if ((o[0x215] & 1) != 0 && *(char**) (o + 0x1ec) != 0) {
		for (i = 0; i < 4; i++) {
			if (*(int*) (*(char**) (o + 0x1ec) + i * 0x9c + 0x1384) != 0) {
				fcn_00456b10(*(char**) (o + 0x1ec) + i * 0x9c + 0x1384);
				*(int*) (*(char**) (o + 0x1ec) + i * 0x9c + 0x138c) = 0;
				*(int*) (*(char**) (o + 0x1ec) + i * 0x9c + 0x13a0) = 0;
				*(int*) (*(char**) (o + 0x1ec) + i * 0x9c + 0x13a4) = 0;
				*(int*) (*(char**) (o + 0x1ec) + i * 0x9c + 0x13a8) = 0;
			}
		}
	}
}
