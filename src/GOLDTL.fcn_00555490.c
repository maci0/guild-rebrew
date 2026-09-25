int __cdecl fcn_0047dca0(char*);

// SIZE 0xc
struct ent_555490 {
	char* e;
	int a;
	int b;
};

// FUNCTION: GOLD 0x54d430
// SIZE: 128
// FUNCTION: GOLDTL 0x555490
// SIZE: 115

int __cdecl fcn_00555490(char* o, struct ent_555490* tab, int* out)
{
	int i;

	if (*(unsigned short*) o != 0xffff && o[8] != 0 && o[2] == 0 && *(char**) (o + 0x184) != 0 &&
	    fcn_0047dca0(o) != 0) {
		for (i = 0; i < 16; i++) {
			if (tab[i].e == 0) {
				return 0;
			}
			if (*(int*) (tab[i].e + 1) == *(int*) (*(char**) (o + 0x184) + 0x2c) &&
			    *(unsigned short*) (tab[i].e + 0x27) != 0xffff) {
				*out = i;
				return 1;
			}
		}
	}
	return 0;
}
