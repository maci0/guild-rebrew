// FUNCTION: GOLD 0x0056dc30
// SIZE: 266
// FUNCTION: GOLDTL 0x576070
// SIZE: 266

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
extern float g_6628a8;

char* __cdecl fcn_00508e40(int);
float __cdecl fcn_004ece30(char*, int, int*);
void __cdecl fcn_00500bb0(struct pos14*, int, int, int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl fcn_00529160(char*, int, int, char*);
void __cdecl fcn_004c35f0(void);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_00576070(char* u)
{
	char* h;

	h = fcn_00508e40(*(int*) (u + 0xac));
	if (h != 0) {
		*(float*) (u + 0xb4) = fcn_004ece30(h, *(int*) (u + 0xb0), (int*) (u + 0xbc));
		if (!(*(float*) (u + 0xb4) <= g_6628a8)) {
			*(int*) (u + 0xb8) = *(int*) (u + 0xbc);
			*(struct pos14*) (u + 0xc0) = g_7f4c00;
			*(struct pos14*) (u + 0x52) = g_7f4c00;
			fcn_00500bb0((struct pos14*) (u + 0x52), 0, 5, 0);
			*(int*) (u + 0x70) = 0;
			fcn_00529160(*(char**) (h + 0x16c), fcn_00502cd0(*(int*) (*(char**) (h + 0x16c) + 0x5d), 2, 6, 0, 0x24b),
			    *(unsigned short*) h, u);
			fcn_004c35f0();
			return;
		}
	}
	fcn_00546190(u);
}
