// FUNCTION: GOLD 0x5cb330
// SIZE: 112
// FUNCTION: GOLDTL 0x005d75d0
// SIZE: 104

int __cdecl fcn_004e8760(char*, int, int);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00535960(void);

int __cdecl fcn_005d75d0(char* e, int a2, int a3)
{
	int h;

	h = fcn_004e8760(e, a2, a3);
	if (h != -1) {
		if (e[2] == 6) {
			while (fcn_004c4450(h) == 0) {
				fcn_00535960();
			}
			return fcn_004c4450(h) != 2;
		}
		return 1;
	}
	return 0;
}
