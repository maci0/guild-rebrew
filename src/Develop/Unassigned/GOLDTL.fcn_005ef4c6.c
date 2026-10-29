#pragma optimize("y", off)
typedef struct Disp { char pad[0x3e8]; } Disp;
void __fastcall fcn_00616815(Disp* self);
void __fastcall fcn_006168be(Disp* self);
int __fastcall fcn_00618c83(Disp* self, int* edxarg, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);
/* ADDRESS: GOLDTL 0x005ef4c6 */
int __stdcall fcn_005ef4c6(int a1, int a2, int a3, int* a4, int* a5, int* a6)
{
	Disp d;
	int ret;
	int rc;
	fcn_00616815(&d);
	ret = 0;
	if (a4 != 0) {
		*a4 = ret;
	}
	if (a5 != 0) {
		*a5 = ret;
	}
	if (a6 != 0) {
		*a6 = ret;
	}
	rc = fcn_00618c83(&d, a4, a1, a2, ret, 1, a3, a4, a5, a6);
	if (rc < 0) {
		ret = rc;
	}
	fcn_006168be(&d);
	return ret;
}
