

typedef struct {
	short w[3];
} Rec6;
// SIZE 0x6

extern Rec6 g_6995d8[];

Rec6 __cdecl gm_GetCategoryStatTemplate(int idx)
{
	if (idx >= 0x23) {
		return g_6995d8[0];
	}
	return g_6995d8[idx];
}
