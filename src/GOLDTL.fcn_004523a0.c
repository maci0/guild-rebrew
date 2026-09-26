// FUNCTION: GOLDTL 0x4523a0
// SIZE: 119

extern char g_1040640[];
extern char g_1040960[];
extern int g_67a370;
extern char* g_1040c74;
extern char* g_1040958;

void __cdecl fcn_004523a0(char* o)
{
	char* owner;

	owner = *(char**) (o + 0x2f4);
	if (*(char**) (o + 0x318) == g_1040960) {
		*(char**) (owner + 0xa4) = *(char**) (o + 0x314);
	} else {
		*(char**) (*(char**) (o + 0x318) + 0x314) = *(char**) (o + 0x314);
	}
	if (*(char**) (o + 0x314) == g_1040640) {
		*(char**) (owner + 0xa8) = *(char**) (o + 0x318);
	} else {
		*(char**) (*(char**) (o + 0x314) + 0x318) = *(char**) (o + 0x318);
	}
	if (owner == ((char*)g_67a370)) {
		g_1040c74 = *(char**) (owner + 0xa4);
		g_1040958 = *(char**) (owner + 0xa8);
	}
}
