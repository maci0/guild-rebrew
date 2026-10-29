


typedef struct
{
	int key;
	char pad[0x40];
} Rec44;
// SIZE 0x44

extern Rec44 g_6918e8[];
extern Rec44 g_693228[];

void __cdecl fcn_004fdd70(Rec44*);

Rec44* __cdecl fcn_004fd9d0(int which, int key)
{
	Rec44* base;
	int i;

	i = 0;
	if (which == 0) {
		base = g_6918e8;
	} else if (which == 1) {
		base = g_693228;
	} else {
		return 0;
	}
	for (; i < 0x5f; i++) {
		if (base[i].key == 0) {
			break;
		}
		if (base[i].key == key) {
			fcn_004fdd70(&base[i]);
			return &base[i];
		}
	}
	return &base[i];
}
