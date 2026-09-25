// GLOBAL: GOLD 0x633198
extern int* g_6b7d78;
// FUNCTION: GOLD 0x00426290
// SIZE: 47
// FUNCTION: GOLDTL 0x422700
// SIZE: 47

int __cdecl fcn_0065f2f0(int, int, int);

int* __cdecl fcn_00422700(int a1)
{
	int* node;

	node = g_6b7d78;
	while (node != 0) {
		if (fcn_0065f2f0((int) node, a1, 0x32) == 0) {
			break;
		}
		node = (int*) node[0x13c / 4];
	}
	return node;
}
