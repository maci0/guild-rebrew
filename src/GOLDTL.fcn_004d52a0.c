/* Sums the price of the entities resolved from a building's three linked
 * entries and books the result on the player's record. */

extern char* g_772e98;
extern char* g_772e9c;
extern unsigned char g_773d75;
extern double g_662908;
extern float g_6628a0;

char* __cdecl fcn_00502cd0(int, ...);
short* __cdecl gm_ResolveParentEntity(short*);
void* __cdecl gm_NextEntityQueryMatch(void);
short* __cdecl gm_GetEntityTableEntry(char*);
float __cdecl fcn_0050bb50(int, unsigned char);
void __cdecl fcn_004c51f0(int, int, int, int, unsigned char, int);
void __cdecl fcn_004c5150(int, int, char, int);

/* ADDRESS: GOLDTL 0x004d52a0 */
int __cdecl fcn_004d52a0(int* a0, char* a1, int* a2, int a3, float a4)
{
	int total;
	int i;
	int q;
	float v;
	char* rec;
	char* ent;
	int* p;

	total = 0;
	if (g_772e9c == 0 || g_772e98 == 0) {
		return 0;
	}
	rec = fcn_00502cd0(*(int*) (a1 + 0x5d), 2, 6, 0, 0x116);
	p = (int*) ((char*) a0 + 0x100);
	for (i = 3; i != 0; i--) {
		if (*p != -1) {
			ent = fcn_00502cd0(0, 2, 7, 1, *p);
			ent = fcn_00502cd0(*(int*) (ent + 0x14), 1, 0, 0x1dd);
			ent = fcn_00502cd0(*(int*) (ent + 0x14), 1, 5);
			while (ent != 0) {
				gm_ResolveParentEntity((short*) ent);
				v = (float) *(int*) (ent + 0xe) * a4;
				if (1.0f > v) {
					v = 1.0f;
				}
				q = (int) v;
				if (rec != 0) {
					fcn_004c51f0(*(int*) (rec + 2), *(int*) (ent + 6),
					    *(unsigned short*) ent, q, g_773d75, 0);
				} else {
					fcn_004c51f0(-1, *(int*) (ent + 6),
					    *(unsigned short*) ent, q, g_773d75, 0);
				}
				total = (int) (fcn_0050bb50(*(unsigned short*) ent, g_773d75)
				    * (float) q + (float) total);
				ent = gm_NextEntityQueryMatch();
			}
			if (rec == 0) {
				total = (int) ((double) total * g_662908);
				fcn_004c5150(a2[1], -1, g_773d75, total);
			}
			ent = gm_GetEntityTableEntry(g_772e9c);
			if (ent != 0) {
				*(int*) (ent + 0x1c) += total;
			}
		}
		p++;
	}
	return total;
}
