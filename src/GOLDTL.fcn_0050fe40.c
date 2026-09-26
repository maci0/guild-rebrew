// FUNCTION: GOLD 0x0050ca10
// SIZE: 64
// FUNCTION: GOLDTL 0x0050fe40
// SIZE: 64

extern char g_7f4ca0[];

void __cdecl fcn_004c54c0(int a, int b, int c, int d);

void __cdecl fcn_0050fe40(unsigned short id, int b)
{
	int i;

	for (i = 0; i < 768; i++) {
		if (((unsigned char*)g_7f4ca0)[i * 0x21c + 0x166] != 0) {
			fcn_004c54c0(id, i, b, 1);
		}
	}
}
