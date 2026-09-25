// FUNCTION: GOLDTL 0x422760
// SIZE: 96

// SIZE 0x30
typedef struct {
	int a;
	int key;
	char pad[0x28];
} T422760;

T422760* __cdecl fcn_00422760(int key, int* idx)
{
	T422760* r = 0;
	T422760* t;
	int i;
	int n;

	if (*(int*) 0x6b7d7c == 0) {
		return (T422760*) 0x14cbbe0;
	}
	t = *(T422760**) 0x6b7e88;
	if (t != 0) {
		n = *(int*) 0x6b7e8c;
		for (i = *idx; i < n; i++) {
			if (t[i].key == key) {
				*idx = i;
				r = &t[i];
				break;
			}
		}
	}
	return r;
}
