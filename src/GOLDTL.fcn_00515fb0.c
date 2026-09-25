extern char g_7f4c00[];
// FUNCTION: GOLD 0x00512870
// SIZE: 70
// FUNCTION: GOLDTL 0x00515fb0
// SIZE: 70

void __cdecl fcn_00500e20(char*);
int __cdecl fcn_00505370(unsigned char*);
void __cdecl fcn_00515f60(const char*, int, int);

void __cdecl fcn_00515fb0(unsigned char* e)
{
	fcn_00500e20(g_7f4c00);
	if (e != 0 && fcn_00505370(e) && *(short*) (e + 0x29) == 0xfd && *e == 0x1e) {
		fcn_00515f60("AesteKnacken_s", 0x50, 0x1f40);
	}
}
