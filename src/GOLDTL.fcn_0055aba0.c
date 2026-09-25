// FUNCTION: GOLD 0x00552a70
// SIZE: 94
// FUNCTION: GOLDTL 0x55aba0
// SIZE: 94

#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

extern struct pos14 g_7f4c00;

int __cdecl fcn_004c5620(int, char*);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_0055aba0(char* u)
{
	if (*(int*) (u + 0x70) != -1 && *(int*) (u + 0x70) != -2) {
		if (u[0x78] & 4) {
			return;
		}
		*(struct pos14*) (u + 0x52) = g_7f4c00;
		*(int*) (u + 0x84) = fcn_004c5620(-1, u);
	} else {
		fcn_00546190(u);
	}
}
