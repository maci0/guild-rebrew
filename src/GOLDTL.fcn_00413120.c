// FUNCTION: GOLDTL 0x413120
// SIZE: 63

void __cdecl fcn_00435500(char*, int);

int __cdecl fcn_00413120(char* p)
{
	int i;
	char* q;

	for (i = 0; i < 3; i++) {
		q = *(char**) (p + 0x1ec);
		if (q != 0 && *(int*) (q + i * 0x7c + 0x484) != 0) {
			fcn_00435500(q + 0xf4, *(int*) (q + i * 0x7c + 0x484));
		}
	}
	return 1;
}
