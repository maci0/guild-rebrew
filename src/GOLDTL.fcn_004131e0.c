extern int g_6b8014;

float* __stdcall fcn_005ebbb9(float* out, const float* in);

/* 0x24 bytes between the camera vector and the matrix keep the matrix
 * at [esp+0x30] inside a 0x70-byte frame. */
// SIZE 0x64
struct CamPad131e0 {
	char hole[0x24];
	float m[16];
};

/* Camera position plus the view matrix at +0x18c applied to
 * (scale, scale, -amount), with scale = -amount * the float at 0x6628a8. */
// FUNCTION: GOLDTL 0x4131e0
// SIZE: 183

void __cdecl fcn_004131e0(float* out, float amount)
{
	float cam[3];
	struct CamPad131e0 blk;
	float neg;
	float scale;
	float a;
	char* base;

	base = (char*) g_6b8014;
	cam[0] = *(float*) (base + 0x4c);
	cam[1] = *(float*) (base + 0x50);
	cam[2] = *(float*) (base + 0x54);
	fcn_005ebbb9(blk.m, (float*) (base + 0x18c));
	neg = -amount;
	scale = neg * *(float*) 0x6628a8;
	*(float*) (blk.hole + 4) = scale;
	a = blk.m[8] * neg;
	a = a + blk.m[4] * scale;
	a = a + *(volatile float*) &blk.m[0] * *(volatile float*) (blk.hole + 4);
	*(float*) (blk.hole + 0x14) = a;
	a = blk.m[9] * neg;
	a = a + blk.m[5] * scale;
	a = a + *(volatile float*) &blk.m[1] * *(volatile float*) (blk.hole + 4);
	*(float*) (blk.hole + 0x18) = a;
	/* One expression: neg and scale stay on the x87 stack through the row,
	 * so the compiler drops them with fstp st(2); fstp st(0) afterwards.
	 * Separate statements pop neg at the m[10] multiply. */
	a = (blk.m[10] * neg + blk.m[6] * scale) + (*(volatile float*) &blk.m[2] * *(volatile float*) (blk.hole + 4));
	out[0] = *(float*) (blk.hole + 0x14) + cam[0];
	out[1] = *(float*) (blk.hole + 0x18) + cam[1];
	out[2] = a + cam[2];
}
