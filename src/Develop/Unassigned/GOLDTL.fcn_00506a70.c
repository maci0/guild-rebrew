


void __cdecl fcn_00529160(int, int, int, int);
void __cdecl he_ClearEntityActions(unsigned short*);
void __cdecl he_CancelEntityActions0x23(unsigned short*);
void __cdecl fcn_005758f0(unsigned short*);
void __cdecl fcn_004e8940(unsigned short*);

void __cdecl fcn_00506a70(unsigned short* e)
{
	if (e != 0 && *e != 0xffff) {
		fcn_00529160(0, 0, *e, 0);
		he_ClearEntityActions(e);
		he_CancelEntityActions0x23(e);
		fcn_005758f0(e);
		fcn_004e8940(e);
	}
}
