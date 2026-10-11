// FUNCTION: GOLDTL 0x439d80

void __cdecl fcn_00439c90(char*);
void __cdecl m_FreeTracked(void*);

void __cdecl fcn_00439d80(char* o)
{
	int i;

	if (*(char**) (o + 0x1ec) != 0) {
		for (i = 0; i < *(unsigned char*) (*(char**) (o + 0x1ec) + 0x163c); i++) {
			fcn_00439c90(*(char**) (o + 0x1ec) + i * 0x4a4 + 0xf4);
		}
		fcn_00439c90(*(char**) (o + 0x1ec) + 0xee0);
		*(unsigned char*) (*(char**) (o + 0x1ec) + 0x163c) = 0;
		m_FreeTracked(*(char**) (o + 0x1ec));
		*(char**) (o + 0x1ec) = 0;
	}
	*(int*) (o + 0x1cc) = 0;
}
