


extern char* g_6b7e98;

void __cdecl fcn_00426680(int, int*);
void __cdecl fcn_004263b0(int);
void __cdecl fcn_00426340(void);

int __cdecl fcn_004275a0(void)
{
	int buf[0x19];
	char* g;
	char* x;

	g = g_6b7e98;
	x = *(char**) (g + 0xc28);
	if (*(int*) (x + *(int*) (x + 8) * 16 + 0x44) != 0) {
		fcn_00426680(*(int*) (g + 0x118), buf);
		if (buf[0] == 0xa && buf[1] == 4) {
			fcn_004263b0(1);
			return 0;
		}
		fcn_00426340();
	}
	return 0;
}
