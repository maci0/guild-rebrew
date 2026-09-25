// FUNCTION: GOLD 0x0056d8b0
// SIZE: 283
// FUNCTION: GOLDTL 0x575cf0
// SIZE: 283

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
char* __cdecl fcn_004ecbe0(int);
float __cdecl fcn_004ecd50(char*, char*, int*);
void __cdecl fcn_00500bb0(struct pos14*, int, int, int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl fcn_00529160(char*, int, int, char*);
void __cdecl fcn_004c35f0(void);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_00575cf0(char* u)
{
	char* h;
	char* p;

	h = fcn_00508e40(*(int*) (u + 0xac));
	if (h != 0) {
		p = fcn_004ecbe0(*(int*) (u + 0xb0));
		if (p != 0) {
			*(float*) (u + 0xb4) = fcn_004ecd50(h, p, (int*) (u + 0xbc));
			if (!(*(float*) (u + 0xb4) <= g_6628a8)) {
				*(int*) (u + 0xb8) = *(int*) (u + 0xbc);
				*(struct pos14*) (u + 0xc0) = g_7f4c00;
				*(struct pos14*) (u + 0x52) = g_7f4c00;
				fcn_00500bb0((struct pos14*) (u + 0x52), 0, 5, 0);
				*(int*) (u + 0x70) = 0;
				fcn_00529160(*(char**) (h + 0x16c),
				    fcn_00502cd0(*(int*) (*(char**) (h + 0x16c) + 0x5d), 2, 6, 0, 0x24b), *(unsigned short*) h, u);
				fcn_004c35f0();
				return;
			}
		}
	}
	fcn_00546190(u);
}
