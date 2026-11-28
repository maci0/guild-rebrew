typedef struct Stat {
	int v[8];
	int(__cdecl* check)(int a, int kind, int* out);
} Stat;
// SIZE 0x24

int __cdecl gm_GetLawEntry(int a, Stat* st);

/* ADDRESS: GOLDTL 0x004a8b70 */
/* ADDRESS: GOLDDE 0x00496ec0 */
int __cdecl ai_CheckLawActionPredicate(int unused1, int actor, char* ctx, int unused4, char* out)
{
	Stat st;

	if (gm_GetLawEntry(*(int*) (ctx + 4), &st) && st.check(actor, st.v[0] & 0xff, (int*) &ctx)) {
		if ((int) ctx != st.v[6] && (int) ctx >= st.v[1] && (int) ctx <= st.v[2]) {
			out[0] = 0x11;
			*(int*) (out + 4) = st.v[0] & 0xff;
			*(int*) (out + 8) = (int) ctx;
			return 1;
		}
	}
	return 0;
}
