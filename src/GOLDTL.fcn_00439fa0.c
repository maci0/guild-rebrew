// FUNCTION: GOLDTL 0x439fa0

extern char g_67a3e4[];

void* __cdecl m_AllocTracked(int, void*);
void __cdecl fcn_00439e10(char*, char*);

void __cdecl fcn_00439fa0(char* o)
{
	int i;

	if (*(char**) (o + 0x1ec) == 0) {
		*(char**) (o + 0x1ec) = (char*) m_AllocTracked(0x1640, g_67a3e4);
		for (i = 0; i <= 3; i++) {
			fcn_00439e10(*(char**) (o + 0x1ec) + i * 0x4a4 + 0xf4, o);
		}
		for (i = 0; i < 4; i++) {
			*(int*) (*(char**) (o + 0x1ec) + i * 0x9c + 0x13a0) = 0;
			*(int*) (*(char**) (o + 0x1ec) + i * 0x9c + 0x13a4) = 0;
			*(int*) (*(char**) (o + 0x1ec) + i * 0x9c + 0x13a8) = 0;
			*(int*) (*(char**) (o + 0x1ec) + i * 0x9c + 0x138c) = 0;
			*(int*) (*(char**) (o + 0x1ec) + i * 0x9c + 0x1384) = 0;
		}
		*(unsigned char*) (*(char**) (o + 0x1ec) + 0x163c) = 0;
		**(int**) (o + 0x1ec) = 0;
		*(int*) (*(char**) (o + 0x1ec) + 0x15f4) = 0;
		*(float*) (*(char**) (o + 0x1ec) + 0x15f8) = 1.0f;
		*(int*) (*(char**) (o + 0x1ec) + 0xb0) = -1;
		*(unsigned char*) (*(char**) (o + 0x1ec) + 0x163d) |= 0x40;
	}
}
