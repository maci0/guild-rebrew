// FUNCTION: GOLD 0x5590c0
// SIZE: 160
// FUNCTION: GOLDTL 0x5612e0
// SIZE: 160

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

void __cdecl fcn_00500bb0(struct pos14*, int, int, int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl fcn_004c64b0(int, int, int, int, int, int, char*);

void __cdecl fcn_005612e0(char* e)
{
	char* t;

	*(struct pos14*) (e + 0x52) = g_7f4c00;
	fcn_00500bb0((struct pos14*) (e + 0x52), 0, 1, 0);
	if (*(int*) (e + 0x10) == -1) {
		t = gm_StartFilteredEntitySearch(1, 5, 0x16);
		if (t != 0 || (t = gm_StartFilteredEntitySearch(1, 5, 0xf)) != 0) {
			*(int*) (e + 0x10) = *(int*) (t + 1);
		}
	}
	*(int*) (e + 0xc4) = -1;
	*(int*) (e + 0xc8) = fcn_004c64b0(0, *(int*) (e + 0x10), -1, 0, 1, 0x174, "SABOTAGE");
}
