// FUNCTION: GOLDTL 0x569a40
// SIZE: 79

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
unsigned short __cdecl fcn_0042e410(int);

void __cdecl fcn_00569a40(char* e)
{
	*(struct pos14*) (e + 0x52) = g_7f4c00;
	fcn_00500bb0((struct pos14*) (e + 0x52), 1, fcn_0042e410(0x1e) - 0x14, 0);
}
