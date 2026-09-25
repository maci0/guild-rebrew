// FUNCTION: GOLD 0x00548480
// SIZE: 143
// FUNCTION: GOLDTL 0x5503f0
// SIZE: 143

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

int __cdecl fcn_004c4450(int);
void __cdecl fcn_00500bb0(struct pos14*, int, int, int);
int __cdecl fcn_004c5620(int, char*);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_005503f0(char* u)
{
	if (*(int*) (u + 0x84) != -1 && fcn_004c4450(*(int*) (u + 0x84)) == 0) {
		return;
	}
	*(int*) (u + 0x84) = -1;
	switch (*(int*) (u + 0x70)) {
	case 0:
		if (u[0x78] & 2) {
			*(struct pos14*) (u + 0x52) = g_7f4c00;
			fcn_00500bb0((struct pos14*) (u + 0x52), 0, 2, 0);
			*(int*) (u + 0x84) = fcn_004c5620(-1, u);
		}
		break;
	case -2:
	case -1:
		fcn_00546190(u);
		break;
	}
}
