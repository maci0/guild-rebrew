// FUNCTION: GOLDTL 0x0050bb50
// SIZE: 86

float __cdecl fcn_0050b980(int, int);

float __cdecl fcn_0050bb50(int id, unsigned char a)
{
	int i;

	for (i = 0; i < 0x55; i++) {
		if (*(unsigned short*) ((char*) 0x85ab90 + a * 0x2a90 + i * 0x80) == id) {
			return *(float*) ((char*) 0x85abc8 + a * 0x2a90 + i * 0x80);
		}
	}
	return fcn_0050b980(id, 100);
}
