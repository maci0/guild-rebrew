// FUNCTION: GOLDTL 0x579410
// SIZE: 69

void __cdecl fcn_0051af00(void*, int, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, int);

void __cdecl fcn_00579410(void* a1, void* a2)
{
	char buf[0x400];

	fcn_0051af00(buf, 0x40ff, *(unsigned short*) a2);
	fcn_00545d40(*(int*) a1, -1, buf, 1, 0x5f4, 0);
}
