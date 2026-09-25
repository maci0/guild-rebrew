// FUNCTION: GOLD 0x45ccc0
// SIZE: 133

/* GOLD twin of GOLDTL fcn_00456b80: entity slots at 0x754, 0x80 bytes each
 * (GOLDTL 0x1384, 0x9c); flag bit 4 of byte 0x211 (GOLDTL bit 1 of 0x215). */

void __cdecl fcn_0045cc80(char*);

void __cdecl fcn_0045ccc0(char* o)
{
	int i;

	if ((o[0x211] & 4) != 0 && *(char**) (o + 0x1ec) != 0) {
		for (i = 0; i < 4; i++) {
			if (*(int*) (*(char**) (o + 0x1ec) + i * 0x80 + 0x754) != 0) {
				fcn_0045cc80(*(char**) (o + 0x1ec) + i * 0x80 + 0x754);
				*(int*) (*(char**) (o + 0x1ec) + i * 0x80 + 0x758) = 0;
				*(int*) (*(char**) (o + 0x1ec) + i * 0x80 + 0x76c) = 0;
				*(int*) (*(char**) (o + 0x1ec) + i * 0x80 + 0x770) = 0;
				*(int*) (*(char**) (o + 0x1ec) + i * 0x80 + 0x774) = 0;
			}
		}
	}
}
