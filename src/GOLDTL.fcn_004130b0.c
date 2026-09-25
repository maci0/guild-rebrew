// FUNCTION: GOLDTL 0x4130b0
// SIZE: 97

int __cdecl fcn_0065f220(int, int);
void __cdecl fcn_00435500(char*, int);
void __cdecl fcn_00438ac0(char*, int);

int __cdecl fcn_004130b0(char* p, int a2)
{
	int i;
	char* q;
	int e;

	for (i = 0; i < 3; i++) {
		q = *(char**) (p + 0x1ec);
		if (q != 0) {
			e = *(int*) (q + i * 0x7c + 0x484);
			if (e != 0 && fcn_0065f220(e, a2) == 0) {
				fcn_00435500(*(char**) (p + 0x1ec) + 0xf4, a2);
				fcn_00438ac0(p, 0);
			}
		}
	}
	return 1;
}
