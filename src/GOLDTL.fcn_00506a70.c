// FUNCTION: GOLDTL 0x00506a70
// SIZE: 64
// FUNCTION: GOLD 0x00503c20
// SIZE: 64

void __cdecl fcn_00529160(int, int, int, int);
void __cdecl fcn_0055bc40(unsigned short*);
void __cdecl fcn_00571100(unsigned short*);
void __cdecl fcn_005758f0(unsigned short*);
void __cdecl fcn_004e8940(unsigned short*);

void __cdecl fcn_00506a70(unsigned short* e)
{
	if (e != 0 && *e != 0xffff) {
		fcn_00529160(0, 0, *e, 0);
		fcn_0055bc40(e);
		fcn_00571100(e);
		fcn_005758f0(e);
		fcn_004e8940(e);
	}
}
