// FUNCTION: GOLD 0x005ba800
// SIZE: 80
// FUNCTION: GOLDTL 0x5c6270
// SIZE: 71

void* __cdecl fcn_00502cd0(int, int, int, int);
int __cdecl fcn_005c61e0(int);

int __cdecl fcn_005c6270(char* a1, int a2)
{
	char* p;

	p = (char*) fcn_00502cd0(*(int*) (a1 + 0x178), 1, 0, a2);
	if (p != 0) {
		if (fcn_005c61e0(*(unsigned short*) p) != 0) {
			if (*(int*) (p + 0x21) != 0) {
				return 1;
			}
		}
	}
	return 0;
}
