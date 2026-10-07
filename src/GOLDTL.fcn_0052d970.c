// FUNCTION: GOLD 0x005282d0
// FUNCTION: GOLDTL 0x0052d970

extern char g_7f4ca0[];

int __cdecl fcn_0065f220(const char*, const char*);
void __cdecl fcn_00442a30(char*, int, char, int);

char __cdecl fcn_0052d970(char* e, char* o)
{
	if (fcn_0065f220(e, "sp_WIMPEL") == 0 && *(unsigned short*) (o + 0x27) != 0xffff) {
		fcn_00442a30(e, *(int*) (e + 0x1cc),
		    *((char*) g_7f4ca0 + 0x54 + *(unsigned short*) (o + 0x27) * 0x21c) + 0x66, 1);
	}
	return 1;
}
