unsigned short __cdecl gm_RandomMod(int);

// SIZE 0x24
struct info_577940 {
	char b0;
	char type;
	char pad[10];
	int owner;
	char pad2[8];
	int kind;
	char pad3[8];
};




void __cdecl gm_GetLawEntry(int, struct info_577940*);

/* ADDRESS: GOLDDE 0x0055d860 */
int __cdecl gm_FindMatchingLawEntry(int x)
{
	struct info_577940 info;
	int y;
	int j;
	int n;
	int s;

	y = x + 3;
	j = 2;
	do {
		j--;
		s = gm_RandomMod(0x1d);
		n = 0x1d;
		do {
			gm_GetLawEntry(s, &info);
			if (info.kind == 1 && info.type == 2 && info.owner == y) {
				return s;
			}
			n--;
			s = (s + 1) % 0x1d;
		} while (n != 0);
		y++;
	} while (j != 0);
	return -1;
}
