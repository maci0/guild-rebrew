#pragma optimize("y", off)

typedef struct SMALL_5ef254 SMALL_5ef254;
struct SMALL_5ef254 {
	int f0;
	int f4;
	int f8;
	int fc;
};

typedef struct DISP_5ef254 DISP_5ef254;
struct DISP_5ef254 {
	char pad_000[0x3e8];
};

void __fastcall fcn_006165dd(SMALL_5ef254* self);
int __fastcall fcn_006165ef(SMALL_5ef254* self, int edxarg, int a1);
void __fastcall fcn_00616815(DISP_5ef254* self);
int __fastcall fcn_00618c83(DISP_5ef254* self, int edxarg, int a1, int a2,
	int a3, int a4, int a5, int a6, int a7, int a8);
void __fastcall fcn_006168be(DISP_5ef254* self);
void __fastcall fcn_0061680a(SMALL_5ef254* self);

/* ADDRESS: GOLDTL 0x005ef254 */
int __stdcall fcn_005ef254(int a1, int a2, int* a3, int* a4, int* a5)
{
	SMALL_5ef254 small;
	DISP_5ef254 disp;
	int ret;
	int rc;

	fcn_006165dd(&small);
	fcn_00616815(&disp);
	ret = 0;
	if (a3 != 0) {
		*a3 = ret;
	}
	if (a4 != 0) {
		*a4 = ret;
	}
	if (a5 != 0) {
		*a5 = ret;
	}
	rc = fcn_006165ef(&small, a1, ret);
	if (rc < 0) {
		ret = rc;
	} else {
		rc = fcn_00618c83(&disp, small.f8, small.fc, a1, 1, a2, a3, a4, a5, 0);
		if (rc < 0) {
			ret = rc;
		}
	}
	fcn_006168be(&disp);
	fcn_0061680a(&small);
	return ret;
}
