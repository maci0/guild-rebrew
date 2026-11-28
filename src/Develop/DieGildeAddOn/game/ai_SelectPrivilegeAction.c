#include <string.h>

typedef struct {
	char text[0x21c];
	int found;
} sel_ctx;

unsigned short __cdecl gm_RandomMod(int);
char* __cdecl he_StartHandlungSearch(int, int, int);
char* __cdecl he_fn_Handlung(void);
int __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_CheckPrivilege(int, char*, int);
int __cdecl ai_CheckAction012Predicate(char*, char*, int, char*, int);
int __cdecl ai_CheckLawActionPredicate(char*, char*, int, char*, int);
int __cdecl ai_CheckAction01cPredicate(char*, char*, int, char*, int);
int __cdecl ai_CheckAction01dPredicate(char*, char*, int, char*, int);
int __cdecl ai_CheckUseTrankPredicate(char*, char*, int, char*, int);
int __cdecl ai_CheckAction025Predicate(char*, char*, int, char*, int);
int __cdecl ai_CheckAction027Predicate(char*, char*, int, char*, int);
int __cdecl ai_CheckAction028Predicate(char*, char*, int, char*, int);
int __cdecl ai_CheckAction029Predicate(char*, char*, int, char*, int);
int __cdecl ai_CheckAction02aPredicate(char*, char*, int, char*, int);
int __cdecl ai_CheckAction02bPredicate(char*, char*, int, char*, int);
int __cdecl ai_CheckAction02cPredicate(char*, char*, int, char*, int);
int __cdecl ai_CheckAction02dPredicate(char*, char*, int, char*, int);
int __cdecl ai_CheckAction031Predicate(char*, char*, int, char*, int);
int __cdecl ai_CheckDunkleEckePredicate(char*, char*, int, char*, int);
int __cdecl ai_CheckAction035Predicate(char*, char*, int, char*, int);
int __cdecl ai_SelectAction037Target(char*, char*, int, char*, int);

int __cdecl fcn_004a8d30(char*, char*, int, char*, int);

/* ADDRESS: GOLDTL 0x004a9b20 */
/* ADDRESS: GOLDDE 0x00497e60 */
int __cdecl ai_SelectPrivilegeAction(char* unused0, char* actorEntity, int unused2, char* ctx, int unused4)
{
	sel_ctx c;
	int ids1[19];
	int ids2[19];
	int* p;
	int n1;
	int n2 = 0;
	int id;
	int sel;
	char* e;
	int r;

	memset(&c, 0, sizeof(c));
	c.found = 0;
	if (*(int*) (actorEntity + 0x1c8) & 0x100) {
		e = he_StartHandlungSearch(1, 0, 0x45);
		while (e != 0) {
			if (*(int*) (e + 0xac) == *(int*) (actorEntity + 4)) {
				c.found = gm_LookupEntityRecordById(*(int*) (e + 0xb0));
				break;
			}
			e = he_fn_Handlung();
		}
	}
	if (*ctx == 0) {
		*(int*) c.text = 1;
		n1 = 0;
		for (p = (int*) 0x67fa58; (int) p < (int) 0x67faa4; p++) {
			if (gm_CheckPrivilege(*p, actorEntity, (int) &c) & 2) {
				ids1[n1] = *p;
				n1++;
			}
		}
		if (c.found != 0) {
			*(int*) c.text = 2;
			n2 = 0;
			for (p = (int*) 0x67fa58; (int) p < (int) 0x67faa4; p++) {
				if (gm_CheckPrivilege(*p, actorEntity, (int) &c) & 2) {
					ids2[n2] = *p;
					n2++;
				}
			}
		}
		if (n1 != 0) {
			r = 0;
			if (n2 != 0) {
				r = gm_RandomMod(2);
			}
		} else {
			if (n2 == 0) {
				return 0;
			}
			r = 1;
		}
		if (r == 0) {
			*(int*) c.text = 1;
			id = ids1[gm_RandomMod(n1)];
			sel = 3;
			if (!(gm_CheckPrivilege(id, actorEntity, (int) &c) & 2)) {
				return 0;
			}
		} else {
			*(int*) c.text = 2;
			id = ids2[gm_RandomMod(n2)];
			sel = 4;
			if (!(gm_CheckPrivilege(id, actorEntity, (int) &c) & 2)) {
				return 0;
			}
		}
		*ctx = 0x10;
		*(int*) (ctx + 4) = id;
		*(int*) (ctx + 8) = sel;
	} else if (*ctx == 0x10) {
		id = *(int*) (ctx + 4);
		*(int*) c.text = 1;
		if (gm_CheckPrivilege(id, actorEntity, (int) &c) & 2) {
			*(int*) (ctx + 8) = 3;
		} else {
			*(int*) c.text = 2;
			if (!(gm_CheckPrivilege(id, actorEntity, (int) &c) & 2)) {
				return 0;
			}
			*(int*) (ctx + 8) = 4;
		}
	} else {
		return 0;
	}
	r = 0;
	switch (id) {
	case 0x12:
		r = ai_CheckAction012Predicate(unused0, actorEntity, (int) &c, ctx, unused4);
		break;
	case 0x13:
	case 0x14:
		r = ai_CheckLawActionPredicate(unused0, actorEntity, (int) &c, ctx, unused4);
		break;
	case 0x1c:
		r = ai_CheckAction01cPredicate(unused0, actorEntity, (int) &c, ctx, unused4);
		break;
	case 0x1d:
		r = ai_CheckAction01dPredicate(unused0, actorEntity, (int) &c, ctx, unused4);
		break;
	case 0x21:
		r = fcn_004a8d30(unused0, actorEntity, (int) &c, ctx, unused4);
		break;
	case 0x24:
		r = ai_CheckUseTrankPredicate(unused0, actorEntity, (int) &c, ctx, unused4);
		break;
	case 0x25:
		r = ai_CheckAction025Predicate(unused0, actorEntity, (int) &c, ctx, unused4);
		break;
	case 0x27:
		r = ai_CheckAction027Predicate(unused0, actorEntity, (int) &c, ctx, unused4);
		break;
	case 0x28:
		r = ai_CheckAction028Predicate(unused0, actorEntity, (int) &c, ctx, unused4);
		break;
	case 0x29:
		r = ai_CheckAction029Predicate(unused0, actorEntity, (int) &c, ctx, unused4);
		break;
	case 0x2a:
		r = ai_CheckAction02aPredicate(unused0, actorEntity, (int) &c, ctx, unused4);
		break;
	case 0x2b:
		r = ai_CheckAction02bPredicate(unused0, actorEntity, (int) &c, ctx, unused4);
		break;
	case 0x2c:
		r = ai_CheckAction02cPredicate(unused0, actorEntity, (int) &c, ctx, unused4);
		break;
	case 0x2d:
		r = ai_CheckAction02dPredicate(unused0, actorEntity, (int) &c, ctx, unused4);
		break;
	case 0x31:
		r = ai_CheckAction031Predicate(unused0, actorEntity, (int) &c, ctx, unused4);
		break;
	case 0x32:
		r = ai_CheckDunkleEckePredicate(unused0, actorEntity, (int) &c, ctx, unused4);
		break;
	case 0x35:
		r = ai_CheckAction035Predicate(unused0, actorEntity, (int) &c, ctx, unused4);
		break;
	case 0x37:
		r = ai_SelectAction037Target(unused0, actorEntity, (int) &c, ctx, unused4);
		break;
	}
	return r;
}
