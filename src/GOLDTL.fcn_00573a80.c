// FUNCTION: GOLD 0x0056b690
// SIZE: 380
// FUNCTION: GOLDTL 0x573a80
// SIZE: 380

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
extern unsigned char g_773d75;

int __cdecl fcn_00500cb0(struct pos14*, struct pos14*);
int __cdecl fcn_004c51f0(int, int, int, int, unsigned char, int);
int __cdecl fcn_004c4450(int);
char* __cdecl fcn_004c4480(int);
void __cdecl fcn_00500bb0(struct pos14*, int, int, int);
void __cdecl fcn_005015e0(int*, char**, int*, int);
void __cdecl fcn_00510820(int, char*, int);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_00573a80(char* u)
{
	char* x;

	switch (*(int*) (u + 0x70)) {
	case 0:
		if (fcn_00500cb0((struct pos14*) (u + 0x52), &g_7f4c00) > 0) {
			break;
		}
		*(int*) (u + 0xc8) = fcn_004c51f0(*(int*) (u + 0xac), -1, *(int*) (u + 0xb4), 1, g_773d75, 0);
		(*(int*) (u + 0x70))++;
		break;
	case 1:
		if (fcn_004c4450(*(int*) (u + 0xc8)) == 0) {
			break;
		}
		if (fcn_004c4450(*(int*) (u + 0xc8)) == 2) {
			goto kill;
		}
		x = fcn_004c4480(*(int*) (u + 0xc8));
		*(int*) (u + 0xb8) = *(int*) (x + 2);
		*(int*) (u + 0xc0) = 0x20;
		*(int*) (u + 0xc4) = 0;
		fcn_00500bb0((struct pos14*) (u + 0x52), 0, 1, 0);
		(*(int*) (u + 0x70))++;
		break;
	case 2:
		if (fcn_00500cb0((struct pos14*) (u + 0x52), &g_7f4c00) >= 0) {
			break;
		}
		do {
			fcn_005015e0(0, &x, 0, *(int*) (u + 0xb8));
			fcn_00500bb0((struct pos14*) (u + 0x52), 0, 1, 0);
			if (*(int*) (u + 0xc4) > *(int*) (u + 0xc0)) {
				fcn_00510820(*(int*) (x + 0x18), x, 1);
				fcn_00546190(u);
				break;
			}
		} while (fcn_00500cb0((struct pos14*) (u + 0x52), &g_7f4c00) < 0);
		break;
	case -2:
	case -1:
kill:
		fcn_00546190(u);
		break;
	}
}
