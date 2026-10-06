// FUNCTION: GOLD 0x00453570
// fcn_00453570 — if(a) fcn_00438e60([a+0x208], a, 0x240, 0x453270).

int __cdecl fcn_00438e60(int, int, int, int);

void __cdecl fcn_00453570(char* a)
{
	if (a != 0) {
		fcn_00438e60(*(int*) (a + 0x208), (int) a, 0x240, 0x453270);
	}
}
