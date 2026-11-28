


typedef struct {
	short w[3];
} Rec6;
// SIZE 0x6

extern Rec6 g_699398[];

/* ADDRESS: GOLDDE 0x004f20b0 */
Rec6 __cdecl gm_GetStatRecord(int idx)
{
	if (idx >= 0x5f) {
		return g_699398[0];
	}
	return g_699398[idx];
}
