


extern char g_7f4ca0[];

int __cdecl fcn_0065f220(const char*, const char*);
void __cdecl SelectTextureSet(char*, int, char, int);

char __cdecl fcn_0052d970(char* e, char* o)
{
	if (fcn_0065f220(e, "sp_WIMPEL") == 0 && *(unsigned short*) (o + 0x27) != 0xffff) {
		SelectTextureSet(e, *(int*) (e + 0x1cc),
		    *((char*) g_7f4ca0 + 0x54 + *(unsigned short*) (o + 0x27) * 0x21c) + 0x66, 1);
	}
	return 1;
}
