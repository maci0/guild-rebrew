


unsigned short __cdecl gm_RandomMod(int);
void __cdecl fcn_005100f0(int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
void __cdecl fcn_0057bed0(char*, char*, int);

void __cdecl fcn_0057c630(char* o, int lvl)
{
	char buf[0x200];
	int n;

	if (lvl < 2) {
		n = gm_RandomMod(2) + 2;
	} else if (lvl == 2) {
		n = gm_RandomMod(2) + 3;
	} else if (lvl == 3) {
		n = gm_RandomMod(lvl) + lvl;
	} else {
		n = gm_RandomMod(4);
		if (lvl == 4) {
			n += 3;
		} else {
			n += 4;
		}
	}
	if (*(int*) (o + 0x194) >= n) {
		fcn_005100f0(*(int*) (o + 4), -n);
		io_FormatTextBuffer(buf, 0x41db, n);
		fcn_00545d40(*(int*) (o + 4), -1, buf, 1, 0x5fa, "_NACHRICHTEN_ZIGEUNER_00");
	} else {
		fcn_0057bed0(o, o, lvl);
	}
}
