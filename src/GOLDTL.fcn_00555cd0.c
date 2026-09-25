// FUNCTION: GOLD 0x0054dc70
// SIZE: 92
// FUNCTION: GOLDTL 0x00555cd0
// SIZE: 92

typedef struct {
	short w[7];
} Rec14;
// SIZE 0xe

extern Rec14 g_7f4c00;

short __cdecl fcn_004ac260(void);
int __cdecl fcn_004c5620(int, char*);

void __cdecl fcn_00555cd0(char* e)
{
	if ((e[0x78] & 4) == 0) {
		*(short*) (e + 0xac) = fcn_004ac260();
		*(int*) (e + 0xb4) = -1;
		*(Rec14*) (e + 0x52) = g_7f4c00;
		*(int*) (e + 0x84) = fcn_004c5620(0, e);
	}
}
