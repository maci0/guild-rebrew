extern char s_67a3a0[];
extern char s_67a384[];
extern char g_6b8004;
extern int d3_ActiveScene;

char* __cdecl m_alloc(int size, char* tag);
void __cdecl d3_InitSceneObject(char* o);
void __cdecl fcn_0064d530(char* dst, char* src, int n);

/* ADDRESS: GOLDTL 0x00439750 */
char* __cdecl d3_SpawnObject(int kind, char* name)
{
	char* o;

	o = m_alloc(0x228, s_67a3a0);
	if (kind >= 5) {
		*(char**) (o + 0x1e8) = m_alloc(0x1ac, s_67a384);
		*(float*) (*(char**) (o + 0x1e8) + 0x1a0) = 1.0f;
	}
	d3_InitSceneObject(o);
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
	*(int*) (o + 0x20c) = d3_ActiveScene;
	return o;
}
