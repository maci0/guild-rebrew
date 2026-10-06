// FUNCTION: GOLD 0x0056d2f0
// FUNCTION: GOLDTL 0x575710

extern char g_6a7e04[];
extern char g_6a7df8[];
extern char g_6a7df0[];

typedef void (__cdecl* handler)(char*);

int __cdecl fcn_00545580(int, handler, handler);
void __cdecl fcn_00530ab0(int, char*, int, int, int);
void __cdecl fcn_00571140(char*);
void __cdecl fcn_00571240(char*);
void __cdecl fcn_00571720(char*);
void __cdecl fcn_00571870(char*);
void __cdecl fcn_00572760(char*);
void __cdecl fcn_00572770(char*);
void __cdecl fcn_00572780(char*);
void __cdecl fcn_005727f0(char*);
void __cdecl fcn_005729e0(char*);
void __cdecl fcn_00572a50(char*);
void __cdecl fcn_00572d90(char*);
void __cdecl fcn_00572da0(char*);
void __cdecl fcn_00572e40(char*);
void __cdecl fcn_00572ff0(char*);
void __cdecl fcn_00573a10(char*);
void __cdecl fcn_00573a80(char*);
void __cdecl fcn_00573c00(char*);
void __cdecl fcn_005744c0(char*);
void __cdecl fcn_00575450(char*);
void __cdecl fcn_00575460(char*);
void __cdecl fcn_00575470(char*);
void __cdecl fcn_005754e0(char*);
void __cdecl fcn_005756f0(char*);
void __cdecl fcn_00575700(char*);

int __cdecl fcn_00575710(void)
{
	if (fcn_00545580(3, fcn_00571140, fcn_00571240) != 0) {
		return 1;
	}
	fcn_00530ab0(3, g_6a7e04, 1, 0x501, 0xac);
	if (fcn_00545580(4, fcn_00571720, fcn_00571870) != 0) {
		return 1;
	}
	fcn_00530ab0(4, g_6a7df8, 1, 0x4ff, 0xac);
	if (fcn_00545580(5, fcn_00572760, fcn_00572770) != 0) {
		return 1;
	}
	if (fcn_00545580(8, fcn_00572780, fcn_005727f0) != 0) {
		return 1;
	}
	fcn_00530ab0(8, g_6a7df0, 1, 0x500, 0xac);
	if (fcn_00545580(9, fcn_005729e0, fcn_00572a50) != 0) {
		return 1;
	}
	fcn_00530ab0(9, g_6a7df0, 1, 0x500, -1);
	if (fcn_00545580(0xa, fcn_00572d90, fcn_00572da0) != 0) {
		return 1;
	}
	if (fcn_00545580(0xb, fcn_00572e40, fcn_00572ff0) != 0) {
		return 1;
	}
	if (fcn_00545580(0xc, fcn_00573a10, fcn_00573a80) != 0) {
		return 1;
	}
	if (fcn_00545580(0xd, fcn_00573c00, fcn_005744c0) != 0) {
		return 1;
	}
	if (fcn_00545580(0xe, fcn_00575450, fcn_00575460) != 0) {
		return 1;
	}
	if (fcn_00545580(0x4c, fcn_00575470, fcn_005754e0) != 0) {
		return 1;
	}
	return fcn_00545580(0x4d, fcn_005756f0, fcn_00575700) != 0;
}
