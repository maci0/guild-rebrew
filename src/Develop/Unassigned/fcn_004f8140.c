typedef struct {
	unsigned char id;
	char pad[0x23];
} Rec24;

int __cdecl fcn_004f4980(char*, int, Rec24*);
void __cdecl fcn_004f5110(void*, int);
int __cdecl fcn_005d6540(void*, void*);

/* ADDRESS: GOLDTL 0x004f8140 */
int __cdecl fcn_004f8140(char* a1, int* a2)
{
	Rec24 rec;
	int r;
	char* v;

	r = 0;
	if (*a2 == 3 || *a2 == 1) {
		if (a1[0x166] == 0)
			return 1;
		if (fcn_004f4980(a1, 1, &rec) == 0)
			return 1;
		if (a1[2] == 6)
			fcn_004f5110((char*) a2 + 0x14, rec.id);
		if (*(int*) (a1 + 0x1c8) & 0x200)
			return 9;
		if (*(int*) (a1 + 0x1c8) & 0x80000)
			return 1;
		a2[1] = rec.id;
		if (*a2 == 3) {
			*(int*) ((char*) a2 + 0x214) = 1;
			r = fcn_005d6540(a1, a2);
		}
		return r | 2;
	}
	if (*a2 == 4 || *a2 == 2) {
		if (((*(int*) (a1 + 0x1c8) & 0x100) == 0) || ((v = *(char**) ((char*) a2 + 0x21c)) == 0))
			return 1;
		if (v[0x166] == 0)
			return 1;
		if (*(int*) (v + 0x1c8) & 0x80000)
			return 1;
		if (fcn_004f4980(v, 1, &rec) == 0)
			return 1;
		a2[1] = rec.id;
		if (*a2 == 4) {
			*(int*) ((char*) a2 + 0x214) = 1;
			r = fcn_005d6540(a1, a2);
		} else if (a1[2] == 6) {
			fcn_004f5110((char*) a2 + 0x14, rec.id);
		}
		return r | 10;
	}
	return 1;
}
