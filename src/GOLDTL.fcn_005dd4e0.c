// FUNCTION: GOLDTL 0x005dd4e0
// SIZE: 177

void __cdecl fcn_00508cf0(int, int*);
void __cdecl fcn_005dcf40(unsigned char*, int);
void __cdecl fcn_004c6330(int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_005dbe90(char*);

int __cdecl fcn_005dd4e0(unsigned char* e, int* a2)
{
	int ids[5];
	char text[0x800];
	int last;
	int i;
	int n;

	last = 0;
	a2[4] = 1;
	fcn_00508cf0(5, ids);
	i = 0;
	n = 0;
	while (n < 1 && i < 5) {
		if (e[ids[i] + 0x80] < 0xfc) {
			fcn_005dcf40(e, ids[i]);
			last = ids[i];
			n++;
		}
		i++;
	}
	if (e[2] == 6) {
		fcn_004c6330(*(int*) (e + 4));
		fcn_0051af00(text, 0xfe8, **(unsigned short**) a2 * 2 + 0xd71, last + 0x16b7);
		fcn_005dbe90(text);
	}
	return 1;
}
