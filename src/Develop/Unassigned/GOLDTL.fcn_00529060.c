


extern char g_7f4ca0[];

void __cdecl fcn_00529060(int idx, char* o)
{
	char* p;
	int i;

	p = g_7f4ca0 + idx * 0x21c;
	for (i = 0; i < 8; i++) {
		if (*(int*) (o + 0x8c + i * 4) == *(int*) (p + 4)) {
			*(int*) (o + 0x8c + i * 4) = -1;
			return;
		}
	}
}
