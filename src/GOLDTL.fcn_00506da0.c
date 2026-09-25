// FUNCTION: GOLDTL 0x00506da0
// SIZE: 66

typedef struct {
	short w[3];
} Rec6;
// SIZE 0x6

extern Rec6 g_6995d8[];

Rec6 __cdecl fcn_00506da0(int idx)
{
	if (idx >= 0x23) {
		return g_6995d8[0];
	}
	return g_6995d8[idx];
}
