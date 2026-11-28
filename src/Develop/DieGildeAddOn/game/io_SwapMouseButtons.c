


// SIZE 0x4c
typedef struct {
	int f00;
	int f04;
	int f08;
	int f0c;
	int f10;
	int f14;
	int f18;
	int f1c;
	int f20;
	int f24;
	int f28;
	int f2c;
	int rest[7];
} T411f90;

extern int g_6b5c94;
extern int io_ActiveInputState[];

void __cdecl io_SwapMouseButtons(void)
{
	T411f90 t;

	if (g_6b5c94 != 0) {
		t = (*(T411f90*)io_ActiveInputState);
		(*(T411f90*)io_ActiveInputState).f0c = (*(T411f90*)io_ActiveInputState).f20;
		(*(T411f90*)io_ActiveInputState).f18 = (*(T411f90*)io_ActiveInputState).f2c;
		(*(T411f90*)io_ActiveInputState).f2c = t.f18;
		(*(T411f90*)io_ActiveInputState).f20 = t.f0c;
	}
}
