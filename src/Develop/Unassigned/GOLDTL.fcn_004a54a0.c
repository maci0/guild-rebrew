


#include <string.h>
#include "Develop/DieGildeAddOn/game/entity_candidate.h"

typedef struct Query {
	int x0;
	int flags;
	char pad8[0x14 - 8];
	int kind;
	char pad18[0x1c - 0x18];
	char name[0x20];
	char pad3c[0x40 - 0x3c];
	int x40;
	char pad44[0x50 - 0x44];
} Query;
// SIZE 0x50


extern char* g_77261c;
extern unsigned int g_7728bc;

int __cdecl fcn_005cf720(unsigned short a, unsigned short b, Query* q, int c);
ENTITY_CANDIDATE* __cdecl fcn_004a34d0(void);

int __cdecl fcn_004a54a0(unsigned short* e, int queryFlags, unsigned int n, char* src, float lo, float hi, unsigned short* out)
{
	Query q;
	unsigned int len;
	int i;
	ENTITY_CANDIDATE* t;

	memset(&q, 0, sizeof(q));
	len = n * 2;
	if (len > 0x20) {
		len = 0x20;
	}
	memcpy(q.name, src, len);
	q.kind = 2;
	if (((unsigned short*)g_77261c) != 0 && !(q.flags & 0x10000000)) {
		q.x40 = 0;
		q.flags = queryFlags;
		if (fcn_005cf720(*e, *((unsigned short*)g_77261c), &q, 0) != 0) {
			*out = *((unsigned short*)g_77261c);
			return 1;
		}
	}
	q.x40 = 0;
	for (i = (*(int*)&g_7728bc); t = fcn_004a34d0(), i != 0 && t->entity != 0; i--) {
		if (!(t->score < lo) && !(t->score > hi) && fcn_005cf720(*e, *(unsigned short*)t->entity, &q, 0) != 0) {
			*out = *(unsigned short*)t->entity;
			return 1;
		}
	}
	return 0;
}
