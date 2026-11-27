typedef struct Cmd {
	char kind;
	int f1;
	int f2;
	int f3;
	int f4;
	int f5;
} Cmd;

extern unsigned char* g_entity_ptr;
extern unsigned char* lpGebaeudePROT;
extern unsigned char g_773d75;
extern int g_666028;
extern int g_66602c;

extern float g_6628bc;


/* SIZE 0x24d: building prototype row of lpGebaeudePROT (0x868050) */
typedef struct {
	unsigned char type;
	char rest[0x24c];
} BLD_PROT_TYPE_VIEW;

int __cdecl he_StartHandlungSearch(int, int, int, int, int);
int __cdecl gm_GetSeasonTreasury(short*, unsigned char);
int __cdecl gm_CalcBuildingCost(short*, int);
int __cdecl gm_GetTypeProductValue(int);
int __cdecl ai_PrepareBuildSite(int, short*, int, Cmd*, Cmd*, int);
int __cdecl ai_StartKreditNehmen(int, short*, int, Cmd*, Cmd*);

/* ADDRESS: GOLDTL 0x00497ec0 */
int __cdecl ai_StartWohnsitzBauen(int a0, short* entity, int a2, Cmd* request, Cmd* a4)
{
	int n;
	int chain[4] = {7, 6, 5, 4};
	Cmd cmd;
	Cmd out;
	int p;
	unsigned char* q;
	unsigned char* rec;
	unsigned char id;
	unsigned char t;
	int j;
	unsigned int lo;
	unsigned int hi;

	if (*(char*) ((char*) entity + 2) == 3)
		return 0;
	if (a2 == 0) {
		if (*(char*) request != 0)
			return 0;
	} else {
		if (a2 == 1) {
			if (*(char*) request != 5 && *(char*) request != 4)
				return 0;
		}
	}
	if (he_StartHandlungSearch(2, 0, 0xd, 2, *(unsigned short*) entity) != 0)
		return 0;
	p = (int) g_entity_ptr;
	n = 0;
	do {
		if (*(unsigned char*) p != 0) {
			id = *(unsigned char*) p;
			rec = (unsigned char*) &((BLD_PROT_TYPE_VIEW*) lpGebaeudePROT)[id];
			lo = 0;
			hi = 0;
			if (rec[0] > 0x1f) {
				hi = 1U << ((rec[0] - 0x20) & 31);
			} else {
				lo = 1U << rec[0];
			}
			if (*(unsigned short*) (p + 0x27) == *(unsigned short*) entity
				&& ((g_666028 & lo) || (g_66602c & hi))) {
				int need;
				int rem;
				int v;

				/* scan address and money value share one stack slot in the
				 * native body; every hit path returns before the scan resumes */
				p = gm_GetSeasonTreasury(entity, g_773d75);
				p = (int) ((float) p * 0.66f);
				out.kind = 0;
				out.f1 = 0;
				out.f2 = 0;
				if (*(char*) request == 0) {
					q = *(unsigned char**) ((char*) entity + 0x170);
					if (q != 0) {
						id = *q;
						rec = (unsigned char*) &((BLD_PROT_TYPE_VIEW*) lpGebaeudePROT)[id];
						if (rec[0] == 2 && !(q[0x5a] & 0x41)) {
							t = rec[0x247];
							if (t < 2 || t == 3) {
								int bid;

								cmd.kind = 5;
								bid = *q;
								j = 0;
								if (bid != 7) {
									do {
										j += 1;
									} while (chain[j] != bid);
								}
								cmd.f1 = chain[j - 1];
								cmd.f2 = 1;
								out.kind = 4;
								out.f1 = *(int*) (q + 1);
								out.f2 = 1;
								if (!ai_PrepareBuildSite(a0, entity, a2, &cmd, &out, 0))
									return 0;
								need = gm_CalcBuildingCost(entity, cmd.f1);
								if (p < need) {
									rem = need - p;
									if ((float) rem / (float) need < 0.25f) {
										request->kind = 0x12;
										request->f2 = rem;
										return ai_StartKreditNehmen(0x11, entity, a2, request, a4);
									}
									return 0;
								}
								*a4 = out;
								*request = cmd;
								return 0x11;
							}
							if (t == 5)
								return 0;
						}
					}
					cmd.kind = 5;
					cmd.f1 = 6;
					cmd.f2 = 1;
					if (ai_PrepareBuildSite(a0, entity, a2, &cmd, &out, 1)) {
						need = gm_CalcBuildingCost(entity, cmd.f1);
						if (p < need) {
							rem = need - p;
							if ((float) rem / (float) need < 0.25f) {
								request->kind = 0x12;
								request->f2 = rem;
								return ai_StartKreditNehmen(0x11, entity, a2, request, a4);
							}
						} else {
							*request = cmd;
							*a4 = out;
							return 0x11;
						}
					}
					cmd.kind = 5;
					cmd.f1 = 4;
					cmd.f2 = 1;
					if (!ai_PrepareBuildSite(a0, entity, a2, &cmd, &out, 1))
						return 0;
					a0 = gm_CalcBuildingCost(entity, cmd.f1);
					if (p < a0) {
						rem = a0 - p;
						if ((float) rem / (float) a0 < 0.25f) {
							request->kind = 0x12;
							request->f2 = rem;
							return ai_StartKreditNehmen(0x11, entity, a2, request, a4);
						}
						return 0;
					}
					*request = cmd;
					*a4 = out;
					return 0x11;
				}
				if (*(char*) request != 5)
					return 0;
				cmd = *request;
				q = *(unsigned char**) ((char*) entity + 0x170);
				if (q != 0) {
					id = *q;
					if (((BLD_PROT_TYPE_VIEW*) lpGebaeudePROT)[id].type != 2)
						return 0;
					v = *(int*) ((char*) request + 4);
					if (v - id != 1)
						return 0;
					if (id == 5 || id == 7)
						return 0;
					cmd.f2 = 1;
					cmd.f1 = v;
					out.kind = 4;
					out.f1 = *(int*) (q + 1);
					out.f2 = 1;
					need = (int) ((float) gm_GetTypeProductValue(v) * 0.3f);
					if (!ai_PrepareBuildSite(a0, entity, a2, &cmd, &out, 0))
						return 0;
					if (p < need) {
						rem = need - p;
						if ((float) rem / (float) need < 0.25f) {
							request->kind = 0x12;
							request->f2 = rem;
							return ai_StartKreditNehmen(0x11, entity, a2, request, a4);
						}
						return 0;
					}
					*request = cmd;
					*a4 = out;
					return 0x11;
				}
				if (((BLD_PROT_TYPE_VIEW*) lpGebaeudePROT)[request->f1].type != 2)
					return 0;
				if (!ai_PrepareBuildSite(a0, entity, a2, &cmd, &out, 1))
					return 0;
				if (*(char*) ((char*) entity + 2) != 5)
					return 0;
				need = gm_CalcBuildingCost(entity, cmd.f1);
				if (p < need) {
					rem = need - p;
					if ((float) rem / (float) need < 0.25f) {
						request->kind = 0x12;
						request->f2 = rem;
						return ai_StartKreditNehmen(0x11, entity, a2, request, a4);
					}
					return 0;
				}
				*request = cmd;
				*a4 = out;
				return 0x11;
			}
		}
		n += 1;
		p += 0xa9;
	} while (n < 0x100);
	return 0;
}
