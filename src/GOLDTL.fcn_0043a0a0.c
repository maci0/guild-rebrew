/* ADDRESS: GOLDTL 0x0043a0a0 */

void __cdecl fcn_0043a0a0(char* o)
{
	if (*(char**) (o + 0x1f4) != 0) {
		*(char**) (*(char**) (o + 0x1f4) + 0x1f8) = *(char**) (o + 0x1f8);
		if (*(char**) (o + 0x1f8) != 0) {
			*(char**) (*(char**) (o + 0x1f8) + 0x1f4) = *(char**) (o + 0x1f4);
		} else if (*(char**) (*(char**) (o + 0x1fc) + 0x200) == o) {
			*(char**) (*(char**) (o + 0x1fc) + 0x200) = *(char**) (o + 0x1f4);
		}
	} else {
		if (*(char**) (o + 0x1f8) != 0) {
			*(char**) (*(char**) (o + 0x1f8) + 0x1f4) = 0;
		} else if (*(char**) (*(char**) (o + 0x1fc) + 0x200) == o) {
			*(char**) (*(char**) (o + 0x1fc) + 0x200) = 0;
		}
	}
	*(char**) (o + 0x1fc) = 0;
	*(char**) (o + 0x1f8) = 0;
	*(char**) (o + 0x1f4) = 0;
	o[0x214] &= ~2;
}
