// FUNCTION: GOLD 0x00504790
// SIZE: 161
// FUNCTION: GOLDTL 0x005077c0
// SIZE: 161

extern char g_7f4ca0[];
extern int g_7746d4;

unsigned char* __cdecl fcn_00509570(unsigned char* e);
int __cdecl fcn_00507b00(int k);

void __cdecl fcn_005077c0(int id, int nk)
{
	unsigned char* o;
	int a;
	int b;

	if (nk != ((unsigned char*)g_7f4ca0)[id * 0x21c + 0x164]) {
		*(int*) (((unsigned char*)g_7f4ca0) + id * 0x21c + 0x174) = 0;
	}
	o = fcn_00509570(((unsigned char*)g_7f4ca0) + id * 0x21c);
	if (o != 0 && (((unsigned char*)g_7f4ca0)[id * 0x21c + 2] == 6 || ((unsigned char*)g_7f4ca0)[id * 0x21c + 2] == 7 || ((unsigned char*)g_7f4ca0)[id * 0x21c + 2] == 5)) {
		a = fcn_00507b00(((unsigned char*)g_7f4ca0)[id * 0x21c + 0x164]);
		o[a + 0x74] = ((unsigned char*)g_7f4ca0)[id * 0x21c + 0x164];
		b = fcn_00507b00(nk);
		if (nk < o[b + 0x74] || o[b + 0x74] == 0) {
			o[b + 0x74] = (unsigned char) nk;
		}
		g_7746d4 = 1;
	}
	((unsigned char*)g_7f4ca0)[id * 0x21c + 0x164] = (unsigned char) nk;
}
