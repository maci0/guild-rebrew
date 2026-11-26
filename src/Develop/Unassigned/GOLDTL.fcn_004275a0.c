


extern char* evt_CurrentScript;

void __cdecl evt_ReadToken(int, int*);
void __cdecl evt_SkipBlock(int);
void __cdecl evt_SeekSemicolon(void);

int __cdecl evt_TrySkipIfFalseBlock(void)
{
	int buf[0x19];
	char* g;
	char* x;

	g = evt_CurrentScript;
	x = *(char**) (g + 0xc28);
	if (*(int*) (x + *(int*) (x + 8) * 16 + 0x44) != 0) {
		evt_ReadToken(*(int*) (g + 0x118), buf);
		if (buf[0] == 0xa && buf[1] == 4) {
			evt_SkipBlock(1);
			return 0;
		}
		evt_SeekSemicolon();
	}
	return 0;
}
