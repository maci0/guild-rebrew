typedef struct {
	unsigned char id;
	char pad[0x23];
} Rec24;
// SIZE 0x24

int __cdecl fcn_004f4980(char*, int, Rec24*);
int __cdecl fcn_004f5110(void*, int);
int __cdecl fcn_005d6540(char*, int*);

// FUNCTION: GOLDTL 0x004f82f0
// SIZE: 418

int __cdecl fcn_004f82f0(char* e, int* s)
{
	Rec24 rec;
	int r;
	char* p;

	r = 0;
	if (*s == 3 || *s == 1) {
		if (e[0x166] == 0)
			return 1;
		if (fcn_004f4980(e, 2, &rec) == 0)
			return 1;
		if (e[2] == 6)
			fcn_004f5110((char*) s + 0x14, rec.id);
		if (*(int*) (e + 0x1c8) & 0x200)
			return 9;
		if (*(int*) (e + 0x1c8) & 0x100000)
			return 1;
		s[1] = rec.id;
		if (*s == 3) {
			s[0x85] = 2;
			r = fcn_005d6540(e, s);
		}
		return r | 2;
	}
	if (*s == 4 || *s == 2) {
		if ((*(int*) (e + 0x1c8) & 0x100) == 0 || (p = *(char**) ((char*) s + 0x21c)) == 0)
			return 1;
		if (p[0x166] == 0)
			return 1;
		if (*(int*) (p + 0x1c8) & 0x100000)
			return 1;
		if (fcn_004f4980(p, 2, &rec) == 0)
			return 1;
		s[1] = rec.id;
		if (*s == 4) {
			s[0x85] = 2;
			r = fcn_005d6540(e, s);
		} else if (e[2] == 6) {
			fcn_004f5110((char*) s + 0x14, rec.id);
		}
		return r | 10;
	}
	return 1;
}
