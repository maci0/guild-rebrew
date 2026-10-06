// FUNCTION: GOLD 0x43cab0

extern char* g_fc2dec;

void __cdecl fcn_0043cab0(char* o)
{
	switch (*(int*) (o + 0x218)) {
	case 3:
		if (g_fc2dec == o) {
			g_fc2dec = 0;
		}
	case 1:
	case 2:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
		*(char**) (*(char**) (o + 0x1f0) + 0x1f4) = *(char**) (o + 0x1f4);
		*(char**) (*(char**) (o + 0x1f4) + 0x1f0) = *(char**) (o + 0x1f0);
		break;
	}
	o[0x210] &= ~2;
}
