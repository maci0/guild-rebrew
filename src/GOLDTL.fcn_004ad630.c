// FUNCTION: GOLDTL 0x4ad630
// SIZE: 97

extern int g_7f4c00;
extern int g_664e0c[];

int __cdecl fcn_004e8a80(int id, int* out);
int __cdecl fcn_00508e40(int h);
void __cdecl fcn_004e8240(int h, int a, int b, int c, int d);

void __cdecl fcn_004ad630(void)
{
	int info[6];
	int n;

	n = g_7f4c00;
	if (n >= 4) {
		n = n % 4;
		if (n != 0) {
			n = g_664e0c[n];
			if (fcn_004e8a80(n, info) != 0) {
				if (fcn_00508e40(info[1]) != 0) {
					fcn_004e8240(info[0], 0, 0, 1, 0xff);
				}
			}
		}
	}
}
