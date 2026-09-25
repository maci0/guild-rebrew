// FUNCTION: GOLDTL 0x0055a8e0
// SIZE: 60

typedef struct {
	short w[7];
} Rec14;
// SIZE 0xe

int __cdecl fcn_004c5620(int, char*);

void __cdecl fcn_0055a8e0(char* e)
{
	if ((e[0x78] & 4) == 0) {
		*(Rec14*) (e + 0x52) = *(Rec14*) (e + 0x44);
		*(int*) (e + 0x84) = fcn_004c5620(0, e);
	}
}
