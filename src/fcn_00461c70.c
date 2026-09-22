// FUNCTION: GOLDTL 0x461c70
// SIZE: 37

int __cdecl fcn_00460a40(int);

int __cdecl fcn_00461c70(char* p)
{
	int v;

	if (p == 0) {
		return -2;
	}
	if (*(int*) (p + 0x1c) == 0) {
		return -2;
	}
	v = *(int*) (*(int*) (p + 0x1c) + 0x14);
	if (v == 0) {
		return -2;
	}
	return fcn_00460a40(v);
}
