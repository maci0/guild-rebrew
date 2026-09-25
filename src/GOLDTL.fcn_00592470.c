// FUNCTION: GOLDTL 0x592470
// SIZE: 86

void __cdecl fcn_00591ea0(void);
void __cdecl fcn_00591d00(void);
void __cdecl fcn_00591da0(int);

void __cdecl fcn_00592470(void)
{
	char c;
	int i;
	char* e;

	c = *(char*) 0x14cf950;
	if (c != 0 && *(int*) 0x7e2700 != 1) {
		if (c == 0x58) {
			fcn_00591ea0();
		}
		fcn_00591d00();
		i = 0;
		for (e = (char*) 0x779d00; (int) e < 0x779d84; e += 12) {
			if (*e == *(char*) 0x14cf950 && *(char*) 0x14cf72a != 0) {
				fcn_00591da0(i);
			}
			i++;
		}
	}
}
