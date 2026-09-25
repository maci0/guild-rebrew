// FUNCTION: GOLD 0x4e4870
// SIZE: 64
// FUNCTION: GOLDTL 0x4e6200
// SIZE: 59

void* __cdecl fcn_00508e40(int);

int __cdecl fcn_004e6200(int id, unsigned char* a2)
{
	int i;

	for (i = 0; i < a2[0x30]; i++) {
		if (*(int*) (a2 + 0x34 + i * 4) == id) {
			if (fcn_00508e40(id) != 0) {
				return 1;
			}
			break;
		}
	}
	return 0;
}
