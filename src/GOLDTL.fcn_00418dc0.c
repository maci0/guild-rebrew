// FUNCTION: GOLD 0x00417800
// SIZE: 63
// FUNCTION: GOLDTL 0x418dc0
// SIZE: 63

extern int g_677680;

// SIZE 0x54
typedef struct {
	char pad[0x38];
	int used;
	char pad2[0x18];
} T418dc0;

extern T418dc0* g_6b5d08;

T418dc0* __cdecl fcn_00418dc0(void)
{
	int i = 0;
	T418dc0* r = 0;
	T418dc0* t;
	int n;

	t = g_6b5d08;
	if (t != 0) {
		n = g_677680;
		for (; i < n; i++) {
			if (t[i].used == 0) {
				r = &t[i];
				break;
			}
		}
	}
	return r;
}
