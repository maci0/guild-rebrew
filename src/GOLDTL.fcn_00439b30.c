// FUNCTION: GOLDTL 0x439b30

extern int g_6b8014;

void __cdecl fcn_00439b30(char* o)
{
	switch (*(int*) (o + 0x218)) {
	case 3:
		if ((*(char**)&g_6b8014) == o) {
			(*(char**)&g_6b8014) = 0;
		}
	case 1:
	case 2:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
		*(char**) (*(char**) (o + 0x1f4) + 0x1f8) = *(char**) (o + 0x1f8);
		*(char**) (*(char**) (o + 0x1f8) + 0x1f4) = *(char**) (o + 0x1f4);
		break;
	}
	o[0x214] &= ~2;
}
