#include <string.h>
#include "Develop/DieGildeAddOn/game/building_prototype.h"
typedef struct Rec18 {
	char pad0[8];
	unsigned char x8;
	char pad9[0xf];
} Rec18;

typedef struct Msg {
	unsigned char type;
	char pad1[3];
	unsigned int object;
	char pad8[8];
	unsigned int param;
	char pad14[4];
} Msg;

typedef struct Bld24d {
	char pad0[0x247];
	unsigned char x247;
	char pad248[5];
} Bld24d;

extern unsigned char* lpGebaeudePROT;

int __cdecl gm_AccumulateTyped2(void*);
void* __cdecl gm_StartFilteredEntitySearch(int, ...);
void* __cdecl gm_FindNextFilteredEntity(void);
void* __cdecl gm_QueryEntities(int, ...);
unsigned short __cdecl gm_RandomMod(unsigned short);
double __cdecl gm_RandomFloat01(void);
int __cdecl amt_GetRoleTemplate(int, Rec18*);
int __cdecl gm_GetStraftatEvidenceOffer(unsigned int, void*, void*, void*, void*);

/* ADDRESS: GOLDTL 0x004ab1a0 */
unsigned int __cdecl ai_FindDunkleEckeStraftat(int* subject, Msg* firstMessage, Msg* secondMessage)
{
	Rec18 rec;
	int found[16];
	int* pair;
	int total;
	int val;
	int n;
	int i;
	int k;
	int tries;
	int g;
	unsigned int out2;
	unsigned int out1;
	unsigned char* ent;
	unsigned char* obj;

	if ((*(unsigned int*) ((char*) subject + 0x1cc) & 0x2000000) == 0) {
		g = *(unsigned int*) 0x7f4c04;
		if ((unsigned short) g >= 0x15 &&
		    (g & 0xffff) % 3 == *(unsigned int*) ((char*) subject + 4) % 3) {
			total = gm_AccumulateTyped2(subject);
			for (k = 0; k < 16; k++) {
				found[k] = 0;
			}
			n = 0;
			ent = (unsigned char*) gm_StartFilteredEntitySearch(1, 5, 0x16);
			if (ent != 0) {
				do {
					if (*(unsigned short*) (ent + 0x27) != 0xffff &&
					    *(unsigned short*) (ent + 0x27) != *(unsigned short*) subject &&
					    ((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*ent].level > 1 &&
					    (obj = (unsigned char*) gm_QueryEntities(*(unsigned int*) (ent + 0x5d), 1, 0, 0x120)) != 0 &&
					    (obj = (unsigned char*) gm_QueryEntities(*(unsigned int*) (obj + 0x14), 1, 0, 300)) != 0) {
						found[n * 2] = (int) ent;
						found[n * 2 + 1] = (int) obj;
						n++;
					}
					ent = (unsigned char*) gm_FindNextFilteredEntity();
				} while (ent != 0);
				if (n != 0) {
					k = gm_RandomMod(n) & 0xffff;
					pair = &found[k * 2];
					i = (unsigned short) gm_RandomMod(3);
					ent = (unsigned char*) pair[0];
					obj = (unsigned char*) pair[1];
					tries = 3;
					do {
						if (gm_GetStraftatEvidenceOffer(*(unsigned int*) (obj + 0x1c + i * 4),
								 (void*) ((unsigned int) *(unsigned short*) (ent + 0x27) * 0x21c + 0x7f4ca0),
								 &val, &out2, &out1) != 0 &&
						    !((float) total * *(float*) 0x662b10 < (float) val)) {
							amt_GetRoleTemplate(*(unsigned char*) ((out2 & 0xffff) * 0x21c + 0x7f4e06), &rec);
							if ((unsigned short) gm_RandomMod(0xc) > (unsigned short) rec.x8) {
								return 0;
							}
							if ((float) gm_RandomFloat01() < *(float*) 0x6628cc) {
								memset(firstMessage, 0, 0x18);
								memset(secondMessage, 0, 0x18);
							} else {
								firstMessage->type = 0x13;
								firstMessage->object = *(unsigned int*) (obj + 0x1c + i * 4);
								firstMessage->param = (unsigned int) val;
								secondMessage->type = 4;
								secondMessage->object = *(unsigned int*) (ent + 1);
							}
							return 1;
						}
						tries--;
						i = (i + 1) % 3;
					} while (tries != 0);
				}
			}
		}
	}
	return 0;
}
