extern char s_5fb698[];
extern char s_5fb67c[];
extern char g_633438;
extern char* g_5fb5b0;

char* __cdecl m_alloc(int size, char* tag);
void __cdecl fcn_0043ce60(char* o);
void __cdecl fcn_005de8c0(char* dst, char* src, int n);

// FUNCTION: GOLD 0x43c570
char* __cdecl fcn_0043c570(int kind, char* name)
{
	char* o;

	o = m_alloc(0x228, s_5fb698);
	if (kind >= 5) {
		*(char**) (o + 0x1e8) = m_alloc(0x1ac, s_5fb67c);
	}
	fcn_0043ce60(o);
	if (kind >= 5) {
		switch (name[0]) {
		case 'p':
			*(int*) (o + 0x218) = 7;
			break;
		case 'r':
			*(int*) (o + 0x218) = 6;
			break;
		case 's':
			*(int*) (o + 0x218) = 8;
			break;
		default:
			*(int*) (o + 0x218) = 5;
			break;
		}
		if (g_633438 != 0 && *(int*) (o + 0x218) == 6) {
			*(int*) (o + 0x218) = 5;
		}
	} else {
		*(int*) (o + 0x218) = kind;
	}
	switch (*(int*) (o + 0x218)) {
	case 6:
		*(int*) (*(char**) (o + 0x1e8) + 0x194) = 0;
		break;
	case 8:
		o[0x211] |= 4;
		break;
	}
	*(int*) (o + 0x21c) = *(int*) (o + 0x218);
	fcn_005de8c0(o, name, 0x40);
	*(int*) (o + 0x208) = (int) g_5fb5b0;
	return o;
}
