// FUNCTION: GOLDTL 0x529670
// SIZE: 159

char* __cdecl fcn_00445600(char*, int, int, char*);
void __cdecl fcn_00455350(char*, char*, float*);
int __cdecl fcn_00451840(char*, float*, float);

int __cdecl fcn_00529670(char* a, char* b)
{
	float pos[4];
	char* d;
	char* x;

	d = *(char**) (a + 0x184);
	if (*(char**) (b + 0x61) != 0) {
		if (d == 0) {
			return 0;
		}
		x = fcn_00445600(*(char**) (b + 0x61), 0x100, 0, "dummy_TUER");
		if (x != 0) {
			fcn_00455350(x, x + 0x4c, pos);
		} else {
			fcn_00455350(*(char**) (b + 0x61), *(char**) (b + 0x61) + 0x4c, pos);
		}
		if (fcn_00451840(*(char**) (d + 0x34) + 0x4c, pos, 750.0f) != 0 &&
		    *(int*) (d + 0x128) == 0) {
			return 1;
		}
	}
	if (d != 0 && *(int*) (d + 0x2c) == *(int*) (b + 1)) {
		return 1;
	}
	return 0;
}
