

void __cdecl fcn_0043cc90(char*);
void __cdecl fcn_00422620(void*);

void __cdecl fcn_0043cd80(char* o)
{
	int i;

	if (*(char**) (o + 0x1ec) != 0) {
		for (i = 0; i < *(unsigned char*) (*(char**) (o + 0x1ec) + 0x96c); i++) {
			fcn_0043cc90(*(char**) (o + 0x1ec) + i * 0x198 + 0xf4);
		}
		fcn_0043cc90(*(char**) (o + 0x1ec) + 0x5bc);
		*(unsigned char*) (*(char**) (o + 0x1ec) + 0x96c) = 0;
		fcn_00422620(*(char**) (o + 0x1ec));
		*(char**) (o + 0x1ec) = 0;
	}
	*(int*) (o + 0x1cc) = 0;
}
