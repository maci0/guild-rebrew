// FUNCTION: GOLDTL 0x5c6220
// SIZE: 73

char* __cdecl fcn_005c6220(int key, int* out)
{
	int n;
	int v;

	v = *(int*) 0x6abb08;
	n = 0;
	while (v != 0) {
		if (v == key) {
			if (out != 0) {
				*out = n;
			}
			return (char*) (0x6abb08 + n * 0x1c);
		}
		n++;
		v = *(int*) (0x6abb08 + n * 0x1c);
	}
	return 0;
}
