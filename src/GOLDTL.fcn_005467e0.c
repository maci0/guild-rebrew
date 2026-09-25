extern int g_6b8010;

// FUNCTION: GOLD 0x0053eaa0
// SIZE: 110
// FUNCTION: GOLDTL 0x5467e0
// SIZE: 110

void __cdecl fcn_004432d0(int, int);
int __cdecl fcn_00445600(int, int, char*, int);
void __cdecl fcn_00546480(char*);
void __cdecl fcn_00442be0(char*);

void __cdecl fcn_005467e0(int* s)
{
	char* h;
	int save;

	h = (char*) s[2];
	if (s[3] != 0) {
		save = g_6b8010;
		s[2] = 0;
		fcn_004432d0(0, 1);
		if (h != 0 && fcn_00445600(0, 0x1c0, h, 0) != 0) {
			fcn_00546480(h);
		}
		fcn_00442be0((char*) s[3]);
		s[3] = 0;
		fcn_004432d0(save, 1);
	}
	s[1] = 0;
	s[0] = -1;
}
