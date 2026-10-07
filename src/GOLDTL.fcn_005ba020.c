// FUNCTION: GOLD 0x005aea30
// FUNCTION: GOLDTL 0x005ba020

void __cdecl fcn_00455350(int, int, float*);
int __cdecl fcn_00451840(int, float*, float);
int __cdecl fcn_005015e0(char**, char**, int*, int);

int __cdecl fcn_005ba020(char* a1, char* a2)
{
	char* s;
	int id;
	char* owner;
	char* next;
	int last;
	float v[4];

	s = *(char**) (a2 + 0x3b);
	if (s == 0) {
		return 0;
	}
	if (*(int*) (a1 + 0x61) != 0) {
		fcn_00455350(*(int*) (a1 + 0x61), *(int*) (a1 + 0x61) + 0x4c, v);
		if (fcn_00451840(*(int*) (s + 0x34) + 0x4c, v, 1350.0f) != 0 && *(int*) (s + 0x128) == 0) {
			return 1;
		}
	}
	id = *(int*) (a2 + 6);
	while (id != -1) {
		if (fcn_005015e0(&owner, &next, &last, id) == 0) {
			return 0;
		}
		if (owner != 0) {
			return owner == a1;
		}
		if (next != 0) {
			id = *(int*) (next + 6);
		}
		if (last != 0) {
			return 0;
		}
	}
	return 0;
}
