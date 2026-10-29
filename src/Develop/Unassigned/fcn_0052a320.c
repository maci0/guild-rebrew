/* ADDRESS: GOLDTL 0x0052a320 */
char __cdecl fcn_0052a320(char* e)
{
	char* base;
	int* src;
	int i;

	if (*(int*) 0x7e4530 == 0) {
		if (e[0x215] & 4)
			base = (char*) 0x6a29a8;
		else
			base = (char*) 0x6a2938;
	} else if (e[0x215] & 4) {
		base = (char*) 0x6a2af8;
	} else {
		base = (char*) 0x6a2a88;
	}
	src = (int*) base;
	for (i = 0; i < 0x150; i += 0x38) {
		*(int*) (*(char**) (e + 0x1e8) + i + 0x18) = *src;
		*(int*) (*(char**) (e + 0x1e8) + i + 0x1c) = src[1];
		*(int*) (*(char**) (e + 0x1e8) + i + 0x20) = src[2];
		*(int*) (*(char**) (e + 0x1e8) + i + 0x24) = src[3];
		src += 4;
	}
	return 1;
}
