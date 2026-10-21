typedef struct {
	unsigned char b0 : 1;
	unsigned char b1 : 1;
	unsigned char b2 : 1;
	unsigned char b3 : 1;
	unsigned char b4 : 1;
	unsigned char b5 : 1;
	unsigned char b6 : 1;
	unsigned char b7 : 1;
} MaskBits;

typedef union {
	unsigned char b;
	MaskBits s;
} Mask;

extern float g_1042fc8[24];
extern float g_10529c8;
extern float g_10421a0;
extern float g_10432a0;
extern float g_1043294;
extern float g_662c6c;

/* ADDRESS: GOLDTL 0x00437ee0 */

/* Tests the eight corner rays against the four side planes and the near/far
 * depths. Returns the plane mask; bit 6 marks a corner outside every plane.
 * When the ray set is not culled, stores the extreme depths. */
unsigned char __cdecl fcn_00437ee0(float* p, float* pmin, float* pmax)
{
	Mask f;
	Mask common;
	Mask flags;
	float lo;
	float hi;
	float* q;
	int i;

	flags.b = 0;
	common.b = 0x3f;
	q = p + 2;
	for (i = 0; i < 8; i++) {
		f.b = (g_1042fc8[0] * q[-2] + g_1042fc8[1] * q[-1]
			+ g_1042fc8[2] * q[0] < g_1042fc8[3]) & 1;
		f.s.b1 = (g_1042fc8[4] * q[-2] + g_1042fc8[5] * q[-1]
			+ g_1042fc8[6] * q[0] < g_1042fc8[7]);
		f.s.b2 = (g_1042fc8[8] * q[-2] + g_1042fc8[9] * q[-1]
			+ g_1042fc8[10] * q[0] < g_1042fc8[11]);
		f.s.b3 = (g_1042fc8[12] * q[-2] + g_1042fc8[13] * q[-1]
			+ g_1042fc8[14] * q[0] < g_1042fc8[15]);
		f.s.b4 = (q[0] < g_10529c8);
		f.s.b5 = (q[0] > g_10421a0);
		flags.b |= f.b;
		common.b &= f.b;
		q += 0x14;
	}
	flags.s.b6 = (common.b != 0);
	if ((flags.b & 0x40) == 0) {
		lo = 1e10f;
		hi = g_662c6c;
		q = p + 2;
		for (i = 0; i < 8; i++) {
			if (!(q[0] > lo))
				lo = q[0];
			if (!(hi > q[0]))
				hi = q[0];
			q += 0x14;
		}
		if (pmin) {
			*pmin = lo;
			if (!(g_10432a0 < lo))
				g_10432a0 = lo;
		}
		if (pmax) {
			*pmax = hi;
			if (!(g_1043294 > hi))
				g_1043294 = hi;
		}
	}
	return flags.b;
}
