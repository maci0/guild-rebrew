// FUNCTION: GOLDTL 0x0055ab40
// SIZE: 89

typedef struct {
	short w[7];
} Rec14;
// SIZE 0xe

extern Rec14 g_7f4c00;

void __cdecl fcn_00500bb0(char*, int, int, int);
int __cdecl fcn_004c5620(int, char*);

void __cdecl fcn_0055ab40(char* e)
{
	if ((e[0x78] & 4) == 0) {
		*(Rec14*) (e + 0x52) = g_7f4c00;
		fcn_00500bb0(e + 0x52, *(int*) (e + 0xb8), 0, 0);
		*(int*) (e + 0x84) = fcn_004c5620(0, e);
	}
}
