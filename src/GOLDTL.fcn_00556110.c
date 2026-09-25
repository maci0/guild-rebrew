// FUNCTION: GOLDTL 0x00556110
// SIZE: 83

typedef struct {
	short w[7];
} Rec14;
// SIZE 0xe

extern Rec14 g_7f4c00;

int __cdecl fcn_004c5620(int, char*);

void __cdecl fcn_00556110(char* e)
{
	if ((e[0x78] & 4) == 0) {
		*(Rec14*) (e + 0x52) = g_7f4c00;
		*(int*) (e + 0xac) = 0;
		*(int*) (e + 0xb0) = 0;
		*(int*) (e + 0x84) = fcn_004c5620(0, e);
	}
}
