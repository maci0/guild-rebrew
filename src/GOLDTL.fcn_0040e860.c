// FUNCTION: GOLDTL 0x40e860

void __cdecl fcn_00455350(char*, char*, char*);
int __cdecl fcn_00442910(int, char*, char*, int);

int __cdecl fcn_0040e860(int* a1, char** a2)
{
	char x[0x10];

	if (*a2 == 0) {
		return 0;
	}
	fcn_00455350(*a2, *a2 + 0x4c, x);
	return fcn_00442910(0, x, *a2 + 0x84, *a1);
}
