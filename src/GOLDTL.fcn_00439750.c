extern char s_67a3a0[];
extern char s_67a384[];
extern char g_6b8004;
extern int g_67a370;

char* __cdecl m_alloc(int size, char* tag);
void __cdecl fcn_00439e70(char* o);
void __cdecl fcn_0064d530(char* dst, char* src, int n);

// FUNCTION: GOLDTL 0x439750
char* __cdecl fcn_00439750(int kind, char* name)
{
	char* o;

	o = m_alloc(0x228, s_67a3a0);
	if (kind >= 5) {
		*(char**) (o + 0x1e8) = m_alloc(0x1ac, s_67a384);
		*(float*) (*(char**) (o + 0x1e8) + 0x1a0) = 1.0f;
	}
	fcn_00439e70(o);
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
		if (g_6b8004 != 0 && *(int*) (o + 0x218) == 6) {
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
		o[0x215] |= 1;
		break;
	}
	*(int*) (o + 0x21c) = *(int*) (o + 0x218);
	fcn_0064d530(o, name, 0x40);
	*(int*) (o + 0x20c) = g_67a370;
	return o;
}
