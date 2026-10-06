// FUNCTION: GOLDTL 0x414be0

void __cdecl fcn_00414be0(char* p, unsigned char r, unsigned char g, unsigned char b)
{
	char* q;

	if (p != 0) {
		q = *(char**) (p + 0x1cc);
		if (q != 0) {
			*(unsigned int*) (q + 0x324) = ((((0xff) & 0xff) << 24) | (((r) & 0xff) << 16) | (((g) & 0xff) << 8) | ((b) & 0xff));
		}
	}
}
