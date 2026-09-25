// FUNCTION: GOLDTL 0x418dc0
// SIZE: 63

// SIZE 0x54
typedef struct {
	char pad[0x38];
	int used;
	char pad2[0x18];
} T418dc0;

T418dc0* __cdecl fcn_00418dc0(void)
{
	int i = 0;
	T418dc0* r = 0;
	T418dc0* t;
	int n;

	t = *(T418dc0**) 0x6b5d08;
	if (t != 0) {
		n = *(int*) 0x677680;
		for (; i < n; i++) {
			if (t[i].used == 0) {
				r = &t[i];
				break;
			}
		}
	}
	return r;
}
