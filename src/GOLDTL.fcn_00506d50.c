// FUNCTION: GOLDTL 0x00506d50
// SIZE: 66

typedef struct {
	short w[3];
} Rec6;
// SIZE 0x6

extern Rec6 g_699398[];

Rec6 __cdecl fcn_00506d50(int idx)
{
	if (idx >= 0x5f) {
		return g_699398[0];
	}
	return g_699398[idx];
}
