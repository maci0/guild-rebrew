// FUNCTION: GOLD 0x004d0520
// SIZE: 79
// FUNCTION: GOLDTL 0x4d1570
// SIZE: 79

typedef struct
{
	int a;
	int b;
	int c;
	char flag;
	char pad[0x1f];
} Rec2c;
// SIZE 0x2c

Rec2c* __cdecl fcn_004ceac0(char*, char*);
void __cdecl fcn_004c67c0(int, Rec2c*);

void __cdecl fcn_004d1570(char* a1, char* a2)
{
	Rec2c* s;
	Rec2c r;

	s = fcn_004ceac0(a1, a2);
	s->flag = 0;
	r = *s;
	r.a = *(int*) (a2 + 4);
	r.b = 8;
	fcn_004c67c0(*(int*) (a1 + 0x10), &r);
}
