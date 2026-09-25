extern int g_7e46ac;
// FUNCTION: GOLDTL 0x005268c0
// SIZE: 83

int __cdecl fcn_00470820(int, int, const char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00519190(int);
void __cdecl fcn_005373e0(int, int);

int __cdecl fcn_005268c0(int a, char flags)
{
	int h;

	if (flags & 0x10) {
		h = fcn_00470820(0, 0, "misc\\Messagebox_BIG");
	} else if (flags & 0x20) {
		h = fcn_00470820(0, 0, "misc\\Messagebox_VERY_BIG");
	} else {
		h = fcn_00470820(0, 0, "misc\\Messagebox");
	}
	fcn_00471b60(h);
	fcn_00519190(a);
	fcn_005373e0(0, g_7e46ac);
	return h;
}
