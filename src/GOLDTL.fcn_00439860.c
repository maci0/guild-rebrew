// FUNCTION: GOLDTL 0x439860
// SIZE: 100

void __cdecl fcn_004379a0(int, int, int, void*, char*);
void __cdecl fcn_00456d50(void);
void __cdecl fcn_00456b80(char*);
void __cdecl fcn_00439d80(char*);

void __cdecl fcn_00439860(char* o)
{
	int h;

	if (o == 0) {
		return;
	}
	h = *(int*) (o + 0x20c);
	if (*(int*) (o + 0x218) == 1 && *(int*) (o + 0x21c) != 1) {
		*(int*) (o + 0x218) = *(int*) (o + 0x21c);
	}
	if (*(int*) (o + 0x218) == 8) {
		fcn_004379a0(h, 0, 0x40, fcn_00456d50, o);
	}
	if ((o[0x215] & 1) != 0) {
		fcn_00456b80(o);
	}
	fcn_00439d80(o);
}
