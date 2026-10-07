// FUNCTION: GOLDTL 0x439aa0

extern int g_6b8014;
extern char g_1042340[];
extern char* g_1042538;
extern int g_67a370;

void __cdecl fcn_00439c60(char*);
void __cdecl fcn_00438cb0(char*, char*);

void __cdecl fcn_00439aa0(char* o)
{
	if (*(int*) (o + 0x218) == 3 && (*(char**)&g_6b8014) == 0) {
		fcn_00439c60(o);
		fcn_00438cb0(o, o + 0x84);
	}
	if (*(int*) (o + 0x218) != 0) {
		*(char**) (o + 0x1f8) = g_1042538;
		*(char**) (o + 0x1f4) = g_1042340;
		*(char**) (g_1042538 + 0x1f4) = o;
		g_1042538 = o;
		o[0x214] |= 3;
	}
	*(int*) (o + 0x20c) = g_67a370;
}
