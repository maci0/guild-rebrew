typedef struct Mult {
	int key;
	int mult;
	int pad[2];
} Mult;
// SIZE 0x10

extern Mult g_664260[7];

int __cdecl fcn_0050dac0(unsigned short id);

// FUNCTION: GOLDTL 0x493ee0
// SIZE: 102
int __cdecl fcn_00493ee0(unsigned short* a, unsigned short* b, int key)
{
	int v;
	int i;

	v = (int) ((fcn_0050dac0(*a) + fcn_0050dac0(*b)) * 0.0005f);
	for (i = 0; i < 7; i++) {
		if (g_664260[i].key == key) {
			return g_664260[i].mult * v;
		}
	}
	return v * 10;
}
