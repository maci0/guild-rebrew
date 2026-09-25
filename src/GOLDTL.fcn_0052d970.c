// FUNCTION: GOLDTL 0x0052d970
// SIZE: 84

int __cdecl fcn_0065f220(const char*, const char*);
void __cdecl fcn_00442a30(char*, int, char, int);

char __cdecl fcn_0052d970(char* e, char* o)
{
	if (fcn_0065f220(e, "sp_WIMPEL") == 0 && *(unsigned short*) (o + 0x27) != 0xffff) {
		fcn_00442a30(e, *(int*) (e + 0x1cc),
		    *((char*) 0x7f4cf4 + *(unsigned short*) (o + 0x27) * 0x21c) + 0x66, 1);
	}
	return 1;
}
